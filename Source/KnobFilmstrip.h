/*
  ==============================================================================

    KnobFilmstrip.h
    Created: 22 Nov 2024 5:49:15pm
    Author:  UFTHaq

  ==============================================================================
*/

#pragma once

#include "FilmstripProject.h"

class KnobFilmstrip : public FilmstripProject
{
private:
    double minAngleDegree{ -135 };
    double maxAngleDegree{ 135 };
    double valueAngleDegree{ 0 };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KnobFilmstrip)

public:
    KnobFilmstrip();
    ~KnobFilmstrip();

    double getFilmstripSizeCalc() override;
    juce::String getFilmstripSizeStatus() override;
};