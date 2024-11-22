/*
  ==============================================================================

    SliderFilmstrip.h
    Created: 22 Nov 2024 5:50:11pm
    Author:  UFTHaq

  ==============================================================================
*/

#pragma once

#include "FilmstripProject.h"

class SliderFilmstrip : public FilmstripProject
{
private:
    // thumbPos use normalize (0 - 1) position
    double minThumbPos{ 0.1 };
    double maxThumbPos{ 0.9 };
    double valueThumbPos{ 0.5 };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SliderFilmstrip)

public:
    SliderFilmstrip();
    ~SliderFilmstrip();

    double getFilmstripSizeCalc() override;
    juce::String getFilmstripSizeStatus() override;
};