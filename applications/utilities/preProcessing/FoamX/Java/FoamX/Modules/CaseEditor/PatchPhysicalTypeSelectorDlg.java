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
package FoamX.Modules.CaseEditor;

import javax.swing.tree.*;
import java.awt.event.ActionEvent;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;

import FoamX.App;
import FoamX.Editors.ApplicationEditor.BoundaryDefinitionModelItem;
import FoamX.Util.FoamXTreeRenderer;

public class PatchPhysicalTypeSelectorDlg
    extends javax.swing.JDialog
{
    //--------------------------------------------------------------------------

    private PatchEditorModel patchEditorModel_;
    private boolean cancelled_;
    private BoundaryDefinitionModelItem currentBoundaryDef_;

    //--------------------------------------------------------------------------
    /** PatchPhysicalTypeSelectorDlg constructor. */
    public PatchPhysicalTypeSelectorDlg(java.awt.Frame parent, PatchEditorModel patchEditorModel)
    {
        super(parent, "Boundary Type Selector", true);  // Modal.

        patchEditorModel_   = patchEditorModel;
        cancelled_          = false;
        currentBoundaryDef_ = patchEditorModel_.getBoundaryDefinition();

        initComponents();

        // Set the tree model.
        patchPhysicalTypeTree_.setModel(patchEditorModel_.getTreeModel());

        // Set tree renderer.
        patchPhysicalTypeTree_.setCellRenderer(new FoamXTreeRenderer());

        // Set single selection.
        patchPhysicalTypeTree_.getSelectionModel().setSelectionMode(TreeSelectionModel.SINGLE_TREE_SELECTION);

        // Listen out for tree selection events.
        patchPhysicalTypeTree_.getSelectionModel().addTreeSelectionListener
        (
            new TreeSelectionListener()
            {
                public void valueChanged(TreeSelectionEvent evt)
                {
                    OnSelectionChanged(evt);
                }
            }
        );

        // Make sure the tree is displayed properly.
        patchPhysicalTypeTree_.updateUI();
    }

    //--------------------------------------------------------------------------

    public boolean wasCancelled()
    {
        return cancelled_;
    }

    //--------------------------------------------------------------------------

    public void OnSelectionChanged(TreeSelectionEvent evt)
    {
        try
        {
            // Get the node object for the current selection.
            if (evt.isAddedPath())    // Has the new node been added to the selection?
            {
                TreePath tp = evt.getPath();
                if (tp != null)
                {
                    // Set the current selection object.
                    DefaultMutableTreeNode nodeItem = (DefaultMutableTreeNode)tp.getLastPathComponent();
                    currentBoundaryDef_ = (BoundaryDefinitionModelItem)nodeItem.getUserObject();
                }
            }
        }
        catch (Exception ex)
        {
            App.printMessage("PatchPhysicalTypeSelectorDlg::OnSelectionChanged : " + ex.getMessage());
        }
    }

    //--------------------------------------------------------------------------
    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the FormEditor.
     */
    private void initComponents() {//GEN-BEGIN:initComponents
        buttonPanel_ = new javax.swing.JPanel();
        okButton_ = new javax.swing.JButton();
        cancelButton_ = new javax.swing.JButton();
        treeScrollPane_ = new javax.swing.JScrollPane();
        patchPhysicalTypeTree_ = new javax.swing.JTree();
        
        getContentPane().setLayout(new java.awt.GridBagLayout());
        java.awt.GridBagConstraints gridBagConstraints1;
        
        setTitle("Select Boundary Type");
        setName("PatchPhysicalTypeSelectorDlg");
        setModal(true);
        setFont(new java.awt.Font("Dialog", 0, 10));
        addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent evt) {
                closeDialog(evt);
            }
        });
        
        buttonPanel_.setLayout(new java.awt.FlowLayout(java.awt.FlowLayout.RIGHT, 10, 10));
        
        buttonPanel_.setBorder(new javax.swing.border.EtchedBorder());
        okButton_.setFont(new java.awt.Font("Dialog", 0, 10));
        okButton_.setText("OK");
        okButton_.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                OnOK(evt);
            }
        });
        
        buttonPanel_.add(okButton_);
        
        cancelButton_.setFont(new java.awt.Font("Dialog", 0, 10));
        cancelButton_.setText("Cancel");
        cancelButton_.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                OnCancel(evt);
            }
        });
        
        buttonPanel_.add(cancelButton_);
        
        gridBagConstraints1 = new java.awt.GridBagConstraints();
        gridBagConstraints1.gridx = 0;
        gridBagConstraints1.gridy = 1;
        gridBagConstraints1.fill = java.awt.GridBagConstraints.HORIZONTAL;
        getContentPane().add(buttonPanel_, gridBagConstraints1);
        
        treeScrollPane_.setFont(new java.awt.Font("Dialog", 0, 10));
        patchPhysicalTypeTree_.setFont(new java.awt.Font("Dialog", 0, 10));
        patchPhysicalTypeTree_.setShowsRootHandles(true);
        patchPhysicalTypeTree_.setVisibleRowCount(10);
        patchPhysicalTypeTree_.setRootVisible(false);
        patchPhysicalTypeTree_.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                OnMouseClicked(evt);
            }
        });
        
        treeScrollPane_.setViewportView(patchPhysicalTypeTree_);
        
        gridBagConstraints1 = new java.awt.GridBagConstraints();
        gridBagConstraints1.gridx = 0;
        gridBagConstraints1.gridy = 0;
        gridBagConstraints1.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints1.insets = new java.awt.Insets(10, 10, 10, 10);
        gridBagConstraints1.anchor = java.awt.GridBagConstraints.NORTH;
        gridBagConstraints1.weightx = 1.0;
        gridBagConstraints1.weighty = 1.0;
        getContentPane().add(treeScrollPane_, gridBagConstraints1);
        
        pack();
        java.awt.Dimension screenSize = java.awt.Toolkit.getDefaultToolkit().getScreenSize();
        setSize(new java.awt.Dimension(300, 250));
        setLocation((screenSize.width-300)/2,(screenSize.height-250)/2);
    }//GEN-END:initComponents

    //--------------------------------------------------------------------------

  private void OnMouseClicked (java.awt.event.MouseEvent evt)
    {//GEN-FIRST:event_OnMouseClicked
        // Check for double click event.
        if (evt.getClickCount()>= 2)
        {
            // Set the selected boundary definition in the model.
            patchEditorModel_.setBoundaryDefinition(currentBoundaryDef_);

            // Close the dialog.
            cancelled_ = false;
            setVisible(false);
            dispose();
        }
  }//GEN-LAST:event_OnMouseClicked

    //--------------------------------------------------------------------------

  private void OnCancel (java.awt.event.ActionEvent evt)
    {//GEN-FIRST:event_OnCancel
        cancelled_ = true;
        setVisible(false);
        dispose();
  }//GEN-LAST:event_OnCancel

  private void OnOK (java.awt.event.ActionEvent evt)
    {//GEN-FIRST:event_OnOK

        // Set the selected boundary definition in the model.
        patchEditorModel_.setBoundaryDefinition(currentBoundaryDef_);

        cancelled_ = false;
        setVisible(false);
        dispose();
  }//GEN-LAST:event_OnOK

    //--------------------------------------------------------------------------
    /** Closes the dialog */
    private void closeDialog(java.awt.event.WindowEvent evt)
    {//GEN-FIRST:event_closeDialog
        // Treat as cancel.
        cancelled_ = true;
        setVisible(false);
        dispose();
    }//GEN-LAST:event_closeDialog

    //--------------------------------------------------------------------------

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JPanel buttonPanel_;
    private javax.swing.JButton okButton_;
    private javax.swing.JButton cancelButton_;
    private javax.swing.JScrollPane treeScrollPane_;
    private javax.swing.JTree patchPhysicalTypeTree_;
    // End of variables declaration//GEN-END:variables

    //--------------------------------------------------------------------------
    //--------------------------------------------------------------------------
    //--------------------------------------------------------------------------
    //--------------------------------------------------------------------------
    //--------------------------------------------------------------------------
    //--------------------------------------------------------------------------
}




