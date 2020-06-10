#pragma once

#include "PluginProcessor.h"

typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
typedef juce::AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment;
typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

class NegativeHarmonyEditor
    : public juce::AudioProcessorEditor
    , juce::MidiKeyboardStateListener
{
public:
    explicit NegativeHarmonyEditor(NegativeHarmonyProcessor&,
                                   juce::AudioProcessorValueTreeState&);
    ~NegativeHarmonyEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    void handleNoteOn(juce::MidiKeyboardState* /*source*/,
                      int /*midi_channel*/,
                      int /*midi_note_number*/,
                      float /*velocity*/) override;
    void handleNoteOff(juce::MidiKeyboardState* /*source*/,
                       int /*midi_channel*/,
                       int /*midi_note_number*/,
                       float /*velocity*/) override;

    NegativeHarmonyProcessor& processor_;
    juce::AudioProcessorValueTreeState& apvts_;

    juce::MidiKeyboardState midi_keyboard_state_;

    juce::MidiKeyboardComponent midi_keyboard_ {
        midi_keyboard_state_, juce::MidiKeyboardComponent::horizontalKeyboard};
    juce::ToggleButton power_on_button_ {"to negative harmony"};
    juce::Slider tonic_note_no_slider_ {
        juce::Slider::SliderStyle::LinearHorizontal,
        juce::Slider::TextEntryBoxPosition::TextBoxBelow};
    juce::ComboBox choice_box_ {"key_choice_box"};
    juce::Label plugin_ui_header_ {"label_plugin_header", processor_.getName()};

    std::unique_ptr<ButtonAttachment> power_on_button_attachment_;
    std::unique_ptr<SliderAttachment> tonic_note_no_slider_attachments_;
    std::unique_ptr<ComboBoxAttachment> choice_box_attachment_;
};
