cmake_minimum_required(VERSION 3.16)
project(fastgeom3d_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
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
  src/Vec2.cpp
  src/Vec3.cpp
  src/Circle2D.cpp
  src/Ellipse2D.cpp
  src/Polygon2D.cpp
  src/Polyline2D.cpp
  src/Triangle2D.cpp
  src/Quadrilateral2D.cpp
  src/AABB.cpp
  src/PolygonalPrism.cpp
  src/PrismSupport.cpp
  src/Cylinder.cpp
  src/EllipticalCylinder.cpp
  src/TriangularPrism.cpp
  src/QuadrilateralPrism.cpp
  src/ContinuousRectangularPrism.cpp
  src/Polyline.cpp
  src/Sphere.cpp
  src/UTMCoordinate.cpp
  src/Intersections.cpp
  src/AnnularSector2D.cpp
)

set(FASTGEOM3D_PUBLIC_HEADERS
  include/fastgeom3d/fastgeom3d.h
  include/fastgeom3d/core.h
  include/fastgeom3d/shapes2d.h
  include/fastgeom3d/prisms.h
  include/fastgeom3d/shapes3d.h
  include/fastgeom3d/geodesy.h
  include/fastgeom3d/algorithms.h
  include/fastgeom3d/Vec2.h
  include/fastgeom3d/Vec3.h
  include/fastgeom3d/AABB.h
  include/fastgeom3d/Circle2D.h
  include/fastgeom3d/Ellipse2D.h
  include/fastgeom3d/Polygon2D.h
  include/fastgeom3d/Polyline2D.h
  include/fastgeom3d/Triangle2D.h
  include/fastgeom3d/Quadrilateral2D.h
  include/fastgeom3d/AnnularSector2D.h
  include/fastgeom3d/PolygonalPrism.h
  include/fastgeom3d/TriangularPrism.h
  include/fastgeom3d/QuadrilateralPrism.h
  include/fastgeom3d/Cylinder.h
  include/fastgeom3d/EllipticalCylinder.h
  include/fastgeom3d/ContinuousRectangularPrism.h
  include/fastgeom3d/Polyline.h
  include/fastgeom3d/Sphere.h
  include/fastgeom3d/UTMCoordinate.h
  include/fastgeom3d/Intersections.h
)

target_include_directories(fastgeom3d
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS fastgeom3d
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES ${FASTGEOM3D_PUBLIC_HEADERS}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fastgeom3d
)

enable_testing()
add_subdirectory(tests)
