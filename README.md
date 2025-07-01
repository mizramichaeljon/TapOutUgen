# TapOutUgen

A SuperCollider UGen that taps an incoming signal and writes it to a shared memory ring buffer for low-latency inter-process audio sharing.

## Features

- Native SuperCollider plugin
- Mono input, passthrough output
- Uses shared memory via `boost::interprocess`
- Companion readers available (CLI, openFrameworks)

---

## Requirements

- SuperCollider **built from source**
- Boost (header-only usage)
- CMake ≥ 3.10
- A C++14-compatible compiler (Visual Studio 2022 / Xcode)
- [shared-ringbuffer](https://github.com/mizramichaeljon/shared-ringbuffer)

---

## Building SuperCollider from Source (Recommended)

To build this plugin, you must build SuperCollider from source to access its plugin headers.

### Clone SuperCollider

```cmd
git clone --recursive https://github.com/supercollider/supercollider.git <path-to-clone-supercollider-source>
```

### Configure and Build (Command Prompt, Windows)

```cmd
cd <path-to-cloned-supercollider-source>
mkdir build
cd build

cmake <path-to-supercollider-source> -G "Visual Studio 17 2022" -A x64 ^
  -DSC_IDE=OFF ^
  -DSC_QT=OFF ^
  -DSC_ED=OFF ^
  -DCMAKE_INSTALL_PREFIX=<path-to-sc-install>
```

Then build:

```cmd
cmake --build . --config Release
```

> ✅ **NOTE:** You do **not** need to run `cmake --install` unless you want to create a full install tree. The plugin uses headers from `include/plugin_interface` and `include/common`.

---

## Building on Windows

### Step 1: Install [vcpkg](https://github.com/microsoft/vcpkg)

```cmd
git clone https://github.com/microsoft/vcpkg <path-to-vcpkg>
cd <path-to-vcpkg>
bootstrap-vcpkg.bat
```

### Step 2: Install Boost (header-only use)

```cmd
vcpkg install boost
```

---

### Step 3: Build TapOutUgen Plugin

#### Clone dependencies

```cmd
git clone https://github.com/mizramichaeljon/shared-ringbuffer.git <path-to-shared-ringbuffer>
git clone https://github.com/mizramichaeljon/TapOutUgen.git <path-to-TapOutUgen>
```

#### Build plugin:

```cmd
cd <path-to-TapOutUgen>
mkdir build
cd build

cmake .. -G "Visual Studio 17 2022" -A x64 ^
  -DSC_PATH=<path-to-supercollider-source> ^
  -DSHARED_RINGBUFFER_PATH=<path-to-shared-ringbuffer> ^
  -DCMAKE_TOOLCHAIN_FILE=<path-to-vcpkg>/scripts/buildsystems/vcpkg.cmake

cmake --build . --config Release
```

This will output the compiled plugin to:

```
<path-to-TapOutUgen>\build\Plugins\TapOut.scx
```

---

## Building on macOS

### Step 1: Install dependencies

Install [Homebrew](https://brew.sh) if you haven’t already, then:

```bash
brew install cmake boost
```

### Step 2: Clone dependencies

```bash
git clone --recursive https://github.com/supercollider/supercollider.git <path-to-supercollider>
git clone https://github.com/mizramichaeljon/shared-ringbuffer.git <path-to-shared-ringbuffer>
git clone https://github.com/mizramichaeljon/TapOutUgen.git <path-to-TapOutUgen>
```

### Step 3: Build SuperCollider

```bash
cd <path-to-supercollider>
mkdir build && cd build

cmake .. -DSC_IDE=OFF -DSC_QT=OFF -DSC_ED=OFF -DCMAKE_INSTALL_PREFIX=<path-to-sc-install>
cmake --build . --config Release
```

### Step 4: Build TapOutUgen

```bash
cd <path-to-TapOutUgen>
mkdir build && cd build

cmake ..   -DSC_PATH=<path-to-supercollider>   -DSHARED_RINGBUFFER_PATH=<path-to-shared-ringbuffer>

cmake --build . --config Release
```

---

## Plugin Installation

To install the plugin, copy both the compiled `.scx` binary and the `TapOut.sc` class file into your SuperCollider user extensions folder.

To find this location:
1. Open SuperCollider.
2. Go to `File > Open User Support Directory`.
3. Inside that directory, create a folder called `Extensions` if it doesn't exist.
4. Create a subfolder called `TapOutUgen` and place the files there.

### Windows

```cmd
mkdir "%APPDATA%\SuperCollider\Extensions\TapOutUgen"
copy build\Plugins\TapOut.scx TapOut.sc "%APPDATA%\SuperCollider\Extensions\TapOutUgen\"
```

### macOS

```bash
mkdir -p ~/Library/Application\ Support/SuperCollider/Extensions/TapOutUgen
cp build/Plugins/TapOut.scx TapOut.sc ~/Library/Application\ Support/SuperCollider/Extensions/TapOutUgen/
```

---

## SuperCollider Usage

```supercollider
TapOut.ar(SinOsc.ar(440))
```

This writes the signal to a shared memory buffer called `"ringbuffer_audio"`.

---

## Related Projects

- [shared-ringbuffer](https://github.com/mizramichaeljon/shared-ringbuffer)
- [ringBufferVisual](https://github.com/mizramichaeljon/ringBufferVisual)

---

## License

MIT © Michael-Jon Mizra, 2025
