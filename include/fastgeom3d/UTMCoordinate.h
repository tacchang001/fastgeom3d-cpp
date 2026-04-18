#ifndef FASTGEOM3D_UTMCOORDINATE_H
#define FASTGEOM3D_UTMCOORDINATE_H

#include "fastgeom3d/Vec3.h"
#include <cmath>
#include <stdexcept>

namespace fastgeom3d {

struct UTMCoordinate {
    const int zoneNumber;
    const bool northernHemisphere;
    const double easting;
    const double northing;
    const double elevation;

    UTMCoordinate(int zoneNumber_, bool northernHemisphere_, double easting_, double northing_, double elevation_) :
        zoneNumber(zoneNumber_), northernHemisphere(northernHemisphere_),
        easting(easting_), northing(northing_), elevation(elevation_) {
        if (zoneNumber_ < 1 || zoneNumber_ > 60) {
            throw std::invalid_argument("UTM zone number must be between 1 and 60");
        }
    }

    Vec3 toVec3() const;
    static UTMCoordinate fromLatLon(double latitude, double longitude, double elevation);
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_UTMCOORDINATE_H
