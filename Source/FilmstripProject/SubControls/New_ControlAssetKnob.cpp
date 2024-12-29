/*
  ==============================================================================

    New_ControlAssetKnob.cpp
    Created: 10 Dec 2024 6:42:46pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "New_ControlAssetKnob.h"

ControlAssetKnob::ControlAssetKnob()
{
}

ControlAssetKnob::~ControlAssetKnob()
{
}

void ControlAssetKnob::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::green);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 3);
}

void ControlAssetKnob::resized()
{
}
