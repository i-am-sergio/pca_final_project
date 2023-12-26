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

# Fedora - sergio
# set(GTEST_INCLUDE_DIR /usr/lib/.build-id/4f/80075776864ad2057e2ddac34f016ce400459c)
# set(GTEST_LIB_DIR /usr/lib64)
# include_directories(${GTEST_INCLUDE_DIR})

set(GTEST_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/googletest/include)
set(GMOCK_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/googletest/include)
set(GTEST_LIB_DIR ${CMAKE_CURRENT_LIST_DIR}/googletest/lib)
set(GMOCK_LIB_DIR ${CMAKE_CURRENT_LIST_DIR}/googletest/lib)
include_directories(${GTEST_INCLUDE_DIR})
include_directories(${GMOCK_INCLUDE_DIR})
include_directories(${INCLUDE_DIR})

set(CMAKE_NINJA_FORCE_RESPONSE_FILE "ON" CACHE BOOL "Force Ninja to use response files.")

# Agrega la siguiente línea para copiar el archivo CSV a la carpeta de compilación
configure_file(${CMAKE_SOURCE_DIR}/pca_result.csv ${CMAKE_BINARY_DIR}/pca_result.csv COPYONLY)

add_executable(pca_kdtree 
              includes/Node.hpp 
              includes/KDTree.hpp 
              utils/Reader.hpp 
              utils/Grapher.hpp
              test.cpp
)

target_link_libraries(pca_kdtree PRIVATE
    ${VTK_LIBRARIES}
    ${GTEST_LIB_DIR}/libgtest.a
    ${GTEST_LIB_DIR}/libgtest_main.a
    ${GMOCK_LIB_DIR}/libgmock.a
    ${GMOCK_LIB_DIR}/libgmock_main.a
)

# # Fedora - sergio
# target_link_libraries(pca_kdtree PRIVATE
#     ${VTK_LIBRARIES}
#     ${GTEST_LIB_DIR}/libgtest.so.1.13.0
#     ${GTEST_LIB_DIR}/libgtest_main.so.1.13.0
# )

vtk_module_autoinit(
  TARGETS pca_kdtree
  MODULES ${VTK_LIBRARIES}
)
