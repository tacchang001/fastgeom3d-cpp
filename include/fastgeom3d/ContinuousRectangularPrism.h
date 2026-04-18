#ifndef FASTGEOM3D_CONTINUOUSRECTANGULARPRISM_H
#define FASTGEOM3D_CONTINUOUSRECTANGULARPRISM_H

#include "fastgeom3d/Shape3D.h"
#include "fastgeom3d/AABB.h"
#include <vector>
#include <limits>
#include <stdexcept>

namespace fastgeom3d {

class ContinuousRectangularPrism final : public Shape3D {
public:
    explicit ContinuousRectangularPrism(const std::vector<AABB>& prisms_) : prisms(prisms_) {
        if (prisms.size() < 2) {
            throw std::invalid_argument("ContinuousRectangularPrism requires at least 2 prisms");
        }
        validateContinuity(prisms);
    }

    const std::vector<AABB>& getPrisms() const {
        return prisms;
    }

    AABB getAABB() const override;

private:
    static void validateContinuity(const std::vector<AABB>& prisms);
    static bool areAdjacentWithMatchingFace(const AABB& a, const AABB& b);
    static bool isFaceAdjacent(
        double minA, double maxA, double minB, double maxB,
        double minC1, double maxC1, double minC2, double maxC2,
        double minD1, double maxD1, double minD2, double maxD2);
    static bool intervalsEqual(double minA, double maxA, double minB, double maxB);

    const std::vector<AABB> prisms;
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_CONTINUOUSRECTANGULARPRISM_H
