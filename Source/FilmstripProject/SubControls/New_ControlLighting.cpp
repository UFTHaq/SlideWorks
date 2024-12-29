/*
  ==============================================================================

    New_ControlLighting.cpp
    Created: 10 Dec 2024 5:50:02pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "New_ControlLighting.h"

ControlLighting::ControlLighting()
{
}

ControlLighting::~ControlLighting()
{
}

void ControlLighting::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::blue);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 3);
}

void ControlLighting::resized()
{
}
