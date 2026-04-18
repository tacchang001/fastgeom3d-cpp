#ifndef FASTGEOM3D_CYLINDER_H
#define FASTGEOM3D_CYLINDER_H

#include "fastgeom3d/Prism.h"
#include "fastgeom3d/Circle2D.h"

namespace fastgeom3d {

class Cylinder final : public Prism {
public:
    Cylinder(const Vec2& center, double radius, double height) :
        Prism(Circle2D(center, radius), height), center(center), radius(radius) {
        if (radius <= 0.0) {
            throw std::invalid_argument("radius must be positive");
        }
    }

    const Vec2& getCenter() const {
        return center;
    }

    double getRadius() const {
        return radius;
    }

private:
    const Vec2 center;
    const double radius;
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_CYLINDER_H
