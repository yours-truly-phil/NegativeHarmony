#include "PluginProcessor.h"
#include "PluginEditor.h"

NegativeHarmonyProcessor::NegativeHarmonyProcessor()
    : apvts_(*this, nullptr, "PARAMETERS", createParameters())
{
}

NegativeHarmonyProcessor::~NegativeHarmonyProcessor() = default;

void NegativeHarmonyProcessor::prepareToPlay(double /*sampleRate*/,
                                             int /*blockSize*/)
{
}

void NegativeHarmonyProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                            juce::MidiBuffer& midiMessages)

{
    midi_processor_.processMidiMsgsBlock(midiMessages);
    buffer.clear();
}

juce::AudioProcessorEditor* NegativeHarmonyProcessor::createEditor()
{
    return new NegativeHarmonyEditor(*this, apvts_);
}

void NegativeHarmonyProcessor::getStateInformation(juce::MemoryBlock& dest_data)
{
    const auto state = apvts_.copyState();
    const auto xml = state.createXml();
    copyXmlToBinary(*xml, dest_data);
}

void NegativeHarmonyProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    const auto xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState != nullptr && xmlState->hasTagName(apvts_.state.getType()))
    {
        apvts_.replaceState(juce::ValueTree::fromXml(*xmlState));
    }
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NegativeHarmonyProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout
    NegativeHarmonyProcessor::createParameters() const
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterBool>(
        kIdIsProcessingActive, "is processing active", false));

    params.push_back(std::make_unique<juce::AudioParameterChoice>(
        kIdKey, "Key", kKeySignatures, 0));

    params.push_back(std::make_unique<juce::AudioParameterInt>(
        kIdMinMidiNoteNumber, "Smallest Midi Note Number", 0, 127, 24));
    params.push_back(std::make_unique<juce::AudioParameterInt>(
        kIdMaxMidiNoteNumber, "Largest Midi Note Number", 0, 127, 127));

    return {params.begin(), params.end()};
}
