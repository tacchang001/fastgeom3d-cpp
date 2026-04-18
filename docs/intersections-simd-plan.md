# Intersections SIMD Optimization Plan

## Goal

`Intersections.cpp` のうち、分岐が少なく同じ計算を大量に繰り返す箇所を優先して SIMD 化し、交差判定全体のスループットを改善する。

## Priority

### 1. Circle vs Ellipse Sampling

対象: [src/Intersections.cpp](src/Intersections.cpp)

`Intersections::intersect(const Circle2D&, const Ellipse2D&)` は円周上の固定サンプル点を 32 個評価する。各サンプルで行う処理は同形で、次の式の繰り返しになる。

```text
sampleX = centerX + radius * cos(theta)
sampleY = centerY + radius * sin(theta)
dx = (sampleX - ellipseCenterX) / radiusX
dy = (sampleY - ellipseCenterY) / radiusY
inside = dx*dx + dy*dy <= 1
```

このループは SIMD 化しやすい。今回のリファクタでは、単位円サンプルテーブルとスカラー評価ヘルパーへ分離し、将来 AVX2/AVX-512 実装へ差し替えやすい形にした。

### 2. Batched AABB Filtering

対象: `intersectionType(const AABB&, const AABB&)` を多数候補向けに拡張した内部 API

単体の AABB 判定は軽量すぎて SIMD 効果が薄いが、1 個のクエリに対して多数の候補 AABB をふるい落とす処理では SIMD 化の効果が大きい。実装するなら AoS ではなく、以下の SoA が望ましい。

```text
minX[] maxX[] minY[] maxY[] minZ[] maxZ[]
```

### 3. Batched Point-in-Ellipse

対象: `pointInEllipse` を多数点向けへ拡張した内部 API

楕円内点判定は分岐が少なく、`Polyline2D vs Ellipse2D`、`Polygon2D vs Ellipse2D`、`Circle2D vs Ellipse2D` の複数箇所で再利用できる。SIMD 化対象として汎用性が高い。

## Lower Priority

### segmentsIntersect

`segmentsIntersect` は `pointOnSegment`、`ccw`、境界条件、早期 return を多用するため、素朴な SIMD 化は複雑になりやすい。ここはまず AABB による粗判定や辺データの前計算を優先する。

### pointInPolygon

レイキャスト法で分岐が多く、頂点列アクセスも不規則なため、直接 SIMD 化するより前処理で候補を減らす方が効果が出やすい。

## Recommended Execution Order

1. 円対楕円のサンプル評価をテーブル化して、`sin`/`cos` の都度計算を無くす
2. 円対楕円のサンプル評価に SIMD 実装を追加する
3. `intersectsAny` 系のために AABB バッチ API を内部追加する
4. 必要なら楕円内点判定のバッチ API を追加する

## Future TODO

今後の実装候補として、次の 2 点を優先タスクとして残す。

1. `circleSamplesIntersectEllipse()` に AVX2 などの SIMD 実装分岐を追加する
2. `intersectsAny` 向けに AABB バッチ判定の内部 API を追加する

## Notes

- 現在の `Vec2` は AoS なので、多数点 SIMD では SoA バッファを内部に持つ方が有利
- 単発判定より、同じクエリを多数候補へ当てる処理で SIMD 効果が出やすい
- `SIMD 化` より先に `粗判定で候補を減らす` 最適化が効く箇所も多い