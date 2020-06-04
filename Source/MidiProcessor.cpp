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

    MidiBuffer::Iterator it(midi_messages);
    MidiMessage cur_msg;
    int sample_pos;

    while (it.getNextEvent(cur_msg, sample_pos))
    {
        if (cur_msg.isNoteOnOrOff())
        {
            if (state_changed_)
            {
                p_midi_buffer_.addEvent(
                    MidiMessage::allNotesOff(cur_msg.getChannel()), sample_pos);
                DBG("AllNotesOff Event added to buffer because of change. Channel: "
                    << cur_msg.getChannel() << " sample_pos: " << sample_pos);
                state_changed_ = false;
            }
            auto space = *max_nn_ - *min_nn_;
            if (*is_on_ && *cur_key_ < kOctaveSpan && space > kOctaveSpan)
            {
                auto note_number = cur_msg.getNoteNumber();

                auto new_nn = getNegHarmNn(note_number, (int) *cur_key_);
                DBG("Transformed ["
                    << note_number << "] "
                    << MidiMessage::getMidiNoteName(note_number, true, true, 4)
                    << " to [" << new_nn << "] "
                    << MidiMessage::getMidiNoteName(new_nn, true, true, 4));
                cur_msg.setNoteNumber(new_nn);
            }
        }
        p_midi_buffer_.addEvent(cur_msg, sample_pos);
    }
    midi_messages.swapWith(p_midi_buffer_);
}

void MidiProcessor::parameterChanged(const String& parameter_id, float new_value)
{
    DBG("parameterChanged Event: - parameter_id: " << parameter_id
                                                   << "new_value: " << new_value);
    state_changed_ = true;
}

int MidiProcessor::getNegHarmNn(uint8 nn, uint8 key)
{
    DBG("getNegHarmNn called, nn: "
        << nn << " key: " << key
        << " NoteName: " << MidiMessage::getMidiNoteName(nn, false, true, 4));

    auto mirrorOctave = floor((nn + 2 - key) / kOctaveSpan);
    auto mirrorPos = mirrorOctave * kOctaveSpan + 3.5 + key;
    auto relPosNnToMirror = nn - mirrorPos;
    auto negHarmRelPos = relPosNnToMirror * (-1);
    auto negHarmPos = negHarmRelPos + mirrorPos;

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
