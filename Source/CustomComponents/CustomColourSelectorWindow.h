/*
  ==============================================================================

    ColourSelectorWindow.h
    Created: 3 Jan 2025 9:40:40pm
    Author:  UFTHaq

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "CustomLookAndFeel.h"
#include "../Source/Globals.h"
#include "CustomColourSelector.h"

class CustomColourSelectorWindow final
    : public juce::DocumentWindow
    , private juce::ChangeListener
{
protected:
    CustomColourSelector selector{ CustomColourSelector::showColourAtTop
                                       | CustomColourSelector::showSliders
                                       | CustomColourSelector::showColourspace };

    //juce::ColourSelector selector{ juce::ColourSelector::showColourAtTop
    //                             | juce::ColourSelector::showSliders
    //                             | juce::ColourSelector::showColourspace };

    juce::TextButton& colorButton;  // Hold reference of the colorButton
    juce::Label& colorValue;        // Hold reference of the colorValue

    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};

    juce::Colour color{};

    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    juce::Colour autoTextColor(juce::Colour& color);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomColourSelectorWindow)

public:
    CustomColourSelectorWindow(
        const juce::String& name 
        , juce::Colour backgroundColor
        , int buttonsNeeded
        , juce::TextButton& colorButton
        , juce::Label& colorValue
    );
    ~CustomColourSelectorWindow() override;

    void closeButtonPressed() override;
};  

// TODO: CUSTOM JUCE::COLOURSELECTOR