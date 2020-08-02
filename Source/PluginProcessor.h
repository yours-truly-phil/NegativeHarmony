#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "MidiProcessor.h"

class NegativeHarmonyProcessor : public juce::AudioProcessor
{
public:
    NegativeHarmonyProcessor();
    ~NegativeHarmonyProcessor() override;

    void prepareToPlay(double sampleRate, int blockSize) override;
    void releaseResources() override {}

    bool isBusesLayoutSupported(const BusesLayout&) const override { return true; }

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return JucePlugin_Name; }

    bool acceptsMidi() const override { return true; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return juce::String(); }
    void changeProgramName(int, const juce::String& /*newName*/) override {}

    void getStateInformation(juce::MemoryBlock& dest_data) override;
    void setStateInformation(const void* data, int size_in_bytes) override;

private:
    juce::AudioProcessorValueTreeState apvts_;

    MidiProcessor midi_processor_ {apvts_};

    static juce::AudioProcessorValueTreeState::ParameterLayout createParameters() ;
};