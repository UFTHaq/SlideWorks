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
    initializeAssets();
}

juce::String KnobFilmstrip::getFilmstripType()
{
    return filmstripType;
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

void KnobFilmstrip::initializeAssets()
{
    addAsset("Knob");
    addAsset("Scale");
}

juce::String KnobFilmstrip::getAnglesOrThumbPosText()
{
    return juce::String("Angles");
}

AnglesOrThumbPos KnobFilmstrip::getAnglesOrThumbPos()
{
    return AnglesOrThumbPos(AnglesOrThumbPos::ANGLES);
}

double KnobFilmstrip::getMinAngleDegree()
{
    return minAngleDegree;
}

void KnobFilmstrip::setMinAngleDegree(double angleDegree)
{
    this->minAngleDegree = angleDegree;
}

double KnobFilmstrip::getMaxAngleDegree()
{
    return maxAngleDegree;
}

void KnobFilmstrip::setMaxAngleDegree(double angleDegree)
{
    this->maxAngleDegree = angleDegree;
}
