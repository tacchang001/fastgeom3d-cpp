#include "fastgeom3d/AnnularSector2D.h"
#include "fastgeom3d/AABB.h"
#include "fastgeom3d/Vec2.h"
#include <algorithm>
#include <cmath>
#include <numbers>

namespace fastgeom3d {

namespace {

constexpr double kHalfPi = std::numbers::pi / 2.0;
constexpr double kPi = std::numbers::pi;
constexpr double kTwoPi = 2.0 * std::numbers::pi;

double normalizeAngle(double angle) {
    double normalized = std::fmod(angle, kTwoPi);
    if (normalized < 0.0) {
        normalized += kTwoPi;
    }
    return normalized;
}

Vec2 pointOnBearing(const Vec2& center, double radius, double bearing) {
    return Vec2(
        center.x + radius * std::sin(bearing),
        center.y + radius * std::cos(bearing)
    );
}

void extendBounds(double x, double y, double& minX, double& maxX, double& minY, double& maxY) {
    minX = std::min(minX, x);
    maxX = std::max(maxX, x);
    minY = std::min(minY, y);
    maxY = std::max(maxY, y);
}

template <typename AddPoint>
void addCriticalBearingIfInRange(double baseBearing, double startBearing, double endBearing, AddPoint&& addPoint) {
    double candidate = baseBearing;
    while (candidate < startBearing) {
        candidate += kTwoPi;
    }

    while (candidate <= endBearing) {
        addPoint(candidate);
        candidate += kTwoPi;
    }
}

} // namespace

class AnnularSector2D::Impl {
public:
    Impl(const Vec2& center_, double outerRadius_, double innerRadius_, double startAngle_, double endAngle_)
        : center(center_), outerRadius(outerRadius_), innerRadius(innerRadius_), startAngle(startAngle_), endAngle(endAngle_) {
        if (outerRadius_ <= 0.0 || innerRadius_ < 0.0 || outerRadius_ <= innerRadius_ || startAngle_ >= endAngle_) {
            throw std::invalid_argument("Invalid parameters for AnnularSector2D");
        }
    }

    Vec2 center;
    double outerRadius;
    double innerRadius;
    double startAngle;
    double endAngle;
};

AnnularSector2D::AnnularSector2D(const Vec2& center_, double outerRadius_, double innerRadius_, double startAngle_, double endAngle_)
    : pImpl(std::make_unique<Impl>(center_, outerRadius_, innerRadius_, startAngle_, endAngle_)) {}

AnnularSector2D::~AnnularSector2D() = default;

const Vec2& AnnularSector2D::getCenter() const {
    return pImpl->center;
}

double AnnularSector2D::getOuterRadius() const {
    return pImpl->outerRadius;
}

double AnnularSector2D::getInnerRadius() const {
    return pImpl->innerRadius;
}

double AnnularSector2D::getStartAngle() const {
    return pImpl->startAngle;
}

double AnnularSector2D::getEndAngle() const {
    return pImpl->endAngle;
}

AABB AnnularSector2D::getAABB() const {
    const double angleRange = pImpl->endAngle - pImpl->startAngle;
    const double startBearing = normalizeAngle(pImpl->startAngle);
    const double endBearing = startBearing + angleRange;

    // 初期値：中心と開始点、終了点
    double x_min = pImpl->center.x;
    double x_max = pImpl->center.x;
    double y_min = pImpl->center.y;
    double y_max = pImpl->center.y;

    // 開始点と終了点を追加
    const Vec2 startPoint = pointOnBearing(pImpl->center, pImpl->outerRadius, startBearing);
    const Vec2 endPoint = pointOnBearing(pImpl->center, pImpl->outerRadius, endBearing);

    extendBounds(startPoint.x, startPoint.y, x_min, x_max, y_min, y_max);
    extendBounds(endPoint.x, endPoint.y, x_min, x_max, y_min, y_max);

    if (pImpl->innerRadius > 0) {
        const Vec2 innerStartPoint = pointOnBearing(pImpl->center, pImpl->innerRadius, startBearing);
        const Vec2 innerEndPoint = pointOnBearing(pImpl->center, pImpl->innerRadius, endBearing);
        extendBounds(innerStartPoint.x, innerStartPoint.y, x_min, x_max, y_min, y_max);
        extendBounds(innerEndPoint.x, innerEndPoint.y, x_min, x_max, y_min, y_max);
    }

    // 地理方位系での極値: 0=北(y最大), π/2=東(x最大), π=南(y最小), 3π/2=西(x最小)
    for (double bearing : {0.0, kHalfPi, kPi, 3.0 * kHalfPi}) {
        addCriticalBearingIfInRange(bearing, startBearing, endBearing, [&](double candidate) {
            const Vec2 point = pointOnBearing(pImpl->center, pImpl->outerRadius, candidate);
            extendBounds(point.x, point.y, x_min, x_max, y_min, y_max);
        });
    }

    if (pImpl->innerRadius > 0) {
        for (double bearing : {0.0, kHalfPi, kPi, 3.0 * kHalfPi}) {
            addCriticalBearingIfInRange(bearing, startBearing, endBearing, [&](double candidate) {
                const Vec2 point = pointOnBearing(pImpl->center, pImpl->innerRadius, candidate);
                extendBounds(point.x, point.y, x_min, x_max, y_min, y_max);
            });
        }
    }

    return AABB(x_min, y_min, 0.0, x_max, y_max, 0.0);
}

} // namespace fastgeom3d