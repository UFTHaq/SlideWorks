/*
  ==============================================================================

    Footer.h
    Created: 15 Dec 2024 8:52:43pm
    Author:  UFTHaq

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "../Source/Globals.h"
#include "../Source/CustomLookAndFeel.h"

class Footer
    : public juce::Component
{
protected:
    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};

    juce::Rectangle<int> bounds{};

public:
    Footer();
    ~Footer();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void drawBackground(juce::Graphics& g);
};