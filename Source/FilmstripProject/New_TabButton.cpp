/*
  ==============================================================================

    New_TabButton.cpp
    Created: 10 Dec 2024 2:20:43pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "New_TabButton.h"

New_TabButton::New_TabButton()
    : customLookAndFeel(Globals::getCustomLookAndFeel())
{
    //setLookAndFeel(customLookAndFeel.get());

    mainButton.setButtonText(name);
    mainButton.setComponentID("Buttons_ID_03_TAB");
    mainButton.setToggleState(true, juce::dontSendNotification);

    addAndMakeVisible(mainButton);

    closeButton.setButtonText("");
    closeButton.setComponentID("Buttons_ID_04_TAB_CLOSE");
    addAndMakeVisible(closeButton);
}

New_TabButton::~New_TabButton()
{
}

void New_TabButton::resized()
{
    mainButton.setBounds(getLocalBounds());

    auto space = 5;
    auto copyLocalBounds = getLocalBounds();
    auto closeButtonArea = copyLocalBounds.removeFromRight(copyLocalBounds.getHeight());
    closeButton.setBounds(closeButtonArea);
}

void New_TabButton::setMainButtonText(juce::String& name)
{
    this->name = name;
    mainButton.setButtonText(name);
}

juce::TextButton& New_TabButton::getMainButton()
{
    return mainButton;
}

juce::TextButton& New_TabButton::getCloseButton()
{
    return closeButton;
}
