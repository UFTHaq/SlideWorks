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
    void setupSimulationButton();
    void setupPreviewButton();
    void setupResizeButton();
    void togglingButtons(juce::TextButton& activeButton, juce::TextButton& inactiveButton);
    void togglingButtons(juce::TextButton& activeButton, juce::TextButton& inactiveButton1, juce::TextButton& inactiveButton2);

    void setupAddKnobButton();
    void setupAddKnobScaleButton();
    void setupAddSliderTrackButton();
    void setupAddSliderThumbButton();
    void setupAddSliderScaleButton();
    void setupCloseDialog1Button();
    void setupCustomGroupComponents();
    void setupFilmstripControls();
    void setupOrientationButtons();
    void setupAnglesKnobControls();

    void resetDialog1();
    void openDialog1(juce::Graphics&);

    void fileChooserWindows(juce::String& inputPath);
    void updateUI();


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

    enum ModeState
    {
        SIMULATION,
        PREVIEW,
        RESIZE
    };

    ModeState SlideWorksMode{ SIMULATION };

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
    juce::TextButton modeSimulationButton{};
    juce::TextButton modePreviewButton{};
    juce::TextButton modeResizeButton{};

    //////////----- LEFT WORKSPACE -----//////////

    /////--- FILMSTRIP BUTTONS ---/////
    juce::Rectangle<int> filmstripBanner{};

    // TOTAL FRAMES
    CustomGroupComponent groupTotalFrames{};
    int filmstripTotalFrames{};
    juce::Slider sliderTotalFrames{};
    juce::Label labelBoxTotalFrames{};
    juce::Rectangle<int> debugOutlineTotalFrames{};       // only for debugging UI position of TotalFrames.
    juce::Rectangle<int> debugOutlineLeftTotalFrames{};
    juce::Rectangle<int> debugOutlineRightTotalFrames{};

    // ORIENTATION
    CustomGroupComponent groupOrientation{};
    juce::TextButton horizontalButton{};
    juce::TextButton verticalButton{};
    bool filmstripIsVertical{};
    juce::Rectangle<int> debugOutlineOrientation{};
    juce::Rectangle<int> debugOutlineOrientationHorizontal{};
    juce::Rectangle<int> debugOutlineOrientationVertical{};

    // ANGLES KNOB
    CustomGroupComponent groupKnobAngles{};
    double minAngleDegree{};
    double maxAngleDegree{};
    juce::Label labelMinAngles{};
    juce::Label labelMaxAngles{};
    juce::Slider sliderMinAngles{};
    juce::Slider sliderMaxAngles{};
    juce::Rectangle<int> debugOutlineAngles{};
    juce::Rectangle<int> debugOutlineAnglesMin{};
    juce::Rectangle<int> debugOutlineAnglesMax{};
    juce::Rectangle<int> debugOutlineAnglesMinTop{};
    juce::Rectangle<int> debugOutlineAnglesMaxTop{};
    juce::Rectangle<int> debugOutlineAnglesMinKnob{};
    juce::Rectangle<int> debugOutlineAnglesMaxKnob{};

    // THUMB POSITION
    CustomGroupComponent groupSliderThumbPositions{};
    int minThumbPosition{};
    int maxThumbPosition{};

    // EXPORT
    juce::TextButton exportButton{};
    bool isExportBundleWithScale{};

    //////////----- RIGHT WORKSPACE -----//////////


    juce::Slider simulationKnob{};

    juce::TextButton editButton{};




    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
