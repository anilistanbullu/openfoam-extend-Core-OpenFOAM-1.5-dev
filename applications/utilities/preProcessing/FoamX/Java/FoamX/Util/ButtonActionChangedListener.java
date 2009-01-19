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

package FoamX.Util;

import java.beans.*;
import javax.swing.*;

public class ButtonActionChangedListener
    implements PropertyChangeListener
{
    private JButton button_;

    public ButtonActionChangedListener(JButton button)
    {
        super();
        button_ = button;
    }

    public void propertyChange(PropertyChangeEvent e)
    {
        String propertyName = e.getPropertyName();
/*
        if (e.getPropertyName().equals(Action.NAME))
        {
            // Change the label on the button if the action name has changed.
            String text = (String)e.getNewValue();
            button_.setText(text);
        }
*/
        if (propertyName.equals("enabled"))
        {
            // Disable the button if the action has been disabled.
            Boolean enabledState = (Boolean)e.getNewValue();
            button_.setEnabled(enabledState.booleanValue());
        }
    }
}
