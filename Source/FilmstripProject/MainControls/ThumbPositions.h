/*
  ==============================================================================

    ThumbPositions.h
    Created: 10 Dec 2024 4:14:47pm
    Author:  UFTHaq

  ==============================================================================
*/

// Put this to -> MainControls
// inherit juce::Component

// CustomGroupComponent Thumb Positions
// Min, Max - Label
// Min, Max - Linear Slider
// Min, Max - Value

#pragma once

#include <JuceHeader.h>

#include "../Source/Globals.h"
#include "../Source/CustomComponents/CustomLookAndFeel.h"
#include "../Source/CustomComponents/CustomGroupComponent.h"

class ThumbPositions
    : public juce::Component
{
protected:
    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};

    CustomGroupComponent group{};

    juce::Slider minThumbPos{};
    juce::Slider maxThumbPos{};
    juce::Label maxText_Label{};
    juce::Label minText_Label{};
    juce::Label minValue_Label{};
    juce::Label maxValue_Label{};

    double rounded_2Digit(double value);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ThumbPositions)

public:
    ThumbPositions();
    ~ThumbPositions();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void setupGroupComponent();
    void setColourGroup();
    void setupThumbControls();

    void setColourMinPos();
    void setColourMaxPos();

    double getMinThumbPos() const;
    double getMaxThumbPos() const;

    CustomGroupComponent& getGroup();

    void resetCurrentTheme();
};