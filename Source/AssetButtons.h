/*
  ==============================================================================

    AssetButtons.h
    Created: 5 Dec 2024 3:00:02pm
    Author:  UFTHaq

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomLookAndFeel.h"
#include "Globals.h"

class AssetButtons
    : public juce::Component
{
protected:
    juce::String type{};
    juce::String fileName{};

    juce::TextButton assetVisibleButton{};
    juce::TextButton deleteAssetButton{};

    size_t index{};

    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AssetButtons)

public:
    AssetButtons(const juce::String type);
    ~AssetButtons();

    void resized() override;
    void paint(juce::Graphics& g) override;

    void reloadButtonVisibility();

    juce::TextButton assetMainButton{};
    juce::TextButton loadImageButton{};

    void setIndex(size_t index);
    size_t getIndex();

    void setNameDisplay(juce::String fileName);
    juce::String getNameDisplay();
};