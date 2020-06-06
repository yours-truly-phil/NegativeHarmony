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
    static int
        calculate(int nn, float key, float min_nn, float max_nn, float octave_span);

    static bool
        negHarmCalcChecks(float key, float min_nn, float max_nn, float octave_span);

private:
    static float negHarmMirAxisNn(int nn, float key, float octave_span);
    NegativeHarmony();
};
