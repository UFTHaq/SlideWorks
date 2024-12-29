/*
  ==============================================================================

    New_ControlAssetKnobScale.cpp
    Created: 10 Dec 2024 6:43:00pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "New_ControlAssetKnobScale.h"

ControlAssetKnobScale::ControlAssetKnobScale()
{
}

ControlAssetKnobScale::~ControlAssetKnobScale()
{
}

void ControlAssetKnobScale::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::yellowgreen);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 3);
}

void ControlAssetKnobScale::resized()
{
}
