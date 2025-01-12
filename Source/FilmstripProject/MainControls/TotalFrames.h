/*
  ==============================================================================

    TotalFrames.h
    Created: 10 Dec 2024 4:04:55pm
    Author:  UFTHaq

  ==============================================================================
*/

// Put this to -> MainControls
// inherit juce::Component

// CustomGroupComponent TotalFrames
// Linear Slider
// Label Value

#pragma once

#include <JuceHeader.h>

#include "../Source/Globals.h"
#include "../Source/CustomComponents/CustomLookAndFeel.h"
#include "../Source/CustomComponents/CustomGroupComponent.h"

class TotalFrames
    : public juce::Component
{
protected:
    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};

    CustomGroupComponent group{};

    juce::Slider totalFrames{};
    juce::Label totalFrames_Label{};

    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(New_TotalFrames)

public:
    TotalFrames();
    ~TotalFrames();

    void paint(juce::Graphics& g) override;
    void resized() override;

    int getTotalFrames() const;

    void setupGroupComponent();
    void setColourGroup();
    void setupTotalFramesControl();
    void setColourTotalFrames();

    void resetCurrentTheme();
};