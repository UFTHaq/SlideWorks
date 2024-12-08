/*
  ==============================================================================

    AssetButtons.cpp
    Created: 5 Dec 2024 3:00:02pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "AssetButtons.h"

AssetButtons::AssetButtons(const juce::String type)
    : type(type), customLookAndFeel(Globals::getCustomLookAndFeel())
{
    assetMainButton.setComponentID("Buttons_ID_11_MAIN_ASSET");
    assetMainButton.setToggleState(false, juce::dontSendNotification);
    assetMainButton.setLookAndFeel(customLookAndFeel.get());
    addAndMakeVisible(assetMainButton);

    assetVisibleButton.setComponentID("Buttons_ID_12_VISIBLE_ASSET");
    assetVisibleButton.setToggleState(true, juce::dontSendNotification);
    assetVisibleButton.setLookAndFeel(customLookAndFeel.get());
    addAndMakeVisible(assetVisibleButton);

    deleteAssetButton.setComponentID("Buttons_ID_13_DELETE_ASSET");
    deleteAssetButton.setToggleState(false, juce::dontSendNotification);
    deleteAssetButton.setLookAndFeel(customLookAndFeel.get());
    addAndMakeVisible(deleteAssetButton);

    loadImageButton.setButtonText("Load Image");
    loadImageButton.setComponentID("Buttons_ID_14_LOAD_ASSET");
    loadImageButton.setToggleState(false, juce::dontSendNotification);
    loadImageButton.setLookAndFeel(customLookAndFeel.get());
    addAndMakeVisible(loadImageButton);

    assetMainButton.setEnabled(false);
    assetVisibleButton.setEnabled(false);
}

AssetButtons::~AssetButtons()
{
}

void AssetButtons::resized()
{
    auto bounds = getLocalBounds();

    assetMainButton.setBounds(bounds);

    auto deleteArea = bounds.removeFromRight(bounds.getHeight());
    deleteAssetButton.setBounds(deleteArea);

    auto visibleArea = bounds.removeFromRight(bounds.getHeight());
    assetVisibleButton.setBounds(visibleArea);

    auto area = getLocalBounds();
    area = area.withSizeKeepingCentre(int(area.getWidth() * 0.5F), area.getHeight() - 4);
    loadImageButton.setBounds(area);
}

void AssetButtons::paint(juce::Graphics& g)
{
}

void AssetButtons::reloadButtonVisibility()
{

    {
        bool visible{ true };

        if (fileName == "") visible = true;
        else visible = false;

        loadImageButton.setVisible(visible);
        loadImageButton.setEnabled(visible);
    }

    {
        bool enable{ true };
        if (fileName != "") enable = true;
        else enable = false;

        assetMainButton.setEnabled(enable);
        assetVisibleButton.setEnabled(enable);
    }
}

void AssetButtons::setIndex(size_t index)
{
    this->index = index;
}

size_t AssetButtons::getIndex()
{
    return index;
}

void AssetButtons::setNameDisplay(juce::String fileName)
{
    this->fileName = fileName;
    assetMainButton.setButtonText(fileName);
}

juce::String AssetButtons::getNameDisplay()
{
    return juce::String(fileName);
}
