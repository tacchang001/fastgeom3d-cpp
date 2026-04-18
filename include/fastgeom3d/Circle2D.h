#ifndef FASTGEOM3D_CIRCLE2D_H
#define FASTGEOM3D_CIRCLE2D_H

#include "fastgeom3d/Shape2D.h"
#include "fastgeom3d/AABB.h"
#include "fastgeom3d/Vec2.h"

namespace fastgeom3d {

class Circle2D final : public Shape2D {
public:
    Circle2D(const Vec2& center_, double radius_) : center(center_), radius(radius_) {
        if (radius_ <= 0.0) {
            throw std::invalid_argument("radius must be positive");
        }
    }

    const Vec2& getCenter() const {
        return center;
    }

    double getRadius() const {
        return radius;
    }

    AABB getAABB() const override {
        return AABB(
            center.x - radius,
            center.y - radius,
            0.0,
            center.x + radius,
            center.y + radius,
            0.0
        );
    }

private:
    const Vec2 center;
    const double radius;
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_CIRCLE2D_H
