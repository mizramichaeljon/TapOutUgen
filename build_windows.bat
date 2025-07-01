@echo off
setlocal

:: Set these once before building
set SC_PATH=
set SHARED_RINGBUFFER_PATH=

echo Cleaning...
rmdir /s /q build >nul 2>&1

echo Building...
mkdir build
cd build
cmake .. -DSC_PATH=%SC_PATH% -DSHARED_RINGBUFFER_PATH=%SHARED_RINGBUFFER_PATH%
cmake --build .

echo ✅ Done. Plugin is in build\Plugins
endlocal
