/*
  ==============================================================================

    New_ControlAssetTrackScale.h
    Created: 10 Dec 2024 6:44:01pm
    Author:  UFTHaq

  ==============================================================================
*/

// Put this to -> New_SubControls
// inherit juce::Component

#pragma once

#include <JuceHeader.h>

#include "../Source/Globals.h"
#include "../Source/CustomComponents/CustomLookAndFeel.h"
#include "../Source/CustomComponents/CustomGroupComponent.h"

#include "New_ControlAsset.h"

class ControlAssetTrackScale
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
    ControlAssetTrackScale();
    ~ControlAssetTrackScale();

    void paint(juce::Graphics& g) override;
    void resized() override;
};