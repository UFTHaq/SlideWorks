/*
  ==============================================================================

    ControlAssetThumb.h
    Created: 10 Dec 2024 6:43:17pm
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

class ControlAssetThumb
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

    // For all component of Sliders
    // All component will be in center. 
    // if (Horizontal = center X), so the component can be control up and down
    // if (Vertical = center Y), so the component can be control left and right
    // So need to track what the slider style is (horizontal / vertical) and track where the min side and the max side
    // Initial idea, (horizontal = left min, right max), (vertical = bottom min, top max)

public:
    ControlAssetThumb();
    ~ControlAssetThumb();

    void paint(juce::Graphics& g) override;
    void resized() override;
};