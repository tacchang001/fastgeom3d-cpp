#include <gtest/gtest.h>
#include "fastgeom3d/core.h"
#include <cmath>
#include <limits>
#include <numbers>

using namespace fastgeom3d;

// 単位立方体の体積ユーティリティが1を返すことを確認する。
TEST(FastGeom3DTests, VolumeOfUnitCube) {
    EXPECT_DOUBLE_EQ(volumeOfUnitCube(), 1.0); // 単位立方体の体積は1.0
}

// 3D距離ユーティリティが代表的な距離を正しく返すことを確認する。
TEST(FastGeom3DTests, Distance3D) {
    EXPECT_DOUBLE_EQ(distance3D(0.0, 0.0, 0.0, 1.0, 2.0, 2.0), 3.0); // (0,0,0)から(1,2,2)までの距離
    EXPECT_DOUBLE_EQ(distance3D(1.0, 1.0, 1.0, 1.0, 1.0, 1.0), 0.0); // 同じ点間の距離
    EXPECT_DOUBLE_EQ(distance3D(0.0, 0.0, 0.0, 3.0, 4.0, 0.0), 5.0); // (0,0,0)から(3,4,0)までの距離
}

// GCCでlong doubleの有効ビット数がdoubleより大きい環境では巨大座標の差分を保持できることを確認する。
TEST(FastGeom3DTests, GccExtendedPrecisionLongDoubleCanRepresentLargeCoordinateOffsets) {
    constexpr long double baseX = 10000000000000000.0L;
    constexpr long double exactOffset = 2.25L;
    constexpr long double tangentDistance = 2.0L;

    const long double exactSeparation = (baseX + exactOffset) - baseX;
    const int doubleDigits = std::numeric_limits<double>::digits;
    const int longDoubleDigits = std::numeric_limits<long double>::digits;

    EXPECT_GE(longDoubleDigits, doubleDigits);

    if (longDoubleDigits > doubleDigits) {
        EXPECT_GT(exactSeparation, tangentDistance);
    } else {
        GTEST_SKIP() << "This diagnostic targets GCC builds where long double has more precision than double.";
    }
}

// 軸方向の三角関数でも厳密なゼロにならないことがあり、libm差が境界判定へ影響しうることを確認する。
TEST(FastGeom3DTests, TrigonometricAxisValuesCanHaveTinyResiduals) {
    volatile long double halfPi = std::numbers::pi_v<long double> / 2.0L;
    volatile long double pi = std::numbers::pi_v<long double>;

    const long double cosineAtHalfPi = std::cos(halfPi);
    const long double sineAtPi = std::sin(pi);

    EXPECT_NE(cosineAtHalfPi, 0.0L);
    EXPECT_NE(sineAtPi, 0.0L);
    EXPECT_LT(std::abs(cosineAtHalfPi), 1.0e-18L);
    EXPECT_LT(std::abs(sineAtPi), 1.0e-18L);
}
