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
    juce::String filmstripType{ "SLIDER" };

    // thumbPos use normalize (0 - 1) position
    double minThumbPos{ 0.1 };
    double maxThumbPos{ 0.9 };
    double valueThumbPos{ 0.5 };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SliderFilmstrip)

public:
    SliderFilmstrip();
    ~SliderFilmstrip();

    juce::String getFilmstripType() override;
    double getFilmstripSizeCalc() override;
    juce::String getFilmstripSizeStatus() override;

    void initializeAssets() override;

    juce::String getAnglesOrThumbPosText() override;
    virtual AnglesOrThumbPos getAnglesOrThumbPos() override;

    double getMinThumbPos();
    void setMinThumbPos(double value);

    double getMaxThumbPos();
    void setMaxThumbPos(double value);
};
