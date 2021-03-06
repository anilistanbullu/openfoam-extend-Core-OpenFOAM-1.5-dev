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

Application
    symmTensorFieldTest

\*---------------------------------------------------------------------------*/

#include "tensorField.H"

using namespace Foam;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    scalarField f1(1, 1);
    symmTensorField sf1(1, symmTensor::one);
    symmTensorField sf2(1, symmTensor::one);
    tensorField tf1(1, tensor(1, 2, 3, 4, 5, 6, 7, 8, 9));

    Info<< (tf1 & sf2) << endl;

    Info<< f1*sf1 << " " << sf1*3 << endl;

    Info<< ((sf1 + sf2) & (sf1 + sf2)) << endl;

    vectorField vf1(1, vector::one);
    Info<< sqr(vf1) << endl;
    Info<< pow<vector, 2>(vf1) << endl;

    Info<< symm(tf1) << endl;

    return(0);
}


// ************************************************************************* //
