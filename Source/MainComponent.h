#pragma once

#include <JuceHeader.h>
#include "CustomLookAndFeel.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component,
                       public juce::Timer,
                       public juce::Button::Listener,
                       public juce::FileDragAndDropTarget,
                       public juce::DragAndDropContainer
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;
    void buttonClicked(juce::Button* button) override;
    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    void filesDropped(const juce::StringArray& files, int x, int y) override;

    bool getInputPathState();
    bool checkInputPathState();
    void setupButtons();
    void setupKnobToggleButton();
    void setupSliderToggleButton();
    void setupBrowseButton();
    void toggleButtons(juce::TextButton& activeButton, juce::TextButton& inactiveButton);

    void updateUI();


    /////////////////////////  DEBUG  ////////////////////////////
    int debugInterval{ 1000 };
    int debugTime{ 0 };

private:
    //==============================================================================
    // Your private member variables go here...

    // Create pointer for CustomLookAndFeel object
    std::unique_ptr<CustomLookAndFeel> customLookAndFeel{};

    bool inputPathState{};

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

    std::unique_ptr<juce::FileChooser> fileChooser{};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
