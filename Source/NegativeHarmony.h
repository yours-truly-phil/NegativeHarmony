/*
  ==============================================================================
    Created by Philipp Seeger on 06/06/2020.

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

class NegativeHarmony
{
public:
    static int calculate(int nn,
                         int key,
                         int min_nn = DEF_MIN_NN,
                         int max_nn = DEF_MAX_NN,
                         int octave_span = DEF_OCTAVE);

    static bool negHarmCalcChecks(int key,
                                  int min_nn = DEF_MIN_NN,
                                  int max_nn = DEF_MAX_NN,
                                  int octave_span = DEF_OCTAVE);

private:
    static float negHarmMirAxisNn(int nn, int key, int octave_span = DEF_OCTAVE);
    NegativeHarmony();

    static constexpr int DEF_OCTAVE = 12;
    static constexpr int DEF_MAX_NN = 127;
    static constexpr int DEF_MIN_NN = 21;
};
