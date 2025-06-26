@echo off
echo Cleaning...
rmdir /s /q build
echo Building...
mkdir build
cd build
cmake .. -DSC_PATH=C:/path/to/supercollider -DSHARED_RINGBUFFER_PATH=C:/path/to/shared-ringbuffer
cmake --build .
echo Done. Plugin is in build/Plugins/
pause
