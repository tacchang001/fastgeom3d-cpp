#ifndef FASTGEOM3D_FASTGEOM3D_H
#define FASTGEOM3D_FASTGEOM3D_H

#include "fastgeom3d/Vec2.h"
#include "fastgeom3d/Vec3.h"
#include "fastgeom3d/Shape3D.h"
#include "fastgeom3d/Shape2D.h"
#include "fastgeom3d/AABB.h"
#include "fastgeom3d/Circle2D.h"
#include "fastgeom3d/Ellipse2D.h"
#include "fastgeom3d/Polygon2D.h"
#include "fastgeom3d/Polyline2D.h"
#include "fastgeom3d/Triangle2D.h"
#include "fastgeom3d/Quadrilateral2D.h"
#include "fastgeom3d/Prism.h"
#include "fastgeom3d/PolygonalPrism.h"
#include "fastgeom3d/TriangularPrism.h"
#include "fastgeom3d/QuadrilateralPrism.h"
#include "fastgeom3d/Cylinder.h"
#include "fastgeom3d/EllipticalCylinder.h"
#include "fastgeom3d/ContinuousRectangularPrism.h"
#include "fastgeom3d/Polyline.h"
#include "fastgeom3d/Sphere.h"
#include "fastgeom3d/UTMCoordinate.h"
#include "fastgeom3d/Intersections.h"

namespace fastgeom3d {

double volumeOfUnitCube();

double distance3D(double x1, double y1, double z1, double x2, double y2, double z2);

} // namespace fastgeom3d

#endif // FASTGEOM3D_FASTGEOM3D_H
