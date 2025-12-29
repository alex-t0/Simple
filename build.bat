cmake -S . -B build/cmake_ms_debug -G "Visual Studio 18 2026"
cmake --build build/cmake_ms_debug --config Debug --parallel 8

cmake -S . -B build/cmake_ms_release -G "Visual Studio 18 2026"
cmake --build build/cmake_ms_release --config Release --parallel 8

cmake -S . -B build/cmake_gcc_debug -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=g++
cmake --build build/cmake_gcc_debug --config Debug --parallel 8

cmake -S . -B build/cmake_gcc_release -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=g++
cmake --build build/cmake_gcc_release --config Release --parallel 8

rem cmake -S . -B build/cmake_clang_debug -G "Ninja" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=clang-standalone.cmake
cmake -S . -B build/cmake_clang_debug -G "Visual Studio 18 2026" -T ClangCL -A x64
cmake --build build/cmake_clang_debug --config Debug --parallel 8

rem cmake -S . -B build/cmake_clang_release -G "Ninja" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=clang-standalone.cmake
cmake -S . -B build/cmake_clang_release -G "Visual Studio 18 2026" -T ClangCL -A x64
cmake --build build/cmake_clang_release --config Release --parallel 8

pause
