# Simple Soft Renderer

## \*NIX

```bash
git clone --recurse-submodules -j4 https://github.com/ZhiruiLi/renderer.git
cd renderer
./init.sh
# Build
cd build
make -j10
# Run
cd src
./renderer.app/Contents/MacOS/renderer
```

## Windows

```bat
git clone --recurse-submodules -j4 https://github.com/ZhiruiLi/renderer.git
rem Use CMake GUI to generate VS project files
rem Open .sln file in build folder
```
