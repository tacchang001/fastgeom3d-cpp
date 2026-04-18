#ifndef FASTGEOM3D_ELLIPSE2D_H
#define FASTGEOM3D_ELLIPSE2D_H

#include "fastgeom3d/Shape2D.h"
#include "fastgeom3d/AABB.h"
#include "fastgeom3d/Vec2.h"

namespace fastgeom3d {

class Ellipse2D final : public Shape2D {
public:
    Ellipse2D(const Vec2& center_, double radiusX_, double radiusY_) :
        center(center_), radiusX(radiusX_), radiusY(radiusY_) {
        if (radiusX_ <= 0.0 || radiusY_ <= 0.0) {
            throw std::invalid_argument("radiusX and radiusY must be positive");
        }
    }

    const Vec2& getCenter() const {
        return center;
    }

    double getRadiusX() const {
        return radiusX;
    }

    double getRadiusY() const {
        return radiusY;
    }

    AABB getAABB() const override {
        return AABB(
            center.x - radiusX,
            center.y - radiusY,
            0.0,
            center.x + radiusX,
            center.y + radiusY,
            0.0
        );
    }

private:
    const Vec2 center;
    const double radiusX;
    const double radiusY;
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_ELLIPSE2D_H
