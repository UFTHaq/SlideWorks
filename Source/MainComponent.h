#pragma once

#include <JuceHeader.h>
#include "CustomLookAndFeel.h"
#include "CustomGroupComponent.h"

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

    void setupLayoutUI();
    bool getInputPathState();
    void checkInputPathState();
    void setupButtons();
    void setupKnobToggleButton();
    void setupSliderToggleButton();
    void setupBrowseButton();
    void setupExportButton();
    void toggleButtons(juce::TextButton& activeButton, juce::TextButton& inactiveButton);

    void setupAddKnobButton();
    void setupAddKnobScaleButton();
    void setupAddSliderTrackButton();
    void setupAddSliderThumbButton();
    void setupAddSliderScaleButton();
    void setupCloseDialog1Button();
    void setupCustomGroupComponents();
    void setupFilmstripControls();
    void resetDialog1();

    void fileChooserWindows(juce::String& inputPath);
    void updateUI();

    void openDialog1(juce::Graphics&);

private:
    //==============================================================================
    // Your private member variables go here...

    // Create pointer for CustomLookAndFeel object
    std::unique_ptr<CustomLookAndFeel> customLookAndFeel{};

    enum PageState
    {
        PAGE1,
        PAGE2
    };

    PageState SlideWorksPage{ PAGE1 };

    bool inputPathState{};

    juce::Rectangle<int> base_SlideWorks{};     // maybe change the name to page1_base_SlideWorks
    juce::Rectangle<int> base_WorkSpace{};
    juce::Rectangle<int> left_WorkSpace{};
    juce::Rectangle<int> right_WorkSpace{};     // page2_right_WorksSpace

    juce::TextButton knobToggleWorksButton{};
    juce::TextButton sliderToggleWorksButton{};
    juce::TextButton browseButton{};

    juce::String inputPathKnob{};
    juce::String inputPathKnobScale{};
    juce::String inputPathSliderTrack{};
    juce::String inputPathSliderThumb{};
    juce::String inputPathSliderScale{};

    std::unique_ptr<juce::FileChooser> fileChooser{};

    juce::TextButton addSliderTrack{};
    juce::TextButton addSliderThumb{};
    juce::TextButton addSliderScale{};

    bool openAddImage_Dialog1{};
    bool openAddImage_Dialog2{};

    CustomGroupComponent groupDialog1{};
    juce::TextButton addKnob{};
    juce::TextButton addKnobScale{};
    juce::TextButton closeDialog1{};

    ////////////////----------- PAGE 2 -----------////////////////
    juce::TextButton simulationButton{};
    juce::TextButton previewButton{};
    juce::TextButton resizeButton{};

    //////////----- LEFT WORKSPACE -----//////////

    /////--- FILMSTRIP BUTTONS ---/////
    juce::Rectangle<int> filmstripBanner{};

    // TOTAL FRAMES
    CustomGroupComponent groupTotalFrames{};
    int filmstripTotalFrames{};
    juce::Slider sliderTotalFrames{};
    juce::Rectangle<int> debugOutline{};       // only for debugging UI position of TotalFrames.

    // ORIENTATION
    CustomGroupComponent groupOrientation{};
    juce::TextButton horizontalButton{};
    juce::TextButton verticalButton{};
    bool filmstripIsVertical{};

    // ANGLES KNOB
    CustomGroupComponent groupKnobAngles{};
    int minAngleDegree{};
    int maxAngleDegree{};

    // THUMB POSITION
    CustomGroupComponent groupSliderThumbPositions{};
    int minThumbPosition{};
    int maxThumbPosition{};

    // EXPORT
    juce::TextButton exportButton{};
    bool isExportBundleWithScale{};

    //////////----- RIGHT WORKSPACE -----//////////
    juce::TextButton editButton{};




    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
