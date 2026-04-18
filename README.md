# fastgeom3d-cpp

## ビルド手順

1. `mkdir -p build`
2. `cd build`
3. `cmake -G "Unix Makefiles" ..`
4. `cmake --build .`
5. `ctest --output-on-failure`

## クリーン手順

- ビルド出力をクリーンする
  - `cd build`
  - `cmake --build . --target clean`

- ビルドディレクトリごと削除する（完全クリーン）
  - `cd ..`
  - `rm -rf build`

## テスト

- `ctest --output-on-failure`