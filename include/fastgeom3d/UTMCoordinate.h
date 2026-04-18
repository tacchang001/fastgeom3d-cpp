#ifndef FASTGEOM3D_UTMCOORDINATE_H
#define FASTGEOM3D_UTMCOORDINATE_H

#include <stdexcept>

namespace fastgeom3d {

class Vec3;

/**
 * @brief UTM (Universal Transverse Mercator) 座標を表す構造体。
 *
 * UTM座標系は、地球を60のゾーンに分け、各ゾーン内で平面座標を提供します。
 * この構造体は、UTMゾーン番号、半球、北東座標、高度を保持します。
 */
struct UTMCoordinate {
    /** @brief UTMゾーン番号 (1-60)。 */
    const int zoneNumber;
    /** @brief 北半球かどうか (true: 北半球, false: 南半球)。 */
    const bool northernHemisphere;
    /** @brief 東方向の座標 (メートル単位)。 */
    const double easting;
    /** @brief 北方向の座標 (メートル単位)。 */
    const double northing;
    /** @brief 高度 (メートル単位)。 */
    const double elevation;

    /**
     * @brief UTMCoordinateのコンストラクタ。
     *
     * @param zoneNumber_ UTMゾーン番号 (1-60)。
     * @param northernHemisphere_ 北半球かどうか。
     * @param easting_ 東方向の座標。
     * @param northing_ 北方向の座標。
     * @param elevation_ 高度。
     * @throws std::invalid_argument ゾーン番号が範囲外の場合。
     */
    UTMCoordinate(int zoneNumber_, bool northernHemisphere_, double easting_, double northing_, double elevation_);

    /**
     * @brief UTM座標をVec3に変換します。
     *
     * @return Vec3形式の座標 (x: easting, y: northing, z: elevation)。
     */
    Vec3 toVec3() const;

    /**
     * @brief 緯度、経度、高度からUTM座標を作成します。
     *
     * @param latitude 緯度 (度単位)。
     * @param longitude 経度 (度単位)。
     * @param elevation 高度 (メートル単位)。
     * @return UTMCoordinateオブジェクト。
     */
    static UTMCoordinate fromLatLon(double latitude, double longitude, double elevation);
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_UTMCOORDINATE_H
