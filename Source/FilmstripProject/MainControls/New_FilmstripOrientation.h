/*
  ==============================================================================

    New_FilmstripOrientation.h
    Created: 10 Dec 2024 4:12:47pm
    Author:  UFTHaq

  ==============================================================================
*/

// Put this to -> New_MainControls
// inherit juce::Component

// CustomGroupComponent Orientation
// Button Horizontal
// Button Vertical

#pragma once

#include <JuceHeader.h>

#include "../Source/Globals.h"
#include "../Source/EnumClass.h"
#include "../Source/CustomLookAndFeel.h"
#include "../Source/CustomGroupComponent.h"

class New_FilmstripOrientation
    : public juce::Component
{
protected:
    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};

    FilmstripOrientation orientation{};
    CustomGroupComponent group{};

    juce::TextButton horizontalButton{};
    juce::TextButton verticalButton{};

    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(New_FilmstripOrientation)

public:
    New_FilmstripOrientation();
    ~New_FilmstripOrientation();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void setupGroupComponent();
    void setupButtonControls();

    bool isHorizontal() const;
    bool isVertical() const;
    FilmstripOrientation getOrientation() const;
};