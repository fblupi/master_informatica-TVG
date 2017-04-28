cmake_minimum_required(VERSION 2.8)

PROJECT(MarchingCubes)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(MarchingCubes MACOSX_BUNDLE MarchingCubes)

if(VTK_LIBRARIES)
  target_link_libraries(MarchingCubes ${VTK_LIBRARIES})
else()
  target_link_libraries(MarchingCubes vtkHybrid vtkWidgets)
endif()
