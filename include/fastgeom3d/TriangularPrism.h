#ifndef FASTGEOM3D_TRIANGULARPRISM_H
#define FASTGEOM3D_TRIANGULARPRISM_H

#include "fastgeom3d/PolygonalPrism.h"

namespace fastgeom3d {

class TriangularPrism final : public PolygonalPrism {
public:
    TriangularPrism(const std::vector<Vec2>& vertices, double height) : PolygonalPrism(vertices, height) {
        if (vertices.size() != 3) {
            throw std::invalid_argument("Triangle2D requires exactly 3 vertices");
        }
    }
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_TRIANGULARPRISM_H
