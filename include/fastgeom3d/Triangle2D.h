#ifndef FASTGEOM3D_TRIANGLE2D_H
#define FASTGEOM3D_TRIANGLE2D_H

#include "fastgeom3d/Polygon2D.h"

namespace fastgeom3d {

class Triangle2D final : public Polygon2D {
public:
    explicit Triangle2D(const std::vector<Vec2>& vertices) : Polygon2D(vertices) {
        if (vertices.size() != 3) {
            throw std::invalid_argument("Triangle2D requires exactly 3 vertices");
        }
    }
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_TRIANGLE2D_H
