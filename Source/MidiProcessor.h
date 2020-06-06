/*
  ==============================================================================

    MidiProcessor.h

  ==============================================================================
*/
#pragma once

#include <juce_audio_utils/juce_audio_utils.h>
#include <atomic>

#include "PluginSettings.h"
#include "NegativeHarmony.h"

class MidiProcessor final : juce::AudioProcessorValueTreeState::Listener
{
public:
    explicit MidiProcessor(juce::AudioProcessorValueTreeState& vts);
    ~MidiProcessor() override;

    void processMidiMsgsBlock(juce::MidiBuffer& midi_messages);

private:
    void parameterChanged(const juce::String& parameter_id,
                          float new_value) override;

    juce::MidiBuffer p_midi_buffer_;

    juce::AudioProcessorValueTreeState& apvts_;
    std::atomic<float>* is_on_;
    std::atomic<float>* cur_key_;
    std::atomic<float>* min_nn_;
    std::atomic<float>* max_nn_;

    bool state_changed_;
};
