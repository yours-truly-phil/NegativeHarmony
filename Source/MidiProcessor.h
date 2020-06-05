/*
  ==============================================================================

    MidiProcessor.h

    Negative Harmony generation illustration in the Key of C:
        _____________________________________________________________________
        |  | | | |  |  | | | | | |  |  | | | |  |  | | | | | |  |  | | | |  |
        |  | | | |  |  | | | | | |  |  | | | |  |  | | | | | |  |  | | | |  |
        |  | | | |  |  | | | | | |  |  | | | |  |  | | | | | |  |  | | | |  |
        |  |_| |_|  |  |_| |_| |_|  |  |_| |_|  |  |_| |_| |_|  |  |_| |_|  |
        |   |   ||  |   |   |   |   |   |   ||  |   |   |   |   |   |   ||  |
        |   |   ||  |   |   |   |   |   |   ||  |   |   |   |   |   |   ||  |
        |___|___||__|___|___|___|___|___|___||__|___|___|___|___|___|___||__|
                 |              |     |      |        |   | |           |
    Mirror at    |              |     C<---- |------->G   | Bb<---------|-------->A
    Axis between |              Bb<----------|----------->A             |
                 |                           |                          |
    Tonic/      C/G                         C/G                        C/G
    Dominant
  ==============================================================================
*/
#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

class MidiProcessor final : juce::AudioProcessorValueTreeState::Listener
{
public:
    explicit MidiProcessor(juce::AudioProcessorValueTreeState& vts);
    ~MidiProcessor() override;

    void processMidiMsgsBlock(juce::MidiBuffer& midi_messages);

    int getNegHarmNn(int nn, int inKeyOf);

private:
    void parameterChanged(const juce::String& parameter_id,
                          float new_value) override;

    float negHarmMirAxisNn(int nn, int inKeyOf);
    bool checkNegHarmPrerequisites(std::atomic<float>* max_note_number,
                                   std::atomic<float>* min_note_number,
                                   std::atomic<float>* key,
                                   std::float_t octave_span,
                                   std::atomic<float>* is_on);

    juce::MidiBuffer p_midi_buffer_;

    juce::AudioProcessorValueTreeState& apvts_;
    std::atomic<float>* is_on_;
    std::atomic<float>* cur_key_;
    std::atomic<float>* min_nn_;

    std::atomic<float>* max_nn_;
    bool state_changed_;
};
