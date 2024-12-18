#pragma once

#include <JuceHeader.h>
#include "CustomLookAndFeel.h"
#include "CustomGroupComponent.h"
#include "OpenGLComponent.h"

#include "ThemeColours.h"
#include "Globals.h"
#include "EnumClass.h"

#include "FilmstripProject.h"
#include "KnobFilmstrip.h"
#include "SliderFilmstrip.h"
#include "AssetButtons.h"

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
    void mouseDown(const juce::MouseEvent& event) override;
    void mouseDoubleClick(const juce::MouseEvent& event) override;

    void updatePageContent(juce::Graphics& g);

    void updatePage2WorkVisibility(bool visible);
    void anglesOrThumbPosVisibility(bool visible);
    void updatePage3InfoVisibility(bool visible);

    void setupLayoutUI();
    void setupKnobsOrSlidersMode(size_t activeIndex);
    void setupLayoutWorkingMode(size_t activeIndex);
    bool getInputPathState();
    void checkInputPathState();
    void loadSimulationImage();
    void setupButtons(CustomLookAndFeel* customLookAndFeel);
    void setupProjectButtons(CustomLookAndFeel* customLookAndFeel);
    void setupTabProjectButtons();
    size_t getActiveProjectIndex() const;
    void setNewProjectActiveAfterCreated();
    void setupNamingProjectLabel(CustomLookAndFeel* customLookAndFeel);
    void reloadNamingProjectLabel(size_t activeIndex);
    void togglingWorkingModeButton(WorkingMode mode);
    void reloadWorkingModeProject(size_t activeIndex);
    void setupBannerProjectTypeLabel(CustomLookAndFeel* customLookAndFeel);
    void reloadBannerFilmstripType(size_t activeIndex);
    void setupExportProjectButton();
    void reloadMainControlProject(size_t activeIndex);
    void setupAddNewAssetButton(CustomLookAndFeel* customLookAndFeel);
    void setupTotalFramesControl(CustomLookAndFeel* customLookAndFeel);
    void reloadTotalFramesControl(size_t activeIndex);
    void setupOrientationControl(CustomLookAndFeel* customLookAndFeel);
    void reloadOrientationControl(size_t activeIndex);
    void setupAnglesOrThumbPosControl(CustomLookAndFeel* customLookAndFeel);
    void reloadAnglesOrThumbPosControl(size_t activeIndex);
    void setupAssetsManager(CustomLookAndFeel* customLookAndFeel);
    void initializeDefaultAssets(std::vector<juce::String>& assetsType, size_t activeIndex);
    void reloadAssets(size_t activeIndex);
    size_t getActiveAssetIndex() const;
    void deleteAssetsProject(size_t index);
    void setupDefaultApplyButton();

    void reloadAllControls(size_t activeIndex);

    void setupKnobToggleButton();
    void setupSliderToggleButton();
    void setupBrowseButton();
    void setupExportButton();
    void setupSimulationButton();
    void setupPreviewButton();
    void setupEditButton();
    void togglingButtons(juce::TextButton& activeButton, juce::TextButton& inactiveButton);
    void togglingButtons(juce::TextButton& activeButton, juce::TextButton& inactiveButton1, juce::TextButton& inactiveButton2);

    void setupAddKnobButton();
    void setupAddKnobScaleButton();
    void setupAddSliderTrackButton();
    void setupAddSliderThumbButton();
    void setupAddSliderScaleButton();
    void setupCloseDialog1Button();
    void setupCustomGroupComponents();
    void setupFilmstripControls(CustomLookAndFeel* customLookAndFeel);
    void setupOrientationButtons();
    void setupAnglesKnobControls(CustomLookAndFeel* customLookAndFeel);

    void setupSimulationKnob(CustomLookAndFeel* customLookAndFeel);

    void resetDialog1();
    void openDialog1(juce::Graphics&);

    void fileChooserWindows(juce::String& inputPath);
    void fileChooserNew(std::function<void(juce::String)> onFileSelected);
    void updateUI();

    CustomLookAndFeel* ptr_Global_CustomLookAndFeel = Globals::getCustomLookAndFeel().get();
private:
    //==============================================================================
    // Your private member variables go here...

    enum class PageState
    {
        PAGE1_GREETINGS,
        PAGE2_WORKSPACE,
        PAGE3_INFO
    };

    PageState currentSlideWorksPage{ PageState::PAGE1_GREETINGS };
    PageState previousSlideWorksPage{};

    enum class ModeState
    {
        SIMULATION,
        PREVIEW,
        EDIT
    };

    //ModeState SlideWorksMode{ ModeState::SIMULATION };

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

    std::vector<std::unique_ptr<FilmstripProject>> filmstripProjects{};
    juce::Viewport filmstripButtonsViewport{};
    juce::Component filmstripButtonsContainer{};

    size_t projectActiveIndex{ SIZE_MAX };

        ///-- LABEL --///
    const int NamingLabelWidth{ 55 };
    const int NamingLabelEditorWidth{ 200 };

    juce::Label naming_Label{};
    juce::TextEditor naming_Editor{};

        ///-- MODE BUTTON --//
    const int MODEButtonWidth{ 80 };

    juce::TextButton mode_SimulationButton{};
    juce::TextButton mode_PreviewButton{};
    juce::TextButton mode_EditButton{};

    //////////////// MAIN CONTROL ////////////////
    juce::Rectangle<int> area_MainControl_Banner_And_Export{};
    juce::Rectangle<int> area_MainControl_Default_And_ApplyButtons{};
    juce::Rectangle<int> area_MainControl_Group_Angles_Or_ThumbPositions{};
    juce::Rectangle<int> area_MainControl_Group_Orientations{};
    juce::Rectangle<int> area_MainControl_Group_TotalFrames{};
    juce::Rectangle<int> area_MainControl_AssestsManager{};

        ///-- BANNER --///
    const int BannerHeight{ 34 };
    const int ExportButtonWidth{ 65 };

    juce::Label banner_FilmstripType_Label{};
    juce::TextButton export_ProjectButton{};

        ///-- DEFAULT APPLY --///
    const int DefaultApplyHeight{ 34 };
    juce::TextButton control_DefaultButton{};
    juce::TextButton control_ApplyButton{};

        ///-- ANGLES / THUMB POS --///
    const int group_AnglesOrThumbPos_Height{ 110 };

    CustomGroupComponent group_AnglesOrThumbPos{};

    juce::Label minText_Label{};
    juce::Label maxText_Label{};

    juce::Slider minAngle_Slider{};
    juce::Slider maxAngle_Slider{};
    juce::Label minAngleValue_Label{};
    juce::Label maxAngleValue_Label{};

    juce::Slider minThumbPos_Slider{};
    juce::Slider maxThumbPos_Slider{};
    juce::Label minThumbPosValue_Label{};
    juce::Label maxThumbPosValue_Label{};

        ///-- ORIENTATION --///
    const int group_Orientation_Height{ 70 };

    CustomGroupComponent group_Orientation{};

    juce::TextButton control_HorizontalButton{};
    juce::TextButton control_VerticalButton{};

        ///-- TOTAL FRAMES --///
    const int group_TotalFrames_Height{ 60 };
    CustomGroupComponent group_TotalFrames{};

    juce::Slider totalFrames_Slider{};
    juce::Label totalFrames_Label{};

        ///-- ASSETS MANAGER --///
    const int NewAssetButtonWidth{ 35 };
    const int NewAssetButtonHeight{ 20 };

    juce::String chooserPath{};
    std::vector<std::vector<std::unique_ptr<AssetButtons>>> assetsManagerPtr{};

    //std::vector<std::unique_ptr<Asset>>* projectAssets{ nullptr };
    //std::unique_ptr<std::vector<Asset>> projectAssets{};

    //std::vector<Asset> projectAssets{};
    //std::vector<std::shared_ptr<Asset>>* projectAssets{ nullptr };
    //std::shared_ptr<std::vector<std::shared_ptr<Asset>>> projectAssets{};

    //std::shared_ptr<std::vector<std::unique_ptr<Asset>>> projectAssets{};
    //std::vector<std::unique_ptr<Asset>> projectAssets{};
    //std::unique_ptr<std::vector<std::unique_ptr<Asset>>> projectAssets{ nullptr };
    //std::shared_ptr<std::vector<std::unique_ptr<Asset>>> projectAssets{ nullptr };

    //std::vector<Asset> projectAssets{};
    //std::vector<Asset>* projectAssets{ nullptr };
    size_t assetActiveIndex{};
    //std::vector<AssetButtons> buttonAssets{};
    //std::vector<std::vector<AssetButtons>> buttonAssets{};

    juce::TextButton add_NewAssetButton{};
    juce::Rectangle<int> area_assetsManager{};

    juce::Viewport assetsViewport{};
    juce::Component assetsContainer{};



    ////////////////----------- PAGE 3 -----------////////////////
    CustomGroupComponent groupDialog_2_Info{};
    juce::Label author_param{};
    juce::Label author_arg{};
    juce::Label version_param{};
    juce::Label version_arg{};
    juce::Label release_param{};
    juce::Label release_arg{};
    juce::Label license_param{};
    juce::Label license_arg{};
    juce::Label juceVersion_arg{};
    juce::TextButton closeDialog_2_Info{};


    //////////////// OLD BUTTON ////////////////
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
    bool filmstripIsVertical{true};
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

    juce::TextButton editButton{};
    
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
