#ifndef FASTGEOM3D_QUADRILATERAL2D_H
#define FASTGEOM3D_QUADRILATERAL2D_H

#include "fastgeom3d/Polygon2D.h"

namespace fastgeom3d {

class Quadrilateral2D final : public Polygon2D {
public:
    explicit Quadrilateral2D(const std::vector<Vec2>& vertices) : Polygon2D(vertices) {
        if (vertices.size() != 4) {
            throw std::invalid_argument("Quadrilateral2D requires exactly 4 vertices");
        }
    }
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_QUADRILATERAL2D_H
