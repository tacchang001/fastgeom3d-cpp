#ifndef FASTGEOM3D_ANNULARSECTOR2D_H
#define FASTGEOM3D_ANNULARSECTOR2D_H

#include "fastgeom3d/Shape2D.h"
#include <memory>

namespace fastgeom3d {

class Vec2;

/**
 * @brief 2D環状扇形を表すクラス。
 *
 * Shape2Dを継承し、2D空間における環状扇形（ドーナツ状の扇形）を表現します。
 */
class AnnularSector2D final : public Shape2D {
public:
    /**
     * @brief AnnularSector2Dのコンストラクタ。
     *
     * @param center_ 環状扇形の中心座標。
     * @param outerRadius_ 外側半径。正の値でなければなりません。
     * @param innerRadius_ 内側半径。0以上でouterRadius_以下でなければなりません。
     * @param startAngle_ 開始角度 (ラジアン単位)。
     * @param endAngle_ 終了角度 (ラジアン単位)。
     */
    AnnularSector2D(const Vec2& center_, double outerRadius_, double innerRadius_, double startAngle_, double endAngle_);
    
    /** @brief デストラクタ。 */
    ~AnnularSector2D();

    /** @brief コピーコンストラクタ (削除)。 */
    AnnularSector2D(const AnnularSector2D& other) = delete;
    /** @brief コピー代入演算子 (削除)。 */
    AnnularSector2D& operator=(const AnnularSector2D& other) = delete;

    /** @brief ムーブコンストラクタ。 */
    AnnularSector2D(AnnularSector2D&& other) noexcept = default;
    /** @brief ムーブ代入演算子。 */
    AnnularSector2D& operator=(AnnularSector2D&& other) noexcept = default;

    /**
     * @brief 環状扇形の中心座標を取得します。
     *
     * @return 中心座標のVec2。
     */
    const Vec2& getCenter() const;
    
    /**
     * @brief 外側半径を取得します。
     *
     * @return 外側半径の値。
     */
    double getOuterRadius() const;
    
    /**
     * @brief 内側半径を取得します。
     *
     * @return 内側半径の値。
     */
    double getInnerRadius() const;
    
    /**
     * @brief 開始角度を取得します。
     *
     * @return 開始角度 (ラジアン単位)。
     */
    double getStartAngle() const;
    
    /**
     * @brief 終了角度を取得します。
     *
     * @return 終了角度 (ラジアン単位)。
     */
    double getEndAngle() const;

    /**
     * @brief 環状扇形のAABBを取得します。
     *
     * @return 環状扇形を囲む軸平行境界ボックス。
     */
    AABB getAABB() const override;

private:
    /** @brief 実装クラスの前方宣言。 */
    class Impl;
    /** @brief PIMPLイディオムのためのポインタ。 */
    std::unique_ptr<Impl> pImpl;
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_ANNULARSECTOR2D_H