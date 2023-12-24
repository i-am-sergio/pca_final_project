cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(pca_kdtree)
enable_testing()

# Find VTK package
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

# Definir variables para archivos y directorios
set(SOURCES
  "${CMAKE_CURRENT_LIST_DIR}/test.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Components/KDTree/kdtree.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/Components/Grapher/grapher.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/Components/Grapher/grapher.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Components/Node/node.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/Components/Node/node.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Components/Reader/reader.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/Components/Reader/reader.cpp"
)

# Añadir el directorio de inclusión
set(INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR})
include_directories(${INCLUDE_DIR})

# Copiar archivos necesarios
configure_file(${CMAKE_SOURCE_DIR}/pca_result.csv ${CMAKE_BINARY_DIR}/pca_result.csv COPYONLY)

# Crear el ejecutable
add_executable(pca_kdtree ${SOURCES})

# Enlazar las bibliotecas de VTK
target_link_libraries(pca_kdtree PRIVATE ${VTK_LIBRARIES})

# Inicialización automática de módulos VTK
vtk_module_autoinit(
  TARGETS pca_kdtree
  MODULES ${VTK_LIBRARIES}
)
