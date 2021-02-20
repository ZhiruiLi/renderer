git submodule update --init --recursive
if not exist ".\build" mkdir build
cd build && cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 .. -G "Visual Studio 15 2017"

