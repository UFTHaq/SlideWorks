/*
  ==============================================================================

    New_SubControls.cpp
    Created: 10 Dec 2024 5:46:26pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "New_SubControls.h"

New_SubControls::New_SubControls()
    : customLookAndFeel(Globals::getCustomLookAndFeel())
{
}

New_SubControls::~New_SubControls()
{
}

void New_SubControls::paint(juce::Graphics& g)
{
    drawBackground(g);
}

void New_SubControls::resized()
{
    bounds = getLocalBounds();
}

void New_SubControls::drawBackground(juce::Graphics& g)
{
    g.setColour(customLookAndFeel->getCurrentTheme().ButtonsID_01_ON);
    g.fillRoundedRectangle(bounds.toFloat(), 1);

    g.setColour(customLookAndFeel->getCurrentTheme().CustomDarkGrey);
    g.drawRoundedRectangle(bounds.toFloat().reduced(0.3F), 1, 0.3F);
}