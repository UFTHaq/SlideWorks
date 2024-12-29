/*
  ==============================================================================

    New_ControlAssetKnobScale.h
    Created: 10 Dec 2024 6:43:00pm
    Author:  UFTHaq

  ==============================================================================
*/

// Put this to -> New_SubControls
// inherit juce::Component

#pragma once

#include <JuceHeader.h>

#include "../Source/Globals.h"
#include "../Source/CustomLookAndFeel.h"
#include "../Source/CustomGroupComponent.h"

#include "New_ControlAsset.h"

class ControlAssetKnobScale
    : public ControlAsset
{
protected:
    std::shared_ptr <CustomLookAndFeel> customLookAndFeel{};

    CustomGroupComponent group{};

    // Still not sure if i need to put value min max for simulation here or in the simulation section.
    // Alright, just move the simulation control in simulation

    // Size width px slider
    // Size height px slider
    // Angle offset slider

public:
    ControlAssetKnobScale();
    ~ControlAssetKnobScale();

    void paint(juce::Graphics& g) override;
    void resized() override;
};