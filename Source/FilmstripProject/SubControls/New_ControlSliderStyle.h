/*
  ==============================================================================

    New_ControlSliderStyle.h
    Created: 31 Dec 2024 11:45:35am
    Author:  UFTHaq

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "../Source/EnumClass.h"
#include "../Source/Globals.h"
#include "../Source/CustomComponents/CustomLookAndFeel.h"
#include "../Source/CustomComponents/CustomGroupComponent.h"

class ControlSliderStyle
    : public juce::Component
{
protected:
    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};

    CustomGroupComponent group{};

    bool styleHorizontal{ true };
    juce::TextButton toggleButton{};

public:
    ControlSliderStyle();
    ~ControlSliderStyle();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void setupGroupComponent();
    void setColourGroup();
    void setupToggleButton();

    void resetCurrentTheme();

    bool isStyleHorizontal() const;
};