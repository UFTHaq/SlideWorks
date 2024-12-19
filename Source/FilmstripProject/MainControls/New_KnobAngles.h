/*
  ==============================================================================

    New_KnobAngles.h
    Created: 10 Dec 2024 4:14:06pm
    Author:  UFTHaq

  ==============================================================================
*/

// Put this to -> New_MainControls
// inherit juce::Component

// CustomGroupComponent Angles
// Min, Max - Label
// Min, Max - Value
// Min, Max - Rotary Slider

// Do mouse down double click at knob area and make the label is enabled so i can edit, 
// but when press return key its disabled, only visible so not bloking input for dragging

#pragma once

#include <JuceHeader.h>

#include "../Source/Globals.h"
#include "../Source/CustomLookAndFeel.h"
#include "../Source/CustomGroupComponent.h"

class New_KnobAngles
    : public juce::Component
{
protected:
    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};

    CustomGroupComponent group{};

    juce::Slider minAngle{};
    juce::Slider maxAngle{};
    juce::Label minText_Label{};
    juce::Label maxText_Label{};
    juce::TextEditor minValue_Label{};
    juce::TextEditor maxValue_Label{};

    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(New_KnobAngles)

public:
    New_KnobAngles();
    ~New_KnobAngles();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void mouseDown(const juce::MouseEvent& event) override;
    void mouseDoubleClick(const juce::MouseEvent& event) override;

    void setupGroupComponent();
    void setColourGroup();
    void setupAngleControls();

    void setColourMinAngle();
    void setColourMaxAngle();

    double getMinAngle() const;
    double getMaxAngle() const;

    CustomGroupComponent& getGroup();

    void resetCurrentTheme();
};