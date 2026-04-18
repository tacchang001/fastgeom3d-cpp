#ifndef FASTGEOM3D_PRISM_SUPPORT_H
#define FASTGEOM3D_PRISM_SUPPORT_H

#include "fastgeom3d/AABB.h"

namespace fastgeom3d::detail {

AABB makePrismAABB(const AABB& baseAABB, double height);

} // namespace fastgeom3d::detail

#endif // FASTGEOM3D_PRISM_SUPPORT_H