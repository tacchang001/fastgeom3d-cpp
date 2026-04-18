#include "fastgeom3d/core.h"
#include <cmath>

namespace fastgeom3d {

double volumeOfUnitCube() {
    return 1.0;
}

double distance3D(double x1, double y1, double z1, double x2, double y2, double z2) {
    const double dx = x2 - x1; // x方向の差
    const double dy = y2 - y1; // y方向の差
    const double dz = z2 - z1; // z方向の差
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

} // namespace fastgeom3d
