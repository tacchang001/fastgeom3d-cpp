#include "fastgeom3d/Vec3.h"
#include "fastgeom3d/UTMCoordinate.h"

namespace fastgeom3d {

Vec3::Vec3(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

Vec3 Vec3::fromUTM(const UTMCoordinate& utm) {
    return utm.toVec3();
}

Vec3 Vec3::fromLatLon(double latitude, double longitude, double elevation) {
    return UTMCoordinate::fromLatLon(latitude, longitude, elevation).toVec3();
}

Vec3 Vec3::add(const Vec3& o) const {
    return Vec3(x + o.x, y + o.y, z + o.z);
}

Vec3 Vec3::sub(const Vec3& o) const {
    return Vec3(x - o.x, y - o.y, z - o.z);
}

double Vec3::dot(const Vec3& o) const {
    return x * o.x + y * o.y + z * o.z;
}

double Vec3::lengthSquared() const {
    return x * x + y * y + z * z;
}

} // namespace fastgeom3d