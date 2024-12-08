/*
  ==============================================================================

    SliderFilmstrip.cpp
    Created: 22 Nov 2024 5:50:11pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "SliderFilmstrip.h"

SliderFilmstrip::SliderFilmstrip()
{
    initializeAssets();
}

SliderFilmstrip::~SliderFilmstrip()
{
}

juce::String SliderFilmstrip::getFilmstripType()
{
    return filmstripType;
}

double SliderFilmstrip::getFilmstripSizeCalc()
{
    // DO CALCULATION ABOUT SIZE LIKE THIS
    // Size : 300 x 300 x 121 = 10.890.000 px = 10.8 MB   |   Still Okay
    return 0.0;
}

juce::String SliderFilmstrip::getFilmstripSizeStatus()
{
    return juce::String("OKAY TESTING SLIDER");
}

void SliderFilmstrip::initializeAssets()
{
    addAsset(juce::String("Thumb"));
    addAsset(juce::String("Track"));
    addAsset(juce::String("Scale"));
}

juce::String SliderFilmstrip::getAnglesOrThumbPosText()
{
    return juce::String("Thumb Positions");
}

AnglesOrThumbPos SliderFilmstrip::getAnglesOrThumbPos()
{
    return AnglesOrThumbPos(AnglesOrThumbPos::THUMB_POS);
}

double SliderFilmstrip::getMinThumbPos()
{
    return minThumbPos;
}

void SliderFilmstrip::setMinThumbPos(double value)
{
    this->minThumbPos = value;
}

double SliderFilmstrip::getMaxThumbPos()
{
    return maxThumbPos;
}

void SliderFilmstrip::setMaxThumbPos(double value)
{
    this->maxThumbPos = value;
}
