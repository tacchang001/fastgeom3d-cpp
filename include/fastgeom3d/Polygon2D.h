#ifndef FASTGEOM3D_POLYGON2D_H
#define FASTGEOM3D_POLYGON2D_H

#include "fastgeom3d/Shape2D.h"
#include "fastgeom3d/AABB.h"
#include "fastgeom3d/Vec2.h"
#include <vector>

namespace fastgeom3d {

class Polygon2D : public Shape2D {
public:
    explicit Polygon2D(const std::vector<Vec2>& vertices_) : vertices(vertices_) {
        if (vertices.size() < 3) {
            throw std::invalid_argument("Polygon2D requires at least 3 vertices");
        }
    }

    const std::vector<Vec2>& getVertices() const {
        return vertices;
    }

    AABB getAABB() const override {
        return AABB::fromPoints2D(vertices);
    }

private:
    const std::vector<Vec2> vertices;
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_POLYGON2D_H
