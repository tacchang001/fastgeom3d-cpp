# fastgeom3d-cpp

## ビルド手順

1. `mkdir -p build`
2. `cd build`
3. `cmake -G "Unix Makefiles" ..`
4. `cmake --build .`
5. `ctest --output-on-failure`

## 推奨 include

公開 API は用途別の集約ヘッダを使ってください。代表的な入口は以下です。

```cpp
#include "fastgeom3d/core.h"        // Vec2, Vec3, AABB
#include "fastgeom3d/shapes2d.h"    // Circle2D, Polygon2D, Triangle2D など
#include "fastgeom3d/prisms.h"      // PolygonalPrism, Cylinder, TriangularPrism など
#include "fastgeom3d/shapes3d.h"    // Sphere, Polyline, ContinuousRectangularPrism など
#include "fastgeom3d/geodesy.h"     // UTMCoordinate
#include "fastgeom3d/algorithms.h"  // Intersections
```

必要なものが少ない場合は、集約ヘッダではなく個別ヘッダを直接 include しても構いません。

## クリーン手順

- ビルド出力をクリーンする
  - `cd build`
  - `cmake --build . --target clean`

- ビルドディレクトリごと削除する（完全クリーン）
  - `cd ..`
  - `rm -rf build`

## テスト

- `ctest --output-on-failure`