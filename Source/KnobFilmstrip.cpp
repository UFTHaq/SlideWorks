/*
  ==============================================================================

    KnobFilmstrip.cpp
    Created: 22 Nov 2024 5:49:15pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "KnobFilmstrip.h"

KnobFilmstrip::KnobFilmstrip()
{
}

KnobFilmstrip::~KnobFilmstrip()
{
}

double KnobFilmstrip::getFilmstripSizeCalc()
{
    // DO CALCULATION ABOUT SIZE LIKE THIS
    // Size : 300 x 300 x 121 = 10.890.000 px = 10.8 MB   |   Still Okay
    return 0.0;
}

juce::String KnobFilmstrip::getFilmstripSizeStatus()
{

    return juce::String("OKAY TESTING KNOB");
}