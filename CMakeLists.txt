cmake_minimum_required(VERSION 3.16)
project(fastgeom3d_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

if(CYGWIN)
  add_compile_definitions(_XOPEN_SOURCE=700 _POSIX_C_SOURCE=200809L)
endif()

include(GNUInstallDirs)
include(FetchContent)

add_library(fastgeom3d
  src/fastgeom3d.cpp
  src/AABB.cpp
  src/ContinuousRectangularPrism.cpp
  src/Polyline.cpp
  src/UTMCoordinate.cpp
  src/Intersections.cpp
)

target_include_directories(fastgeom3d
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

enable_testing()
add_subdirectory(tests)
