/*
  ==============================================================================

    New_FilmstripOrientation.cpp
    Created: 10 Dec 2024 4:12:47pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "New_FilmstripOrientation.h"

New_FilmstripOrientation::New_FilmstripOrientation()
    : orientation(FilmstripOrientation::VERTICAL_FILMSTRIP), 
      customLookAndFeel(Globals::getCustomLookAndFeel())
{
    setupGroupComponent();
    setupButtonControls();
}

New_FilmstripOrientation::~New_FilmstripOrientation()
{
}

void New_FilmstripOrientation::paint(juce::Graphics& g)
{
    group.paint(g);
}

void New_FilmstripOrientation::resized()
{
    group.setBounds(getLocalBounds());

    auto bounds = getLocalBounds().reduced(13);

    auto area = bounds;
    auto totalWidth = int(area.getWidth() * 0.95F);
    area = area.withSizeKeepingCentre(totalWidth, area.getHeight());
    area.removeFromTop(10);

    auto horizontal = area.removeFromLeft(area.getWidth() / 2);
    auto vertical = area;

    horizontalButton.setBounds(horizontal.reduced(2));
    verticalButton.setBounds(vertical.reduced(2));
}

void New_FilmstripOrientation::setupGroupComponent()
{
    auto font = customLookAndFeel->getFontRobotoCondensedRegular().withHeight(16.0F);
    auto fontColor = customLookAndFeel->getCurrentTheme().CustomDarkGrey;
    auto outlineColor = customLookAndFeel->getCurrentTheme().OutlineControl;

    float indentation = 5.0F;
    float gap = 6.0F;
    float cornerSize = 5.0F;
    float lineThick = 1.0F;

    group.setText("Orientation");
    group.setTextLabelPosition(juce::Justification::centred);
    group.setFont(font);
    group.setFontColour(fontColor);
    group.setOutlineColour(outlineColor);
    group.setIndentation(indentation);
    group.setTextLineGap(gap);
    group.setCornerSize(cornerSize);
    group.setLineThickness(lineThick);
    addAndMakeVisible(group);
}

void New_FilmstripOrientation::setupButtonControls()
{
    horizontalButton.setButtonText("Horizontal");
    horizontalButton.setComponentID("Buttons_ID_10_ORIENTATION");
    horizontalButton.setToggleState(false, juce::dontSendNotification);
    horizontalButton.onClick = [this]()
        {
            if (verticalButton.getToggleState())
            {
                horizontalButton.setToggleState(true, juce::dontSendNotification);
                verticalButton.setToggleState(false, juce::dontSendNotification);
                orientation = FilmstripOrientation::HORIZONTAL_FILMSTRIP;
            }

        };
    addAndMakeVisible(horizontalButton);

    verticalButton.setButtonText("Vertical");
    verticalButton.setComponentID("Buttons_ID_10_ORIENTATION");
    verticalButton.setToggleState(true, juce::dontSendNotification);
    verticalButton.onClick = [this]()
        {
            if (horizontalButton.getToggleState())
            {
                verticalButton.setToggleState(true, juce::dontSendNotification);
                horizontalButton.setToggleState(false, juce::dontSendNotification);
                orientation = FilmstripOrientation::VERTICAL_FILMSTRIP;
            }
        };
    addAndMakeVisible(verticalButton);
}

bool New_FilmstripOrientation::isHorizontal() const
{
    return horizontalButton.getToggleState();
}

bool New_FilmstripOrientation::isVertical() const
{
    return verticalButton.getToggleState();
}

FilmstripOrientation New_FilmstripOrientation::getOrientation() const
{
    return orientation;
}
