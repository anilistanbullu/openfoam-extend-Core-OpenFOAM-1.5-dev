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

#include "mag.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    namespace calcTypes
    {
        defineTypeNameAndDebug(mag, 0);
        addToRunTimeSelectionTable(calcType, mag, dictionary);
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::calcTypes::mag::mag()
:
    calcType()
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::calcTypes::mag::~mag()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::calcTypes::mag::init()
{
    Foam::argList::validArgs.append("mag");
    argList::validArgs.append("fieldName1 .. fieldNameN");
}


void Foam::calcTypes::mag::preCalc
(
    const argList& args,
    const Time& runTime,
    const fvMesh& mesh
)
{
    if (args.additionalArgs().size() < 2)
    {
        Info<< nl << "must specify one or more fields" << nl;
        args.printUsage();
        FatalError.exit();
    }
}


void Foam::calcTypes::mag::calc
(
    const argList& args,
    const Time& runTime,
    const fvMesh& mesh
)
{
    const stringList& params = args.additionalArgs();

    for (label fieldi=1; fieldi<params.size(); fieldi++)
    {
        const word fieldName(params[fieldi]);

        IOobject fieldHeader
        (
            fieldName,
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ
        );

        // Check field exists
        if (fieldHeader.headerOk())
        {
            bool processed = false;

            writeMagField<scalar>(fieldHeader, mesh, processed);
            writeMagField<vector>(fieldHeader, mesh, processed);
            writeMagField<sphericalTensor>(fieldHeader, mesh, processed);
            writeMagField<symmTensor>(fieldHeader, mesh, processed);
            writeMagField<tensor>(fieldHeader, mesh, processed);

            if (!processed)
            {
                 FatalError
                     << "Unable to process " << fieldName << nl
                     << "No call to mag for fields of type "
                     << fieldHeader.headerClassName() << nl << nl
                     << exit(FatalError);
            }
        }
        else
        {
            Info<< "    No " << fieldName << endl;
        }
    }
}


// ************************************************************************* //

