#ifndef FASTGEOM3D_ELLIPTICALCYLINDER_H
#define FASTGEOM3D_ELLIPTICALCYLINDER_H

#include "fastgeom3d/Prism.h"
#include "fastgeom3d/Ellipse2D.h"

namespace fastgeom3d {

class EllipticalCylinder final : public Prism {
public:
    EllipticalCylinder(const Vec2& center, double radiusX, double radiusY, double height) :
        Prism(Ellipse2D(center, radiusX, radiusY), height),
        center(center), radiusX(radiusX), radiusY(radiusY) {
        if (radiusX <= 0.0 || radiusY <= 0.0) {
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

private:
    const Vec2 center;
    const double radiusX;
    const double radiusY;
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_ELLIPTICALCYLINDER_H
