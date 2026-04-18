#ifndef FASTGEOM3D_VEC3_H
#define FASTGEOM3D_VEC3_H

namespace fastgeom3d {

struct UTMCoordinate;

/**
 * @brief 3Dベクトルを表すクラス。
 *
 * x, y, zの座標を持つ3次元ベクトルです。ベクトル演算を提供します。
 */
class Vec3 {
public:
    /** @brief x座標。 */
    double x;
    /** @brief y座標。 */
    double y;
    /** @brief z座標。 */
    double z;

    /**
     * @brief Vec3のコンストラクタ。
     *
     * @param x_ x座標。
     * @param y_ y座標。
     * @param z_ z座標。
     */
    Vec3(double x_, double y_, double z_);

    /**
     * @brief UTM座標からVec3を作成します。
     *
     * @param utm UTM座標。
     * @return Vec3オブジェクト。
     */
    static Vec3 fromUTM(const UTMCoordinate& utm);

    /**
     * @brief 緯度、経度、高度からVec3を作成します。
     *
     * @param latitude 緯度 (度単位)。
     * @param longitude 経度 (度単位)。
     * @param elevation 高度 (メートル単位)。
     * @return Vec3オブジェクト。
     */
    static Vec3 fromLatLon(double latitude, double longitude, double elevation);

    /**
     * @brief ベクトルの加算を行います。
     *
     * @param o 加算するベクトル。
     * @return 加算結果のVec3。
     */
    Vec3 add(const Vec3& o) const;

    /**
     * @brief ベクトルの減算を行います。
     *
     * @param o 減算するベクトル。
     * @return 減算結果のVec3。
     */
    Vec3 sub(const Vec3& o) const;

    /**
     * @brief ベクトルの内積を計算します。
     *
     * @param o 内積を取るベクトル。
     * @return 内積の値。
     */
    double dot(const Vec3& o) const;

    /**
     * @brief ベクトルの長さの二乗を計算します。
     *
     * @return 長さの二乗。
     */
    double lengthSquared() const;
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_VEC3_H
