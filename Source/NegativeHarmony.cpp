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
#include <cmath>
#include "NegativeHarmony.h"

NegativeHarmony::NegativeHarmony() = default;

/*
 * calculates the negative harmony note number
 * by selecting the to the given note number closest
 * axis (between tonic and dominant) that returns a
 * valid result.
 */
int NegativeHarmony::calculate(
    int nn, int key, int min_nn, int max_nn, int octave_span)
{
    int mirrorNn = negHarmMirAxisNn(nn, key, octave_span);
    int negHarmPos = static_cast<int>(2.0f * (float) mirrorNn - (float) nn);

    return intoRange(negHarmPos, min_nn, max_nn, octave_span);
}

int NegativeHarmony::intoRange(int note_number,
                               int min_nn,
                               int max_nn,
                               int octave_span)
{
    while (note_number < min_nn)
    {
        note_number += octave_span;
    }
    while (note_number > max_nn)
    {
        note_number -= octave_span;
    }
    return note_number;
}

bool NegativeHarmony::negHarmCalcChecks(int key,
                                        int min_nn,
                                        int max_nn,
                                        int octave_span)
{
    auto available_space = max_nn - min_nn + 1;
    return key >= 0 && key < octave_span && octave_span >= 0
           && available_space >= octave_span;
}

int NegativeHarmony::negHarmMirAxisNn(int nn, int key, int octave_span)
{
    auto mirrorNo = std::floor((float) (nn + 2 - key) / (float) octave_span);
    auto mirrorNn = mirrorNo * (float) octave_span + 3.5f + (float) key;
    return static_cast<int>(mirrorNn);
}
