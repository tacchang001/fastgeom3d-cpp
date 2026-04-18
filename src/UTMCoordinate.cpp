#include "fastgeom3d/UTMCoordinate.h"
#include "fastgeom3d/Vec3.h"
#include <cmath>
#include <numbers>

namespace fastgeom3d {

namespace {

constexpr double kRadiansPerDegree = std::numbers::pi_v<double> / 180.0;

} // namespace

/**
 * @brief UTM座標をゾーン、半球、平面座標、高度から初期化する。
 */
UTMCoordinate::UTMCoordinate(int zoneNumber_, bool northernHemisphere_, double easting_, double northing_, double elevation_) :
    zoneNumber(zoneNumber_), northernHemisphere(northernHemisphere_),
    easting(easting_), northing(northing_), elevation(elevation_) {
    if (zoneNumber_ < 1 || zoneNumber_ > 60) {
        throw std::invalid_argument("UTM zone number must be between 1 and 60");
    }
}

/**
 * @brief UTM座標を3次元ベクトルへ変換する。
 */
Vec3 UTMCoordinate::toVec3() const {
    return Vec3(easting, northing, elevation);
}

/**
 * @brief 緯度経度からWGS84ベースのUTM座標を生成する。
 */
UTMCoordinate UTMCoordinate::fromLatLon(double latitude, double longitude, double elevation) {
    if (latitude < -80.0 || latitude > 84.0) {
        throw std::invalid_argument("Latitude must be between -80 and 84 degrees for UTM");
    }

    int zoneNumber = static_cast<int>(std::floor((longitude + 180.0) / 6.0)) + 1;
    if (zoneNumber < 1) {
        zoneNumber = 1;
    } else if (zoneNumber > 60) {
        zoneNumber = 60;
    }

    const bool northernHemisphere = latitude >= 0.0;
    const double latRad = latitude * kRadiansPerDegree;
    const double lonRad = longitude * kRadiansPerDegree;
    const double centralMeridian = (-183.0 + zoneNumber * 6.0) * kRadiansPerDegree;

    const double a = 6378137.0;
    const double f = 1.0 / 298.257223563;
    const double k0 = 0.9996;
    const double e2 = f * (2.0 - f);
    const double ePrime2 = e2 / (1.0 - e2);

    const double n = a / std::sqrt(1.0 - e2 * std::sin(latRad) * std::sin(latRad));
    const double t = std::tan(latRad) * std::tan(latRad);
    const double c = ePrime2 * std::cos(latRad) * std::cos(latRad);
    const double aLon = std::cos(latRad) * (lonRad - centralMeridian);

    // 子午線弧長を高次項まで含めて近似し、ゾーン中央子午線からの展開へ使う。
    const double m = a * ((1.0 - e2 / 4.0 - 3.0 * e2 * e2 / 64.0 - 5.0 * e2 * e2 * e2 / 256.0) * latRad
        - (3.0 * e2 / 8.0 + 3.0 * e2 * e2 / 32.0 + 45.0 * e2 * e2 * e2 / 1024.0) * std::sin(2.0 * latRad)
        + (15.0 * e2 * e2 / 256.0 + 45.0 * e2 * e2 * e2 / 1024.0) * std::sin(4.0 * latRad)
        - (35.0 * e2 * e2 * e2 / 3072.0) * std::sin(6.0 * latRad));

    // 東西方向は中央子午線からの経度差を奇数次まで展開して算出する。
    const double easting = k0 * n * (aLon + (1.0 - t + c) * std::pow(aLon, 3) / 6.0
        + (5.0 - 18.0 * t + t * t + 72.0 * c - 58.0 * ePrime2) * std::pow(aLon, 5) / 120.0)
        + 500000.0;

    // 南北方向は子午線弧長に経度差の偶数次補正を加えて求める。
    double northing = k0 * (m + n * std::tan(latRad) * (aLon * aLon / 2.0
        + (5.0 - t + 9.0 * c + 4.0 * c * c) * std::pow(aLon, 4) / 24.0
        + (61.0 - 58.0 * t + t * t + 600.0 * c - 330.0 * ePrime2) * std::pow(aLon, 6) / 720.0));

    if (!northernHemisphere) {
        northing += 10000000.0;
    }

    return UTMCoordinate(zoneNumber, northernHemisphere, easting, northing, elevation);
}

} // namespace fastgeom3d
