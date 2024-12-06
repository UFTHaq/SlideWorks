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

    juce::TextButton assetMainButton{};
    juce::TextButton assetVisibleButton{};
    juce::TextButton deleteAssetButton{};

    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AssetButtons)

public:
    AssetButtons(juce::String type, juce::String fileName);
    ~AssetButtons();

    void resized() override;
    void paint(juce::Graphics& g) override;
};