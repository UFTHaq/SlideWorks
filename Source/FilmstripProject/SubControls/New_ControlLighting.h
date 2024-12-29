/*
  ==============================================================================

    New_ControlLighting.h
    Created: 10 Dec 2024 5:50:02pm
    Author:  UFTHaq

  ==============================================================================
*/

// Put this to -> New_SubControls
// inherit juce::Component

// CustomGroupComponent
// Control Lighting
// XY PAD, Z lighting
// Color chooser
// Intensity
// Bump
// Button Invert Bump

#pragma once

#include <JuceHeader.h>

#include "../Source/CustomGroupComponent.h"
#include "../Source/CustomLookAndFeel.h"
#include "../Source/Globals.h"

class ControlLighting
    : public juce::Component
{
protected:
    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};

    CustomGroupComponent group{};

    // XY 
    // Z slider
    // Color label
    // Color Chooser with hex code
    // Intensity label
    // Intensity slider
    // Bump label
    // Bump slider
    // juce::TextButton invertBump{};

public:
    ControlLighting();
    ~ControlLighting();

    void paint(juce::Graphics& g) override;
    void resized() override;
};