#include "fastgeom3d/Polyline.h"
#include "fastgeom3d/UTMCoordinate.h"

namespace fastgeom3d {

Polyline Polyline::fromUTM(const std::vector<UTMCoordinate>& utmPoints) {
    std::vector<Vec3> points;
    points.reserve(utmPoints.size());
    for (const auto& utm : utmPoints) {
        points.push_back(utm.toVec3());
    }
    return Polyline(points);
}

} // namespace fastgeom3d
