//
// Created by Philipp Seeger on 05/06/2020.
//
constexpr float kOctaveSpan {12.0f};

const juce::StringArray kKeySignatures {
    "C",
    "Db",
    "D",
    "Eb",
    "E",
    "F",
    "F# & Gb",
    "G",
    "Ab",
    "A",
    "Bb",
    "B",
};

const juce::String kIdKey {"id_key"};
const juce::String kIdIsProcessingActive = "id_is_processing_active";

const juce::String kIdMinMidiNoteNumber = "id_min_midi_note_number";
const juce::String kIdMaxMidiNoteNumber = "id_max_midi_note_number";