#ifndef FASTGEOM3D_SHAPE2D_H
#define FASTGEOM3D_SHAPE2D_H

#include "fastgeom3d/Shape3D.h"

namespace fastgeom3d {

/**
 * @brief 2D形状の基底クラス。
 *
 * Shape3Dを継承し、2D形状の共通インターフェースを提供します。
 */
class Shape2D : public Shape3D {
};

/**
 * @brief Shape2DConcept: Shape2Dを継承した型かどうかを判定するコンセプト。
 *
 * @tparam T 判定する型。
 */
template <typename T>
concept Shape2DConcept = std::is_base_of_v<Shape2D, T>;

} // namespace fastgeom3d

#endif // FASTGEOM3D_SHAPE2D_H
