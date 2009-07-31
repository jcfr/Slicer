/*=auto=========================================================================

Portions (c) Copyright 2005 Brigham and Women's Hospital (BWH) All Rights Reserved.

See Doc/copyright/copyright.txt
or http://www.slicer.org/copyright/copyright.txt for details.

Program:   3D Slicer
Module:    $RCSfile: vtkVolumeRenderingGUI.h,v $
Date:      $Date: 2006/03/19 17:12:29 $
Version:   $Revision: 1.3 $

=========================================================================auto=*/
#ifndef __vtkVolumeRenderingGUI_h
#define __vtkVolumeRenderingGUI_h

#include "vtkSlicerModuleGUI.h"
#include "vtkVolumeRendering.h"
#include "vtkVolumeRenderingLogic.h"

#include "vtkMRMLVolumeRenderingParametersNode.h"
#include "vtkSlicerNodeSelectorWidget.h"

#include "vtkKWLabel.h"
#include "vtkKWHistogram.h"
#include "vtkKWEntryWithLabel.h"
#include "vtkKWTkUtilities.h"


#include <string>

class vtkSlicerVolumeTextureMapper3D;
class vtkFixedPointVolumeRayCastMapper;
class vtkSlicerVRHelper;
class vtkSlicerVolumePropertyWidget;
class VTK_SLICERVOLUMERENDERING1_EXPORT vtkVolumeRenderingGUI :public vtkSlicerModuleGUI
{
public:

    static vtkVolumeRenderingGUI *New();
    vtkTypeMacro(vtkVolumeRenderingGUI,vtkSlicerModuleGUI);

    void PrintSelf(ostream& os, vtkIndent indent);

    // Description: Get/Set module logic
    vtkGetObjectMacro (Logic, vtkVolumeRenderingLogic);
    virtual void SetLogic(vtkVolumeRenderingLogic *log)
    {
        this->Logic=log;
        this->Logic->RegisterNodes();
    }

    // Description: Implements vtkSlicerModuleGUI::SetModuleLogic for this GUI
    virtual void SetModuleLogic(vtkSlicerLogic *logic)
    {
      this->SetLogic( dynamic_cast<vtkVolumeRenderingLogic*> (logic) );
    }

    //vtkSetObjectMacro (Logic, vtkVolumeRenderingLogic);
    // Description:
    // Create widgets
    virtual void BuildGUI ( );

    // Description:
    // This method releases references and key-bindings,
    // and optionally removes observers.
    virtual void TearDownGUI ( );

    // Description:
    // Methods for adding module-specific key bindings and
    // removing them.
    virtual void CreateModuleEventBindings ( );
    virtual void ReleaseModuleEventBindings ( );

    // Description:
    // Add obsereves to GUI widgets
    virtual void AddGUIObservers ( );
    virtual void AddMRMLObservers ( );

    // Description:
    // Remove obsereves to GUI widgets
    virtual void RemoveGUIObservers ( );
    virtual void RemoveMRMLObservers ( );
    virtual void RemoveLogicObservers ( );

    // Description:
    // Process events generated by Logic
    virtual void ProcessLogicEvents ( vtkObject *caller, unsigned long event,
        void *callData ){};

    // Description:
    // Process events generated by GUI widgets
    virtual void ProcessGUIEvents ( vtkObject *caller, unsigned long event,
        void *callData );

    // Description:
    // Process events generated by MRML
    virtual void ProcessMRMLEvents ( vtkObject *caller, unsigned long event, 
        void *callData);


    // Description:
    // Methods describe behavior at module enter and exit.
    virtual void Enter ( );
    virtual void Exit ( );


    // Description:
    // Get/Set the main slicer viewer widget, for picking
    vtkGetObjectMacro(ViewerWidget, vtkSlicerViewerWidget);
    virtual void SetViewerWidget(vtkSlicerViewerWidget *viewerWidget);

    // Description:
    // Get/Set the slicer interactorstyle, for picking
    vtkGetObjectMacro(InteractorStyle, vtkSlicerViewerInteractorStyle);
    virtual void SetInteractorStyle(vtkSlicerViewerInteractorStyle *interactorStyle);

   vtkGetObjectMacro(ParametersNode, vtkMRMLVolumeRenderingParametersNode);


    // Description:
    // Get methods on class members ( no Set methods required. )
    vtkGetObjectMacro (HideSurfaceModelsButton, vtkKWPushButton);
    vtkGetObjectMacro (VolumeRenderingParameterSelector, vtkSlicerNodeSelectorWidget);
    vtkGetObjectMacro (VolumeNodeSelector, vtkSlicerNodeSelectorWidget);

protected:
    vtkVolumeRenderingGUI();
    ~vtkVolumeRenderingGUI();
    vtkVolumeRenderingGUI(const vtkVolumeRenderingGUI&);//not implemented
    void operator=(const vtkVolumeRenderingGUI&);//not implemented

    // Description:
    // Updates GUI widgets based on parameters values in MRML node
    void UpdateGUIFromMRML();

    // Description:
    // Updates parameters values in MRML node based on GUI widgets 
    void UpdateMRMLFromGUI();

    void CreateParametersNode();

    void UpdateParametersNode();

    // Description:
    // Pointer to the module's logic class
    vtkVolumeRenderingLogic *Logic;

    vtkMRMLVolumeRenderingParametersNode *ParametersNode;

    // Description:
    // A pointer back to the viewer widget, useful for picking
    vtkSlicerViewerWidget *ViewerWidget;

    // Description:
    // A poitner to the interactor style, useful for picking
    vtkSlicerViewerInteractorStyle *InteractorStyle;

    //Frame Save/Load
    vtkKWPushButton *HideSurfaceModelsButton;

    //Frame Details
    vtkSlicerModuleCollapsibleFrame *DetailsFrame;
    
    vtkSlicerNodeSelectorWidget *VolumeNodeSelector;

    vtkSlicerNodeSelectorWidget *VolumeRenderingParameterSelector;
    
    int UpdatingGUI;
    int ProcessingGUIEvents;
    int ProcessingMRMLEvents;
};

#endif
