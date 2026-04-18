#ifndef FASTGEOM3D_INTERSECTIONS_H
#define FASTGEOM3D_INTERSECTIONS_H

#include "fastgeom3d/Shape3D.h"
#include "fastgeom3d/Shape2D.h"
#include "fastgeom3d/AABB.h"
#include "fastgeom3d/Sphere.h"
#include "fastgeom3d/Vec2.h"
#include "fastgeom3d/Circle2D.h"
#include "fastgeom3d/Ellipse2D.h"
#include "fastgeom3d/Polygon2D.h"
#include "fastgeom3d/Polyline2D.h"
#include "fastgeom3d/Polyline.h"
#include <vector>

namespace fastgeom3d {

class Intersections {
public:
    enum class IntersectionType {
        NONE,
        OVERLAP,
        TOUCH
    };

    static bool intersect(const AABB& a, const AABB& b);
    static bool intersect(const Sphere& a, const Sphere& b);
    static bool intersect(const AABB& box, const Sphere& s);
    static bool intersect(const Shape3D& s1, const Shape3D& s2);
    static bool intersect(const Shape2D& s1, const Shape2D& s2);
    static bool intersect(const Polyline2D& line, const Polyline2D& other);
    static bool intersect(const Polyline2D& line, const Circle2D& circle);
    static bool intersect(const Polyline2D& line, const Polygon2D& polygon);
    static bool intersect(const Circle2D& a, const Circle2D& b);
    static bool intersect(const Polygon2D& polygon, const Circle2D& circle);
    static bool intersect(const Polygon2D& a, const Polygon2D& b);
    static bool intersect(const Polyline2D& line, const Ellipse2D& ellipse);
    static bool intersect(const Circle2D& circle, const Ellipse2D& ellipse);
    static bool intersect(const Polygon2D& polygon, const Ellipse2D& ellipse);
    static bool intersectsAny(const Polyline& line, const std::vector<const Shape3D*>& shapes);
    static bool intersectsAny(const Polyline& line1, const Polyline& line2, const std::vector<const Shape3D*>& shapes);
    static bool intersectsAny(const std::vector<Polyline>& lines, const std::vector<const Shape3D*>& shapes);
    static std::vector<const Shape3D*> intersectingShapes(const Polyline& line, const std::vector<const Shape3D*>& shapes);
    static std::vector<const Shape3D*> intersectingShapes(const std::vector<Polyline>& lines, const std::vector<const Shape3D*>& shapes);
    static IntersectionType intersectionType(const Shape3D& s1, const Shape3D& s2);
    static IntersectionType intersectionType(const AABB& a, const AABB& b);
    static IntersectionType intersectionType(const Sphere& a, const Sphere& b);
    static IntersectionType intersectionType(const AABB& box, const Sphere& s);

private:
    static bool segmentIntersectsCircle(const Vec2& a, const Vec2& b, const Vec2& center, double radius);
    static bool segmentIntersectsEllipse(const Vec2& a, const Vec2& b, const Ellipse2D& ellipse);
    static bool pointInPolygon(const Vec2& point, const Polygon2D& polygon);
    static bool pointInEllipse(const Vec2& point, const Ellipse2D& ellipse);
    static bool pointOnSegment(const Vec2& point, const Vec2& a, const Vec2& b);
    static bool segmentsIntersect(const Vec2& a1, const Vec2& a2, const Vec2& b1, const Vec2& b2);
    static int ccw(const Vec2& a, const Vec2& b, const Vec2& c);
    static double squaredDistance(const Vec2& a, const Vec2& b);
    static bool intersect(const Polyline& line, const Shape3D& shape);
    static bool intervalIntersects(double minA, double maxA, double minB, double maxB);
    static bool intervalOverlaps(double minA, double maxA, double minB, double maxB);
    static double clamp(double v, double min, double max);
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_INTERSECTIONS_H
