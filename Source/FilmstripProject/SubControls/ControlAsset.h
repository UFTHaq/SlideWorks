/*
  ==============================================================================

    ControlAsset.h
    Created: 28 Dec 2024 5:54:08pm
    Author:  UFTHaq

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ControlAsset
    : public juce::Component
{
public:
    ControlAsset();
    ~ControlAsset();

    void paint(juce::Graphics& g) override;
    void resized() override;
};