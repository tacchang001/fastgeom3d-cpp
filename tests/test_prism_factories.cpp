#include <gtest/gtest.h>
#include "fastgeom3d/prisms.h"

using namespace fastgeom3d;

TEST(PrismFactoryTests, TriangularPrismFactory) {
    TriangularPrism prism = makeTriangularPrism({
        Vec2(0.0, 0.0), Vec2(1.0, 0.0), Vec2(0.0, 1.0)
    }, 2.0);
    EXPECT_EQ(prism.getBase().getVertices().size(), 3);
    EXPECT_DOUBLE_EQ(prism.getHeight(), 2.0);
}

TEST(PrismFactoryTests, QuadrilateralPrismFactory) {
    QuadrilateralPrism prism = makeQuadrilateralPrism({
        Vec2(0.0, 0.0), Vec2(2.0, 0.0), Vec2(2.0, 1.0), Vec2(0.0, 1.0)
    }, 3.0);
    EXPECT_EQ(prism.getBase().getVertices().size(), 4);
    EXPECT_DOUBLE_EQ(prism.getHeight(), 3.0);
}