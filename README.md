# TapOutUgen

A custom SuperCollider UGen that taps audio from the signal chain and writes it to a shared memory ring buffer using Boost.Interprocess. This allows for low-latency audio data sharing between SuperCollider and other processes (e.g., openFrameworks).

---

## 🛠 Features

- Native SuperCollider plugin
- Mono input, passthrough output
- Shared memory buffer (via Boost)

---

## ✅ Prerequisites

### 🧰 Dependencies:

- macOS with Homebrew
- [SuperCollider](https://github.com/supercollider/supercollider) (built from source)
- Boost (`brew install boost`)
- [shared-ringbuffer](https://github.com/mizramichaeljon/shared-ringbuffer)

---

## 📦 Build Instructions

### 1. Clone this repo:

```bash
git clone https://github.com/YOUR_USERNAME/TapOutUgen.git
cd TapOutUgen
```

### 2. Set environment variables:

```bash
export SC_PATH=~/Documents/GitHub/supercollider
export SHARED_RINGBUFFER_PATH=~/Documents/GitHub/shared-ringbuffer
```

Adjust the paths above to match your machine.

### 3. Build the plugin:

```bash
rm -rf build
mkdir build && cd build
cmake .. \
  -DSC_PATH=$SC_PATH \
  -DSHARED_RINGBUFFER_PATH=$SHARED_RINGBUFFER_PATH
cmake --build .
```

If successful, the plugin binary will be found in:

```bash
./build/Plugins/TapOut.scx
```

---

## 📁 Installation

Copy the plugin and class file to your SC extensions directory:

```bash
mkdir -p ~/Library/Application\ Support/SuperCollider/Extensions/TapOutUgen
cp build/Plugins/TapOut.scx ~/Library/Application\ Support/SuperCollider/Extensions/TapOutUgen/
cp TapOut.sc ~/Library/Application\ Support/SuperCollider/Extensions/TapOutUgen/
```

---

## 🧪 Usage in SuperCollider

```supercollider
TapOut.ar(SinOsc.ar(440))
```

This will:

- Output the signal as usual
- Write the same signal to a shared memory segment named `ringbuffer_audio`

---

## 🧠 Notes

- The shared buffer is 1 second at 48kHz, stereo (float32).
- You can adjust name/size inside `TapOut.cpp`
- Use your `shared-ringbuffer` reader to inspect buffer contents externally

---

## ✅ License

MIT (c) 2025 Michael-Jon Mizra

---

## 🧵 TODO

- Add multichannel support
- Implement blocking writes or overwrite protection
- Build openFrameworks reader demo

---

