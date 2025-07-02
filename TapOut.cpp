#include "SC_PlugIn.hpp"              // Required for SuperCollider plugin interface
#include "SharedRingBufferWriter.hpp" // Shared memory ring buffer writer
#include <cstring>                    // For std::memcpy
#include <vector>                     // For interleaved buffer

// Required by SuperCollider plugins: provides function table pointer
static InterfaceTable *ft;

// ================================
// TapOut UGen Definition
// ================================
struct TapOut : public Unit
{
    SharedRingBufferWriter *ringBuffer;

    TapOut()
    {
        try
        {
            ringBuffer = new SharedRingBufferWriter("ringbuffer_audio");
        }
        catch (const std::exception &e)
        {
            Print("[TapOut] Failed to attach to shared memory: %s\n", e.what());
            ringBuffer = nullptr;
        }

        mCalcFunc = [](Unit *unit, int inNumSamples)
        {
            static_cast<TapOut *>(unit)->next(inNumSamples);
        };

        for (int i = 0; i < mNumOutputs; ++i)
        {
            ClearUnitOutputs(this, i);
        }
    }

    // Destructor: Called when the Synth is freed
    ~TapOut()
    {
        if (ringBuffer)
        {
            delete ringBuffer;
            ringBuffer = nullptr;
        }
    }

    // DSP loop: Called every control block
    void next(int inNumSamples)
    {
        float *inL = mInBuf[0];                               // Left channel input
        float *inR = (mNumInputs >= 2) ? mInBuf[1] : nullptr; // Right channel input (optional)

        float *outL = mOutBuf[0];                               // Left output
        float *outR = (mNumOutputs > 1) ? mOutBuf[1] : nullptr; // Right output (optional)

        // Interleave audio data into a single buffer for writing to shared memory
        std::vector<float> interleaved(2 * inNumSamples);
        for (int i = 0; i < inNumSamples; ++i)
        {
            interleaved[2 * i] = inL[i];
            interleaved[2 * i + 1] = inR ? inR[i] : 0.0f;
        }

        // Copy input to output (passthrough)
        std::memcpy(outL, inL, sizeof(float) * inNumSamples);
        if (outR && inR)
        {
            std::memcpy(outR, inR, sizeof(float) * inNumSamples);
        }

        // Write interleaved audio to shared memory
        if (ringBuffer)
        {
            ringBuffer->write(interleaved.data(), interleaved.size());
        }
    }
};

// ================================
// UGen Registration
// ================================
extern "C"
{
    // Constructor bridge required by SuperCollider
    void TapOut_Ctor(TapOut *unit)
    {
        new (unit) TapOut(); // Placement new: calls constructor on pre-allocated memory
    }

    // Destructor bridge
    void TapOut_Dtor(TapOut *unit)
    {
        unit->~TapOut(); // Explicit destructor call
    }

    // Entry point when the plugin is loaded
    PluginLoad(TapOut)
    {
        ft = inTable;
        DefineDtorUnit(TapOut); // Registers the UGen with its constructor and destructor
    }
}
