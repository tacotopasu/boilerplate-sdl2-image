@echo off
setlocal

echo Building Project...

REM Setting the vcpkg toolchain file automatically, should be adjusted if vcpkg is installed elsewhere
set "VCPKG_TOOLCHAIN_FILE=%USERPROFILE%\vcpkg\scripts\buildsystems\vcpkg.cmake"

if not exist build (
    mkdir build
)

cmake -B build -S . ^
  -DCMAKE_BUILD_TYPE=Debug ^
  -DCMAKE_TOOLCHAIN_FILE=%VCPKG_TOOLCHAIN_FILE%

cmake --build build

echo Build complete.
pause
