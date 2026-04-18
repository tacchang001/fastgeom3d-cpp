#ifndef FASTGEOM3D_QUADRILATERALPRISM_H
#define FASTGEOM3D_QUADRILATERALPRISM_H

#include "fastgeom3d/PolygonalPrism.h"

namespace fastgeom3d {

class QuadrilateralPrism final : public PolygonalPrism {
public:
    QuadrilateralPrism(const std::vector<Vec2>& vertices, double height) : PolygonalPrism(vertices, height) {
        if (vertices.size() != 4) {
            throw std::invalid_argument("Quadrilateral2D requires exactly 4 vertices");
        }
    }
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_QUADRILATERALPRISM_H
