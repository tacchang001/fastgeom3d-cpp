# Cross-Platform Floating-Point Investigation

## 結論

前提を次のように固定しても、Windows と Linux で結果が異なる可能性は残る。

- コンパイラは両方とも GCC
- `long double` は両方とも `double` より高精度
- Intel CPU の拡張精度を使うようにコンパイルする

この条件下では、主因は `long double` の精度差ではなく、次の差に移る。

- C ランタイム / `libm` の `sin`, `cos`, `sqrt`, `pow`, `fmod` の最終丸め
- 境界値を許容誤差なしで比較する実装
- `long double` から `double` へ落とす箇所の丸め

このリポジトリでは、特に次の 3 系統が差異源になりやすい。

1. 三角関数や `pow` の最終丸め差
2. 計算結果に対する厳密な `==` 比較
3. `double` 固定 API に入れる直前の丸め

## 現在の Windows 環境で確認した値

現在の環境では、一時的な C++ プローブで次を確認した。

- `sizeof(double) = 8`
- `sizeof(long double) = 16`
- `std::numeric_limits<double>::digits = 53`
- `std::numeric_limits<long double>::digits = 64`
- `cos(pi/2) = 6.12323399573676603587e-17`
- `sin(pi) = 1.22464679914735320717e-16`
- `fmod(-0.0, 2*pi) = -0.0`

このため、現在の Windows + Cygwin GCC 環境では `long double` は `double` より高精度であり、今回の追加条件には合致している。

さらに、`-mfpmath=387` を付けた一時プローブでは次も確認した。

- `cos(pi/2) = -2.50827880633416601173e-20`
- `sin(pi) = -5.01655761266833202345e-20`

つまり、GCC 統一かつ拡張精度を使っても、軸方向の三角関数は厳密なゼロではなく微小残差を返す。

## 実例 1: 三角関数の最終丸め差

対象コード:

- [src/AnnularSector2D.cpp](src/AnnularSector2D.cpp)
- [src/Intersections.cpp](src/Intersections.cpp)

`AnnularSector2D::getAABB()` では `sin` / `cos` を使って AABB を作っている。`Intersections::intersect(const Circle2D&, const Ellipse2D&)` でも、円周サンプル生成に `sin` / `cos` を使っている。

たとえば理論上は `cos(pi/2) = 0` だが、実際には 0 にならず、ごく小さい誤差を持つことがある。今回の Windows GCC 環境でも `cos(pi/2)` は `-2.5e-20` 程度だった。

この差が影響する理由は、次のように閾値を誤差なしで比較している箇所があるためである。

```cpp
return dx * dx + dy * dy <= 1.0;
```

境界に非常に近い円・楕円配置では、Windows と Linux の `libm` の最終 1 ULP の違いだけで `true` / `false` が入れ替わる可能性がある。

この性質は [tests/test_fastgeom3d.cpp](tests/test_fastgeom3d.cpp) の診断テストで、`cos(pi/2)` と `sin(pi)` が厳密なゼロではないこととして記録している。

## 実例 2: 厳密な == 比較

対象コード:

- [src/AABB.cpp](src/AABB.cpp)
- [src/ContinuousRectangularPrism.cpp](src/ContinuousRectangularPrism.cpp)

`AABB::operator==` は各座標をそのまま `==` で比較している。

```cpp
return minX == other.minX && minY == other.minY && minZ == other.minZ &&
       maxX == other.maxX && maxY == other.maxY && maxZ == other.maxZ;
```

また `ContinuousRectangularPrism` では隣接判定でも `==` を使っている。

```cpp
return minA == minB && maxA == maxB;
```

もし AABB が三角関数や地理変換など計算結果から作られていれば、Windows と Linux の丸め差により「本来同じつもりの値」が最後の 1 bit だけ異なり、`==` が失敗する可能性がある。

## 実例 3: double 固定 API へ落とす直前の丸め

対象コード: [tests/test_fastgeom3d.cpp](tests/test_fastgeom3d.cpp)

`1e16 + 2.25` のような値は、`double` では `1e16 + 2.0` に丸め込まれることがある。一方、`long double` の精度が `double` より高い環境では `2.25` を維持できる。

この差は、巨大座標の円どうしの接触/非交差判定にそのまま影響する。

実際に今のテスト群には [tests/test_intersections.cpp](tests/test_intersections.cpp) に、巨大座標では `double` 丸めにより幾何判定が変わりうる例がある。ここで効いているのは Linux / Windows の違いより、`long double` で計算した参照値を最終的に `double` API へ落とすことである。

## 実例 4: UTM 変換

対象コード: [src/UTMCoordinate.cpp](src/UTMCoordinate.cpp)

`UTMCoordinate::fromLatLon()` は `sin`, `cos`, `tan`, `sqrt`, `pow` を複数回組み合わせている。こうした式は各演算の丸め誤差が蓄積しやすく、`libm` や最適化設定が異なると最終結果も少しずれる。

現状の [tests/test_utm.cpp](tests/test_utm.cpp) は広い範囲チェックしかしていないので OS 差では壊れにくいが、将来 `EXPECT_DOUBLE_EQ` で東西・北方向座標を固定するとクロスプラットフォームで不安定になりやすい。

## 実務上の判断

GCC を両 OS で使い、`long double` も両方で拡張精度に寄せる前提なら、このリポジトリで Windows / Linux 差が起きやすい順は次の通り。

1. `sin`, `cos`, `pow`, `sqrt`, `fmod` を使う境界判定
2. 計算結果への厳密な `==` 比較
3. `double` 固定 API に入る直前の丸め

逆に、整数値や定数の単純代入、比較的単純な加減乗除だけなら差は出にくい。

## 推奨

- クロスプラットフォームで安定させたい比較は `EXPECT_NEAR` や許容誤差付き比較へ寄せる
- `AABB::operator==` や隣接判定のような `==` は、用途に応じて許容誤差版 API を別途検討する
- `long double` を参照値に使うテストは、GCC 拡張精度が有効な条件を明示する