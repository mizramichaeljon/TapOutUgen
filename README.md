# TapOutUgen

A SuperCollider UGen that taps an incoming signal and writes it to a shared memory ring buffer for low-latency inter-process audio sharing.

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

## Building SuperCollider from Source

To get access to the necessary plugin headers, SuperCollider must be built from source. Follow the official instructions:

- https://github.com/supercollider/supercollider/blob/develop/README.md

Ensure you retain the source folder after building, as the plugin includes headers from its `include/plugin_interface` and `include/common` directories.

---

## Build Instructions

### macOS

Install dependencies via [Homebrew](https://brew.sh):

```bash
brew install cmake boost
```

Clone required dependencies:

```bash
git clone https://github.com/supercollider/supercollider.git ~/dev/supercollider
git clone https://github.com/mizramichaeljon/shared-ringbuffer.git ~/dev/shared-ringbuffer
```

Set the paths once inside `build_macos.sh`, then:

```bash
chmod +x build_macos.sh
./build_macos.sh
```

---

### Windows

Install [CMake](https://cmake.org/), [Boost](https://www.boost.org/), and optionally install Boost using [vcpkg](https://github.com/microsoft/vcpkg):

```bash
vcpkg install boost
```

Clone the required projects:

```powershell
git clone https://github.com/supercollider/supercollider.git C:\dev\supercollider
git clone https://github.com/mizramichaeljon/shared-ringbuffer.git C:\dev\shared-ringbuffer
```

Set the paths once inside `build_windows.bat`, then run:

```powershell
build_windows.bat
```

---

## Manual CMake Build (Advanced)

```bash
cmake .. -DSC_PATH=/path/to/supercollider -DSHARED_RINGBUFFER_PATH=/path/to/shared-ringbuffer
cmake --build .
```

---

## Plugin Installation

```bash
mkdir -p ~/Library/Application\ Support/SuperCollider/Extensions/TapOutUgen
cp build/Plugins/TapOut.scx ~/Library/Application\ Support/SuperCollider/Extensions/TapOutUgen/
cp TapOut.sc ~/Library/Application\ Support/SuperCollider/Extensions/TapOutUgen/
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
