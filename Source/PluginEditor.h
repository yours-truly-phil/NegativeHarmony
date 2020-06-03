#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#define PLUGIN_HEIGHT 300
#define PLUGIN_WIDTH 800

typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
typedef AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment;
typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

class NegativeHarmonyEditor
    : public AudioProcessorEditor
    , MidiKeyboardStateListener
{
public:
    explicit NegativeHarmonyEditor(NegativeHarmonyProcessor&,
                                   AudioProcessorValueTreeState&);
    ~NegativeHarmonyEditor() override;

    void paint(Graphics&) override;
    void resized() override;

private:
    void handleNoteOn(MidiKeyboardState* source,
                      int midi_channel,
                      int midi_note_number,
                      float velocity) override;
    void handleNoteOff(MidiKeyboardState* source,
                       int midi_channel,
                       int midi_note_number,
                       float velocity) override;

    NegativeHarmonyProcessor& processor_;
    AudioProcessorValueTreeState& apvts_;

    MidiKeyboardState midi_keyboard_state_;

    MidiKeyboardComponent midi_keyboard_ {midi_keyboard_state_,
                                          MidiKeyboardComponent::horizontalKeyboard};
    ToggleButton power_on_button_ {"to negative harmony"};
    Slider tonic_note_no_slider_ {Slider::SliderStyle::LinearHorizontal,
                                  Slider::TextEntryBoxPosition::TextBoxBelow};
    ComboBox choice_box_ {"key_choice_box"};
    Label plugin_ui_header_ {"label_plugin_header", processor_.getName()};

    std::unique_ptr<ButtonAttachment> power_on_button_attachment_;
    std::unique_ptr<SliderAttachment> tonic_note_no_slider_attachments_;
    std::unique_ptr<ComboBoxAttachment> choice_box_attachment_;
};
