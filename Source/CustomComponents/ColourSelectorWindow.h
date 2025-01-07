/*
  ==============================================================================

    ColourSelectorWindow.h
    Created: 3 Jan 2025 9:40:40pm
    Author:  UFTHaq

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ColourSelectorWindow final
    : public juce::DocumentWindow
    , private juce::ChangeListener
{
protected:
    juce::ColourSelector selector{ juce::ColourSelector::showColourAtTop
                                 | juce::ColourSelector::showSliders
                                 | juce::ColourSelector::showColourspace };

    juce::TextButton& colorButton;  // Hold reference of the colorButton
    juce::Label& colorValue;        // Hold reference of the colorValue

    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    juce::Colour autoTextColor(juce::Colour& color);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ColourSelectorWindow)

public:
    ColourSelectorWindow(
        const juce::String& name 
        , juce::Colour backgroundColor
        , int buttonsNeeded
        , juce::TextButton& colorButton
        , juce::Label& colorValue
    );
    ~ColourSelectorWindow() override;

    void closeButtonPressed() override;
};  
