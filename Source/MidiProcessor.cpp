#include "MidiProcessor.h"

#include "PluginProcessor.h"

MidiProcessor::MidiProcessor(AudioProcessorValueTreeState& vts)
    : apvts_(vts)
{
    is_on_ = apvts_.getRawParameterValue(kIdIsProcessingActive);
    cur_key_ = apvts_.getRawParameterValue(kIdKey);
    min_nn_ = apvts_.getRawParameterValue(kIdMinMidiNoteNumber);
    max_nn_ = apvts_.getRawParameterValue(kIdMaxMidiNoteNumber);

    apvts_.addParameterListener(kIdIsProcessingActive, this);
    apvts_.addParameterListener(kIdKey, this);

    state_changed_ = true;
}

MidiProcessor::~MidiProcessor() = default;

void MidiProcessor::processMidiMsgsBlock(MidiBuffer& midi_messages)
{
    p_midi_buffer_.clear();

    for (auto meta: midi_messages)
    {
        auto cur_msg = meta.getMessage();
        if (cur_msg.isNoteOnOrOff())
        {
            if (state_changed_)
            {
                p_midi_buffer_.addEvent(
                    MidiMessage::allNotesOff(cur_msg.getChannel()),
                    meta.samplePosition);
                state_changed_ = false;
            }
            auto space = *max_nn_ - *min_nn_;
            if (*is_on_ && *cur_key_ < kOctaveSpan && space > kOctaveSpan)
            {
                auto note_number = cur_msg.getNoteNumber();

                auto new_nn = getNegHarmNn(note_number, *cur_key_);

                cur_msg.setNoteNumber(new_nn);
            }
        }
    }

    midi_messages.swapWith(p_midi_buffer_);
}

void MidiProcessor::parameterChanged(const String& parameter_id, float new_value)
{
    DBG("parameterChanged Event: - parameter_id: " << parameter_id
                                                   << "new_value: " << new_value);
    state_changed_ = true;
}

int MidiProcessor::getNegHarmNn(int nn, int inKeyOf)
{
    DBG("getNegHarmNn called, nn: "
        << nn << " inKeyOf: " << inKeyOf
        << " NoteName: " << MidiMessage::getMidiNoteName(nn, false, true, 4));

    auto mirrorNn = negHarmMirAxisNn(nn, inKeyOf);
    auto negHarmPos = 2 * mirrorNn - nn;

    while (*min_nn_ > negHarmPos)
    {
        negHarmPos += kOctaveSpan;
    }
    while (*max_nn_ < negHarmPos)
    {
        negHarmPos -= kOctaveSpan;
    }
    return negHarmPos;
}

float MidiProcessor::negHarmMirAxisNn(int nn, int inKeyOf)
{
    auto mirrorNo = std::floor((nn + 2 - inKeyOf) / kOctaveSpan);
    auto mirrorNn = mirrorNo * kOctaveSpan + 3.5 + inKeyOf;
    return mirrorNn;
}
