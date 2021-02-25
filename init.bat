git submodule update --init --recursive
if not exist ".\build" mkdir build
cd build && cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DPACKAGE_TESTS=OFF .. -G "Visual Studio 15 2017"

pause
