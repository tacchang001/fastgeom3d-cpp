#include "fastgeom3d/UTMCoordinate.h"
#include "fastgeom3d/Vec3.h"
#include <cmath>

namespace fastgeom3d {

UTMCoordinate::UTMCoordinate(int zoneNumber_, bool northernHemisphere_, double easting_, double northing_, double elevation_) :
    zoneNumber(zoneNumber_), northernHemisphere(northernHemisphere_),
    easting(easting_), northing(northing_), elevation(elevation_) {
    if (zoneNumber_ < 1 || zoneNumber_ > 60) {
        throw std::invalid_argument("UTM zone number must be between 1 and 60");
    }
}

Vec3 UTMCoordinate::toVec3() const {
    return Vec3(easting, northing, elevation);
}

UTMCoordinate UTMCoordinate::fromLatLon(double latitude, double longitude, double elevation) {
    // latitude: 緯度 (度単位)
    // longitude: 経度 (度単位)
    // elevation: 高度 (メートル単位)
    if (latitude < -80.0 || latitude > 84.0) {
        throw std::invalid_argument("Latitude must be between -80 and 84 degrees for UTM");
    }

    int zoneNumber = static_cast<int>(std::floor((longitude + 180.0) / 6.0)) + 1; // UTMゾーン番号の計算
    if (zoneNumber < 1) {
        zoneNumber = 1;
    } else if (zoneNumber > 60) {
        zoneNumber = 60;
    }

    bool northernHemisphere = latitude >= 0.0; // 北半球かどうか
    double latRad = latitude * M_PI / 180.0; // 緯度をラジアンに変換
    double lonRad = longitude * M_PI / 180.0; // 経度をラジアンに変換
    double centralMeridian = (-183.0 + zoneNumber * 6.0) * M_PI / 180.0; // 中央子午線

    double a = 6378137.0; // WGS84楕円体の長半径
    double f = 1.0 / 298.257223563; // 扁平率
    double k0 = 0.9996; // 縮尺係数
    double e2 = f * (2.0 - f); // 第一離心率の二乗
    double ePrime2 = e2 / (1.0 - e2); // 第二離心率の二乗

    double n = a / std::sqrt(1.0 - e2 * std::sin(latRad) * std::sin(latRad)); // 卯酉線曲率半径
    double t = std::tan(latRad) * std::tan(latRad); // tan^2(lat)
    double c = ePrime2 * std::cos(latRad) * std::cos(latRad); // e'^2 * cos^2(lat)
    double aLon = std::cos(latRad) * (lonRad - centralMeridian); // 中央子午線からの経度差

    double m = a * ((1.0 - e2 / 4.0 - 3.0 * e2 * e2 / 64.0 - 5.0 * e2 * e2 * e2 / 256.0) * latRad
        - (3.0 * e2 / 8.0 + 3.0 * e2 * e2 / 32.0 + 45.0 * e2 * e2 * e2 / 1024.0) * std::sin(2.0 * latRad)
        + (15.0 * e2 * e2 / 256.0 + 45.0 * e2 * e2 * e2 / 1024.0) * std::sin(4.0 * latRad)
        - (35.0 * e2 * e2 * e2 / 3072.0) * std::sin(6.0 * latRad)); // 子午線弧長

    double easting = k0 * n * (aLon + (1.0 - t + c) * std::pow(aLon, 3) / 6.0
        + (5.0 - 18.0 * t + t * t + 72.0 * c - 58.0 * ePrime2) * std::pow(aLon, 5) / 120.0)
        + 500000.0; // 東方向座標

    double northing = k0 * (m + n * std::tan(latRad) * (aLon * aLon / 2.0
        + (5.0 - t + 9.0 * c + 4.0 * c * c) * std::pow(aLon, 4) / 24.0
        + (61.0 - 58.0 * t + t * t + 600.0 * c - 330.0 * ePrime2) * std::pow(aLon, 6) / 720.0)); // 北方向座標

    if (!northernHemisphere) {
        northing += 10000000.0; // 南半球の場合オフセット
    }

    return UTMCoordinate(zoneNumber, northernHemisphere, easting, northing, elevation);
}

} // namespace fastgeom3d
