#ifndef FASTGEOM3D_POLYLINE_H
#define FASTGEOM3D_POLYLINE_H

#include "fastgeom3d/Shape3D.h"
#include "fastgeom3d/AABB.h"
#include "fastgeom3d/Vec3.h"
#include <vector>

namespace fastgeom3d {

struct UTMCoordinate;

class Polyline final : public Shape3D {
public:
    explicit Polyline(const std::vector<Vec3>& points_) : points(points_) {
        if (points.size() < 2) {
            throw std::invalid_argument("Polyline requires at least 2 points");
        }
    }

    static Polyline fromUTM(const std::vector<UTMCoordinate>& utmPoints);

    const std::vector<Vec3>& getPoints() const {
        return points;
    }

    AABB getAABB() const override {
        return AABB::fromPoints(points);
    }

private:
    const std::vector<Vec3> points;
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_POLYLINE_H
