/*
  ==============================================================================

    ControlAssetTrack.h
    Created: 10 Dec 2024 6:43:38pm
    Author:  UFTHaq

  ==============================================================================
*/

// Put this to -> SubControls
// inherit juce::Component

#pragma once

#include <JuceHeader.h>

#include "../Source/Globals.h"
#include "../Source/CustomComponents/CustomLookAndFeel.h"
#include "../Source/CustomComponents/CustomGroupComponent.h"

#include "ControlAsset.h"

class ControlAssetTrack
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
    ControlAssetTrack();
    ~ControlAssetTrack();

    void paint(juce::Graphics& g) override;
    void resized() override;
};