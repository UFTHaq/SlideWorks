/*
  ==============================================================================

    New_ControlCanvas.h
    Created: 10 Dec 2024 5:50:36pm
    Author:  UFTHaq

  ==============================================================================
*/

// Put this to -> New_SubControls
// inherit juce::Component

// Control Canvas
// Canvas render work size
// - Knob : only size when has same width height, 
//     or just use both, and lock the aspect ratio
// - Slider : width and height, lock the aspect ratio
//   rotate button to determine the min max orientiation flow
// Color chooser
// 
// XY PAD, Z lighting
// Color chooser
// Intensity
// Bump
// Button Invert Bump

#pragma once

#include <JuceHeader.h>

#include "../Source/Globals.h"
#include "../Source/CustomLookAndFeel.h"
#include "../Source/CustomGroupComponent.h"

class ControlCanvas
    : public juce::Component
{
protected:
    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};

    CustomGroupComponent group{};

    // Radio or toggle to lock ratio
    // Size width px slider
    // Size height px slider
    // Color chooser


public:
    ControlCanvas();
    ~ControlCanvas();

    void paint(juce::Graphics& g) override;
    void resized() override;
};
