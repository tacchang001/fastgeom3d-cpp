#include "fastgeom3d/Polyline.h"
#include "fastgeom3d/AABB.h"
#include "fastgeom3d/UTMCoordinate.h"
#include <stdexcept>

namespace fastgeom3d {

/**
 * @brief 3次元ポリラインを順序付き点列から初期化する。
 */
Polyline::Polyline(const std::vector<Vec3>& points_) : points(points_) {
    if (points.size() < 2) {
        throw std::invalid_argument("Polyline requires at least 2 points");
    }
}

/**
 * @brief ポリラインの制御点列を返す。
 */
const std::vector<Vec3>& Polyline::getPoints() const {
    return points;
}

/**
 * @brief UTM座標列をVec3へ変換してポリラインを生成する。
 */
Polyline Polyline::fromUTM(const std::vector<UTMCoordinate>& utmPoints) {
    std::vector<Vec3> points;
    points.reserve(utmPoints.size());

    // 変換結果を順序通りに積み上げて、元の折れ線の接続関係を保つ。
    for (const auto& utm : utmPoints) {
        points.push_back(utm.toVec3());
    }
    return Polyline(points);
}

/**
 * @brief ポリラインを包含する軸平行境界ボックスを返す。
 */
AABB Polyline::getAABB() const {
    return AABB::fromPoints(points);
}

} // namespace fastgeom3d
