/*
  ==============================================================================

    FilmstripOrientation.h
    Created: 10 Dec 2024 4:12:47pm
    Author:  UFTHaq

  ==============================================================================
*/

// Put this to -> MainControls
// inherit juce::Component

// CustomGroupComponent Orientation
// Button Horizontal
// Button Vertical

#pragma once

#include <JuceHeader.h>

#include "../Source/Globals.h"
#include "../Source/EnumClass.h"
#include "../Source/CustomComponents/CustomLookAndFeel.h"
#include "../Source/CustomComponents/CustomGroupComponent.h"

class FilmstripOrientation
    : public juce::Component
{
protected:
    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};

    FilmstripOrientationEnum orientation{};
    CustomGroupComponent group{};

    juce::TextButton horizontalButton{};
    juce::TextButton verticalButton{};

    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(New_FilmstripOrientation)

public:
    FilmstripOrientation();
    ~FilmstripOrientation();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void setupGroupComponent();
    void setupButtonControls();

    bool isHorizontal() const;
    bool isVertical() const;
    FilmstripOrientationEnum getOrientation() const;
};