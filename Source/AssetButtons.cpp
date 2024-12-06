/*
  ==============================================================================

    AssetButtons.cpp
    Created: 5 Dec 2024 3:00:02pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "AssetButtons.h"

AssetButtons::AssetButtons(juce::String type, juce::String fileName)
    : type(type), fileName(fileName), customLookAndFeel(Globals::getCustomLookAndFeel())
{
    assetMainButton.setComponentID("Buttons_ID_12_MAIN_ASSET");
    assetMainButton.setToggleState(true, juce::dontSendNotification);
    assetMainButton.setLookAndFeel(customLookAndFeel.get());
    addAndMakeVisible(assetMainButton);

    assetVisibleButton.setComponentID("Buttons_ID_13_VISIBLE_ASSET");
    assetVisibleButton.setToggleState(true, juce::dontSendNotification);
    assetVisibleButton.setLookAndFeel(customLookAndFeel.get());
    addAndMakeVisible(assetVisibleButton);

    deleteAssetButton.setComponentID("Buttons_ID_14_DELETE_ASSET");
    deleteAssetButton.setToggleState(true, juce::dontSendNotification);
    deleteAssetButton.setLookAndFeel(customLookAndFeel.get());
    addAndMakeVisible(deleteAssetButton);
}

AssetButtons::~AssetButtons()
{
}

void AssetButtons::resized()
{
    auto bounds = getLocalBounds();

    auto deleteArea = bounds.removeFromRight(bounds.getHeight());
    deleteAssetButton.setBounds(deleteArea);

    auto visibleArea = bounds.removeFromRight(bounds.getHeight());
    assetVisibleButton.setBounds(visibleArea);
}

void AssetButtons::paint(juce::Graphics& g)
{
}
