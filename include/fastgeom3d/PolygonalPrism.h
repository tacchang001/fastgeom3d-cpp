#ifndef FASTGEOM3D_POLYGONALPRISM_H
#define FASTGEOM3D_POLYGONALPRISM_H

#include "fastgeom3d/Prism.h"
#include "fastgeom3d/Polygon2D.h"

namespace fastgeom3d {

class PolygonalPrism : public Prism {
public:
    PolygonalPrism(const std::vector<Vec2>& vertices, double height) :
        Prism(Polygon2D(vertices), height), base(vertices) {}

    const Polygon2D& getBase() const {
        return base;
    }

private:
    const Polygon2D base;
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_POLYGONALPRISM_H
