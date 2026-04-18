#include "fastgeom3d/ContinuousRectangularPrism.h"
#include <algorithm>
#include <limits>
#include <stdexcept>

namespace fastgeom3d {

namespace {

bool intervalsEqual(double minA, double maxA, double minB, double maxB) {
    return minA == minB && maxA == maxB;
}

bool isFaceAdjacent(
    double minA, double maxA, double minB, double maxB,
    double minC1, double maxC1, double minC2, double maxC2,
    double minD1, double maxD1, double minD2, double maxD2) {
    const bool faceTouching = (maxA == minB) || (minA == maxB);
    const bool faceDimensionsMatch = intervalsEqual(minC1, maxC1, minC2, maxC2)
        && intervalsEqual(minD1, maxD1, minD2, maxD2);
    return faceTouching && faceDimensionsMatch;
}

bool areAdjacentWithMatchingFace(const AABB& a, const AABB& b) {
    return isFaceAdjacent(a.minX, a.maxX, b.minX, b.maxX, a.minY, a.maxY, b.minY, b.maxY, a.minZ, a.maxZ, b.minZ, b.maxZ)
        || isFaceAdjacent(a.minY, a.maxY, b.minY, b.maxY, a.minX, a.maxX, b.minX, b.maxX, a.minZ, a.maxZ, b.minZ, b.maxZ)
        || isFaceAdjacent(a.minZ, a.maxZ, b.minZ, b.maxZ, a.minX, a.maxX, b.minX, b.maxX, a.minY, a.maxY, b.minY, b.maxY);
}

void validateContinuity(const std::vector<AABB>& prisms) {
    for (std::size_t i = 1; i < prisms.size(); ++i) {
        const AABB& previous = prisms[i - 1];
        const AABB& current = prisms[i];

        // 隣接判定は「面で接する」ことに加えて、接続面の寸法が一致することを要求する。
        if (!areAdjacentWithMatchingFace(previous, current)) {
            throw std::invalid_argument(
                "Prisms must be connected by matching faces with the same dimensions and aligned centers"
            );
        }
    }
}

} // namespace

/**
 * @brief 面同士が連続する直方体列から連続角柱を初期化する。
 */
ContinuousRectangularPrism::ContinuousRectangularPrism(const std::vector<AABB>& prisms_) : prisms(prisms_) {
    if (prisms.size() < 2) {
        throw std::invalid_argument("ContinuousRectangularPrism requires at least 2 prisms");
    }
    validateContinuity(prisms);
}

/**
 * @brief 連結された直方体列を返す。
 */
const std::vector<AABB>& ContinuousRectangularPrism::getPrisms() const {
    return prisms;
}

/**
 * @brief 連続角柱全体を包含する軸平行境界ボックスを返す。
 */
AABB ContinuousRectangularPrism::getAABB() const {
    double minX = std::numeric_limits<double>::infinity();
    double minY = std::numeric_limits<double>::infinity();
    double minZ = std::numeric_limits<double>::infinity();
    double maxX = -std::numeric_limits<double>::infinity();
    double maxY = -std::numeric_limits<double>::infinity();
    double maxZ = -std::numeric_limits<double>::infinity();

    // 各直方体の境界を集約して全体の外接AABBを構成する。
    for (const auto& prism : prisms) {
        minX = std::min(minX, prism.minX);
        minY = std::min(minY, prism.minY);
        minZ = std::min(minZ, prism.minZ);
        maxX = std::max(maxX, prism.maxX);
        maxY = std::max(maxY, prism.maxY);
        maxZ = std::max(maxZ, prism.maxZ);
    }

    return AABB(minX, minY, minZ, maxX, maxY, maxZ);
}

} // namespace fastgeom3d
