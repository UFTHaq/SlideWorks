#pragma once

#include <JuceHeader.h>
#include "CustomLookAndFeel.h"
#include "CustomGroupComponent.h"
#include "OpenGLComponent.h"

#include "ThemeColours.h"
#include "Globals.h"
#include "EnumClass.h"

#include "FilmstripProject/New_FilmstripProject.h"
#include "PageInfo/PageInfo.h"


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

    void updatePageContent(juce::Graphics& g);

    void NewUpdateVisibilityPAGE_2(bool visible);
    void updatePage3InfoVisibility(bool visible);

    void setupLayoutUI();
    void setupButtons(CustomLookAndFeel* customLookAndFeel);
    void setupPageInfo();

    void setupProjectButtons(CustomLookAndFeel* customLookAndFeel);
    void setupSimulationKnob(CustomLookAndFeel* customLookAndFeel);

    CustomLookAndFeel* ptr_Global_CustomLookAndFeel = Globals::getCustomLookAndFeel().get();
private:
    //==============================================================================
    // Your private member variables go here...

    PageState currentSlideWorksPage{ PageState::PAGE1_GREETINGS };
    PageState previousSlideWorksPage{};


    WorkingMode workingMode{ WorkingMode::SIMULATION_MODE };

    bool inputPathState{};

    juce::Rectangle<int> base_SlideWorks{};     // maybe change the name to page1_base_SlideWorks
    juce::Rectangle<int> base_Workspace{};
    juce::Rectangle<int> left_WorkSpace{};      // Will be deleted
    juce::Rectangle<int> right_WorkSpace{};     // page2_right_WorksSpace

    //////////////// NEW UI ////////////////

    //////////////// NEW BUTTON ////////////////
    const int MenuButtonWidth{ 52 };
    const int MenuButtonHeight{ 22 };

    juce::TextButton SW_NewProjectButton{};
    juce::TextButton SW_ThemeButton{};
    juce::TextButton SW_InfoButton{};

    ////////////////----------- PAGE 2 -----------////////////////
    const int FooterHeight    { 25 };
    const int MainControlWidth{ 240 };
    const int FPButtonWidth{ 100 };
    const int ModeButtonHeight{ 25 };
    const int SubControlWidth { 190 };

    juce::Rectangle<int> area_Footer{};
    juce::Rectangle<int> area_MainControl{};
    juce::Rectangle<int> area_Layer1_MainWorkspace{};
    juce::Rectangle<int> area_FilmstripProjects{};
    juce::Rectangle<int> area_Layer2_MainWorkspace{};
    juce::Rectangle<int> area_ModeButtons{};
    juce::Rectangle<int> area_Layer3_MainWorkspace{};
    juce::Rectangle<int> area_Canvas{};
    juce::Rectangle<int> area_SubControl{};

    juce::Colour canvasColor = Globals::getCustomLookAndFeel()->getCurrentTheme().SlideworksBaseColour;

    std::vector<std::unique_ptr<New_FilmstripProject>> newFilmstripProjects{};

    ////////////////----------- PAGE 3 -----------////////////////
    PageInfo pageInfo{};

    /////////////////////////////////////////////////////////////////

    
    // SIMULATION 
    // TODO: 
    // - Make slider rotary (knob), and make it work by real implementation of filmstrip already made in background according to setup filmstrip.
    // - zoom in out to resize the display.
    // - set the simulation min max value to control.
    //
    juce::Slider simulationKnob{};
    juce::Slider simulationSlider{};
    int simulationInterval{};
    juce::Rectangle<int> debugOutlineSimulationArea{};
    juce::Image debugImageSimulation{};
    bool isSimulationImageLoaded{false};

    // PREVIEW
    // TODO:
    // - Display the filmstrip that already made (like zen pixel do).
    // - Using rectangle as abstraction area to display
    // - zoom in out, scrolling.
    //
    juce::Rectangle<int> previewFilmstripArea{};        // will be dynamic according to setup (total frames, orientation)

    // RESIZE
    // - Display and choose the image need to resize (need to click the iamge symbol to activate the image).
    // - Using rectangles as abstraction to resize each images (knob, scale), and will always centred.
    // - Resize the slider will be different.
    // - It will have base workspace long wide rectangle. and can arrange the rectangle of track, thumb and scale.
    //
    juce::Rectangle<int> resizeKnob{};
    juce::Rectangle<int> resizeKnobScale{};
    juce::Rectangle<int> resizeSliderTrack{};
    juce::Rectangle<int> resizeSliderThumb{};
    juce::Rectangle<int> resizeSliderScale{};



    OpenGLComponent openGLComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
