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

NegativeHarmony::NegativeHarmony()
{
}

/*
 * calculates the negative harmony note number
 * by selecting the to the given note number closest
 * axis (between tonic and dominant) that returns a
 * valid result.
 */
int NegativeHarmony::calculate(
    int nn, int key, int min_nn, int max_nn, int octave_span)
{
    auto mirrorNn = negHarmMirAxisNn(nn, key, octave_span);
    auto negHarmPos = static_cast<int>(2.0f * mirrorNn - nn);

    while (negHarmPos < min_nn)
    {
        negHarmPos += octave_span;
    }
    while (negHarmPos > max_nn)
    {
        negHarmPos -= octave_span;
    }
    return negHarmPos;
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

float NegativeHarmony::negHarmMirAxisNn(int nn, int key, int octave_span)
{
    auto mirrorNo = std::floor((float) (nn + 2 - key) / octave_span);
    auto mirrorNn = mirrorNo * octave_span + 3.5f + key;
    return mirrorNn;
}
