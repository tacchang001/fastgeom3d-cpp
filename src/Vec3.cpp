#include "fastgeom3d/Vec3.h"
#include "fastgeom3d/UTMCoordinate.h"

namespace fastgeom3d {

/**
 * @brief 3次元ベクトルを直交座標成分から初期化する。
 */
Vec3::Vec3(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

/**
 * @brief UTM座標を3次元ベクトルへ変換する。
 */
Vec3 Vec3::fromUTM(const UTMCoordinate& utm) {
    return utm.toVec3();
}

/**
 * @brief 緯度経度をUTM経由で3次元ベクトルへ変換する。
 */
Vec3 Vec3::fromLatLon(double latitude, double longitude, double elevation) {
    return UTMCoordinate::fromLatLon(latitude, longitude, elevation).toVec3();
}

/**
 * @brief 他方のベクトルとの成分ごとの和を返す。
 */
Vec3 Vec3::add(const Vec3& o) const {
    return Vec3(x + o.x, y + o.y, z + o.z);
}

/**
 * @brief 他方のベクトルとの差を成分ごとに計算して返す。
 */
Vec3 Vec3::sub(const Vec3& o) const {
    return Vec3(x - o.x, y - o.y, z - o.z);
}

/**
 * @brief 他方のベクトルとの内積を計算する。
 */
double Vec3::dot(const Vec3& o) const {
    return x * o.x + y * o.y + z * o.z;
}

/**
 * @brief ユークリッド長の二乗を計算する。
 */
double Vec3::lengthSquared() const {
    return x * x + y * y + z * z;
}

} // namespace fastgeom3d