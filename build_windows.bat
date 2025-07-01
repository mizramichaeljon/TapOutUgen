@echo off
setlocal

:: === Set your paths here ===
set "SC_PATH=E:\GitHub\supercollider-source"
set "SHARED_RINGBUFFER_PATH=E:\GitHub\shared-ringbuffer"

echo Cleaning...
rmdir /s /q build >nul 2>&1

echo Building...
mkdir build
cd build
cmake .. -DSC_PATH=%SC_PATH% -DSHARED_RINGBUFFER_PATH=%SHARED_RINGBUFFER_PATH%
cmake --build . --config Release

echo ✅ Done. Plugin is in build\Plugins
endlocal
