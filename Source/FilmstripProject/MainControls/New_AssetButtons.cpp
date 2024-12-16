/*
  ==============================================================================

    New_AssetButtons.cpp
    Created: 10 Dec 2024 5:22:46pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "New_AssetButtons.h"

New_AssetButtons::New_AssetButtons(const juce::String& type)
    : type(type)
{
    mainButton.setName(type);
    mainButton.setComponentID("Buttons_ID_11_MAIN_ASSET");
    mainButton.setToggleState(false, juce::dontSendNotification);
    addAndMakeVisible(mainButton);

    visibleButton.setComponentID("Buttons_ID_12_VISIBLE_ASSET");
    visibleButton.setToggleState(false, juce::dontSendNotification);
    addAndMakeVisible(visibleButton);

    deleteButton.setComponentID("Buttons_ID_13_DELETE_ASSET");
    deleteButton.setToggleState(false, juce::dontSendNotification);
    addAndMakeVisible(deleteButton);

    loadButton.setButtonText("Load Image");
    loadButton.setComponentID("Buttons_ID_14_LOAD_ASSET");
    loadButton.setToggleState(false, juce::dontSendNotification);
    addAndMakeVisible(loadButton);

    mainButton.setEnabled(false);
    visibleButton.setEnabled(false);
}

New_AssetButtons::~New_AssetButtons()
{
}

void New_AssetButtons::resized()
{
    auto bounds = getLocalBounds();
    auto center = bounds;
    auto buttonWidth = bounds.getHeight();

    mainButton.setBounds(bounds);

    auto deleteArea = bounds.removeFromRight(buttonWidth);
    deleteButton.setBounds(deleteArea.reduced(1));

    auto visibleArea = bounds.removeFromRight(buttonWidth);
    visibleArea.setX(visibleArea.getX() + 1);
    visibleButton.setBounds(visibleArea.reduced(1));

    auto loadArea = bounds.removeFromRight(120);
    loadArea.setX(loadArea.getX() + 1);
    loadArea = loadArea.withSizeKeepingCentre(loadArea.getWidth(), loadArea.getHeight() - 2);
    loadButton.setBounds(loadArea);
}

juce::TextButton& New_AssetButtons::getMainButton()
{
    return mainButton;
}

juce::TextButton& New_AssetButtons::getLoadImageButton()
{
    return loadButton;
}

juce::TextButton& New_AssetButtons::getVisibleButton()
{
    return visibleButton;
}

juce::TextButton& New_AssetButtons::getDeleteButton()
{
    return deleteButton;
}

void New_AssetButtons::setNameDisplay(const juce::String& fileName)
{
    if (fileName.isNotEmpty())
    {
        this->fileName = fileName;
        mainButton.setButtonText(fileName);

        loadButton.setVisible(false);
        loadButton.setEnabled(false);

        mainButton.setVisible(true);
        mainButton.setEnabled(true);
    }
    else
    {
        jassertfalse;
    }
}

juce::String New_AssetButtons::getNameDisplay() const
{
    return fileName;
}

void New_AssetButtons::setIndex(const size_t index)
{
    this->index = index;
}

const size_t& New_AssetButtons::getIndex() const
{
    return index;
}
