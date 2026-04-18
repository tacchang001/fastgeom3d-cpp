#ifndef FASTGEOM3D_AABB_H
#define FASTGEOM3D_AABB_H

#include "fastgeom3d/Shape3D.h"
#include "fastgeom3d/Vec3.h"
#include "fastgeom3d/Vec2.h"
#include <algorithm>
#include <limits>
#include <stdexcept>
#include <vector>

namespace fastgeom3d {

class AABB final : public Shape3D {
public:
    const double minX;
    const double minY;
    const double minZ;
    const double maxX;
    const double maxY;
    const double maxZ;

    AABB(double minX_, double minY_, double minZ_,
         double maxX_, double maxY_, double maxZ_) :
        minX(minX_), minY(minY_), minZ(minZ_),
        maxX(maxX_), maxY(maxY_), maxZ(maxZ_) {}

    static AABB fromCenterHalfExtents(const Vec3& center, const Vec3& halfExtents);
    static AABB fromPoints(const std::vector<Vec3>& points);
    static AABB fromPoints2D(const std::vector<Vec2>& points);

    AABB getAABB() const override;

    bool operator==(const AABB& other) const;
    bool operator!=(const AABB& other) const;
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_AABB_H
