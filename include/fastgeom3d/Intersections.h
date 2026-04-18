#ifndef FASTGEOM3D_INTERSECTIONS_H
#define FASTGEOM3D_INTERSECTIONS_H

#include <vector>

namespace fastgeom3d {

class AABB;
class Circle2D;
class Ellipse2D;
class Polygon2D;
class Polyline;
class Polyline2D;
class Shape2D;
class Shape3D;
class Sphere;

/**
 * @brief 形状間の交差判定を提供するクラス。
 *
 * 様々な3Dおよび2D形状間の交差を判定する静的メソッドを提供します。
 */
class Intersections {
public:
    /**
     * @brief 交差の種類を表す列挙型。
     */
    enum class IntersectionType {
        NONE,   /**< 交差なし。 */
        OVERLAP, /**< 重なりあり。 */
        TOUCH   /**< 接している。 */
    };

    /**
     * @brief 2つのAABBが交差するかを判定します。
     *
     * @param a 最初のAABB。
     * @param b 2番目のAABB。
     * @return 交差する場合true。
     */
    static bool intersect(const AABB& a, const AABB& b);

    /**
     * @brief 2つの球が交差するかを判定します。
     *
     * @param a 最初の球。
     * @param b 2番目の球。
     * @return 交差する場合true。
     */
    static bool intersect(const Sphere& a, const Sphere& b);

    /**
     * @brief AABBと球が交差するかを判定します。
     *
     * @param box AABB。
     * @param s 球。
     * @return 交差する場合true。
     */
    static bool intersect(const AABB& box, const Sphere& s);

    /**
     * @brief 2つの3D形状が交差するかを判定します。
     *
     * @param s1 最初の3D形状。
     * @param s2 2番目の3D形状。
     * @return 交差する場合true。
     */
    static bool intersect(const Shape3D& s1, const Shape3D& s2);

    /**
     * @brief 2つの2D形状が交差するかを判定します。
     *
     * @param s1 最初の2D形状。
     * @param s2 2番目の2D形状。
     * @return 交差する場合true。
     */
    static bool intersect(const Shape2D& s1, const Shape2D& s2);

    /**
     * @brief 2つの2Dポリラインが交差するかを判定します。
     *
     * @param line 最初のポリライン。
     * @param other 2番目のポリライン。
     * @return 交差する場合true。
     */
    static bool intersect(const Polyline2D& line, const Polyline2D& other);

    /**
     * @brief 2Dポリラインと円が交差するかを判定します。
     *
     * @param line ポリライン。
     * @param circle 円。
     * @return 交差する場合true。
     */
    static bool intersect(const Polyline2D& line, const Circle2D& circle);

    /**
     * @brief 2Dポリラインと多角形が交差するかを判定します。
     *
     * @param line ポリライン。
     * @param polygon 多角形。
     * @return 交差する場合true。
     */
    static bool intersect(const Polyline2D& line, const Polygon2D& polygon);

    /**
     * @brief 2つの円が交差するかを判定します。
     *
     * @param a 最初の円。
     * @param b 2番目の円。
     * @return 交差する場合true。
     */
    static bool intersect(const Circle2D& a, const Circle2D& b);

    /**
     * @brief 多角形と円が交差するかを判定します。
     *
     * @param polygon 多角形。
     * @param circle 円。
     * @return 交差する場合true。
     */
    static bool intersect(const Polygon2D& polygon, const Circle2D& circle);

    /**
     * @brief 2つの多角形が交差するかを判定します。
     *
     * @param a 最初の多角形。
     * @param b 2番目の多角形。
     * @return 交差する場合true。
     */
    static bool intersect(const Polygon2D& a, const Polygon2D& b);

    /**
     * @brief 2Dポリラインと楕円が交差するかを判定します。
     *
     * @param line ポリライン。
     * @param ellipse 楕円。
     * @return 交差する場合true。
     */
    static bool intersect(const Polyline2D& line, const Ellipse2D& ellipse);

    /**
     * @brief 円と楕円が交差するかを判定します。
     *
     * @param circle 円。
     * @param ellipse 楕円。
     * @return 交差する場合true。
     */
    static bool intersect(const Circle2D& circle, const Ellipse2D& ellipse);

    /**
     * @brief 多角形と楕円が交差するかを判定します。
     *
     * @param polygon 多角形。
     * @param ellipse 楕円。
     * @return 交差する場合true。
     */
    static bool intersect(const Polygon2D& polygon, const Ellipse2D& ellipse);

    /**
     * @brief ポリラインが形状リストのいずれかと交差するかを判定します。
     *
     * @param line ポリライン。
     * @param shapes 形状のリスト。
     * @return いずれかと交差する場合true。
     */
    static bool intersectsAny(const Polyline& line, const std::vector<const Shape3D*>& shapes);

    /**
     * @brief 2つのポリラインが形状リストのいずれかと交差するかを判定します。
     *
     * @param line1 最初のポリライン。
     * @param line2 2番目のポリライン。
     * @param shapes 形状のリスト。
     * @return いずれかと交差する場合true。
     */
    static bool intersectsAny(const Polyline& line1, const Polyline& line2, const std::vector<const Shape3D*>& shapes);

    /**
     * @brief ポリラインのリストが形状リストのいずれかと交差するかを判定します。
     *
     * @param lines ポリラインのリスト。
     * @param shapes 形状のリスト。
     * @return いずれかと交差する場合true。
     */
    static bool intersectsAny(const std::vector<Polyline>& lines, const std::vector<const Shape3D*>& shapes);

    /**
     * @brief ポリラインと交差する形状のリストを取得します。
     *
     * @param line ポリライン。
     * @param shapes 形状のリスト。
     * @return 交差する形状のリスト。
     */
    static std::vector<const Shape3D*> intersectingShapes(const Polyline& line, const std::vector<const Shape3D*>& shapes);

    /**
     * @brief ポリラインのリストと交差する形状のリストを取得します。
     *
     * @param lines ポリラインのリスト。
     * @param shapes 形状のリスト。
     * @return 交差する形状のリスト。
     */
    static std::vector<const Shape3D*> intersectingShapes(const std::vector<Polyline>& lines, const std::vector<const Shape3D*>& shapes);

    /**
     * @brief 2つの3D形状の交差の種類を判定します。
     *
     * @param s1 最初の3D形状。
     * @param s2 2番目の3D形状。
     * @return 交差の種類。
     */
    static IntersectionType intersectionType(const Shape3D& s1, const Shape3D& s2);

    /**
     * @brief 2つのAABBの交差の種類を判定します。
     *
     * @param a 最初のAABB。
     * @param b 2番目のAABB。
     * @return 交差の種類。
     */
    static IntersectionType intersectionType(const AABB& a, const AABB& b);

    /**
     * @brief 2つの球の交差の種類を判定します。
     *
     * @param a 最初の球。
     * @param b 2番目の球。
     * @return 交差の種類。
     */
    static IntersectionType intersectionType(const Sphere& a, const Sphere& b);

    /**
     * @brief AABBと球の交差の種類を判定します。
     *
     * @param box AABB。
     * @param s 球。
     * @return 交差の種類。
     */
    static IntersectionType intersectionType(const AABB& box, const Sphere& s);
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_INTERSECTIONS_H
