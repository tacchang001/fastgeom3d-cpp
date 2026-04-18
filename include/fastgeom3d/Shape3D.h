#ifndef FASTGEOM3D_SHAPE3D_H
#define FASTGEOM3D_SHAPE3D_H

#include <type_traits>

namespace fastgeom3d {

class AABB;

/**
 * @brief 3D形状の基底クラス。
 *
 * すべての3D形状が継承する抽象基底クラスで、AABBを取得するインターフェースを提供します。
 */
class Shape3D {
public:
    /** @brief 仮想デストラクタ。 */
    virtual ~Shape3D() = default;

    /**
     * @brief 形状の軸平行境界ボックス (AABB) を取得します。
     *
     * @return AABBオブジェクト。
     */
    virtual AABB getAABB() const = 0;
};

/**
 * @brief Shape3DConcept: Shape3Dを継承した型かどうかを判定するコンセプト。
 *
 * @tparam T 判定する型。
 */
template <typename T>
concept Shape3DConcept = std::is_base_of_v<Shape3D, T>;

} // namespace fastgeom3d

#endif // FASTGEOM3D_SHAPE3D_H
