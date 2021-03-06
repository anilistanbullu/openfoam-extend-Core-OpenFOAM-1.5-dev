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

Description

\*---------------------------------------------------------------------------*/

#include "patchToFace.H"
#include "polyMesh.H"

#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{

defineTypeNameAndDebug(patchToFace, 0);

addToRunTimeSelectionTable(topoSetSource, patchToFace, word);

addToRunTimeSelectionTable(topoSetSource, patchToFace, istream);

}


Foam::topoSetSource::addToUsageTable Foam::patchToFace::usage_
(
    patchToFace::typeName,
    "\n    Usage: patchToFace patch\n\n"
    "    Select all faces in the patch\n\n"
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void Foam::patchToFace::combine(topoSet& set, const bool add) const
{
    label patchI = mesh_.boundaryMesh().findPatchID(patchName_);

    if (patchI != -1)
    {
        const polyPatch& pp = mesh_.boundaryMesh()[patchI];

        for (label faceI = pp.start(); faceI < pp.start() + pp.size(); faceI++)
        {
            addOrDelete(set, faceI, add);
        }
    }
    else
    {
        WarningIn("patchToFace::combine(topoSet&, const bool)")
            << "Cannot find patch named " << patchName_ << endl
            << "Valid names are " << mesh_.boundaryMesh().names() << endl;
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from components
Foam::patchToFace::patchToFace
(
    const polyMesh& mesh,
    const word& patchName
)
:
    topoSetSource(mesh),
    patchName_(patchName)
{}


// Construct from dictionary
Foam::patchToFace::patchToFace
(
    const polyMesh& mesh,
    const dictionary& dict
)
:
    topoSetSource(mesh),
    patchName_(dict.lookup("name"))
{}


// Construct from Istream
Foam::patchToFace::patchToFace
(
    const polyMesh& mesh,
    Istream& is
)
:
    topoSetSource(mesh),
    patchName_(checkIs(is))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::patchToFace::~patchToFace()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::patchToFace::applyToSet
(
    const topoSetSource::setAction action,
    topoSet& set
) const
{
    if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
    {
        Info<< "    Adding all faces of patch " << patchName_ << " ..." << endl;

        combine(set, true);
    }
    else if (action == topoSetSource::DELETE)
    {
        Info<< "    Removing all faces of patch " << patchName_ << " ..."
            << endl;

        combine(set, false);
    }
}


// ************************************************************************* //
