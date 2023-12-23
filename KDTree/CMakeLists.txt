cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(pca_kdtree)


find_package(VTK COMPONENTS 
  CommonColor
  CommonCore
  CommonDataModel
  CommonTransforms
  FiltersSources
  FiltersModeling
  InteractionStyle
  InteractionWidgets
  RenderingAnnotation
  RenderingContextOpenGL2
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingOpenGL2
)

include_directories(${INCLUDE_DIR})

set(CMAKE_NINJA_FORCE_RESPONSE_FILE "ON" CACHE BOOL "Force Ninja to use response files.")

# Agrega la siguiente línea para copiar el archivo CSV a la carpeta de compilación
configure_file(${CMAKE_SOURCE_DIR}/pca_result.csv ${CMAKE_BINARY_DIR}/pca_result.csv COPYONLY)

add_executable(pca_kdtree test.cpp Node.hpp KDTree.hpp Reader.hpp Grapher.hpp)

target_link_libraries(pca_kdtree PRIVATE ${VTK_LIBRARIES})

vtk_module_autoinit(
  TARGETS pca_kdtree
  MODULES ${VTK_LIBRARIES}
)
