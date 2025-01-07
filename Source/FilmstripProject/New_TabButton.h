/*
  ==============================================================================

    New_TabButton.h
    Created: 10 Dec 2024 2:20:43pm
    Author:  UFTHaq

  ==============================================================================
*/

// Put this to -> New_FilmstripProject
// inherit juce::Component


// TabButton
// CloaseButton

#pragma once

#include <JuceHeader.h>

#include "../Source/CustomComponents/CustomLookAndFeel.h"
#include "../Source/Globals.h"

class New_TabButton
    : public juce::Component
{
protected:
    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};

    juce::String name{"Untitled"};

    juce::TextButton mainButton{};
    juce::TextButton closeButton{};

    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(New_TabButton)
public:
    New_TabButton();
    ~New_TabButton();

    void resized() override;

    void setMainButtonText(juce::String& name);

    juce::TextButton& getMainButton();
    juce::TextButton& getCloseButton();
};