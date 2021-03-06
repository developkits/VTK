if(NOT VTK_SOURCE_DIR)
  cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
  project(vtkRenderingOpenVR)
  find_package(VTK REQUIRED)
endif()
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${VTK_CMAKE_DIR}")
if(NOT VTK_SOURCE_DIR)
  include(vtkExternalModuleMacros)
endif()

find_package(OpenVR REQUIRED)

set(Module_SRCS
  vtkOpenVRCamera.cxx
  vtkOpenVRControlsHelper.cxx
  vtkOpenVRDefaultOverlay.cxx
  vtkOpenVRFollower.cxx
  vtkOpenVRHardwarePicker.cxx
  vtkOpenVRInteractorStyle.cxx
  vtkOpenVRMenuRepresentation.cxx
  vtkOpenVRMenuWidget.cxx
  vtkOpenVRModel.cxx
  vtkOpenVROverlay.cxx
  vtkOpenVRPanelRepresentation.cxx
  vtkOpenVRPanelWidget.cxx
  vtkOpenVRPropPicker.cxx
  vtkOpenVRRenderer.cxx
  vtkOpenVRRenderWindow.cxx
  vtkOpenVRRenderWindowInteractor.cxx
  )

# This option determines if the VR rendering code will become
# the default renderer
option(VTK_OPENVR_OBJECT_FACTORY
  "Make openVR the default render window for VTK" ON)

mark_as_advanced(VTK_OPENVR_OBJECT_FACTORY)

if (VTK_OPENVR_OBJECT_FACTORY)
  include(vtkObjectFactory)
  vtk_add_override(vtkCamera vtkOpenVRCamera)
  vtk_add_override(vtkRenderer vtkOpenVRRenderer)
  vtk_add_override(vtkRenderWindow vtkOpenVRRenderWindow)
  vtk_add_override(vtkRenderWindowInteractor vtkOpenVRRenderWindowInteractor)

  # add extra init code, we have to disable the existing
  # opengl overrides otherwise they will get picked first
  # instead of ours
  set (_vtk_override_includes ${_vtk_override_includes}
    "#include \"vtkOverrideInformation.h\"\n#include \"vtkOverrideInformationCollection.h\"\n")
  set (vtk-object-factory-extra-init "\
    vtkOverrideInformation *oi;\n\
    vtkOverrideInformationCollection  *oic = vtkOverrideInformationCollection::New();\n\
    vtkObjectFactory::GetOverrideInformation(\"vtkRenderWindow\",oic);\n\
    for (oic->InitTraversal(); oi = oic->GetNextItem(); )\n\
      {\n\
      oi->GetObjectFactory()->Disable(\"vtkRenderWindow\");\n\
      }\n\
    vtkObjectFactory::GetOverrideInformation(\"vtkCamera\",oic);\n\
    for (oic->InitTraversal(); oi = oic->GetNextItem(); )\n\
      {\n\
      oi->GetObjectFactory()->Disable(\"vtkCamera\");\n\
      }\n\
    vtkObjectFactory::GetOverrideInformation(\"vtkRenderWindowInteractor\",oic);\n\
    for (oic->InitTraversal(); oi = oic->GetNextItem(); )\n\
      {\n\
      oi->GetObjectFactory()->Disable(\"vtkRenderWindowInteractor\");\n\
      }\n\
    vtkObjectFactory::GetOverrideInformation(\"vtkRenderer\",oic);\n\
    for (oic->InitTraversal(); oi = oic->GetNextItem(); )\n\
      {\n\
      oi->GetObjectFactory()->Disable(\"vtkRenderer\");\n\
      }\n\
    oic->Delete();\n")
  vtk_object_factory_configure("${vtk_module_overrides}")

  set(Module_SRCS ${Module_SRCS}
    ${CMAKE_CURRENT_BINARY_DIR}/${vtk-module}ObjectFactory.cxx
    )
endif()

list(APPEND ${vtk-module}_SYSTEM_INCLUDE_DIRS ${OPENVR_INCLUDE_DIRS})


vtk_module_library(${vtk-module} ${Module_SRCS})
vtk_module_link_libraries(${vtk-module} LINK_PRIVATE ${OPENVR_LIBRARY})


include(vtkOpenGL)
vtk_opengl_link(${vtk-module})

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/OpenVRDashboard.jpg"
  "${CMAKE_BINARY_DIR}/OpenVRDashboard.jpg"
  COPYONLY
  )
