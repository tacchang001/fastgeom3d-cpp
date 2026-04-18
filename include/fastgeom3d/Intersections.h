#ifndef FASTGEOM3D_INTERSECTIONS_H
#define FASTGEOM3D_INTERSECTIONS_H

#include "fastgeom3d/AABB.h"
#include "fastgeom3d/Polygon2D.h"
#include "fastgeom3d/Vec2.h"
#include <type_traits>
#include <vector>

namespace fastgeom3d {

class Circle2D;
class Ellipse2D;
class Polyline;
class Polyline2D;
class Quadrilateral2D;
class QuadrilateralPrism;
class Sphere;
class Triangle2D;
class TriangularPrism;

template <typename T, typename = void>
struct IsAABBShape : std::false_type {};

template <typename T>
struct IsAABBShape<T, std::void_t<decltype(std::declval<const T&>().getAABB())>>
    : std::bool_constant<std::is_same_v<decltype(std::declval<const T&>().getAABB()), AABB>> {};

template <typename T>
inline constexpr bool kIsAABBShape = IsAABBShape<T>::value;

template <typename T>
inline constexpr bool kIsSupported2DShape =
    std::is_same_v<std::remove_cvref_t<T>, Circle2D> ||
    std::is_same_v<std::remove_cvref_t<T>, Ellipse2D> ||
    std::is_same_v<std::remove_cvref_t<T>, Polygon2D> ||
    std::is_same_v<std::remove_cvref_t<T>, Triangle2D> ||
    std::is_same_v<std::remove_cvref_t<T>, Quadrilateral2D> ||
    std::is_same_v<std::remove_cvref_t<T>, Polyline2D>;

template <typename T, typename = void>
struct IsPolygonLike : std::false_type {};

template <typename T>
struct IsPolygonLike<T, std::void_t<
    decltype(std::declval<const T&>().getVertices()),
    decltype(std::declval<const T&>().getAABB())>> : std::true_type {};

template <typename T>
inline constexpr bool kIsPolygonLike = IsPolygonLike<T>::value;

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
    template <typename Polygon, std::enable_if_t<kIsPolygonLike<Polygon>, int> = 0>
    static bool intersect(const Polyline2D& line, const Polygon& polygon);

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
    template <typename Polygon, std::enable_if_t<kIsPolygonLike<Polygon>, int> = 0>
    static bool intersect(const Polygon& polygon, const Circle2D& circle);

    static bool intersect(const Polygon2D& polygon, const Circle2D& circle);

    /**
     * @brief 2つの多角形が交差するかを判定します。
     *
     * @param a 最初の多角形。
     * @param b 2番目の多角形。
     * @return 交差する場合true。
     */
    template <typename PolygonA, typename PolygonB,
              std::enable_if_t<kIsPolygonLike<PolygonA> && kIsPolygonLike<PolygonB>, int> = 0>
    static bool intersect(const PolygonA& a, const PolygonB& b);

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
    template <typename Polygon, std::enable_if_t<kIsPolygonLike<Polygon>, int> = 0>
    static bool intersect(const Polygon& polygon, const Ellipse2D& ellipse);

    static bool intersect(const Polygon2D& polygon, const Ellipse2D& ellipse);

    /**
     * @brief ポリラインが形状リストのいずれかと交差するかを判定します。
     *
     * @param line ポリライン。
     * @param shapes 形状のリスト。
     * @return いずれかと交差する場合true。
     */
    template <typename Shape, std::enable_if_t<kIsAABBShape<Shape>, int> = 0>
    static bool intersectsAny(const Polyline& line, const std::vector<const Shape*>& shapes);

    /**
     * @brief 2つのポリラインが形状リストのいずれかと交差するかを判定します。
     *
     * @param line1 最初のポリライン。
     * @param line2 2番目のポリライン。
     * @param shapes 形状のリスト。
     * @return いずれかと交差する場合true。
     */
    template <typename Shape, std::enable_if_t<kIsAABBShape<Shape>, int> = 0>
    static bool intersectsAny(const Polyline& line1, const Polyline& line2, const std::vector<const Shape*>& shapes);

    /**
     * @brief ポリラインのリストが形状リストのいずれかと交差するかを判定します。
     *
     * @param lines ポリラインのリスト。
     * @param shapes 形状のリスト。
     * @return いずれかと交差する場合true。
     */
    template <typename Shape, std::enable_if_t<kIsAABBShape<Shape>, int> = 0>
    static bool intersectsAny(const std::vector<Polyline>& lines, const std::vector<const Shape*>& shapes);

    /**
     * @brief ポリラインと交差する形状のリストを取得します。
     *
     * @param line ポリライン。
     * @param shapes 形状のリスト。
     * @return 交差する形状のリスト。
     */
    template <typename Shape, std::enable_if_t<kIsAABBShape<Shape>, int> = 0>
    static std::vector<const Shape*> intersectingShapes(const Polyline& line, const std::vector<const Shape*>& shapes);

    /**
     * @brief ポリラインのリストと交差する形状のリストを取得します。
     *
     * @param lines ポリラインのリスト。
     * @param shapes 形状のリスト。
     * @return 交差する形状のリスト。
     */
    template <typename Shape, std::enable_if_t<kIsAABBShape<Shape>, int> = 0>
    static std::vector<const Shape*> intersectingShapes(const std::vector<Polyline>& lines, const std::vector<const Shape*>& shapes);

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

    template <typename ShapeA, typename ShapeB,
              std::enable_if_t<kIsAABBShape<ShapeA> && kIsAABBShape<ShapeB>, int> = 0>
    static bool intersect(const ShapeA& s1, const ShapeB& s2) {
        using First = std::remove_cvref_t<ShapeA>;
        using Second = std::remove_cvref_t<ShapeB>;

        if constexpr (kIsSupported2DShape<First> && kIsSupported2DShape<Second>) {
            if constexpr (std::is_same_v<First, Polyline2D> && std::is_same_v<Second, Polyline2D>) return intersect(s1, s2);
            if constexpr (std::is_same_v<First, Polyline2D> && std::is_same_v<Second, Circle2D>) return intersect(s1, s2);
            if constexpr (std::is_same_v<First, Circle2D> && std::is_same_v<Second, Polyline2D>) return intersect(s2, s1);
            if constexpr (std::is_same_v<First, Polyline2D> && kIsPolygonLike<Second>) return intersect(s1, s2);
            if constexpr (kIsPolygonLike<First> && std::is_same_v<Second, Polyline2D>) return intersect(s2, s1);
            if constexpr (std::is_same_v<First, Circle2D> && std::is_same_v<Second, Circle2D>) return intersect(s1, s2);
            if constexpr (kIsPolygonLike<First> && std::is_same_v<Second, Circle2D>) return intersect(s1, s2);
            if constexpr (std::is_same_v<First, Circle2D> && kIsPolygonLike<Second>) return intersect(s2, s1);
            if constexpr (kIsPolygonLike<First> && kIsPolygonLike<Second>) return intersect(s1, s2);
            if constexpr (std::is_same_v<First, Polyline2D> && std::is_same_v<Second, Ellipse2D>) return intersect(s1, s2);
            if constexpr (std::is_same_v<First, Ellipse2D> && std::is_same_v<Second, Polyline2D>) return intersect(s2, s1);
            if constexpr (std::is_same_v<First, Circle2D> && std::is_same_v<Second, Ellipse2D>) return intersect(s1, s2);
            if constexpr (std::is_same_v<First, Ellipse2D> && std::is_same_v<Second, Circle2D>) return intersect(s2, s1);
            if constexpr (kIsPolygonLike<First> && std::is_same_v<Second, Ellipse2D>) return intersect(s1, s2);
            if constexpr (std::is_same_v<First, Ellipse2D> && kIsPolygonLike<Second>) return intersect(s2, s1);
        }

        return intersect(s1.getAABB(), s2.getAABB());
    }

    template <typename ShapeA, typename ShapeB,
              std::enable_if_t<kIsAABBShape<ShapeA> && kIsAABBShape<ShapeB>, int> = 0>
    static IntersectionType intersectionType(const ShapeA& s1, const ShapeB& s2) {
        return intersectionType(s1.getAABB(), s2.getAABB());
    }

private:
    static bool intersectPolylineWithPolygonVertices(const Polyline2D& line, const std::vector<Vec2>& vertices);
    static bool intersectPolygonWithCircleVertices(const std::vector<Vec2>& vertices, const Circle2D& circle);
    static bool intersectPolygonVertices(const std::vector<Vec2>& verticesA, const std::vector<Vec2>& verticesB);
    static bool intersectPolygonWithEllipseVertices(const std::vector<Vec2>& vertices, const Ellipse2D& ellipse);
};

template <typename Shape, std::enable_if_t<kIsAABBShape<Shape>, int>>
bool Intersections::intersectsAny(const Polyline& line, const std::vector<const Shape*>& shapes) {
    for (const Shape* shape : shapes) {
        if (shape != nullptr && intersect(line, *shape)) {
            return true;
        }
    }
    return false;
}

template <typename Polygon, std::enable_if_t<kIsPolygonLike<Polygon>, int>>
bool Intersections::intersect(const Polyline2D& line, const Polygon& polygon) {
    return intersectPolylineWithPolygonVertices(line, polygon.getVertices());
}

template <typename Polygon, std::enable_if_t<kIsPolygonLike<Polygon>, int>>
bool Intersections::intersect(const Polygon& polygon, const Circle2D& circle) {
    return intersectPolygonWithCircleVertices(polygon.getVertices(), circle);
}

template <typename PolygonA, typename PolygonB, std::enable_if_t<kIsPolygonLike<PolygonA> && kIsPolygonLike<PolygonB>, int>>
bool Intersections::intersect(const PolygonA& a, const PolygonB& b) {
    return intersectPolygonVertices(a.getVertices(), b.getVertices());
}

template <typename Polygon, std::enable_if_t<kIsPolygonLike<Polygon>, int>>
bool Intersections::intersect(const Polygon& polygon, const Ellipse2D& ellipse) {
    return intersectPolygonWithEllipseVertices(polygon.getVertices(), ellipse);
}

template <typename Shape, std::enable_if_t<kIsAABBShape<Shape>, int>>
bool Intersections::intersectsAny(const Polyline& line1, const Polyline& line2, const std::vector<const Shape*>& shapes) {
    for (const Shape* shape : shapes) {
        if (shape != nullptr && (intersect(line1, *shape) || intersect(line2, *shape))) {
            return true;
        }
    }
    return false;
}

template <typename Shape, std::enable_if_t<kIsAABBShape<Shape>, int>>
bool Intersections::intersectsAny(const std::vector<Polyline>& lines, const std::vector<const Shape*>& shapes) {
    for (const Shape* shape : shapes) {
        if (shape == nullptr) {
            continue;
        }
        for (const Polyline& line : lines) {
            if (intersect(line, *shape)) {
                return true;
            }
        }
    }
    return false;
}

template <typename Shape, std::enable_if_t<kIsAABBShape<Shape>, int>>
std::vector<const Shape*> Intersections::intersectingShapes(const Polyline& line, const std::vector<const Shape*>& shapes) {
    std::vector<const Shape*> result;
    for (const Shape* shape : shapes) {
        if (shape != nullptr && intersect(line, *shape)) {
            result.push_back(shape);
        }
    }
    return result;
}

template <typename Shape, std::enable_if_t<kIsAABBShape<Shape>, int>>
std::vector<const Shape*> Intersections::intersectingShapes(const std::vector<Polyline>& lines, const std::vector<const Shape*>& shapes) {
    std::vector<const Shape*> result;
    for (const Shape* shape : shapes) {
        if (shape == nullptr) {
            continue;
        }
        for (const Polyline& line : lines) {
            if (intersect(line, *shape)) {
                result.push_back(shape);
                break;
            }
        }
    }
    return result;
}

} // namespace fastgeom3d

#endif // FASTGEOM3D_INTERSECTIONS_H
