#include "fastgeom3d/Prism.h"
#include "fastgeom3d/Shape2D.h"
#include "fastgeom3d/Vec3.h"
#include <stdexcept>

namespace fastgeom3d {

double Prism::getHeight() const {
    return height;
}

double Prism::getBottomZ() const {
    return aabb.minZ;
}

double Prism::getTopZ() const {
    return aabb.maxZ;
}

AABB Prism::getAABB() const {
    return aabb;
}

void Prism::validateHorizontalPlane(const std::vector<Vec3>& vertices) {
    if (vertices.empty()) {
        throw std::invalid_argument("vertices must not be empty");
    }

    const double z = vertices[0].z;
    for (const auto& vertex : vertices) {
        if (vertex.z != z) {
            throw std::invalid_argument("All vertices must lie in the same horizontal plane");
        }
    }
}

Prism::Prism(const Shape2D& baseShape, double height_) : height(height_), aabb(createAABB(baseShape, height_)) {
    if (height_ <= 0.0) {
        throw std::invalid_argument("height must be positive");
    }
}

AABB Prism::createAABB(const Shape2D& baseShape, double height_) {
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

} // namespace fastgeom3d