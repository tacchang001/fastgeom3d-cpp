#ifndef FASTGEOM3D_PRISM_H
#define FASTGEOM3D_PRISM_H

#include "fastgeom3d/AABB.h"
#include "fastgeom3d/Shape2D.h"
#include "fastgeom3d/Vec3.h"
#include <stdexcept>

namespace fastgeom3d {

class Prism : public Shape3D {
public:
    double getHeight() const {
        return height;
    }

    double getBottomZ() const {
        return aabb.minZ;
    }

    double getTopZ() const {
        return aabb.maxZ;
    }

    AABB getAABB() const override {
        return aabb;
    }

    static void validateHorizontalPlane(const std::vector<Vec3>& vertices) {
        if (vertices.empty()) {
            throw std::invalid_argument("vertices must not be empty");
        }
        double z = vertices[0].z;
        for (const auto& vertex : vertices) {
            if (vertex.z != z) {
                throw std::invalid_argument("All vertices must lie in the same horizontal plane");
            }
        }
    }

protected:
    Prism(const Shape2D& baseShape, double height_) : height(height_), aabb(createAABB(baseShape, height_)) {
        if (height_ <= 0.0) {
            throw std::invalid_argument("height must be positive");
        }
    }

private:
    static AABB createAABB(const Shape2D& baseShape, double height_) {
        AABB baseAABB = baseShape.getAABB();
        if (baseAABB.minZ != baseAABB.maxZ) {
            throw std::invalid_argument("base shape must be flat in the Z axis");
        }
        return AABB(
            baseAABB.minX,
            baseAABB.minY,
            baseAABB.minZ,
            baseAABB.maxX,
            baseAABB.maxY,
            baseAABB.minZ + height_
        );
    }

    const double height;
    const AABB aabb;
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_PRISM_H
