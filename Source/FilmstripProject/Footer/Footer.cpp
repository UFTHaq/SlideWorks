/*
  ==============================================================================

    Footer.cpp
    Created: 15 Dec 2024 8:52:43pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "Footer.h"

Footer::Footer()
    : customLookAndFeel(Globals::getCustomLookAndFeel())
{
}

Footer::~Footer()
{
}

void Footer::paint(juce::Graphics& g)
{
    drawBackground(g);
}

void Footer::resized()
{
    bounds = getLocalBounds();
}

void Footer::drawBackground(juce::Graphics& g)
{
    g.setColour(customLookAndFeel->getCurrentTheme().ButtonsID_01_ON);
    g.fillRoundedRectangle(bounds.toFloat(), 1);

    g.setColour(customLookAndFeel->getCurrentTheme().CustomDarkGrey);
    //g.drawRoundedRectangle(bounds.toFloat().reduced(0.3F), 1, 0.3F);
}
