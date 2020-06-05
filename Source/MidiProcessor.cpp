#include "MidiProcessor.h"

//#include "PluginProcessor.h"

MidiProcessor::MidiProcessor(juce::AudioProcessorValueTreeState& vts)
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

void MidiProcessor::processMidiMsgsBlock(juce::MidiBuffer& midi_messages)
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
                    juce::MidiMessage::allNotesOff(cur_msg.getChannel()),
                    meta.samplePosition);
                state_changed_ = false;
            }

            if (checkNegHarmPrerequisites(
                    max_nn_, min_nn_, cur_key_, kOctaveSpan, is_on_))
            {
                auto note_number = cur_msg.getNoteNumber();

                auto new_nn = getNegHarmNn(note_number, *cur_key_);

                cur_msg.setNoteNumber(new_nn);
            }
        }
    }

    midi_messages.swapWith(p_midi_buffer_);
}

bool MidiProcessor::checkNegHarmPrerequisites(std::atomic<float>* max_note_number,
                                              std::atomic<float>* min_note_number,
                                              std::atomic<float>* key,
                                              std::float_t octave_span,
                                              std::atomic<float>* is_on)
{
    auto available_space = *max_note_number - *min_note_number;
    return *is_on && *key < octave_span && available_space > octave_span;
}

void MidiProcessor::parameterChanged(const juce::String& parameter_id,
                                     float new_value)
{
    DBG("parameterChanged Event: - parameter_id: " << parameter_id
                                                   << "new_value: " << new_value);
    state_changed_ = true;
}

int MidiProcessor::getNegHarmNn(int nn, int inKeyOf)
{
    DBG("getNegHarmNn called, nn: "
        << nn << " inKeyOf: " << inKeyOf
        << " NoteName: " << juce::MidiMessage::getMidiNoteName(nn, false, true, 4));

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
    return static_cast<int>(negHarmPos);
}

float MidiProcessor::negHarmMirAxisNn(int nn, int inKeyOf)
{
    auto mirrorNo = std::floor((nn + 2 - inKeyOf) / kOctaveSpan);
    auto mirrorNn = mirrorNo * kOctaveSpan + 3.5f + inKeyOf;
    return mirrorNn;
}
