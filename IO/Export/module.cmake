if(ANDROID OR APPLE_IOS) # No gl2ps on mobile
  set(gl2ps_depends)
  set(gl2ps_test_depends)
elseif(VTK_RENDERING_BACKEND STREQUAL "OpenGL2")
  set(gl2ps_depends vtkRenderingGL2PSOpenGL2)
  set(gl2ps_test_depends vtkIOExportOpenGL2)
endif()
vtk_module(vtkIOExport
  GROUPS
    Rendering
  TEST_DEPENDS
    vtkCommonColor
    vtkChartsCore
    vtkInteractionImage
    vtkIOParallel
    vtkTestingRendering
    vtkInteractionStyle
    vtkRenderingAnnotation
    vtkRenderingContextOpenGL2
    vtkRenderingLabel
    vtkRenderingVolumeOpenGL2
    vtkViewsContext2D
    ${gl2ps_test_depends}
  DEPENDS
    ${gl2ps_depends}
    vtkCommonCore
    vtkIOCore
    vtkIOImage
    vtkRenderingContext2D
    vtkRenderingCore
    vtkRenderingFreeType
  PRIVATE_DEPENDS
    vtkCommonDataModel
    vtkCommonMath
    vtkCommonTransforms
    vtkFiltersGeometry
    vtkIOImage
    vtkImagingCore
    vtklibharu
  )
