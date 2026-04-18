#ifndef FASTGEOM3D_CORE_H
#define FASTGEOM3D_CORE_H

#include "fastgeom3d/Vec2.h"
#include "fastgeom3d/Vec3.h"
#include "fastgeom3d/AABB.h"

namespace fastgeom3d {

/**
 * @brief 単位立方体の体積を計算します。
 *
 * @return 単位立方体の体積 (1.0)。
 */
double volumeOfUnitCube();

/**
 * @brief 3D空間における2点間の距離を計算します。
 *
 * @param x1 点1のx座標。
 * @param y1 点1のy座標。
 * @param z1 点1のz座標。
 * @param x2 点2のx座標。
 * @param y2 点2のy座標。
 * @param z2 点2のz座標。
 * @return 2点間の距離。
 */
double distance3D(double x1, double y1, double z1, double x2, double y2, double z2);

} // namespace fastgeom3d

#endif // FASTGEOM3D_CORE_H