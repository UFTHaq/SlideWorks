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
    font = customLookAndFeel->getFontRobotoCondensedRegular().withHeight(14.0F);
}

Footer::~Footer()
{
}

void Footer::paint(juce::Graphics& g)
{
    drawBackground(g);
    drawRecomendedSize(g);
    drawProjectSize(g);
    drawNotification(g);
    drawDate(g);
}

void Footer::resized()
{
    bounds = getLocalBounds();

    auto area = bounds;
    auto recomendedSizeArea = area.removeFromLeft(240);
    recomendedSizeArea.removeFromLeft(10);
    recomendedSize = recomendedSizeArea;

    auto projectSizeArea = area.removeFromLeft(300);
    projectSizeArea.removeFromLeft(10);
    projectSize = projectSizeArea;

    auto notificationArea = area.removeFromLeft(80);
    notificationArea.removeFromLeft(10);
    notification = notificationArea;

    auto dateArea = area;
    dateArea.removeFromRight(10);
    date = dateArea;
}

void Footer::drawBackground(juce::Graphics& g)
{
    g.setColour(customLookAndFeel->getCurrentTheme().ButtonsID_01_ON);
    g.fillRoundedRectangle(bounds.toFloat(), 1);

    //g.setColour(customLookAndFeel->getCurrentTheme().CustomDarkGrey);
    //g.drawRoundedRectangle(bounds.toFloat().reduced(0.3F), 1, 0.3F);
}

void Footer::drawRecomendedSize(juce::Graphics& g)
{
    text = recomendedSizeStr;
    auto area = recomendedSize;

    g.setFont(font);
    g.setColour(customLookAndFeel->getCurrentTheme().CustomGrey);
    g.drawText(text, area.toFloat(), juce::Justification::centredLeft);
}

void Footer::drawProjectSize(juce::Graphics& g)
{
    text = projectSizeStr;
    auto area = projectSize;

    g.setFont(font);
    g.setColour(customLookAndFeel->getCurrentTheme().CustomGrey);
    g.drawText(text, area.toFloat(), juce::Justification::centredLeft);
}

void Footer::drawNotification(juce::Graphics& g)
{
    text = notificationStr;
    auto area = notification;

    g.setFont(font);
    g.setColour(customLookAndFeel->getCurrentTheme().CustomGrey);
    g.drawText(text, area.toFloat(), juce::Justification::centredLeft);
}

void Footer::drawDate(juce::Graphics& g)
{
    text = dateStr;
    auto area = date;

    g.setFont(font);
    g.setColour(customLookAndFeel->getCurrentTheme().CustomGrey);
    g.drawText(text, area.toFloat(), juce::Justification::centredRight);
}
