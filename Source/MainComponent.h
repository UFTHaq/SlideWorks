#pragma once

#include <JuceHeader.h>
#include "CustomLookAndFeel.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    bool inputPathEmptyCheck();
    void toggleButtons(juce::TextButton& activeButton, juce::TextButton& inactiveButton);

private:
    //==============================================================================
    // Your private member variables go here...

    // Create pointer for CustomLookAndFeel object
    std::unique_ptr<CustomLookAndFeel> customLookAndFeel{};

    bool isInputPathEmpty{};

    juce::Rectangle<int> baseSlideWorks{};
    juce::Rectangle<int> baseWorkSpace{};

    juce::TextButton knobToggleWorksButton{};
    juce::TextButton sliderToggleWorksButton{};
    juce::TextButton browseButton{};

    juce::String inputPathKnob{};
    juce::String inputPathKnobScale{};

    juce::String inputPathSliderTrack{};
    juce::String inputPathSliderThumb{};
    juce::String inputPathSliderScale{};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
