#include "PrismSupport.h"
#include <stdexcept>

namespace fastgeom3d::detail {

AABB makePrismAABB(const AABB& baseAABB, double height) {
    if (height <= 0.0) {
        throw std::invalid_argument("height must be positive");
    }

    if (baseAABB.minZ != baseAABB.maxZ) {
        throw std::invalid_argument("base shape must be flat in the Z axis");
    }

    return AABB(
        baseAABB.minX,
        baseAABB.minY,
        baseAABB.minZ,
        baseAABB.maxX,
        baseAABB.maxY,
        baseAABB.minZ + height
    );
}

} // namespace fastgeom3d::detail