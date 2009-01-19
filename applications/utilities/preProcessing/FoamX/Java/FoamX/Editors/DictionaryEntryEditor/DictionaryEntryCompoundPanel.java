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
package FoamX.Editors.DictionaryEntryEditor;

import javax.swing.*;
import FoamX.App;

public class DictionaryEntryCompoundPanel
    extends javax.swing.JPanel
{
    //--------------------------------------------------------------------------
    //--------------------------------------------------------------------------
    /** Creates new form DictionaryEntryCompoundPanel */

    public DictionaryEntryCompoundPanel()
    {
        initComponents();
    }

    //--------------------------------------------------------------------------

    public JLabel Label()
    {
        return label;
    }
    public JButton EditButton()
    {
        return editButton;
    }

    //--------------------------------------------------------------------------
    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the FormEditor.
    */
    private void initComponents()//GEN-BEGIN:initComponents
    {
        label = new javax.swing.JLabel();
        editButton = new javax.swing.JButton();
        
        setLayout(new java.awt.BorderLayout());
        
        label.setFont(new java.awt.Font("Dialog", 0, 10));
        label.setOpaque(true);
        add(label, java.awt.BorderLayout.CENTER);
        
        editButton.setFont(new java.awt.Font("Dialog", 0, 10));
        editButton.setText("...");
        add(editButton, java.awt.BorderLayout.EAST);
        
    }//GEN-END:initComponents

    //--------------------------------------------------------------------------

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JLabel label;
    private javax.swing.JButton editButton;
    // End of variables declaration//GEN-END:variables

    //--------------------------------------------------------------------------
    //--------------------------------------------------------------------------
    //--------------------------------------------------------------------------
    //--------------------------------------------------------------------------

}
