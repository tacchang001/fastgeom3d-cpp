#ifndef FASTGEOM3D_VEC3_H
#define FASTGEOM3D_VEC3_H

namespace fastgeom3d {

struct UTMCoordinate;

struct Vec3 {
    const double x;
    const double y;
    const double z;

    Vec3(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

    static Vec3 fromUTM(const UTMCoordinate& utm);
    static Vec3 fromLatLon(double latitude, double longitude, double elevation);

    Vec3 add(const Vec3& o) const {
        return Vec3(x + o.x, y + o.y, z + o.z);
    }

    Vec3 sub(const Vec3& o) const {
        return Vec3(x - o.x, y - o.y, z - o.z);
    }

    double dot(const Vec3& o) const {
        return x * o.x + y * o.y + z * o.z;
    }

    double lengthSquared() const {
        return x * x + y * y + z * z;
    }
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_VEC3_H
