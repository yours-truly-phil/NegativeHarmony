#include "MidiProcessor.h"

MidiProcessor::MidiProcessor(juce::AudioProcessorValueTreeState& vts)
    : apvts_(vts)
{
    is_on_ = apvts_.getRawParameterValue(kIdIsProcessingActive);
    cur_key_ = apvts_.getRawParameterValue(kIdKey);

    apvts_.addParameterListener(kIdIsProcessingActive, this);
    apvts_.addParameterListener(kIdKey, this);

    state_changed_ = true;
}

MidiProcessor::~MidiProcessor() = default;

void MidiProcessor::processMidiMsgsBlock(juce::MidiBuffer& midi_messages)
{
    p_midi_buffer_.clear();

    int key;

    for (auto meta: midi_messages)
    {
        auto cur_msg = meta.getMessage();
        if (cur_msg.isNoteOnOrOff())
        {
            if (state_changed_)
            {
                p_midi_buffer_.addEvent(
                    juce::MidiMessage::allNotesOff(cur_msg.getChannel()),
                    meta.samplePosition);
                state_changed_ = false;
            }

            if (*is_on_ != 0.0f
                && NegativeHarmony::negHarmCalcChecks(key = (int) cur_key_->load()))
            {
                auto note_number = cur_msg.getNoteNumber();

                auto new_nn = NegativeHarmony::calculate(note_number, key);

                cur_msg.setNoteNumber(new_nn);

                p_midi_buffer_.addEvent(cur_msg, meta.samplePosition);
            }
        }
    }

    midi_messages.swapWith(p_midi_buffer_);
}

void MidiProcessor::parameterChanged(const juce::String& parameter_id,
                                     float new_value)
{
    DBG("parameterChanged Event: - parameter_id: " << parameter_id
                                                   << "new_value: " << new_value);
    state_changed_ = true;
}
