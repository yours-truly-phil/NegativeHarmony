#pragma once

#include <JuceHeader.h>
#include "MidiProcessor.h"

class NegativeHarmonyProcessor : public AudioProcessor
{
public:
    NegativeHarmonyProcessor();
    ~NegativeHarmonyProcessor() override;

    void prepareToPlay(double sampleRate, int blockSize) override;
    void releaseResources() override {}

    bool isBusesLayoutSupported(const BusesLayout&) const override { return true; }

    void processBlock(AudioBuffer<float>&, MidiBuffer&) override;

    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const String getName() const override { return JucePlugin_Name; }

    bool acceptsMidi() const override { return true; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const String getProgramName(int) override { return String(); }
    void changeProgramName(int, const String& /*newName*/) override {}

    void getStateInformation(MemoryBlock& dest_data) override;
    void setStateInformation(const void* data, int size_in_bytes) override;

private:
    AudioProcessorValueTreeState apvts_;

    MidiProcessor midi_processor_ {apvts_};

    AudioProcessorValueTreeState::ParameterLayout createParameters() const;
};