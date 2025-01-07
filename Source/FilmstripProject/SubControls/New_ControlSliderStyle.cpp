/*
  ==============================================================================

    New_ControlSliderStyle.cpp
    Created: 31 Dec 2024 11:45:35am
    Author:  UFTHaq

  ==============================================================================
*/

#include "New_ControlSliderStyle.h"

ControlSliderStyle::ControlSliderStyle()
    : customLookAndFeel(Globals::getCustomLookAndFeel())
{
    setupGroupComponent();
    setupToggleButton();
}

ControlSliderStyle::~ControlSliderStyle()
{
}

void ControlSliderStyle::paint(juce::Graphics& g)
{
    group.paint(g);
}

void ControlSliderStyle::resized()
{
    group.setBounds(getLocalBounds());

    auto bounds = getLocalBounds();
    bounds.removeFromTop(13);

    auto w = bounds.getWidth() - 20;
    auto h = bounds.getHeight() - 20;
    bounds = bounds.withSizeKeepingCentre(w, h);

    auto areaH = bounds.getHeight();

    toggleButton.setBounds(bounds);
}

void ControlSliderStyle::setupGroupComponent()
{
    auto font = customLookAndFeel->getFontRobotoCondensedRegular().withHeight(16.0F);
    auto fontColor = customLookAndFeel->getCurrentTheme().CustomDarkGrey;
    auto outlineColor = customLookAndFeel->getCurrentTheme().OutlineControl;

    float indentation = 5.0F;
    float gap = 6.0F;
    float cornerSize = 5.0F;
    float lineThick = 1.0F;

    group.setText("Slider Style");
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

void ControlSliderStyle::setColourGroup()
{
    group.setFontColour(customLookAndFeel->getCurrentTheme().CustomDarkGrey);
    group.setOutlineColour(customLookAndFeel->getCurrentTheme().OutlineControl);
}

void ControlSliderStyle::setupToggleButton()
{
    toggleButton.setButtonText("Horizontal");
    toggleButton.setComponentID("Buttons_ID_15_SLIDER_TOGGLE_STYLE");
    toggleButton.setToggleState(true, juce::dontSendNotification);
    toggleButton.onClick = [this]()
        {
            if (toggleButton.getToggleState() == true)
            {
                toggleButton.setButtonText("Vertical");
                toggleButton.setToggleState(false, juce::dontSendNotification);
                styleHorizontal = false;
            }
            else
            {
                toggleButton.setButtonText("Horizontal");
                toggleButton.setToggleState(true, juce::dontSendNotification);
                styleHorizontal = true;
            }

            DBG("--> Toggle Slider Style Click");
        };
    addAndMakeVisible(toggleButton);
}

void ControlSliderStyle::resetCurrentTheme()
{
    setColourGroup();
}

bool ControlSliderStyle::isStyleHorizontal() const
{
    return styleHorizontal;
}
