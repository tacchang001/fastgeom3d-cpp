# fastgeom3d-cpp

## ビルド手順

1. `mkdir -p build`
2. `cd build`
3. `cmake -G "Unix Makefiles" ..`
4. `cmake --build .`
5. `ctest --output-on-failure`

## 推奨 include

新規コードでは `fastgeom3d/fastgeom3d.h` の一括 include ではなく、用途別の集約ヘッダを使ってください。`fastgeom3d/fastgeom3d.h` は既存コード互換のため引き続き利用できますが、段階的な移行先は以下です。

```cpp
#include "fastgeom3d/core.h"        // Vec2, Vec3, AABB, Shape2D, Shape3D
#include "fastgeom3d/shapes2d.h"    // Circle2D, Polygon2D, Triangle2D など
#include "fastgeom3d/prisms.h"      // Prism, Cylinder, TriangularPrism など
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