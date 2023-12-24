cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(pca_kdtree)
set(CMAKE_CXX_STANDARD 14)
enable_testing()

# List of options
option(BUILD_EXAMPLE "Builds the example" OFF)
option(SILENCE_DEBUG_OUTPUT "Silence debugs" OFF)

# Include directories
include_directories("/opt/vtk/9.3.0/include/vtk-9.3/")
include_directories("${CMAKE_CURRENT_LIST_DIR}/Components/Grapher")
include_directories("${CMAKE_CURRENT_LIST_DIR}/Components/Node")
include_directories("${CMAKE_CURRENT_LIST_DIR}/Components/Reader")

# Copy CSV file to build directory
configure_file(${CMAKE_SOURCE_DIR}/pca_result.csv ${CMAKE_BINARY_DIR}/pca_result.csv COPYONLY)

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
include_directories(${VTK_INCLUDE_DIRS})

# List source files
file(GLOB_RECURSE GRAPH_SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/Components/Grapher/*.cpp")
file(GLOB_RECURSE GRAPH_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/Components/Grapher/*.hpp")

file(GLOB_RECURSE NODE_SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/Components/Node/*.cpp")
file(GLOB_RECURSE NODE_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/Components/Node/*.hpp")

file(GLOB_RECURSE READER_SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/Components/Reader/*.cpp")
file(GLOB_RECURSE READER_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/Components/Reader/*.hpp")

# Create libraries
add_library(GrapherLib ${GRAPH_SRC} ${GRAPH_HEADERS})
add_library(NodeLib ${NODE_SRC} ${NODE_HEADERS})
add_library(ReaderLib ${READER_SRC} ${READER_HEADERS})

# Specify include directories for libraries
target_include_directories(GrapherLib PRIVATE ${VTK_INCLUDE_DIRS})
target_include_directories(NodeLib PRIVATE ${VTK_INCLUDE_DIRS})
target_include_directories(ReaderLib PRIVATE ${VTK_INCLUDE_DIRS})

# Set compile definitions
if(SILENCE_DEBUG_OUTPUT)
    target_compile_definitions(GrapherLib PRIVATE "SILENCE_DEBUG")
    target_compile_definitions(NodeLib PRIVATE "SILENCE_DEBUG")
    target_compile_definitions(ReaderLib PRIVATE "SILENCE_DEBUG")
endif()

if(BUILD_EXAMPLE)
    # Add test.cpp and kdtree.hpp directly to the example executable
    add_executable(example "${CMAKE_CURRENT_LIST_DIR}/test.cpp" "${CMAKE_CURRENT_LIST_DIR}/Components/KDTree/kdtree.hpp")

    # Link necessary libraries
    target_link_libraries(example PRIVATE ${VTK_LIBRARIES} GrapherLib NodeLib ReaderLib)
    set_target_properties(example PROPERTIES OUTPUT_NAME "pca_kdtree")
endif()
