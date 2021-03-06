/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by original author
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

\*---------------------------------------------------------------------------*/

#include "metisDecomp.H"
#include "addToRunTimeSelectionTable.H"
#include "floatScalar.H"
#include "IFstream.H"
#include "Time.H"
#include "cyclicPolyPatch.H"

extern "C"
{
#define OMPI_SKIP_MPICXX
#   include "metis.h"
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(metisDecomp, 0);

    addToRunTimeSelectionTable
    (
        decompositionMethod,
        metisDecomp,
        dictionaryMesh
    );
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// Call Metis with options from dictionary.
Foam::label Foam::metisDecomp::decompose
(
    const List<int>& adjncy,
    const List<int>& xadj,

    List<int>& finalDecomp
)
{
    // C style numbering
    int numFlag = 0;

    // Method of decomposition
    // recursive: multi-level recursive bisection (default)
    // k-way: multi-level k-way 
    word method("k-way");

    // decomposition options. 0 = use defaults
    List<int> options(5, 0);

    // processor weights initialised with no size, only used if specified in
    // a file
    Field<floatScalar> processorWeights;

    // cell weights (so on the vertices of the dual)
    List<int> cellWeights;

    // face weights (so on the edges of the dual)
    List<int> faceWeights;

    // Check for user supplied weights and decomp options
    if (decompositionDict_.found("metisCoeffs"))
    {
        dictionary metisDecompCoeffs
        (
            decompositionDict_.subDict("metisCoeffs")
        );

        if (metisDecompCoeffs.found("method"))
        {
            metisDecompCoeffs.lookup("method") >> method;

            if (method != "recursive" && method != "k-way")
            {
                FatalErrorIn("metisDecomp::decompose()")
                    << "Method " << method << " in metisCoeffs in dictionary : "
                    << decompositionDict_.name()
                    << " should be 'recursive' or 'k-way'"
                    << exit(FatalError);
            }

            Info<< "metisDecomp : Using Metis options     " << options
                << endl << endl;
        }

        if (metisDecompCoeffs.found("options"))
        {
            metisDecompCoeffs.lookup("options") >> options;

            if (options.size() != 5)
            {
                FatalErrorIn("metisDecomp::decompose()")
                    << "Number of options in metisCoeffs in dictionary : "
                    << decompositionDict_.name()
                    << " should be 5"
                    << exit(FatalError);
            }

            Info<< "metisDecomp : Using Metis options     " << options
                << endl << endl;
        }

        if (metisDecompCoeffs.found("processorWeights"))
        {
            metisDecompCoeffs.lookup("processorWeights") >> processorWeights;
            processorWeights /= sum(processorWeights);

            if (processorWeights.size() != nProcessors_)
            {
                FatalErrorIn("metisDecomp::decompose(const pointField&)")
                    << "Number of processor weights "
                    << processorWeights.size()
                    << " does not equal number of domains " << nProcessors_
                    << exit(FatalError);
            }
        }

        if (metisDecompCoeffs.found("cellWeightsFile"))
        {
            Info<< "metisDecomp : Using cell-based weights." << endl;

            word cellWeightsFile
            (
                metisDecompCoeffs.lookup("cellWeightsFile")
            );

            IOList<int> cellIOWeights
            (
                IOobject
                (
                    cellWeightsFile,
                    mesh_.time().timeName(),
                    mesh_,
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
                )
            );
            cellWeights.transfer(cellIOWeights);

            if (cellWeights.size() != xadj.size()-1)
            {
                FatalErrorIn("metisDecomp::decompose(const pointField&)")
                    << "Number of cell weights " << cellWeights.size()
                    << " does not equal number of cells " << xadj.size()-1
                    << exit(FatalError);
            }
        }

        //- faceWeights disabled. Only makes sense for cellCells from mesh.
        //if (metisDecompCoeffs.found("faceWeightsFile"))
        //{
        //    Info<< "metisDecomp : Using face-based weights." << endl;
        //
        //    word faceWeightsFile
        //    (
        //        metisDecompCoeffs.lookup("faceWeightsFile")
        //    );
        //
        //    IOList<int> weights
        //    (
        //        IOobject
        //        (
        //            faceWeightsFile,
        //            mesh_.time().timeName(),
        //            mesh_,
        //            IOobject::MUST_READ,
        //            IOobject::AUTO_WRITE
        //        )
        //    );
        //
        //    if (weights.size() != adjncy.size()/2)
        //    {
        //        FatalErrorIn("metisDecomp::decompose(const pointField&)")
        //            << "Number of face weights " << weights.size()
        //            << " does not equal number of internal faces "
        //            << adjncy.size()/2
        //            << exit(FatalError);
        //    }
        //
        //    // Assume symmetric weights. Keep same ordering as adjncy.
        //    faceWeights.setSize(adjncy.size());
        //
        //    labelList nFacesPerCell(mesh_.nCells(), 0);
        //
        //    for (label faceI = 0; faceI < mesh_.nInternalFaces(); faceI++)
        //    {
        //        label w = weights[faceI];
        //
        //        label own = mesh_.faceOwner()[faceI];
        //        label nei = mesh_.faceNeighbour()[faceI];
        //
        //        faceWeights[xadj[own] + nFacesPerCell[own]++] = w;
        //        faceWeights[xadj[nei] + nFacesPerCell[nei]++] = w;
        //    }
        //}
    }

    int numCells = xadj.size()-1;
    int nProcs = nProcessors_;

    // output: cell -> processor addressing
    finalDecomp.setSize(numCells);

    // output: number of cut edges
    int edgeCut = 0;

    // Vertex weight info
    int wgtFlag = 0;
    int* vwgtPtr = NULL;
    int* adjwgtPtr = NULL;

    if (cellWeights.size() > 0)
    {
        vwgtPtr = cellWeights.begin();
        wgtFlag += 2;       // Weights on vertices
    }
    if (faceWeights.size() > 0)
    {
        adjwgtPtr = faceWeights.begin();
        wgtFlag += 1;       // Weights on edges
    }

    if (method == "recursive")
    {
        if (processorWeights.size())
        {
            METIS_WPartGraphRecursive
            (
                &numCells,         // num vertices in graph
                const_cast<List<int>&>(xadj).begin(),   // indexing into adjncy
                const_cast<List<int>&>(adjncy).begin(), // neighbour info
                vwgtPtr,           // vertexweights
                adjwgtPtr,         // no edgeweights
                &wgtFlag,
                &numFlag,
                &nProcs,
                processorWeights.begin(),
                options.begin(),
                &edgeCut,
                finalDecomp.begin()
            );
        }
        else
        {
            METIS_PartGraphRecursive
            (
                &numCells,         // num vertices in graph
                const_cast<List<int>&>(xadj).begin(),   // indexing into adjncy
                const_cast<List<int>&>(adjncy).begin(), // neighbour info
                vwgtPtr,           // vertexweights
                adjwgtPtr,         // no edgeweights
                &wgtFlag,
                &numFlag,
                &nProcs,
                options.begin(),
                &edgeCut,
                finalDecomp.begin()
            );
        }
    }
    else
    {
        if (processorWeights.size())
        {
            METIS_WPartGraphKway
            (
                &numCells,         // num vertices in graph
                const_cast<List<int>&>(xadj).begin(),   // indexing into adjncy
                const_cast<List<int>&>(adjncy).begin(), // neighbour info
                vwgtPtr,           // vertexweights
                adjwgtPtr,         // no edgeweights
                &wgtFlag,
                &numFlag,
                &nProcs,
                processorWeights.begin(),
                options.begin(),
                &edgeCut,
                finalDecomp.begin()
            );
        }
        else
        {
            METIS_PartGraphKway
            (
                &numCells,         // num vertices in graph
                const_cast<List<int>&>(xadj).begin(),   // indexing into adjncy
                const_cast<List<int>&>(adjncy).begin(), // neighbour info
                vwgtPtr,           // vertexweights
                adjwgtPtr,         // no edgeweights
                &wgtFlag,
                &numFlag,
                &nProcs,
                options.begin(),
                &edgeCut,
                finalDecomp.begin()
            );
        }
    }

    return edgeCut;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::metisDecomp::metisDecomp
(
    const dictionary& decompositionDict,
    const polyMesh& mesh
)
:
    decompositionMethod(decompositionDict),
    mesh_(mesh)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

Foam::labelList Foam::metisDecomp::decompose(const pointField& points)
{
    if (points.size() != mesh_.nCells())
    {
        FatalErrorIn("metisDecomp::decompose(const pointField&)")
            << "Can use this decomposition method only for the whole mesh"
            << endl
            << "and supply one coordinate (cellCentre) for every cell." << endl
            << "The number of coordinates " << points.size() << endl
            << "The number of cells in the mesh " << mesh_.nCells()
            << exit(FatalError);
    }

    // Make Metis CSR (Compressed Storage Format) storage
    //   adjncy      : contains neighbours (= edges in graph)
    //   xadj(celli) : start of information in adjncy for celli

    List<int> xadj(mesh_.nCells()+1);

    // Initialise the number of internal faces of the cells to twice the
    // number of internal faces
    label nInternalFaces = 2*mesh_.nInternalFaces();

    // Check the boundary for coupled patches and add to the number of 
    // internal faces
    const polyBoundaryMesh& pbm = mesh_.boundaryMesh();

    forAll(pbm, patchi)
    {
        if (isA<cyclicPolyPatch>(pbm[patchi]))
        {
            nInternalFaces += pbm[patchi].size();
        }
    }

    // Create the adjncy array the size of the total number of internal and
    // coupled faces
    List<int> adjncy(nInternalFaces);

    // Fill in xadj
    // ~~~~~~~~~~~~
    label freeAdj = 0;

    for (label cellI = 0; cellI < mesh_.nCells(); cellI++)
    {
        xadj[cellI] = freeAdj;

        const labelList& cFaces = mesh_.cells()[cellI];

        forAll(cFaces, i)
        {
            label faceI = cFaces[i];

            if
            (
                mesh_.isInternalFace(faceI)
             || isA<cyclicPolyPatch>(pbm[pbm.whichPatch(faceI)])
            )
            {
                freeAdj++;
            }
        }
    }
    xadj[mesh_.nCells()] = freeAdj;


    // Fill in adjncy
    // ~~~~~~~~~~~~~~

    labelList nFacesPerCell(mesh_.nCells(), 0);

    // Internal faces
    for (label faceI = 0; faceI < mesh_.nInternalFaces(); faceI++)
    {
        label own = mesh_.faceOwner()[faceI];
        label nei = mesh_.faceNeighbour()[faceI];

        adjncy[xadj[own] + nFacesPerCell[own]++] = nei;
        adjncy[xadj[nei] + nFacesPerCell[nei]++] = own;
    }

    // Coupled faces. Only cyclics done.
    forAll(pbm, patchi)
    {
        if (isA<cyclicPolyPatch>(pbm[patchi]))
        {
            const unallocLabelList& faceCells = pbm[patchi].faceCells();

            label sizeby2 = faceCells.size()/2;

            for (label facei=0; facei<sizeby2; facei++)
            {
                label own = faceCells[facei];
                label nei = faceCells[facei + sizeby2];

                adjncy[xadj[own] + nFacesPerCell[own]++] = nei;
                adjncy[xadj[nei] + nFacesPerCell[nei]++] = own;
            }
        }
    }

    // Decompose using default weights
    List<int> finalDecomp;
    decompose(adjncy, xadj, finalDecomp);

    // Copy back to labelList
    labelList decomp(finalDecomp.size());
    forAll(decomp, i)
    {
        decomp[i] = finalDecomp[i];
    }
    return decomp;
}


// From cell-cell connections to Metis format (like CompactListList)
void Foam::metisDecomp::calcMetisCSR
(
    const labelListList& cellCells,
    List<int>& adjncy,
    List<int>& xadj
)
{
    // Count number of internal faces
    label nConnections = 0;

    forAll(cellCells, coarseI)
    {
        nConnections += cellCells[coarseI].size();
    }

    // Create the adjncy array as twice the size of the total number of
    // internal faces
    adjncy.setSize(nConnections);

    xadj.setSize(cellCells.size()+1);


    // Fill in xadj
    // ~~~~~~~~~~~~
    label freeAdj = 0;

    forAll(cellCells, coarseI)
    {
        xadj[coarseI] = freeAdj;

        const labelList& cCells = cellCells[coarseI];

        forAll(cCells, i)
        {
            adjncy[freeAdj++] = cCells[i];
        }
    }
    xadj[cellCells.size()] = freeAdj;
}


Foam::labelList Foam::metisDecomp::decompose
(
    const labelList& agglom,
    const pointField& agglomPoints
)
{
    if (agglom.size() != mesh_.nCells())
    {
        FatalErrorIn
        (
            "parMetisDecomp::decompose(const labelList&, const pointField&)"
        )   << "Size of cell-to-coarse map " << agglom.size()
            << " differs from number of cells in mesh " << mesh_.nCells()
            << exit(FatalError);
    }

    // Make Metis CSR (Compressed Storage Format) storage
    //   adjncy      : contains neighbours (= edges in graph)
    //   xadj(celli) : start of information in adjncy for celli
    List<int> adjncy;
    List<int> xadj;
    {
        // Get cellCells on coarse mesh.
        labelListList cellCells;
        calcCellCells
        (
            mesh_,
            agglom,
            agglomPoints.size(),
            cellCells
        );

        calcMetisCSR(cellCells, adjncy, xadj);
    }

    // Decompose using default weights
    List<int> finalDecomp;
    decompose(adjncy, xadj, finalDecomp);


    // Rework back into decomposition for original mesh_
    labelList fineDistribution(agglom.size());

    forAll(fineDistribution, i)
    {
        fineDistribution[i] = finalDecomp[agglom[i]];
    }

    return fineDistribution;
}


Foam::labelList Foam::metisDecomp::decompose
(
    const labelListList& globalCellCells,
    const pointField& cellCentres
)
{
    if (cellCentres.size() != globalCellCells.size())
    {
        FatalErrorIn
        (
            "metisDecomp::decompose(const pointField&, const labelListList&)"
        )   << "Inconsistent number of cells (" << globalCellCells.size()
            << ") and number of cell centres (" << cellCentres.size()
            << ")." << exit(FatalError);
    }


    // Make Metis CSR (Compressed Storage Format) storage
    //   adjncy      : contains neighbours (= edges in graph)
    //   xadj(celli) : start of information in adjncy for celli

    List<int> adjncy;
    List<int> xadj;
    calcMetisCSR(globalCellCells, adjncy, xadj);


    // Decompose using default weights
    List<int> finalDecomp;
    decompose(adjncy, xadj, finalDecomp);

    // Copy back to labelList
    labelList decomp(finalDecomp.size());
    forAll(decomp, i)
    {
        decomp[i] = finalDecomp[i];
    }
    return decomp;
}


// ************************************************************************* //
