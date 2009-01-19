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

package PatchTool.Events;


public class PatchEvent
    extends java.util.EventObject
{
    protected String patchName_;
    protected String patchType_;

    /** PatchEvent constructor. */
    public PatchEvent(Object source, String patchName, String patchType)
    {
        super(source);
        patchName_ = patchName;
        patchType_ = patchType;
    }

    public String toString()
    {
        return "PatchEvent : " + patchName_ + " " + patchType_;
    }

    public String getPatchName()
    {
        return patchName_;
    }

    public String getPatchType()
    {
        return patchType_;
    }
}



