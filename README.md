# TapOutUgen

A SuperCollider UGen that taps an incoming signal and writes it to a shared memory ring buffer for low-latency inter-process audio sharing (e.g., with openFrameworks).

## Features

- Native SuperCollider plugin
- Mono input, passthrough output
- Uses shared memory via `boost::interprocess`
- Companion readers available (CLI, oF)

---

## Requirements

- SuperCollider built from source
- Boost (only headers needed)
- CMake ≥ 3.10
- A C++14-compatible compiler
- [shared-ringbuffer](https://github.com/mizramichaeljon/shared-ringbuffer)

---

## Build Instructions

### macOS

1. Install dependencies:

```bash
brew install cmake boost
```

2. Clone and build:

```bash
git clone https://github.com/mizramichaeljon/TapOutUgen.git
cd TapOutUgen
chmod +x build_macos.sh
./build_macos.sh
```

The plugin `.scx` will be found in `build/Plugins`.

---

### Windows

1. Install [CMake](https://cmake.org/), [Boost](https://www.boost.org/) and optionally [vcpkg](https://github.com/microsoft/vcpkg) for Boost headers:

```powershell
vcpkg install boost
```

2. Build:

```powershell
git clone https://github.com/mizramichaeljon/TapOutUgen.git
cd TapOutUgen
build_windows.bat
```

---

## Environment Variables (Advanced)

You can build manually with:

```bash
cmake .. -DSC_PATH=/path/to/supercollider -DSHARED_RINGBUFFER_PATH=/path/to/shared-ringbuffer
cmake --build .
```

The `SC_PATH` should point to the SuperCollider source root, and `SHARED_RINGBUFFER_PATH` to the shared-ringbuffer repo.

---

## Install Plugin

Copy the plugin and class file:

```bash
mkdir -p ~/Library/Application\ Support/SuperCollider/Extensions/TapOutUgen
cp build/Plugins/TapOut.scx ~/Library/Application\ Support/SuperCollider/Extensions/TapOutUgen/
cp TapOut.sc ~/Library/Application\ Support/SuperCollider/Extensions/TapOutUgen/
```

---

## Usage

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
