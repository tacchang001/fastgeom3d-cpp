#ifndef FASTGEOM3D_POLYLINE2D_H
#define FASTGEOM3D_POLYLINE2D_H

#include "fastgeom3d/Shape2D.h"
#include "fastgeom3d/AABB.h"
#include "fastgeom3d/Vec2.h"
#include <vector>

namespace fastgeom3d {

class Polyline2D final : public Shape2D {
public:
    explicit Polyline2D(const std::vector<Vec2>& points_) : points(points_) {
        if (points.size() < 2) {
            throw std::invalid_argument("Polyline2D requires at least 2 points");
        }
    }

    const std::vector<Vec2>& getPoints() const {
        return points;
    }

    AABB getAABB() const override {
        return AABB::fromPoints2D(points);
    }

private:
    const std::vector<Vec2> points;
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_POLYLINE2D_H
