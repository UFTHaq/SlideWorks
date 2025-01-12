/*
  ==============================================================================

    TabButton.h
    Created: 10 Dec 2024 2:20:43pm
    Author:  UFTHaq

  ==============================================================================
*/

// Put this to -> FilmstripProject
// inherit juce::Component


// TabButton
// CloaseButton

#pragma once

#include <JuceHeader.h>

#include "../Source/CustomComponents/CustomLookAndFeel.h"
#include "../Source/EnumClass.h"
#include "../Source/Globals.h"

class TabButton
    : public juce::Component
{
protected:
    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};
    FilmstripType filmstripType{};

    juce::String name{"Untitled"};
    juce::TextButton mainButton{};
    juce::TextButton closeButton{};

    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(New_TabButton)
public:
    TabButton(const FilmstripType& type);
    ~TabButton();

    void resized() override;

    void setMainButtonText(juce::String& name);

    juce::TextButton& getMainButton();
    juce::TextButton& getCloseButton();
};