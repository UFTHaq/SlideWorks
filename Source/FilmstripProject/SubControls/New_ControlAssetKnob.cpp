/*
  ==============================================================================

    New_ControlAssetKnob.cpp
    Created: 10 Dec 2024 6:42:46pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "New_ControlAssetKnob.h"

ControlAssetKnob::ControlAssetKnob()
    : customLookAndFeel(Globals::getCustomLookAndFeel())
{
    setupGroupComponent();
}

ControlAssetKnob::~ControlAssetKnob()
{
}

void ControlAssetKnob::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::green);
    //g.fillRoundedRectangle(getLocalBounds().toFloat(), 3);

    group.paint(g);
}

void ControlAssetKnob::resized()
{
    group.setBounds(getLocalBounds());
}

void ControlAssetKnob::setupGroupComponent()
{
    auto font = customLookAndFeel->getFontRobotoCondensedRegular().withHeight(16.0F);
    auto fontColor = customLookAndFeel->getCurrentTheme().CustomDarkGrey;
    auto outlineColor = customLookAndFeel->getCurrentTheme().OutlineControl;

    float indentation = 5.0F;
    float gap = 6.0F;
    float cornerSize = 5.0F;
    float lineThick = 1.0F;

    group.setText("Knob");
    group.setTextLabelPosition(juce::Justification::centred);
    group.setFont(font);
    group.setFontColour(fontColor);
    group.setOutlineColour(outlineColor);
    group.setIndentation(indentation);
    group.setTextLineGap(gap);
    group.setCornerSize(cornerSize);
    group.setLineThickness(lineThick);
    addAndMakeVisible(group);

    setColourGroup();
}

void ControlAssetKnob::setColourGroup()
{
    group.setFontColour(customLookAndFeel->getCurrentTheme().CustomDarkGrey);
    group.setOutlineColour(customLookAndFeel->getCurrentTheme().OutlineControl);
}

void ControlAssetKnob::resetCurrentTheme()
{
    setColourGroup();
}
