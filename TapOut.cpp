#include "SC_PlugIn.hpp"             // Required for SuperCollider plugin interface
#include "SharedRingBuffer.hpp"      // Your custom shared memory class
#include <cstring>                   // For std::memcpy

// Required by SuperCollider plugins: provides function table pointer
static InterfaceTable* ft;

// ================================
// TapOut UGen Definition
// ================================
struct TapOut : public Unit {
    SharedRingBuffer* ringBuffer;

    // Constructor: Called once when the Synth is instantiated
    TapOut() {
        // Create a shared ring buffer with enough space for 1 second of stereo audio at 48kHz
        ringBuffer = new SharedRingBuffer("ringbuffer_audio", 48000 * sizeof(float) * 2);

        // Assign the audio processing callback (next method)
       mCalcFunc = [](Unit* unit, int inNumSamples) {
    static_cast<TapOut*>(unit)->next(inNumSamples);
};

        // Zero out all output buffers initially
        for (int i = 0; i < mNumOutputs; ++i) {
            ClearUnitOutputs(this, i);
        }
    }

    // Destructor: Called when the Synth is freed
    ~TapOut() {
        if (ringBuffer) {
            ringBuffer->close();
            delete ringBuffer;
            ringBuffer = nullptr;
        }
    }

    // DSP loop: Called every control block
    void next(int inNumSamples) {
        float* in = mInBuf[0];   // First input channel
        float* out = mOutBuf[0]; // First output channel

        // Simple passthrough: copy input directly to output
        std::memcpy(out, in, sizeof(float) * inNumSamples);

        // Write input to shared memory
        if (ringBuffer) {
            ringBuffer->write(in, inNumSamples);
        }
    }
};

// ================================
// UGen Registration
// ================================

extern "C" {
    // Constructor bridge required by SuperCollider
    void TapOut_Ctor(TapOut* unit) {
        new (unit) TapOut(); // Placement new: calls constructor on pre-allocated memory
    }

    // Destructor bridge
    void TapOut_Dtor(TapOut* unit) {
        unit->~TapOut(); // Explicit destructor call
    }

    // Entry point when the plugin is loaded
    PluginLoad(TapOut) {
        ft = inTable;
        DefineDtorUnit(TapOut); // Registers the UGen with its constructor and destructor
    }
}