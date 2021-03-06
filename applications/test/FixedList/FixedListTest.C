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
    FixedListTest

Description

\*---------------------------------------------------------------------------*/

#include "argList.H"
#include "IOstreams.H"
#include "FixedList.H"
#include "IFstream.H"
#include "OFstream.H"
#include "IPstream.H"
#include "OPstream.H"

using namespace Foam;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//  Main program:

int main(int argc, char *argv[])
{
    argList::validArgs.clear();
    argList args(argc, argv);

    FixedList<label, 4> list;
    list[0] = 1;
    list[1] = 2;
    list[2] = 3;
    list[3] = 4;
    Info<< list << endl;

    label a[4] = {0, 1, 2, 3};
    FixedList<label, 4> list2(a);
    Info<< list2 << endl;

    Info<< FixedList<label, 4>::Hash<>()(list2) << endl;

    //FixedList<label, 3> hmm(Sin);
    //Info<< hmm << endl;

    if (Pstream::parRun())
    {
        if (Pstream::myProcNo() != Pstream::masterNo())
        {
            Serr<< "slave sending to master "
                << Pstream::masterNo() << endl;
            OPstream toMaster(Pstream::blocking, Pstream::masterNo(), IOstream::ASCII);
            FixedList<label, 2> list3;
            list3[0] = 0;
            list3[1] = 1;
            toMaster << list3;
        }
        else
        {
            for
            (
                int slave=Pstream::firstSlave();
                slave<=Pstream::lastSlave();
                slave++
            )
            {
                Serr << "master receiving from slave " << slave << endl;
                IPstream fromSlave(Pstream::blocking, slave, IOstream::ASCII);
                FixedList<label, 2> list3(fromSlave);

                Serr<< list3 << endl;
            }
        }
    }

    return 0;
}


// ************************************************************************* //
