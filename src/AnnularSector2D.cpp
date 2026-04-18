#include "fastgeom3d/AnnularSector2D.h"
#include "fastgeom3d/AABB.h"
#include "fastgeom3d/Vec2.h"
#include <algorithm>
#include <cmath>

namespace fastgeom3d {

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
    // 角度を0-2πに正規化
    double sa = std::fmod(pImpl->startAngle, 2 * M_PI);
    if (sa < 0) sa += 2 * M_PI;
    double ea = std::fmod(pImpl->endAngle, 2 * M_PI);
    if (ea < 0) ea += 2 * M_PI;
    if (ea < sa) ea += 2 * M_PI; // 角度範囲が360度を超える場合

    double angleRange = ea - sa;

    // 初期値：中心と開始点、終了点
    double x_min = pImpl->center.x;
    double x_max = pImpl->center.x;
    double y_min = pImpl->center.y;
    double y_max = pImpl->center.y;

    // 開始点と終了点を追加
    double startX = pImpl->center.x + pImpl->outerRadius * std::cos(sa);
    double startY = pImpl->center.y + pImpl->outerRadius * std::sin(sa);
    double endX = pImpl->center.x + pImpl->outerRadius * std::cos(ea);
    double endY = pImpl->center.y + pImpl->outerRadius * std::sin(ea);

    x_min = std::min({x_min, startX, endX});
    x_max = std::max({x_max, startX, endX});
    y_min = std::min({y_min, startY, endY});
    y_max = std::max({y_max, startY, endY});

    if (pImpl->innerRadius > 0) {
        double innerStartX = pImpl->center.x + pImpl->innerRadius * std::cos(sa);
        double innerStartY = pImpl->center.y + pImpl->innerRadius * std::sin(sa);
        double innerEndX = pImpl->center.x + pImpl->innerRadius * std::cos(ea);
        double innerEndY = pImpl->center.y + pImpl->innerRadius * std::sin(ea);
        x_min = std::min({x_min, innerStartX, innerEndX});
        x_max = std::max({x_max, innerStartX, innerEndX});
        y_min = std::min({y_min, innerStartY, innerEndY});
        y_max = std::max({y_max, innerStartY, innerEndY});
    }

    // 角度範囲内でcosとsinの極値をチェック
    // xの極値：cos(theta)が最小/最大
    // theta = 0, π, sa, ea
    std::vector<double> angles = {0, M_PI, sa, ea};
    if (angleRange < 2 * M_PI) {
        // 角度範囲内でcosが最小/最大になるthetaを追加
        double cosMinTheta = std::floor(sa / M_PI) * M_PI + M_PI; // 次のπ
        if (cosMinTheta < ea) angles.push_back(cosMinTheta);
        double cosMaxTheta = std::floor(sa / M_PI) * M_PI; // 次の0
        if (cosMaxTheta < ea) angles.push_back(cosMaxTheta);
    }

    for (double theta : angles) {
        if (theta >= sa && theta <= ea) {
            double x = pImpl->center.x + pImpl->outerRadius * std::cos(theta);
            double y = pImpl->center.y + pImpl->outerRadius * std::sin(theta);
            x_min = std::min(x_min, x);
            x_max = std::max(x_max, x);
            y_min = std::min(y_min, y);
            y_max = std::max(y_max, y);
        }
    }

    // 同様にinnerRadius
    if (pImpl->innerRadius > 0) {
        for (double theta : angles) {
            if (theta >= sa && theta <= ea) {
                double x = pImpl->center.x + pImpl->innerRadius * std::cos(theta);
                double y = pImpl->center.y + pImpl->innerRadius * std::sin(theta);
                x_min = std::min(x_min, x);
                x_max = std::max(x_max, x);
                y_min = std::min(y_min, y);
                y_max = std::max(y_max, y);
            }
        }
    }

    return AABB(x_min, y_min, 0.0, x_max, y_max, 0.0);
}

} // namespace fastgeom3d