#include "SC_PlugIn.hpp"
#include "SharedRingBufferWriter.hpp"
#include <vector>
#include <cstring>

static InterfaceTable* ft;

struct TapOut : public SCUnit
{
    SharedRingBufferWriter* ringBuffer;

    TapOut()
    {
        Print("[TapOut] mNumInputs = %d, mNumOutputs = %d\n", mNumInputs, mNumOutputs);

        try {
            ringBuffer = new SharedRingBufferWriter("ringbuffer_audio");
        }
        catch (const std::exception& e) {
            Print("[TapOut] Failed to attach to shared memory: %s\n", e.what());
            ringBuffer = nullptr;
        }

        set_calc_function<TapOut, &TapOut::next>();
        for (int i = 0; i < mNumOutputs; ++i) {
            ClearUnitOutputs(this, i);
        }
    }

    ~TapOut()
    {
        if (ringBuffer) {
            delete ringBuffer;
            ringBuffer = nullptr;
        }
    }

    void next(int inNumSamples)
    {
        std::vector<float> interleaved(2 * inNumSamples, 0.0f);

        for (int i = 0; i < inNumSamples; ++i) {
            float inL = mInBuf[0][i];
            float inR = (mNumInputs >= 2) ? mInBuf[1][i] : 0.0f;

            interleaved[2 * i]     = inL;
            interleaved[2 * i + 1] = inR;

            mOutBuf[0][i] = inL;
            if (mNumOutputs >= 2) {
                mOutBuf[1][i] = inR;
            }
        }

        // Print("[TapOut] inL[0] = %f, inR[0] = %f\n", interleaved[0], interleaved[1]);

        if (ringBuffer) {
            ringBuffer->write(interleaved.data(), static_cast<unsigned int>(interleaved.size()));
        }
    }
};

// ================================
// UGen Registration
// ================================
PluginLoad(TapOut)
{
    ft = inTable;
    registerUnit<TapOut>(ft, "TapOut");
}
