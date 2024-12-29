/*
  ==============================================================================

    New_ControlCanvas.cpp
    Created: 10 Dec 2024 5:50:36pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "New_ControlCanvas.h"

ControlCanvas::ControlCanvas()
{
}

ControlCanvas::~ControlCanvas()
{
}

void ControlCanvas::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::red);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 3);
}

void ControlCanvas::resized()
{
}
