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

int NegativeHarmony::calculate(
    int nn, float key, float min_nn, float max_nn, float octave_span)
{
    auto mirrorNn = negHarmMirAxisNn(nn, key, octave_span);
    auto negHarmPos = 2 * mirrorNn - nn;

    while (min_nn > negHarmPos)
    {
        negHarmPos += octave_span;
    }
    while (max_nn < negHarmPos)
    {
        negHarmPos -= octave_span;
    }
    return static_cast<int>(negHarmPos);
}

bool NegativeHarmony::negHarmCalcChecks(float key,
                                        float min_nn,
                                        float max_nn,
                                        float octave_span)
{
    auto available_space = max_nn - min_nn;
    return key < octave_span && available_space > octave_span;
}

float NegativeHarmony::negHarmMirAxisNn(int nn, float key, float octave_span)
{
    auto mirrorNo = std::floor((nn + 2 - key) / octave_span);
    auto mirrorNn = mirrorNo * octave_span + 3.5f + key;
    return mirrorNn;
}
