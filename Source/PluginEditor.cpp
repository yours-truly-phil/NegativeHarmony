#include "PluginProcessor.h"
#include "PluginEditor.h"

NegativeHarmonyEditor::NegativeHarmonyEditor(NegativeHarmonyProcessor& p,
                                             juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor(&p)
    , processor_(p)
    , apvts_(vts)
{
    midi_keyboard_state_.addListener(this);
    addAndMakeVisible(midi_keyboard_);

    power_on_button_attachment_ = std::make_unique<ButtonAttachment>(
        apvts_, kIdIsProcessingActive, power_on_button_);
    addAndMakeVisible(power_on_button_);

    tonic_note_no_slider_attachments_ =
        std::make_unique<SliderAttachment>(apvts_, kIdKey, tonic_note_no_slider_);
    addAndMakeVisible(tonic_note_no_slider_);

    choice_box_.addItemList(kKeySignatures,
                            1); // Choices have to be filled before attachment
    choice_box_attachment_ =
        std::make_unique<ComboBoxAttachment>(apvts_, kIdKey, choice_box_);
    addAndMakeVisible(choice_box_);

    addAndMakeVisible(plugin_ui_header_);

    setSize(PLUGIN_WIDTH, PLUGIN_HEIGHT);
}

NegativeHarmonyEditor::~NegativeHarmonyEditor()
{
    midi_keyboard_state_.removeListener(this);
}

void NegativeHarmonyEditor::handleNoteOn(juce::MidiKeyboardState* /*source*/,
                                         int /*midi_channel*/,
                                         int /*midi_note_number*/,
                                         float /*velocity*/)
{
}

void NegativeHarmonyEditor::handleNoteOff(juce::MidiKeyboardState* /*source*/,
                                          int /*midi_channel*/,
                                          int /*midi_note_number*/,
                                          float /*velocity*/)
{
}

void NegativeHarmonyEditor::paint(juce::Graphics& g)
{
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void NegativeHarmonyEditor::resized()
{
    auto bounds = getLocalBounds();

    midi_keyboard_.setBounds(bounds.removeFromBottom(200));
    power_on_button_.setBounds(bounds.removeFromLeft(200));
    tonic_note_no_slider_.setBounds(bounds.removeFromLeft(200));
    choice_box_.setBounds(bounds.removeFromLeft(200));
    plugin_ui_header_.setBounds(bounds.removeFromRight(200));
    plugin_ui_header_.setJustificationType(juce::Justification::topRight);
}
