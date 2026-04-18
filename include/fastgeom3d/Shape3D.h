#ifndef FASTGEOM3D_SHAPE3D_H
#define FASTGEOM3D_SHAPE3D_H

namespace fastgeom3d {

class AABB;

class Shape3D {
public:
    virtual ~Shape3D() = default;
    virtual AABB getAABB() const = 0;
};

} // namespace fastgeom3d

#endif // FASTGEOM3D_SHAPE3D_H
