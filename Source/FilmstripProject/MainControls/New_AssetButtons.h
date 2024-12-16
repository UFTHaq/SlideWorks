/*
  ==============================================================================

    New_AssetButtons.h
    Created: 10 Dec 2024 5:22:46pm
    Author:  UFTHaq

  ==============================================================================
*/

// Put this to -> New_AssetsManager
// inherit juce::Component

// Same as AssetButtons

#pragma once

#include <JuceHeader.h>

class New_AssetButtons
    : public juce::Component
{
protected:
    juce::String type{};
    juce::String fileName{};

    juce::TextButton mainButton{};
    juce::TextButton loadButton{};
    juce::TextButton visibleButton{};
    juce::TextButton deleteButton{};

    size_t index{};

public:
    New_AssetButtons(const juce::String& type);
    ~New_AssetButtons();

    void resized() override;

    juce::TextButton& getMainButton();
    juce::TextButton& getLoadImageButton();
    juce::TextButton& getVisibleButton();
    juce::TextButton& getDeleteButton();

    void setNameDisplay(const juce::String& fileName);
    juce::String getNameDisplay() const;

    void setIndex(const size_t index);
    const size_t& getIndex() const;
};