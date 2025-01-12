/*
  ==============================================================================

    TabButton.cpp
    Created: 10 Dec 2024 2:20:43pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "TabButton.h"

TabButton::TabButton(const FilmstripType& type)
    : filmstripType(type)
    , customLookAndFeel(Globals::getCustomLookAndFeel())
{
    mainButton.setButtonText(name);
    mainButton.setComponentID("Buttons_ID_03_TAB");
    mainButton.setToggleState(true, juce::dontSendNotification);

    addAndMakeVisible(mainButton);

    closeButton.setButtonText("");
    closeButton.setComponentID("Buttons_ID_04_TAB_CLOSE");
    addAndMakeVisible(closeButton);
}

TabButton::~TabButton()
{
}

void TabButton::resized()
{
    mainButton.setBounds(getLocalBounds());

    auto space = 5;
    auto copyLocalBounds = getLocalBounds();
    auto closeButtonArea = copyLocalBounds.removeFromRight(copyLocalBounds.getHeight());
    closeButton.setBounds(closeButtonArea);
}

void TabButton::setMainButtonText(juce::String& name)
{
    this->name = name;
    mainButton.setButtonText(name);
}

juce::TextButton& TabButton::getMainButton()
{
    return mainButton;
}

juce::TextButton& TabButton::getCloseButton()
{
    return closeButton;
}
