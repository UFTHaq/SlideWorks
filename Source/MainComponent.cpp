#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize(820, 540);   // This is mandatory to not trigger error in debug mode

    setupLayoutUI();
    setupButtons(ptr_Global_CustomLookAndFeel);

    setupCustomGroupComponents();

    updateUI();
}

MainComponent::~MainComponent()
{
    stopTimer();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)

    updatePageContent(g);

}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

    setupLayoutUI();
}


void MainComponent::timerCallback()
{

}


void MainComponent::buttonClicked(juce::Button* button)
{
    // THIS buttonClicked methods is kinda obsolete now according to chatGPT, so will delete it later. and use lambda + function.
    if (button == &browseButton)
    {
        //fileChooserWindows();
    }
}

bool MainComponent::isInterestedInFileDrag(const juce::StringArray& files)  // This should be called in everycallback but not.
{
    for (auto& file : files)
    {
        if (file.endsWith(".png")) return true;
    }
    return false;
}

void MainComponent::filesDropped(const juce::StringArray& files, int x, int y)
{
    if (files.size() > 0)
    {
        juce::File selectedFile = juce::File(files[0]);
        if (selectedFile.existsAsFile())
        {
            juce::String path = selectedFile.getFullPathName();
            DBG("Dropped file: " << path);

            if (knobToggleWorksButton.getToggleState())
            {
                inputPathKnob = path;
            }
            else {
                inputPathSliderTrack = path;
            }

            updateUI();

            DBG("getInputPathState: " << (getInputPathState() ? "true" : "false"));
        }
    }

    juce::MouseCursor normalCursor = juce::MouseCursor(juce::MouseCursor::StandardCursorType::NormalCursor);
    juce::Desktop::getInstance().getMainMouseSource().showMouseCursor(normalCursor);
}

void MainComponent::updatePageContent(juce::Graphics& g)
{
    g.fillAll(ptr_Global_CustomLookAndFeel->getBackgroundColour());

    if (currentSlideWorksPage == PageState::PAGE1_GREETINGS)
    {
        g.setColour(ptr_Global_CustomLookAndFeel->getCurrentTheme().Page_1);
        g.fillRoundedRectangle(base_Workspace.toFloat(), 1);

        if (openAddImage_Dialog1 == false)
        {
            g.setFont(ptr_Global_CustomLookAndFeel->getFontRobotoCondensedBold().withHeight(ptr_Global_CustomLookAndFeel->getFontSizeTitle()));
            g.setColour(ptr_Global_CustomLookAndFeel->getColorCustomDarkGrey());

            g.drawText("Filmstrip Knob & Slider Generator", base_Workspace, juce::Justification::centred, true);
        }

        if (openAddImage_Dialog1 == true)
        {
            openDialog1(g);
        }
    }

    if (currentSlideWorksPage == PageState::PAGE2_WORKSPACE)
    {
        g.setColour(ptr_Global_CustomLookAndFeel->getCurrentTheme().ButtonsID_01_ON);
        
        g.fillRoundedRectangle(area_Footer.toFloat(), 1);
        g.fillRoundedRectangle(area_MainControl.toFloat(), 1);
        g.fillRoundedRectangle(area_Layer1_MainWorkspace.toFloat(), 1);

        g.setColour(ptr_Global_CustomLookAndFeel->getCurrentTheme().SlideworksBaseColour);
        g.fillRoundedRectangle(area_Layer2_MainWorkspace.toFloat(), 1);
        g.setColour(ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomDarkest);
        g.drawRoundedRectangle(area_Layer2_MainWorkspace.toFloat(), 1, 0.2F);

        g.setColour(ptr_Global_CustomLookAndFeel->getCurrentTheme().SlideworksBaseColour);
        g.fillRoundedRectangle(area_Layer3_MainWorkspace.toFloat(), 1);

        g.setColour(ptr_Global_CustomLookAndFeel->getCurrentTheme().SlideworksBaseColour);
        g.fillRoundedRectangle(area_Canvas.toFloat(), 1);
        g.setColour(ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomDarkest);
        g.drawRoundedRectangle(area_Canvas.toFloat(), 1, 0.2F);

        g.setColour(ptr_Global_CustomLookAndFeel->getCurrentTheme().ButtonsID_01_ON);
        g.fillRoundedRectangle(area_SubControl.toFloat(), 1);
        g.setColour(ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomDarkest);
        g.drawRoundedRectangle(area_SubControl.toFloat(), 1, 0.2F);

        g.setColour(ptr_Global_CustomLookAndFeel->getCurrentTheme().BannerFilmstripType);
        g.fillRoundedRectangle(area_MainControl_Banner_And_Export.toFloat(), 2.0F);
        g.setColour(ptr_Global_CustomLookAndFeel->getCurrentTheme().BannerFilmstripType.darker(0.1F));
        g.drawRoundedRectangle(area_MainControl_Banner_And_Export.toFloat(), 2.0F, 1.5F);

        g.setColour(ptr_Global_CustomLookAndFeel->getCurrentTheme().SlideworksBaseColour);
        g.fillRoundedRectangle(area_assetsManager.toFloat(), 1);
        g.setColour(ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomGrey);
        g.drawRoundedRectangle(area_assetsManager.toFloat(), 1, 0.2F);

        group_AnglesOrThumbPos.paint(g);
        group_Orientation.paint(g);
        group_TotalFrames.paint(g);


    }
    
    //if (currentSlideWorksPage == PageState::PAGE2_WORKSPACE)
    //{
    //    g.setColour(ptr_Global_CustomLookAndFeel->getColorCustomLightGrey());

    //    g.fillRoundedRectangle(left_WorkSpace.toFloat(), ptr_Global_CustomLookAndFeel->getRoundedCornerSize());
    //    g.fillRoundedRectangle(right_WorkSpace.toFloat(), ptr_Global_CustomLookAndFeel->getRoundedCornerSize());

    //    g.setColour(ptr_Global_CustomLookAndFeel->getColorCustomDarkGrey());
    //    g.fillRoundedRectangle(filmstripBanner.toFloat(), ptr_Global_CustomLookAndFeel->getRoundedCornerSize());

    //    g.setFont(ptr_Global_CustomLookAndFeel->getFontRobotoCondensedBold().withHeight(18));
    //    g.setColour(ptr_Global_CustomLookAndFeel->getColorCustomWhite());
    //    g.drawText("FILMSTRIP", filmstripBanner, juce::Justification::centred, true);

    //    if (knobToggleWorksButton.getToggleState())
    //    {
    //        groupTotalFrames.paint(g);
    //        groupOrientation.paint(g);
    //        groupKnobAngles.paint(g);
    //    }

    //    if (sliderToggleWorksButton.getToggleState())
    //    {
    //        groupTotalFrames.paint(g);
    //        groupOrientation.paint(g);
    //        groupSliderThumbPositions.paint(g);
    //    }

    //    // debug only
    //    g.setColour(ptr_Global_CustomLookAndFeel->getColorCustomGrey());
    //    //g.drawRoundedRectangle(debugOutlineTotalFrames.toFloat().reduced(debugOutlineTotalFrames.getWidth() * 0.01F), 5.0F, 1.0F);
    //    //g.drawRoundedRectangle(debugOutlineLeftTotalFrames.toFloat().reduced(debugOutlineTotalFrames.getWidth() * 0.01F), 5.0F, 1.0F);
    //    //g.drawRoundedRectangle(debugOutlineRightTotalFrames.toFloat().reduced(debugOutlineTotalFrames.getWidth() * 0.01F), 5.0F, 1.0F);

    //    //g.drawRoundedRectangle(debugOutlineOrientation.toFloat().reduced(debugOutlineOrientation.getWidth() * 0.01F), 5.0F, 1.0F);
    //    //g.drawRoundedRectangle(debugOutlineOrientationHorizontal.toFloat().reduced(debugOutlineOrientation.getWidth() * 0.01F), 5.0F, 1.0F);
    //    //g.drawRoundedRectangle(debugOutlineOrientationVertical.toFloat().reduced(debugOutlineOrientation.getWidth() * 0.01F), 5.0F, 1.0F);

    //    //g.drawRoundedRectangle(debugOutlineAngles.toFloat().reduced(debugOutlineAngles.getWidth() * 0.01F), 5.0F, 1.0F);
    //    //g.drawRoundedRectangle(debugOutlineAnglesMin.toFloat().reduced(debugOutlineAnglesMin.getWidth() * 0.01F), 5.0F, 1.0F);
    //    //g.drawRoundedRectangle(debugOutlineAnglesMax.toFloat().reduced(debugOutlineAnglesMax.getWidth() * 0.01F), 5.0F, 1.0F);

    //    //g.drawRoundedRectangle(debugOutlineAnglesMinTop.toFloat().reduced(debugOutlineAnglesMinTop.getWidth() * 0.01F), 5.0F, 1.0F);
    //    //g.drawRoundedRectangle(debugOutlineAnglesMinKnob.toFloat().reduced(debugOutlineAnglesMinKnob.getWidth() * 0.01F), 5.0F, 1.0F);

    //    //g.drawRoundedRectangle(debugOutlineAnglesMaxTop.toFloat().reduced(debugOutlineAnglesMaxTop.getWidth() * 0.01F), 5.0F, 1.0F);
    //    //g.drawRoundedRectangle(debugOutlineAnglesMaxKnob.toFloat().reduced(debugOutlineAnglesMaxKnob.getWidth() * 0.01F), 5.0F, 1.0F);

    //    if (SlideWorksMode == ModeState::SIMULATION)
    //    {
    //        g.setColour(ptr_Global_CustomLookAndFeel->getColorCustomWhite());
    //        g.drawRoundedRectangle(debugOutlineSimulationArea.toFloat(), 3.0F, 0.5F);
    //    }

    //}

    if (currentSlideWorksPage == PageState::PAGE3_INFO)
    {
        g.setColour(ptr_Global_CustomLookAndFeel->getCurrentTheme().Page_1);
        g.fillRoundedRectangle(base_Workspace.toFloat(), 1);
        
        groupDialog_2_Info.paint(g);
    }
}

void MainComponent::updatePage2WorkVisibility(bool visible)
{
    for (size_t i = 0; i < filmstripProjects.size(); i++)
    {
        auto& button = filmstripProjects.at(i);

        if (button != nullptr)
        {
            button.get()->setVisible(visible);
            button.get()->setEnabled(visible);

        }
    }

    {
        naming_Label.setVisible(visible);
        naming_Label.setEnabled(visible);

        naming_Editor.setVisible(visible);
        naming_Editor.setEnabled(visible);
    }

    {
        mode_SimulationButton.setVisible(visible);
        mode_SimulationButton.setEnabled(visible);
        mode_PreviewButton.setVisible(visible);
        mode_PreviewButton.setEnabled(visible);
        mode_EditButton.setVisible(visible);
        mode_EditButton.setEnabled(visible);
    }

    {
        banner_FilmstripType_Label.setVisible(visible);
        banner_FilmstripType_Label.setEnabled(visible);

        export_ProjectButton.setVisible(visible);
        export_ProjectButton.setEnabled(visible);
    }

    {
        control_DefaultButton.setVisible(visible);
        control_DefaultButton.setEnabled(visible);

        control_ApplyButton.setVisible(visible);
        control_ApplyButton.setEnabled(visible);
    }

    {
        group_AnglesOrThumbPos.setVisible(visible);
        group_AnglesOrThumbPos.setEnabled(visible);
    }

    {
        group_Orientation.setVisible(visible);
        group_Orientation.setEnabled(visible);
    }

    {
        group_TotalFrames.setVisible(visible);
        group_TotalFrames.setEnabled(visible);

        totalFrames_Slider.setVisible(visible);
        totalFrames_Slider.setEnabled(visible);

        totalFrames_Label.setVisible(visible);
        totalFrames_Label.setEnabled(visible);
    }

    {
        add_NewAssetButton.setVisible(visible);
        add_NewAssetButton.setEnabled(visible);
    }
}

void MainComponent::updatePage3InfoVisibility(bool visible)
{
    closeDialog_2_Info.setEnabled(visible);
    closeDialog_2_Info.setVisible(visible);

    author_param.setVisible(visible);
    author_arg.setVisible(visible);

    version_param.setVisible(visible);
    version_arg.setVisible(visible);

    release_param.setVisible(visible);
    release_arg.setVisible(visible);

    license_param.setVisible(visible);
    license_arg.setVisible(visible);

    juceVersion_arg.setVisible(visible);
}

/////////////////////////////////////////////////////////////////////
void MainComponent::setupLayoutUI()
{
    ///////////////// NEW PLAN PAGE 1 COMPONENT /////////////////
    base_SlideWorks = getLocalBounds().reduced(5);
    int componentSpace = 2;

    juce::Rectangle<int> area_NewProjectButton{ base_SlideWorks.getX(), base_SlideWorks.getY(), MenuButtonWidth, MenuButtonHeight };
    juce::Rectangle<int> area_ThemeButton{ area_NewProjectButton.getRight() + componentSpace, area_NewProjectButton.getY(), area_NewProjectButton.getWidth(), area_NewProjectButton.getHeight() };
    juce::Rectangle<int> area_InfoButton{ area_ThemeButton.getRight() + componentSpace, area_NewProjectButton.getY(), area_NewProjectButton.getWidth(), area_NewProjectButton.getHeight() };

    SW_NewProjectButton.setBounds(area_NewProjectButton);
    SW_ThemeButton.setBounds(area_ThemeButton);
    SW_InfoButton.setBounds(area_InfoButton);

    base_Workspace = base_SlideWorks;
    base_Workspace.removeFromTop(SW_NewProjectButton.getHeight() + componentSpace);

    //////// ==== PAGE 2 WORKSPACE ==== ////////

    ///== Area Footer ==///
    auto copy_base_Workspace = base_Workspace;
    area_Footer = copy_base_Workspace.removeFromBottom(FooterHeight);
    copy_base_Workspace.removeFromBottom(1);
    area_MainControl = copy_base_Workspace.removeFromLeft(MainControlWidth);
    copy_base_Workspace.removeFromLeft(1);
    area_Layer1_MainWorkspace = copy_base_Workspace;

    area_FilmstripProjects = copy_base_Workspace.removeFromTop(FooterHeight);
    area_Layer2_MainWorkspace = copy_base_Workspace;
    area_Layer2_MainWorkspace = area_Layer2_MainWorkspace.reduced(1);

    auto copy_area_Layer2_MainWorkspace = area_Layer2_MainWorkspace;
    area_ModeButtons = copy_area_Layer2_MainWorkspace.removeFromTop(FooterHeight);
    copy_area_Layer2_MainWorkspace.removeFromLeft(1);
    copy_area_Layer2_MainWorkspace.removeFromRight(1);
    copy_area_Layer2_MainWorkspace.removeFromBottom(1);
    area_Layer3_MainWorkspace = copy_area_Layer2_MainWorkspace;

    auto copy_area_Layer3_MainWorkspace = area_Layer3_MainWorkspace;

    //if (SlideWorksMode == ModeState::EDIT)

    if (filmstripProjects.size() >= 1)
    {
        // GET ACTIVE PROJECT
        projectActiveIndex = getActiveProjectIndex();

        
        // TAB BUTTON VIEWPORT
        auto copy_area_FilmstripProjects = area_FilmstripProjects;

        filmstripButtonsViewport.setBounds(copy_area_FilmstripProjects);
        filmstripButtonsViewport.setScrollBarsShown(false, true, false, true);

        int tabsTotalWidth = static_cast<int>(filmstripProjects.size()) * FPButtonWidth;

        filmstripButtonsContainer.setBounds(0, 0, tabsTotalWidth, filmstripButtonsViewport.getHeight());
        filmstripButtonsViewport.setViewedComponent(&filmstripButtonsContainer, false);

        if (filmstripButtonsViewport.getViewedComponent() == &filmstripButtonsContainer)
            DBG("Child component successfully attached to viewport!");
        else
            DBG("Failed to attach child component to viewport.");

        if (filmstripButtonsViewport.canScrollHorizontally())
            DBG("CAN SCROLL HORIZONTAL");


        juce::Rectangle<int> tabButtonArea{ copy_area_FilmstripProjects.getX(),copy_area_FilmstripProjects.getY(), FPButtonWidth, filmstripButtonsViewport.getHeight()};
        
        for (auto& project : filmstripProjects)
        {
            if (project != nullptr)
            {
                project->setBounds(tabButtonArea.reduced(1));
                tabButtonArea.translate(FPButtonWidth - 1, 0);

                DBG("\n" <<project->getFilmstripType());
                DBG("FILMSTRIP PROJECT BOUNDS: " << project->getBounds().toString());
                DBG("BUTTON BOUNDS : " << project->tabButton.getBounds().toString());
            }
        }


        // PROJECT NAMING VIEWPORT
        auto copy_area_ProjectNaming = area_ModeButtons;

        juce::Rectangle<int> namingLabelArea{ copy_area_ProjectNaming.getX(), copy_area_ProjectNaming.getY(), NamingLabelWidth, copy_area_ProjectNaming.getHeight() };
        juce::Rectangle<int> namingLabelEditorArea{ copy_area_ProjectNaming.getX() + (NamingLabelWidth - 1), copy_area_ProjectNaming.getY(), NamingLabelEditorWidth, copy_area_ProjectNaming.getHeight() };

        naming_Label.setBounds(namingLabelArea.reduced(1));
        naming_Editor.setBounds(namingLabelEditorArea.reduced(1));

        // MODE BUTTON VIEWPORT
        auto copy_area_ModeButtons = area_ModeButtons;

        juce::Rectangle<int> modeButtonsArea{ copy_area_ModeButtons.getRight() - MODEButtonWidth, copy_area_ModeButtons.getY(), MODEButtonWidth, copy_area_ModeButtons.getHeight() };
        mode_SimulationButton.setBounds(modeButtonsArea.reduced(1));

        modeButtonsArea = { modeButtonsArea.getX() - (MODEButtonWidth - 1), copy_area_ModeButtons.getY(), MODEButtonWidth, copy_area_ModeButtons.getHeight() };
        mode_PreviewButton.setBounds(modeButtonsArea.reduced(1));

        modeButtonsArea = { modeButtonsArea.getX() - (MODEButtonWidth - 1), copy_area_ModeButtons.getY(), MODEButtonWidth, copy_area_ModeButtons.getHeight() };
        mode_EditButton.setBounds(modeButtonsArea.reduced(1));

        // BANNER FILMSTRIP
        auto copy_area_MainControl = area_MainControl.reduced(0);

        area_MainControl_Banner_And_Export = copy_area_MainControl.removeFromTop(BannerHeight).reduced(4);
        banner_FilmstripType_Label.setBounds(area_MainControl_Banner_And_Export.withSizeKeepingCentre(
            area_MainControl_Banner_And_Export.getWidth() - 20, 
            area_MainControl_Banner_And_Export.getHeight())
        );

        auto area_exportButton = juce::Rectangle<int>(
            area_MainControl_Banner_And_Export.getRight() - ExportButtonWidth,
            area_MainControl_Banner_And_Export.getY(),
            ExportButtonWidth,
            area_MainControl_Banner_And_Export.getHeight()
        ).reduced(2);

        export_ProjectButton.setBounds(area_exportButton);

        // DEFAULT AND APPLY BUTTON
        copy_area_MainControl = copy_area_MainControl.withSizeKeepingCentre(copy_area_MainControl.getWidth() - 15, copy_area_MainControl.getHeight());

        area_MainControl_Default_And_ApplyButtons = copy_area_MainControl.removeFromBottom(DefaultApplyHeight);

        auto copy_area_MainControl_Default_And_ApplyButtons = area_MainControl_Default_And_ApplyButtons.reduced(2);
        control_DefaultButton.setBounds(copy_area_MainControl_Default_And_ApplyButtons.removeFromLeft(copy_area_MainControl_Default_And_ApplyButtons.getWidth() / 2).reduced(2));
        control_ApplyButton.setBounds(copy_area_MainControl_Default_And_ApplyButtons.reduced(2));

        // ANGLES / THUMB POSITION
        copy_area_MainControl.setHeight(copy_area_MainControl.getHeight() + 4);
        group_AnglesOrThumbPos.setBounds(copy_area_MainControl.removeFromBottom(group_AnglesOrThumbPos_Height));

        // ORIENTATIONS
        group_Orientation.setBounds(copy_area_MainControl.removeFromBottom(group_Orientation_Height));

        // TOTAL FRAMES
        group_TotalFrames.setBounds(copy_area_MainControl.removeFromBottom(group_TotalFrames_Height));
        {
            auto area = group_TotalFrames.getBounds().reduced(13);
            auto totalWidth = int(area.getWidth() * 0.95F);
            area = area.withSizeKeepingCentre(totalWidth, area.getHeight());
            area.removeFromTop(10);

            auto slider = area.removeFromLeft(int(area.getWidth() * 0.8F));
            auto label= area;

            totalFrames_Slider.setBounds(slider.reduced(2));
            totalFrames_Label.setBounds(label.reduced(2));
        }

        // VIEWPORT ASSETS
        copy_area_MainControl.removeFromLeft(5);
        copy_area_MainControl.removeFromRight(5);
        copy_area_MainControl.removeFromBottom(5);

        auto add_NewAssetButtonArea = copy_area_MainControl.removeFromTop(NewAssetButtonHeight).removeFromLeft(NewAssetButtonWidth);
        add_NewAssetButton.setBounds(add_NewAssetButtonArea);

        copy_area_MainControl.removeFromTop(3);
        area_assetsManager = copy_area_MainControl;


        reloadAllControls(projectActiveIndex);
    }





    ///////////////// PAGE 1 COMPONENT /////////////////
    //base_SlideWorks = getLocalBounds().reduced(10);

    //knobToggleWorksButton.setBounds(
    //    { base_SlideWorks.getX(), 
    //    base_SlideWorks.getY(), 
    //    75, 25 
    //    }
    //);
    //sliderToggleWorksButton.setBounds(
    //    {
    //        knobToggleWorksButton.getX() + knobToggleWorksButton.getWidth() + 5,
    //        knobToggleWorksButton.getY(),
    //        knobToggleWorksButton.getWidth(),
    //        knobToggleWorksButton.getHeight()
    //    }
    //);
    //browseButton.setBounds(
    //    {
    //        base_SlideWorks.getRight() - knobToggleWorksButton.getWidth(),
    //        knobToggleWorksButton.getY(),
    //        knobToggleWorksButton.getWidth(),
    //        knobToggleWorksButton.getHeight()
    //    }
    //);

    //base_WorkSpace = base_SlideWorks;
    //base_WorkSpace.removeFromTop(knobToggleWorksButton.getHeight() + 5);

    ///////////////// PAGE 2 COMPONENT /////////////////
    {
        //auto buttonW = 90;
        //    mode_SimulationButton.setBounds
        //    (
        //        {
        //            base_SlideWorks.getRight() - buttonW,
        //            knobToggleWorksButton.getY(),
        //            buttonW,
        //            knobToggleWorksButton.getHeight()
        //        }
        //);

        //mode_PreviewButton.setBounds
        //(
        //    {
        //        mode_SimulationButton.getX() - buttonW - 5,
        //        mode_SimulationButton.getY(),
        //        mode_SimulationButton.getWidth(),
        //        mode_SimulationButton.getHeight()
        //    }
        //);

        //mode_EditButton.setBounds
        //(
        //    {
        //        mode_PreviewButton.getX() - buttonW - 5,
        //        mode_SimulationButton.getY(),
        //        mode_SimulationButton.getWidth(),
        //        mode_SimulationButton.getHeight()
        //    }
        //);
    }


    auto area = base_Workspace;
    //left_WorkSpace = area.removeFromLeft(275);
    left_WorkSpace = area.removeFromLeft(int(area.getWidth() * 0.35F));
    area.removeFromLeft(5);
    right_WorkSpace = area;

    auto left_area = left_WorkSpace.reduced(5);
    auto left_area_H = left_area.getHeight();
    auto spacing = int(left_area_H * 0.035F);

    filmstripBanner = left_area.removeFromTop(25);
    left_area = left_area.withSizeKeepingCentre(left_area.getWidth() - 25, left_area.getHeight());
    left_area.removeFromTop(int(spacing * 1.5));

    ////////------------ INFO CARD GROUP ------------////////
    auto base_groupDialog_2_Info{ base_Workspace.withSizeKeepingCentre(275, 240) };
    auto groupDialog_2_Info_Area = base_groupDialog_2_Info.reduced(10);
    groupDialog_2_Info_Area.removeFromBottom(40);
    groupDialog_2_Info.setBounds(groupDialog_2_Info_Area);

    auto infoArea = groupDialog_2_Info_Area;
    infoArea.removeFromTop(8);
    infoArea = infoArea.reduced(20);
    infoArea = infoArea.withSizeKeepingCentre(150, infoArea.getHeight());

    auto contentHeight = infoArea.getHeight() / 5;
    auto author = infoArea.removeFromTop(contentHeight);
    auto version = infoArea.removeFromTop(contentHeight);
    auto release = infoArea.removeFromTop(contentHeight);
    auto license = infoArea.removeFromTop(contentHeight);
    auto juceVer = infoArea.removeFromTop(contentHeight);

    auto paramWidht = static_cast<int>(infoArea.getWidth() * 0.4F);
    author_param.setBounds(author.removeFromLeft(paramWidht));
    author_arg.setBounds(author);
    version_param.setBounds(version.removeFromLeft(paramWidht));
    version_arg.setBounds(version);
    release_param.setBounds(release.removeFromLeft(paramWidht));
    release_arg.setBounds(release);
    license_param.setBounds(license.removeFromLeft(paramWidht));
    license_arg.setBounds(license);
    juceVersion_arg.setBounds(juceVer);

    // CLOSE BUTTON
    {
        auto w = 100;
        auto h = 30;
        juce::Rectangle dialog2_Close{
            base_groupDialog_2_Info.getX() + (base_groupDialog_2_Info.getWidth() - w) / 2,
            base_groupDialog_2_Info.getBottom() - h - 10,
            w,
            h
        };
        closeDialog_2_Info.setBounds(dialog2_Close);
    }
    
    ////////------------ INFO CARD GROUP ------------////////

    ////////------------ TOTAL FRAMES ------------////////
    auto groupTotalFramesArea = left_area.removeFromTop(int(left_area_H * 0.160F));
    groupTotalFrames.setBounds(groupTotalFramesArea);
    left_area.removeFromTop(spacing);

    auto control1Area = groupTotalFramesArea;
    control1Area.removeFromTop(int(spacing * 0.70F));
    control1Area = control1Area.withSizeKeepingCentre(int(control1Area.getWidth() * 0.825F), control1Area.getHeight());
    debugOutlineTotalFrames = control1Area;

    auto sliderH = int(control1Area.getHeight() * 0.35F);
    auto control1AreaLeft = control1Area;
    auto ratio = 0.20F;
    control1AreaLeft.removeFromRight(int(control1Area.getWidth() * ratio));
    debugOutlineLeftTotalFrames = control1AreaLeft;
    control1AreaLeft = control1AreaLeft.withSizeKeepingCentre(control1AreaLeft.getWidth(), sliderH);
    sliderTotalFrames.setBounds(control1AreaLeft);

    auto control1AreaRight = control1Area;
    control1AreaRight = control1AreaRight.removeFromRight(int(control1AreaRight.getWidth() * ratio));
    debugOutlineRightTotalFrames = control1AreaRight;
    control1AreaRight.removeFromLeft(int(control1AreaRight.getWidth() * 0.1F));  // For spacing to left a bit.
    control1AreaRight = control1AreaRight.withSizeKeepingCentre(control1AreaRight.getWidth(), sliderH);
    labelBoxTotalFrames.setBounds(control1AreaRight);

    ////////------------ ORIENTATION ------------////////
    auto groupOrientationArea = left_area.removeFromTop(int(left_area_H * 0.225F));
    groupOrientation.setBounds(groupOrientationArea);
    left_area.removeFromTop(spacing);

    auto orientationArea = groupOrientationArea;
    orientationArea.removeFromTop(int(spacing * 0.70F));
    orientationArea = orientationArea.withSizeKeepingCentre(int(orientationArea.getWidth() * 0.825F), orientationArea.getHeight());
    debugOutlineOrientation = orientationArea;

    auto buttonH = int(orientationArea.getHeight() * 0.55F);
    auto orientationAreaLeft = orientationArea;
    ratio = 0.5F;
    orientationAreaLeft.removeFromRight(int(orientationArea.getWidth() * ratio));
    debugOutlineOrientationHorizontal = orientationAreaLeft;
    orientationAreaLeft = orientationAreaLeft.withSizeKeepingCentre(orientationAreaLeft.getWidth(), buttonH);
    orientationAreaLeft.removeFromRight(int(orientationAreaLeft.getWidth() * 0.065F));
    horizontalButton.setBounds(orientationAreaLeft);

    auto orientationAreaRight = orientationArea;
    orientationAreaRight = orientationAreaRight.removeFromRight(int(orientationAreaRight.getWidth() * ratio));
    debugOutlineOrientationVertical = orientationAreaRight;
    orientationAreaRight = orientationAreaRight.withSizeKeepingCentre(orientationAreaRight.getWidth(), buttonH);
    orientationAreaRight.removeFromLeft(int(orientationAreaRight.getWidth() * 0.065F));
    verticalButton.setBounds(orientationAreaRight);

    ////////------------ ANGLES ------------////////
    auto groupAnglesArea = left_area.removeFromTop(int(left_area_H * 0.370F));
    groupKnobAngles.setBounds(groupAnglesArea);

    auto anglesArea = groupAnglesArea;
    anglesArea.removeFromTop(int(spacing * 0.70F));
    anglesArea = anglesArea.withSizeKeepingCentre(int(anglesArea.getWidth() * 0.825F), anglesArea.getHeight());
    anglesArea = anglesArea.withSizeKeepingCentre(int(anglesArea.getWidth()), int(anglesArea.getHeight() * 0.825F));
    debugOutlineAngles = anglesArea;

    {
        ///-- MIN ANGLES --///
        ratio = 0.5F;
        auto anglesAreaMin = anglesArea;
        anglesAreaMin.removeFromRight(int(anglesAreaMin.getWidth() * ratio));
        debugOutlineAnglesMin = anglesAreaMin;

        auto ratioAnglesSection = 0.85F;
        auto anglesAreaMinTop = anglesAreaMin;
        anglesAreaMinTop.removeFromBottom(int(anglesAreaMin.getHeight() * ratioAnglesSection));
        labelMinAngles.setBounds(anglesAreaMinTop);
        debugOutlineAnglesMinTop = anglesAreaMinTop;

        auto anglesAreaMinKnob = anglesAreaMin;
        anglesAreaMinKnob = anglesAreaMinKnob.removeFromBottom(int(anglesAreaMinKnob.getHeight() * ratioAnglesSection));
        sliderMinAngles.setBounds(anglesAreaMinKnob);
        debugOutlineAnglesMinKnob = anglesAreaMinKnob;
    }

    {
        ///-- MAX ANGLES --///
        ratio = 0.5F;
        auto anglesAreaMax = anglesArea;
        anglesAreaMax.removeFromLeft(int(anglesAreaMax.getWidth() * ratio));
        debugOutlineAnglesMax = anglesAreaMax;

        auto ratioAnglesSection = 0.85F;
        auto anglesAreaMaxTop = anglesAreaMax;
        anglesAreaMaxTop.removeFromBottom(int(anglesAreaMax.getHeight() * ratioAnglesSection));
        labelMaxAngles.setBounds(anglesAreaMaxTop);
        debugOutlineAnglesMaxTop = anglesAreaMaxTop;

        auto anglesAreaMaxKnob = anglesAreaMax;
        anglesAreaMaxKnob = anglesAreaMaxKnob.removeFromBottom(int(anglesAreaMaxKnob.getHeight() * ratioAnglesSection));
        sliderMaxAngles.setBounds(anglesAreaMaxKnob);
        debugOutlineAnglesMaxKnob = anglesAreaMaxKnob;
    }


    ////////------------ THUMB POSITIONS ------------////////
    auto groupThumbPosArea = groupAnglesArea;
    groupSliderThumbPositions.setBounds(groupThumbPosArea);

    left_area.removeFromTop(spacing/2);

    auto exportButtonArea = left_area.withSizeKeepingCentre(100, 25);
    exportButton.setBounds(exportButtonArea);


    ////////------///--------- SIMULATION ---------///------////////
    auto widhtHeight = int(right_WorkSpace.getHeight() * 0.5F);
    auto simulationKnobArea = right_WorkSpace.withSizeKeepingCentre(widhtHeight, widhtHeight);
    simulationKnob.setBounds(simulationKnobArea);
    debugOutlineSimulationArea = simulationKnobArea;
    
}

// This function layout need to call repaint() after use
void MainComponent::setupLayoutWorkingMode(size_t activeIndex)
{
    reloadWorkingModeProject(activeIndex);

    auto copy_area_Layer3_MainWorkspace = area_Layer3_MainWorkspace;
    if (workingMode == WorkingMode::EDIT_MODE)
    {
        area_SubControl = copy_area_Layer3_MainWorkspace.removeFromRight(SubControlWidth);
        copy_area_Layer3_MainWorkspace.removeFromRight(1);
        area_Canvas = copy_area_Layer3_MainWorkspace;
    }
    else {
        area_Canvas = copy_area_Layer3_MainWorkspace;
        area_SubControl = { 0,0,0,0 };
    }
}

void MainComponent::checkInputPathState()
{
    if (inputPathKnob.isNotEmpty() ||
        inputPathKnobScale.isNotEmpty() ||
        inputPathSliderTrack.isNotEmpty() ||
        inputPathSliderThumb.isNotEmpty() ||
        inputPathSliderScale.isNotEmpty()
        )
    {
        currentSlideWorksPage = PageState::PAGE2_WORKSPACE;

        loadSimulationImage();
    }
    else
    {
        currentSlideWorksPage = PageState::PAGE1_GREETINGS;
    }


}

void MainComponent::loadSimulationImage()
{
    if (isSimulationImageLoaded == false && inputPathKnob.isNotEmpty()) {
        juce::Image image{ juce::ImageFileFormat::loadFrom(inputPathKnob) };
        int totalStrip = 11;
        ptr_Global_CustomLookAndFeel->setSimulationKnobImage(image, totalStrip, filmstripIsVertical, -135, 135);

        openGLComponent.setBounds(0, 0, image.getWidth(), image.getHeight() * totalStrip);
        openGLComponent.drawFilmstripKnobImage(image, totalStrip, filmstripIsVertical, -135, 135);
        ptr_Global_CustomLookAndFeel->setFilmStripKnob(openGLComponent.getFilmstrip());

        isSimulationImageLoaded = true;
    }
}

bool MainComponent::getInputPathState()
{
    return inputPathState;
}

void MainComponent::setupButtons(CustomLookAndFeel* customLookAndFeel)
{
    setupProjectButtons(customLookAndFeel);
    setupTabProjectButtons();
    setupNamingProjectLabel(customLookAndFeel);

    setupSimulationButton();
    setupPreviewButton();
    setupEditButton();

    setupBannerProjectTypeLabel(customLookAndFeel);
    setupExportProjectButton();
    setupAddNewAssetButton();
    setupDefaultApplyButton();

    setupTotalFramesControl(customLookAndFeel);

    //setupKnobToggleButton();
    setupSliderToggleButton();
    setupBrowseButton();
    setupExportButton();


    setupAddKnobButton();
    setupAddKnobScaleButton();
    setupAddSliderTrackButton();
    setupAddSliderThumbButton();
    setupAddSliderScaleButton();
    setupCloseDialog1Button();

    setupFilmstripControls(customLookAndFeel);
    setupOrientationButtons();
    setupAnglesKnobControls(customLookAndFeel);

    setupSimulationKnob(customLookAndFeel);
}

void MainComponent::setupProjectButtons(CustomLookAndFeel* customLookAndFeel)
{
    SW_NewProjectButton.setButtonText("New");
    SW_NewProjectButton.setComponentID("Buttons_ID_01_SW");
    SW_NewProjectButton.setLookAndFeel(customLookAndFeel);
    SW_NewProjectButton.onClick = [&, customLookAndFeel, this]()
        {
            bool buttonMenuEnable{ false };
            if (filmstripProjects.size() < 5)
            {
                buttonMenuEnable = true;
            }


            juce::PopupMenu menu;
            menu.addSectionHeader("New Filmstrip Project");
            menu.addSeparator();
            menu.addItem(1, "Knob Filmstrip", buttonMenuEnable, false);
            menu.addItem(2, "Slider Filmstrip", buttonMenuEnable, false);
            menu.setLookAndFeel(customLookAndFeel);



            menu.showMenuAsync(juce::PopupMenu::Options{}.withTargetComponent(SW_NewProjectButton), [this](int result)
                {
                    if (result == 1)
                    {
                        //// Create New Knob Filmstrip Project
                        auto project = std::make_unique<KnobFilmstrip>();
                        addAndMakeVisible(*project);

                        auto* ptrProject = project.get();
                        ptrProject->tabButton.onClick = [this, ptrProject]()
                            {
                                for (auto& project : filmstripProjects)
                                {
                                    project->tabButton.setToggleState(false, juce::dontSendNotification);
                                }
                                ptrProject->tabButton.setToggleState(true, juce::dontSendNotification);

                                projectActiveIndex = getActiveProjectIndex(); // GET ACTIVE INDEX

                                // RELOAD WORKSPACE : 
                                // NAMING, SLIDERS, ETC.
                                reloadAllControls(projectActiveIndex);
                            };

                        // using safePointer to MainComponent cause this is lambda deleting object from the object it self, so if the object already deleted
                        // cant access mainComponent::resized() or mainComponent::setupLayoutUI() to recalculate the viewport buttons cause the object already died.
                        // so need safePointer to outlive the object to run the last task from that object. 
                        ptrProject->onDeleteRequest = [safeThis = juce::Component::SafePointer<MainComponent>(this)](FilmstripProject* projectToDelete)
                            {
                                if (auto* mainComp = safeThis.getComponent())

                                {
                                    auto it = std::find_if(mainComp->filmstripProjects.begin(), mainComp->filmstripProjects.end(), [projectToDelete](const std::unique_ptr<FilmstripProject>& project)
                                        {
                                            return project.get() == projectToDelete;
                                        });

                                    if (it != mainComp->filmstripProjects.end())
                                    {
                                        size_t deletedIndex = std::distance(mainComp->filmstripProjects.begin(), it);
                                        bool wasActiveProject = mainComp->filmstripProjects.at(deletedIndex)->tabButton.getToggleState();

                                        mainComp->removeChildComponent(it->get());
                                        mainComp->filmstripProjects.erase(it);
                                        mainComp->setupLayoutUI();                // RECALCULATE TAB BUTTON COUNTS

                                        
                                        if (mainComp->filmstripProjects.size() > 0)
                                        {
                                            if (wasActiveProject)
                                            {
                                                // IF active project is in the end
                                                if (deletedIndex == mainComp->filmstripProjects.size())
                                                {
                                                    mainComp->filmstripProjects.at(deletedIndex - 1)->tabButton.setToggleState(true, juce::dontSendNotification);
                                                }
                                                else
                                                {
                                                    mainComp->filmstripProjects.at(deletedIndex)->tabButton.setToggleState(true, juce::dontSendNotification);
                                                }

                                                mainComp->projectActiveIndex = mainComp->getActiveProjectIndex();

                                                mainComp->reloadAllControls(mainComp->projectActiveIndex);
                                            }
                                        }
                                        else
                                        {
                                            // ZERO
                                            size_t index = SIZE_MAX;

                                            mainComp->reloadAllControls(index);

                                            mainComp->currentSlideWorksPage = PageState::PAGE1_GREETINGS;
                                            mainComp->updatePage2WorkVisibility(false);
                                            mainComp->repaint();
                                        }
                                    }
                                }
                            };

                        filmstripProjects.push_back(std::move(project));

                        
                        

                    }
                    else if (result == 2)
                    {
                        //// Create New Slider Filmstrip Project
                        auto project = std::make_unique<SliderFilmstrip>();
                        addAndMakeVisible(*project);

                        auto* ptrProject = project.get();
                        ptrProject->tabButton.onClick = [this, ptrProject]()
                            {
                                for (auto& project : filmstripProjects)
                                {
                                    project->tabButton.setToggleState(false, juce::dontSendNotification);
                                }
                                ptrProject->tabButton.setToggleState(true, juce::dontSendNotification);

                                projectActiveIndex = getActiveProjectIndex(); // GET ACTIVE INDEX

                                reloadAllControls(projectActiveIndex);

                            };

                        ptrProject->onDeleteRequest = [safeThis = juce::Component::SafePointer<MainComponent>(this)](FilmstripProject* projectToDelete)
                            {
                                if (auto* mainComp = safeThis.getComponent())

                                {
                                    auto it = std::find_if(mainComp->filmstripProjects.begin(), mainComp->filmstripProjects.end(), [projectToDelete](const std::unique_ptr<FilmstripProject>& project)
                                        {
                                            return project.get() == projectToDelete;
                                        });

                                    if (it != mainComp->filmstripProjects.end())
                                    {
                                        size_t deletedIndex = std::distance(mainComp->filmstripProjects.begin(), it);
                                        bool wasActiveProject = mainComp->filmstripProjects.at(deletedIndex)->tabButton.getToggleState();

                                        mainComp->removeChildComponent(it->get());
                                        mainComp->filmstripProjects.erase(it);
                                        mainComp->setupLayoutUI();


                                        if (mainComp->filmstripProjects.size() > 0)
                                        {
                                            if (wasActiveProject)
                                            {
                                                // IF active project is in the end
                                                if (deletedIndex == mainComp->filmstripProjects.size())
                                                {
                                                    mainComp->filmstripProjects.at(deletedIndex - 1)->tabButton.setToggleState(true, juce::dontSendNotification);
                                                }
                                                else
                                                {
                                                    mainComp->filmstripProjects.at(deletedIndex)->tabButton.setToggleState(true, juce::dontSendNotification);
                                                }

                                                mainComp->projectActiveIndex = mainComp->getActiveProjectIndex();

                                                mainComp->reloadAllControls(mainComp->projectActiveIndex);
                                            }
                                        }
                                        else
                                        {
                                            // ZERO
                                            size_t index = SIZE_MAX;

                                            mainComp->reloadAllControls(index);

                                            mainComp->currentSlideWorksPage = PageState::PAGE1_GREETINGS;
                                            mainComp->updatePage2WorkVisibility(false);
                                            mainComp->repaint();
                                        }
                                    }
                                }
                            };

                        filmstripProjects.push_back(std::move(project));
                    }

                    if (filmstripProjects.empty() == false)
                    {
                        for (auto& project : filmstripProjects)
                        {
                            project->tabButton.setToggleState(false, juce::dontSendNotification);
                        }
                        filmstripProjects.back()->tabButton.setToggleState(true, juce::dontSendNotification);

                        size_t KnobTotal{};
                        size_t SliderTotal{};

                        for (auto& project : filmstripProjects)
                        {
                            if (auto* knob = dynamic_cast<KnobFilmstrip*>(project.get()))
                            {
                                KnobTotal++;
                            }

                            if (auto* slider = dynamic_cast<SliderFilmstrip*>(project.get()))
                            {
                                SliderTotal++;
                            }
                        }

                        DBG("PROJECT BOUNDS: " << filmstripProjects.back()->getBounds().toString());
                        DBG("BUTTON BOUNDS : " << filmstripProjects.back()->tabButton.getBounds().toString());

                        DBG("==> TESTING POINTER : " << filmstripProjects.back()->getFilmstripSizeStatus());
                        DBG("==> Total Projects  : " << filmstripProjects.size());
                        DBG("==> Total Knobs     : " << KnobTotal);
                        DBG("==> Total Sliders   : " << SliderTotal);
                    }

                    if (filmstripProjects.size() > 0) 
                    {
                        currentSlideWorksPage = PageState::PAGE2_WORKSPACE;

                        updatePage2WorkVisibility(true);
                        updatePage3InfoVisibility(false);
                    }

                    setupLayoutUI();
                    repaint();
                }
            );
        };
    addAndMakeVisible(SW_NewProjectButton);

    SW_ThemeButton.setButtonText("Theme");
    SW_ThemeButton.setComponentID("Buttons_ID_01_SW");
    SW_ThemeButton.setLookAndFeel(customLookAndFeel);
    SW_ThemeButton.onClick = [&, customLookAndFeel, this] ()
        {
            ThemeType currentTheme = customLookAndFeel->getCurrentThemeType();

            juce::PopupMenu menu;
            menu.setLookAndFeel(customLookAndFeel);
            menu.addSectionHeader("Theme");
            menu.addSeparator();
            menu.addItem(1, "Office Light", true, currentTheme == ThemeType::OfficeLight);
            menu.addItem(2, "Dark Night", true, currentTheme == ThemeType::DarkNight);

            menu.showMenuAsync(juce::PopupMenu::Options{}.withTargetComponent(SW_ThemeButton), [this, customLookAndFeel](int result)
                {
                    if (result == 1)
                    {
                        customLookAndFeel->setTheme(ThemeType::OfficeLight);
                    }
                    else if (result == 2)
                    {
                        customLookAndFeel->setTheme(ThemeType::DarkNight);
                    }
                    repaint();

                    Globals::repaintTitleBar = true;

                }
            );
        };
    addAndMakeVisible(SW_ThemeButton);

    SW_InfoButton.setButtonText("Info");
    SW_InfoButton.setComponentID("Buttons_ID_01_SW");
    SW_InfoButton.setLookAndFeel(customLookAndFeel);
    SW_InfoButton.onClick = [this]()
        {
            if (currentSlideWorksPage != PageState::PAGE3_INFO)
            {
                previousSlideWorksPage = currentSlideWorksPage;
                currentSlideWorksPage = PageState::PAGE3_INFO;

                updatePage2WorkVisibility(false);
                updatePage3InfoVisibility(true);
                repaint();
            }
        };
    addAndMakeVisible(SW_InfoButton);
}

void MainComponent::setupTabProjectButtons()
{
    // SETUP TAB BUTTONS
    addAndMakeVisible(filmstripButtonsContainer);
    addAndMakeVisible(filmstripButtonsViewport);
}

size_t MainComponent::getActiveProjectIndex() const
{
    for (size_t i = 0; i < filmstripProjects.size(); i++)
    {
        if (filmstripProjects.at(i)->tabButton.getToggleState() == true)
        {
            return i;
        }
    }
    return static_cast<size_t>(-1);
}

void MainComponent::setupNamingProjectLabel(CustomLookAndFeel* customLookAndFeel)
{
    // SETUP NAMING LABEL
    naming_Label.setText("Name : ", juce::dontSendNotification);
    naming_Label.setComponentID("Label_ID_O1_Naming");
    naming_Label.setLookAndFeel(customLookAndFeel);
    naming_Label.setFont(customLookAndFeel->getFontRobotoCondensedRegular().withHeight(16.0F));
    naming_Label.setJustificationType(juce::Justification::centredLeft);
    naming_Label.setColour(juce::Label::backgroundColourId, customLookAndFeel->getCurrentTheme().NamingLabel);
    naming_Label.setEditable(false, false);
    addAndMakeVisible(naming_Label);
    
    naming_Editor.setText("Untitled", juce::dontSendNotification);
    naming_Editor.setComponentID("Label_ID_01_NamingEditor");
    naming_Editor.setLookAndFeel(customLookAndFeel);
    naming_Editor.setFont(customLookAndFeel->getFontRobotoCondensedRegular().withHeight(16.0F));
    naming_Editor.setJustificationType(juce::Justification::centredLeft);
    naming_Editor.setColour(juce::Label::backgroundColourId, customLookAndFeel->getCurrentTheme().TransparentBlack);
    naming_Editor.setColour(juce::Label::textColourId, customLookAndFeel->getCurrentTheme().CustomDarkGrey);
    naming_Editor.setColour(juce::Label::backgroundWhenEditingColourId, customLookAndFeel->getCurrentTheme().SlideworksBaseColour); // This should follow the layer2 color if not mat
    naming_Editor.setColour(juce::Label::textWhenEditingColourId, customLookAndFeel->getCurrentTheme().CustomDarkGrey);
    naming_Editor.setColour(juce::Label::outlineWhenEditingColourId, customLookAndFeel->getCurrentTheme().CustomGrey);
    naming_Editor.setColour(juce::Label::outlineColourId, customLookAndFeel->getCurrentTheme().CustomGrey.brighter());
    naming_Editor.setColour(juce::TextEditor::highlightColourId, customLookAndFeel->getCurrentTheme().TitleBar);
    naming_Editor.setColour(juce::TextEditor::highlightedTextColourId, customLookAndFeel->getCurrentTheme().CustomWhite);
    naming_Editor.setColour(juce::CaretComponent::caretColourId, customLookAndFeel->getCurrentTheme().TitleBar.darker());
    naming_Editor.setEditable(false, true);
    naming_Editor.onTextChange = [this]()
        {
            filmstripProjects.at(projectActiveIndex)->setProjectName(naming_Editor.getText());
        };
    addAndMakeVisible(naming_Editor);

}

void MainComponent::reloadNamingProjectLabel(size_t activeIndex)
{
    if (activeIndex != SIZE_MAX)
    {
        naming_Editor.setText(filmstripProjects.at(activeIndex)->getProjectName(), juce::dontSendNotification);
    }
    else
    {
        naming_Editor.setText("", juce::dontSendNotification);
    }
}

void MainComponent::togglingWorkingModeButton(WorkingMode mode)
{
    if (mode == WorkingMode::EDIT_MODE)
    {
        togglingButtons(mode_EditButton, mode_PreviewButton, mode_SimulationButton);
    }
    else if (mode == WorkingMode::PREVIEW_MODE)
    {
        togglingButtons(mode_PreviewButton, mode_SimulationButton, mode_EditButton);
    }
    else if (mode == WorkingMode::SIMULATION_MODE)
    {
        togglingButtons(mode_SimulationButton, mode_EditButton, mode_PreviewButton);
    }
}

void MainComponent::reloadWorkingModeProject(size_t activeIndex)
{
    if (activeIndex != SIZE_MAX)
    {
        workingMode = filmstripProjects.at(activeIndex)->getWorkingMode();
        togglingWorkingModeButton(workingMode);
    }
    else
    {
        workingMode = WorkingMode::EDIT_MODE;
    }
}

void MainComponent::setupBannerProjectTypeLabel(CustomLookAndFeel* customLookAndFeel)
{
    banner_FilmstripType_Label.setText("", juce::dontSendNotification);
    banner_FilmstripType_Label.setComponentID("Label_ID_02_FilmstripType");
    banner_FilmstripType_Label.setLookAndFeel(customLookAndFeel);
    banner_FilmstripType_Label.setFont(customLookAndFeel->getFontRobotoCondensedBold().withHeight(17.0F));
    banner_FilmstripType_Label.setColour(juce::Label::textColourId, customLookAndFeel->getCurrentTheme().FontBlack);
    banner_FilmstripType_Label.setJustificationType(juce::Justification::centredLeft);
    banner_FilmstripType_Label.setEditable(false, false);
    addAndMakeVisible(banner_FilmstripType_Label);
}

void MainComponent::reloadBannerFilmstripType(size_t activeIndex)
{
    if (activeIndex != SIZE_MAX)
    {
        juce::String text{ "FILMSTRIP : " + filmstripProjects.at(activeIndex)->getFilmstripType() };
        banner_FilmstripType_Label.setText(text, juce::dontSendNotification);
    }
    else {
        banner_FilmstripType_Label.setText("", juce::dontSendNotification);
    }
}

void MainComponent::setupExportProjectButton()
{
    export_ProjectButton.setButtonText("Export");
    export_ProjectButton.setComponentID("Buttons_ID_06_EXPORT");
    export_ProjectButton.onClick = [this]() {};
    addAndMakeVisible(export_ProjectButton);
}

void MainComponent::reloadMainControlProject(size_t activeIndex)
{
    if (activeIndex != SIZE_MAX)
    {
        group_AnglesOrThumbPos.setText(filmstripProjects.at(activeIndex)->getAnglesOrThumbPosText());
    }
    else {
        group_AnglesOrThumbPos.setText("");
    }
    
    reloadTotalFramesControl(activeIndex);
}

void MainComponent::setupAddNewAssetButton()
{
    add_NewAssetButton.setComponentID("Buttons_ID_07_NEW_ASSET");
    add_NewAssetButton.onClick = [this]() {};
    addAndMakeVisible(add_NewAssetButton);
}

void MainComponent::setupTotalFramesControl(CustomLookAndFeel* customLookAndFeel)
{
    totalFrames_Slider.setComponentID("Slider_ID_01_WithThumb");
    totalFrames_Slider.setRange(0, 1, 1.0);
    totalFrames_Slider.setLookAndFeel(customLookAndFeel);
    totalFrames_Slider.setValue(0);
    totalFrames_Slider.setSliderStyle(juce::Slider::LinearHorizontal);
    totalFrames_Slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    totalFrames_Slider.setColour(juce::Slider::trackColourId, customLookAndFeel->getCurrentTheme().SlideworksBaseColour);
    totalFrames_Slider.setColour(juce::Slider::thumbColourId, customLookAndFeel->getCurrentTheme().SliderThumbColour);
    totalFrames_Slider.setColour(juce::Slider::textBoxBackgroundColourId, customLookAndFeel->getColorCustomDarkGrey());
    totalFrames_Slider.setColour(juce::Slider::textBoxTextColourId, customLookAndFeel->getColorCustomLightGrey().brighter());
    totalFrames_Slider.setMouseClickGrabsKeyboardFocus(false);
    totalFrames_Slider.setTextBoxIsEditable(false);
    totalFrames_Slider.onValueChange = [this]() {};
    addAndMakeVisible(totalFrames_Slider);

    totalFrames_Label.setComponentID("Slider_ID_01_WithThumb");
    totalFrames_Label.setText(std::to_string(totalFrames_Slider.getValue()), juce::dontSendNotification);
    totalFrames_Label.setFont(customLookAndFeel->getFontRobotoCondensedRegular().withHeight(17.F));
    totalFrames_Label.setJustificationType(juce::Justification::centred);
    totalFrames_Label.setColour(juce::Label::backgroundColourId, customLookAndFeel->getCurrentTheme().SlideworksBaseColour);
    totalFrames_Label.setColour(juce::Label::textColourId, customLookAndFeel->getCurrentTheme().CustomDarkGrey);
    totalFrames_Label.setColour(juce::Label::backgroundWhenEditingColourId, customLookAndFeel->getCurrentTheme().SlideworksBaseColour);
    totalFrames_Label.setColour(juce::Label::textWhenEditingColourId, customLookAndFeel->getCurrentTheme().CustomDarkGrey);
    totalFrames_Label.setColour(juce::Label::outlineColourId, customLookAndFeel->getCurrentTheme().CustomDarkest);
    totalFrames_Label.setColour(juce::TextEditor::highlightColourId, customLookAndFeel->getCurrentTheme().TitleBar);
    totalFrames_Label.setColour(juce::TextEditor::highlightedTextColourId, customLookAndFeel->getCurrentTheme().CustomWhite);
    totalFrames_Label.setColour(juce::CaretComponent::caretColourId, customLookAndFeel->getCurrentTheme().TitleBar);

    totalFrames_Label.setColour(juce:: TextEditor::textColourId, customLookAndFeel->getColorCustomLightGrey().brighter(1.F));
    totalFrames_Label.setColour(juce:: TextEditor::highlightColourId, customLookAndFeel->getColorCustomLightGrey());
    totalFrames_Label.setColour(juce:: TextEditor::highlightedTextColourId, customLookAndFeel->getColorCustomDarkGrey());
    totalFrames_Label.setColour(juce:: CaretComponent::caretColourId, customLookAndFeel->getColorCustomWhite());
    totalFrames_Label.setLookAndFeel(customLookAndFeel);
    totalFrames_Label.setEditable(false, true);

    totalFrames_Label.onTextChange = [this]()
        {
            auto newValue = totalFrames_Label.getText().getIntValue();

            auto minValue = filmstripProjects.at(projectActiveIndex)->getMinFrames();
            auto maxValue = filmstripProjects.at(projectActiveIndex)->getMaxFrames();

            if ( newValue >= minValue && newValue <= maxValue)
            {
                newValue = newValue;
            }
            else if (newValue <= minValue)
            {
                newValue = minValue;
            }
            else if (newValue >= maxValue)
            {
                newValue = maxValue;
            }
            else 
            {
                newValue = minValue;
            }

            DBG("MIN VALUE : " << minValue);
            DBG("MAX VALUE : " << maxValue);

            totalFrames_Slider.setValue(newValue, juce::sendNotification);
            //filmstripTotalFrames = newValue;
            //filmstripProjects.at(activeIndex)->fram
        };
    addAndMakeVisible(totalFrames_Label);
}

void MainComponent::reloadTotalFramesControl(size_t activeIndex)
{
    if (activeIndex != SIZE_MAX)
    {
        auto project = filmstripProjects.at(activeIndex).get();
        totalFrames_Slider.setRange(project->getMinFrames(), project->getMaxFrames(), 1.0);
        totalFrames_Slider.setValue(filmstripProjects.at(activeIndex)->getTotalFrames());
        totalFrames_Slider.onValueChange = [this, activeIndex]() 
            {
                auto value = int(totalFrames_Slider.getValue());
                filmstripProjects.at(activeIndex)->setTotalFrames(value);
                totalFrames_Label.setText(std::to_string(value), juce::dontSendNotification);
            };
    }
    else {
        totalFrames_Slider.setValue(0, juce::dontSendNotification);
    }
}

void MainComponent::setupDefaultApplyButton()
{
    control_DefaultButton.setButtonText("Default");
    control_DefaultButton.setComponentID("Buttons_ID_08_DEFAULT");
    control_DefaultButton.onClick = [this]() {};
    addAndMakeVisible(control_DefaultButton);

    control_ApplyButton.setButtonText("Apply");
    control_ApplyButton.setComponentID("Buttons_ID_09_APPLY");
    control_ApplyButton.onClick = [this]() {};
    addAndMakeVisible(control_ApplyButton);
}

void MainComponent::reloadAllControls(size_t activeIndex)
{
    setupLayoutWorkingMode(activeIndex);

    reloadNamingProjectLabel(activeIndex);
    reloadBannerFilmstripType(activeIndex);
    reloadMainControlProject(activeIndex);

    repaint();
}





void MainComponent::setupKnobToggleButton()
{
    knobToggleWorksButton.setButtonText("KNOB");
    knobToggleWorksButton.setName("knobWorks");
    knobToggleWorksButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    knobToggleWorksButton.onClick = [this]() { togglingButtons(knobToggleWorksButton, sliderToggleWorksButton); };
    //addAndMakeVisible(knobToggleWorksButton);
}

void MainComponent::setupSliderToggleButton()
{
    sliderToggleWorksButton.setButtonText("SLIDER");
    sliderToggleWorksButton.setName("sliderWorks");
    sliderToggleWorksButton.setToggleState(false, juce::NotificationType::dontSendNotification);
    sliderToggleWorksButton.onClick = [this]() { togglingButtons(sliderToggleWorksButton, knobToggleWorksButton); };
    //addAndMakeVisible(sliderToggleWorksButton);
}

void MainComponent::setupBrowseButton()
{
    browseButton.setButtonText("BROWSE");
    browseButton.setName("browseButton");
    browseButton.onClick = [this]() 
        { 
            openAddImage_Dialog1 = true;

            closeDialog1.setVisible(true);
            closeDialog1.setEnabled(true);

        };
    //addAndMakeVisible(browseButton);
}

void MainComponent::setupExportButton()
{
    exportButton.setButtonText("EXPORT");
    exportButton.setName("exportButton");
    exportButton.onClick = [this]() {};
    addAndMakeVisible(exportButton);
}

void MainComponent::setupSimulationButton()
{
    mode_SimulationButton.setButtonText("Simulation");
    mode_SimulationButton.setComponentID("Buttons_ID_05_MODE");
    mode_SimulationButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    mode_SimulationButton.onClick = [this]() 
        {
            workingMode = WorkingMode::SIMULATION_MODE;

            filmstripProjects.at(projectActiveIndex)->setWorkingMode(workingMode);
            togglingButtons(mode_SimulationButton, mode_PreviewButton, mode_EditButton);

            setupLayoutWorkingMode(projectActiveIndex);
            repaint();
        };
    addAndMakeVisible(mode_SimulationButton);
}

void MainComponent::setupPreviewButton()
{
    mode_PreviewButton.setButtonText("Preview");
    mode_PreviewButton.setComponentID("Buttons_ID_05_MODE");
    mode_PreviewButton.setToggleState(false, juce::NotificationType::dontSendNotification);
    mode_PreviewButton.onClick = [this]() 
        {
            workingMode = WorkingMode::PREVIEW_MODE;
         
            filmstripProjects.at(projectActiveIndex)->setWorkingMode(workingMode);
            togglingButtons(mode_PreviewButton, mode_SimulationButton, mode_EditButton);
            
            setupLayoutWorkingMode(projectActiveIndex);
            repaint();
        };
    addAndMakeVisible(mode_PreviewButton);
}

void MainComponent::setupEditButton()
{
    mode_EditButton.setButtonText("Edit");
    mode_EditButton.setComponentID("Buttons_ID_05_MODE");
    mode_EditButton.setToggleState(false, juce::NotificationType::dontSendNotification);
    mode_EditButton.onClick = [this]() 
        {
            workingMode = WorkingMode::EDIT_MODE;

            filmstripProjects.at(projectActiveIndex)->setWorkingMode(workingMode);
            togglingButtons(mode_EditButton, mode_SimulationButton, mode_PreviewButton);

            setupLayoutWorkingMode(projectActiveIndex);
            repaint();
        };
    addAndMakeVisible(mode_EditButton);
}

void MainComponent::togglingButtons(juce::TextButton& activeButton, juce::TextButton& inactiveButton)
{
    activeButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    inactiveButton.setToggleState(false, juce::NotificationType::dontSendNotification);

    //updateUI();
}

void MainComponent::togglingButtons(juce::TextButton& activeButton, juce::TextButton& inactiveButton1, juce::TextButton& inactiveButton2)
{
    activeButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    inactiveButton1.setToggleState(false, juce::NotificationType::dontSendNotification);
    inactiveButton2.setToggleState(false, juce::NotificationType::dontSendNotification);
    
    //updateUI();
}


void MainComponent::setupAddKnobButton()
{
    addKnob.setButtonText("KNOB");
    addKnob.setName("addKnob");
    addKnob.onClick = [this]() 
        {
            fileChooserWindows(inputPathKnob);
        };
    addAndMakeVisible(addKnob);
}

void MainComponent::setupAddKnobScaleButton() 
{
    addKnobScale.setButtonText("SCALE");
    addKnobScale.setName("addKnobScale");
    addKnobScale.onClick = [this]() 
        {
            fileChooserWindows(inputPathKnobScale);
        };
    addAndMakeVisible(addKnobScale);
}

void MainComponent::setupAddSliderTrackButton() 
{
    addSliderTrack.setButtonText("TRACK");
    addSliderTrack.setName("addSliderTrack");
    addSliderTrack.onClick = [this]() 
        {
            fileChooserWindows(inputPathSliderTrack);
        };
    addAndMakeVisible(addSliderTrack);
}
void MainComponent::setupAddSliderThumbButton() 
{
    addSliderThumb.setButtonText("THUMB");
    addSliderThumb.setName("addSliderThumb");
    addSliderThumb.onClick = [this]() 
        {
            fileChooserWindows(inputPathSliderThumb);
        };
    addAndMakeVisible(addSliderThumb);
}
void MainComponent::setupAddSliderScaleButton() 
{
    addSliderScale.setButtonText("SCALE");
    addSliderScale.setName("addSliderScale");
    addSliderScale.onClick = [this]() 
        {
            fileChooserWindows(inputPathSliderScale);

        };
    addAndMakeVisible(addSliderScale);
}
void MainComponent::setupCloseDialog1Button()
{
    closeDialog1.setButtonText("CLOSE");
    closeDialog1.setName("closeDialog1");
    closeDialog1.setComponentID("Buttons_ID_02_Close_Group");
    closeDialog1.onClick = [this]() 
        { 
            openAddImage_Dialog1 = false;

            resetDialog1();
        };
    addAndMakeVisible(closeDialog1);
}

void MainComponent::setupCustomGroupComponents()
{
    auto indentation = 5.0F;
    auto gap = 6.0F;
    auto cornerSize = 5.0F;
    auto lineThick = 1.0F;
    auto fontSize = 16.0F;
    auto font = ptr_Global_CustomLookAndFeel->getFontRobotoCondensedRegular().withHeight(fontSize);
    auto fontColor = ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomDarkGrey;
    auto outlineColor = ptr_Global_CustomLookAndFeel->getCurrentTheme().OutlineControl;

    group_AnglesOrThumbPos.setText("Angles");
    group_AnglesOrThumbPos.setTextLabelPosition(juce::Justification::centred);
    group_AnglesOrThumbPos.setFont(font);
    group_AnglesOrThumbPos.setFontColour(fontColor);
    group_AnglesOrThumbPos.setOutlineColour(outlineColor);
    group_AnglesOrThumbPos.setCornerSize(cornerSize);
    group_AnglesOrThumbPos.setIndentation(indentation);
    group_AnglesOrThumbPos.setTextLineGap(gap);
    group_AnglesOrThumbPos.setLineThickness(lineThick);
    addAndMakeVisible(group_AnglesOrThumbPos);

    group_Orientation.setText("Orientation");
    group_Orientation.setTextLabelPosition(juce::Justification::centred);
    group_Orientation.setFont(font);
    group_Orientation.setFontColour(fontColor);
    group_Orientation.setOutlineColour(outlineColor);
    group_Orientation.setCornerSize(cornerSize);
    group_Orientation.setIndentation(indentation);
    group_Orientation.setTextLineGap(gap);
    group_Orientation.setLineThickness(lineThick);
    addAndMakeVisible(group_Orientation);

    group_TotalFrames.setText("Total Frames");
    group_TotalFrames.setTextLabelPosition(juce::Justification::centred);
    group_TotalFrames.setFont(font);
    group_TotalFrames.setFontColour(fontColor);
    group_TotalFrames.setOutlineColour(outlineColor);
    group_TotalFrames.setCornerSize(cornerSize);
    group_TotalFrames.setIndentation(indentation);
    group_TotalFrames.setTextLineGap(gap);
    group_TotalFrames.setLineThickness(lineThick);
    addAndMakeVisible(group_TotalFrames);
    

    groupDialog_2_Info.setName("DIALOG 2 INFO");
    groupDialog_2_Info.setText("SLIDEWORKS");
    groupDialog_2_Info.setTextLabelPosition(juce::Justification::centred);
    groupDialog_2_Info.setFont(ptr_Global_CustomLookAndFeel->getFontRobotoCondensedBold().withHeight(18.0F));
    groupDialog_2_Info.setFontColour(ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomGroupComponent);
    groupDialog_2_Info.setOutlineColour(ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomGroupComponent);
    groupDialog_2_Info.setCornerSize(10.0F);
    groupDialog_2_Info.setIndentation(3.0F);
    groupDialog_2_Info.setTextLineGap(8.0F);
    groupDialog_2_Info.setLineThickness(1.5F);
    addAndMakeVisible(groupDialog_2_Info);

    author_param.setText("Author", juce::dontSendNotification);
    author_param.setJustificationType(juce::Justification::centredLeft);
    author_param.setFont(ptr_Global_CustomLookAndFeel->getFontRobotoCondensedBold().withHeight(17.0F));
    author_param.setColour(juce::Label::backgroundColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomTransparent);
    author_param.setColour(juce::Label::textColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomGroupComponent);
    author_param.setLookAndFeel(ptr_Global_CustomLookAndFeel);
    addAndMakeVisible(author_param);
    author_arg.setText(":  UFTHaq", juce::dontSendNotification);
    author_arg.setJustificationType(juce::Justification::centredLeft);
    author_arg.setFont(ptr_Global_CustomLookAndFeel->getFontRobotoCondensedBold().withHeight(17.0F));
    author_arg.setColour(juce::Label::backgroundColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomTransparent);
    author_arg.setColour(juce::Label::textColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomGroupComponent);
    author_arg.setLookAndFeel(ptr_Global_CustomLookAndFeel);
    addAndMakeVisible(author_arg);

    version_param.setText("Version", juce::dontSendNotification);
    version_param.setJustificationType(juce::Justification::centredLeft);
    version_param.setFont(ptr_Global_CustomLookAndFeel->getFontRobotoCondensedBold().withHeight(17.0F));
    version_param.setColour(juce::Label::backgroundColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomTransparent);
    version_param.setColour(juce::Label::textColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomGroupComponent);
    version_param.setLookAndFeel(ptr_Global_CustomLookAndFeel);
    addAndMakeVisible(version_param);
    version_arg.setText(":  1.0", juce::dontSendNotification);
    version_arg.setJustificationType(juce::Justification::centredLeft);
    version_arg.setFont(ptr_Global_CustomLookAndFeel->getFontRobotoCondensedBold().withHeight(17.0F));
    version_arg.setColour(juce::Label::backgroundColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomTransparent);
    version_arg.setColour(juce::Label::textColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomGroupComponent);
    version_arg.setLookAndFeel(ptr_Global_CustomLookAndFeel);
    addAndMakeVisible(version_arg);

    release_param.setText("Release", juce::dontSendNotification);
    release_param.setJustificationType(juce::Justification::centredLeft);
    release_param.setFont(ptr_Global_CustomLookAndFeel->getFontRobotoCondensedBold().withHeight(17.0F));
    release_param.setColour(juce::Label::backgroundColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomTransparent);
    release_param.setColour(juce::Label::textColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomGroupComponent);
    release_param.setLookAndFeel(ptr_Global_CustomLookAndFeel);
    addAndMakeVisible(release_param);
    release_arg.setText(":  15/12/2024", juce::dontSendNotification);
    release_arg.setJustificationType(juce::Justification::centredLeft);
    release_arg.setFont(ptr_Global_CustomLookAndFeel->getFontRobotoCondensedBold().withHeight(17.0F));
    release_arg.setColour(juce::Label::backgroundColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomTransparent);
    release_arg.setColour(juce::Label::textColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomGroupComponent);
    release_arg.setLookAndFeel(ptr_Global_CustomLookAndFeel);
    addAndMakeVisible(release_arg);

    license_param.setText("License", juce::dontSendNotification);
    license_param.setJustificationType(juce::Justification::centredLeft);
    license_param.setFont(ptr_Global_CustomLookAndFeel->getFontRobotoCondensedBold().withHeight(17.0F));
    license_param.setColour(juce::Label::backgroundColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomTransparent);
    license_param.setColour(juce::Label::textColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomGroupComponent);
    license_param.setLookAndFeel(ptr_Global_CustomLookAndFeel);
    addAndMakeVisible(license_param);
    license_arg.setText(":  APGLv3", juce::dontSendNotification);
    license_arg.setJustificationType(juce::Justification::centredLeft);
    license_arg.setFont(ptr_Global_CustomLookAndFeel->getFontRobotoCondensedBold().withHeight(17.0F));
    license_arg.setColour(juce::Label::backgroundColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomTransparent);
    license_arg.setColour(juce::Label::textColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomGroupComponent);
    license_arg.setLookAndFeel(ptr_Global_CustomLookAndFeel);
    addAndMakeVisible(license_arg);

    juceVersion_arg.setText("Created with JUCE 8.0.3", juce::dontSendNotification);
    juceVersion_arg.setJustificationType(juce::Justification::centredBottom);
    juceVersion_arg.setFont(ptr_Global_CustomLookAndFeel->getFontRobotoCondensedBold().withHeight(17.0F));
    juceVersion_arg.setColour(juce::Label::backgroundColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomTransparent);
    juceVersion_arg.setColour(juce::Label::textColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomGroupComponent);
    juceVersion_arg.setLookAndFeel(ptr_Global_CustomLookAndFeel);
    addAndMakeVisible(juceVersion_arg);

    closeDialog_2_Info.setButtonText("CLOSE");
    closeDialog_2_Info.setComponentID("Buttons_ID_02_Close_Group");
    closeDialog_2_Info.onClick = [this]()
        {
            currentSlideWorksPage = previousSlideWorksPage;

            if (currentSlideWorksPage == PageState::PAGE2_WORKSPACE) 
                updatePage2WorkVisibility(true);

            updatePage3InfoVisibility(false);
            repaint();
        };
    addAndMakeVisible(closeDialog_2_Info);

    updatePage3InfoVisibility(false);



    ///// OLD /////
    groupDialog1.setName("DIALOG1");
    groupDialog1.setText("ADD IMAGES");
    groupDialog1.setTextLabelPosition(juce::Justification::centred);
    groupDialog1.setFont(ptr_Global_CustomLookAndFeel->getFontRobotoCondensedBold().withHeight(17.0F));
    groupDialog1.setFontColour(ptr_Global_CustomLookAndFeel->getColorCustomDarkGrey());
    groupDialog1.setOutlineColour(ptr_Global_CustomLookAndFeel->getColorCustomDarkGrey());
    groupDialog1.setCornerSize(10.0F);
    groupDialog1.setIndentation(3);
    groupDialog1.setTextLineGap(8.0F);
    groupDialog1.setLineThickness(2.0F);
    addAndMakeVisible(groupDialog1);


    groupTotalFrames.setName("TOTAL FRAMES");
    groupTotalFrames.setText("TOTAL FRAMES");
    groupTotalFrames.setTextLabelPosition(juce::Justification::centred);
    groupTotalFrames.setFont(ptr_Global_CustomLookAndFeel->getFontRobotoCondensedBold().withHeight(17.0F));
    groupTotalFrames.setFontColour(ptr_Global_CustomLookAndFeel->getColorCustomDarkGrey().darker());
    groupTotalFrames.setOutlineColour(ptr_Global_CustomLookAndFeel->getColorCustomDarkGrey());
    groupTotalFrames.setCornerSize(10.0F);
    groupTotalFrames.setIndentation(indentation);
    groupTotalFrames.setTextLineGap(gap);
    groupTotalFrames.setLineThickness(2.0F);
    addAndMakeVisible(groupTotalFrames);

    groupOrientation.setName("ORIENTATION");
    groupOrientation.setText("ORIENTATION");
    groupOrientation.setTextLabelPosition(juce::Justification::centred);
    groupOrientation.setFont(ptr_Global_CustomLookAndFeel->getFontRobotoCondensedBold().withHeight(17.0F));
    groupOrientation.setFontColour(ptr_Global_CustomLookAndFeel->getColorCustomDarkGrey().darker());
    groupOrientation.setOutlineColour(ptr_Global_CustomLookAndFeel->getColorCustomDarkGrey());
    groupOrientation.setCornerSize(10.0F);
    groupOrientation.setIndentation(indentation);
    groupOrientation.setTextLineGap(gap);
    groupOrientation.setLineThickness(2.0F);
    addAndMakeVisible(groupOrientation);

    groupKnobAngles.setName("ANGLES");
    groupKnobAngles.setText("ANGLES");
    groupKnobAngles.setTextLabelPosition(juce::Justification::centred);
    groupKnobAngles.setFont(ptr_Global_CustomLookAndFeel->getFontRobotoCondensedBold().withHeight(17.0F));
    groupKnobAngles.setFontColour(ptr_Global_CustomLookAndFeel->getColorCustomDarkGrey().darker());
    groupKnobAngles.setOutlineColour(ptr_Global_CustomLookAndFeel->getColorCustomDarkGrey());
    groupKnobAngles.setCornerSize(10.0F);
    groupKnobAngles.setIndentation(indentation);
    groupKnobAngles.setTextLineGap(gap);
    groupKnobAngles.setLineThickness(2.0F);
    addAndMakeVisible(groupKnobAngles);

    groupSliderThumbPositions.setName("THUMB POSITION");
    groupSliderThumbPositions.setText("THUMB POSITION");
    groupSliderThumbPositions.setTextLabelPosition(juce::Justification::centred);
    groupSliderThumbPositions.setFont(ptr_Global_CustomLookAndFeel->getFontRobotoCondensedBold().withHeight(17.0F));
    groupSliderThumbPositions.setFontColour(ptr_Global_CustomLookAndFeel->getColorCustomDarkGrey().darker());
    groupSliderThumbPositions.setOutlineColour(ptr_Global_CustomLookAndFeel->getColorCustomDarkGrey());
    groupSliderThumbPositions.setCornerSize(10.0F);
    groupSliderThumbPositions.setIndentation(indentation);
    groupSliderThumbPositions.setTextLineGap(gap);
    groupSliderThumbPositions.setLineThickness(2.0F);
    addAndMakeVisible(groupSliderThumbPositions);
}

void MainComponent::setupFilmstripControls(CustomLookAndFeel* customLookAndFeel)
{
    sliderTotalFrames.setName("sliderTotalFrames");
    sliderTotalFrames.setRange(7.0, 128, 1.0);
    sliderTotalFrames.setLookAndFeel(customLookAndFeel);
    sliderTotalFrames.setValue(69.0);
    sliderTotalFrames.setSliderStyle(juce::Slider::LinearHorizontal);
    sliderTotalFrames.setTextBoxStyle(juce::Slider::NoTextBox, true, 40, 20);
    sliderTotalFrames.setColour(juce::Slider::trackColourId, customLookAndFeel->getColorCustomDarkGrey());
    sliderTotalFrames.setColour(juce::Slider::thumbColourId, customLookAndFeel->getColorCustomWhite());
    sliderTotalFrames.setColour(juce::Slider::textBoxBackgroundColourId, customLookAndFeel->getColorCustomDarkGrey());
    sliderTotalFrames.setColour(juce::Slider::textBoxTextColourId, customLookAndFeel->getColorCustomLightGrey().brighter());
    sliderTotalFrames.setMouseClickGrabsKeyboardFocus(false);
    sliderTotalFrames.setTextBoxIsEditable(false);
    sliderTotalFrames.onValueChange = [this]() 
        {
            auto value = int(sliderTotalFrames.getValue());
            filmstripTotalFrames = value;
            labelBoxTotalFrames.setText(std::to_string(value), juce::dontSendNotification);
        };
    addAndMakeVisible(sliderTotalFrames);

    labelBoxTotalFrames.setName("labelBoxTotalFrames");
    labelBoxTotalFrames.setText(std::to_string(sliderTotalFrames.getValue()), juce::dontSendNotification);
    labelBoxTotalFrames.setFont(customLookAndFeel->getFontRobotoCondensedBold().withHeight(18.F));
    labelBoxTotalFrames.setColour(juce::Label::backgroundColourId, customLookAndFeel->getColorCustomDarkGrey());
    labelBoxTotalFrames.setColour(juce::Label::backgroundWhenEditingColourId, customLookAndFeel->getColorCustomDarkGrey());
    labelBoxTotalFrames.setColour(juce::Label::textColourId, customLookAndFeel->getColorCustomLightGrey().brighter(1.F));
    labelBoxTotalFrames.setColour(juce::Label::textWhenEditingColourId, customLookAndFeel->getColorCustomLightGrey().brighter(1.25F));
    labelBoxTotalFrames.setColour(juce::TextEditor::textColourId, customLookAndFeel->getColorCustomLightGrey().brighter(1.F));
    labelBoxTotalFrames.setColour(juce::TextEditor::highlightColourId, customLookAndFeel->getColorCustomLightGrey());
    labelBoxTotalFrames.setColour(juce::TextEditor::highlightedTextColourId, customLookAndFeel->getColorCustomDarkGrey());
    labelBoxTotalFrames.setColour(juce::CaretComponent::caretColourId, customLookAndFeel->getColorCustomWhite());
    labelBoxTotalFrames.setLookAndFeel(customLookAndFeel);
    labelBoxTotalFrames.setEditable(true, true, false);
    labelBoxTotalFrames.onTextChange = [this]() 
        {
            auto newValue = labelBoxTotalFrames.getText().getIntValue();

            if (newValue <= sliderTotalFrames.getMinimum())
            {
                newValue = int(sliderTotalFrames.getMinimum());
            }
            else if (newValue >= sliderTotalFrames.getMaximum())
            {
                newValue = int(sliderTotalFrames.getMaximum());
            }

            sliderTotalFrames.setValue(newValue, juce::sendNotification);
            filmstripTotalFrames = newValue;
        };
    addAndMakeVisible(labelBoxTotalFrames);
}

void MainComponent::setupOrientationButtons()
{
    horizontalButton.setName("horizontalButton");
    horizontalButton.setButtonText("HORIZONTAL");
    horizontalButton.setToggleState(false, juce::dontSendNotification);
    horizontalButton.onClick = [this]() 
        {
            togglingButtons(horizontalButton, verticalButton); 
            filmstripIsVertical = false;
        };
    addAndMakeVisible(horizontalButton);

    verticalButton.setName("verticalButton");
    verticalButton.setButtonText("VERTICAL");
    verticalButton.setToggleState(true, juce::dontSendNotification);
    verticalButton.onClick = [this]() 
        {
            togglingButtons(verticalButton, horizontalButton);
            filmstripIsVertical = true;
        };
    addAndMakeVisible(verticalButton);
}

void MainComponent::setupAnglesKnobControls(CustomLookAndFeel* customLookAndFeel)
{
    double minimalAngleBetween = 45.0;

    labelMinAngles.setName("labelMinAngles");
    labelMinAngles.setText("MIN", juce::dontSendNotification);
    labelMinAngles.setFont(customLookAndFeel->getFontRobotoCondensedBold().withHeight(customLookAndFeel->getFontSizeRegular()));
    labelMinAngles.setColour(juce::Label::textColourId, customLookAndFeel->getColorCustomDarkGrey().darker());
    labelMinAngles.setJustificationType(juce::Justification::centred);
    labelMinAngles.setLookAndFeel(customLookAndFeel);
    labelMinAngles.setEditable(false, false, false);
    addAndMakeVisible(labelMinAngles);

    sliderMinAngles.setName("sliderMinAngles");
    sliderMinAngles.setRange(-175, 175, 0.5);
    sliderMinAngles.setValue(-135);
    sliderMinAngles.setDoubleClickReturnValue(true, -135);
    sliderMinAngles.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    sliderMinAngles.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    //sliderMinAngles.setRotaryParameters(juce::degreesToRadians(-175.0F), juce::degreesToRadians(175.0F), true);
    sliderMinAngles.setRotaryParameters(juce::degreesToRadians(0.0F), juce::degreesToRadians(350.F), true);
    sliderMinAngles.setLookAndFeel(customLookAndFeel);
    sliderMinAngles.setColour(juce::Slider::trackColourId, customLookAndFeel->getColorCustomLightGrey());
    sliderMinAngles.setColour(juce::Slider::backgroundColourId, customLookAndFeel->getColorCustomDarkGrey());
    sliderMinAngles.setColour(juce::Slider::thumbColourId, customLookAndFeel->getColorCustomLightGrey());
    sliderMinAngles.setColour(juce::Slider::textBoxTextColourId, customLookAndFeel->getColorCustomDarkGrey().darker());
    sliderMinAngles.setColour(juce::TextEditor::backgroundColourId, customLookAndFeel->getColorCustomGrey());
    sliderMinAngles.setTextBoxIsEditable(true);
    sliderMinAngles.onValueChange = [this, minimalAngleBetween]()
        {
            if (sliderMaxAngles.getValue() - sliderMinAngles.getValue() <= minimalAngleBetween)
            {
                sliderMinAngles.setValue(sliderMaxAngles.getValue() - minimalAngleBetween);
            }
            minAngleDegree = sliderMinAngles.getValue();
        };
    addAndMakeVisible(sliderMinAngles);


    labelMaxAngles.setName("labelMaxAngles");
    labelMaxAngles.setText("MAX", juce::dontSendNotification);
    labelMaxAngles.setFont(customLookAndFeel->getFontRobotoCondensedBold().withHeight(customLookAndFeel->getFontSizeRegular()));
    labelMaxAngles.setColour(juce::Label::textColourId, customLookAndFeel->getColorCustomDarkGrey().darker());
    labelMaxAngles.setJustificationType(juce::Justification::centred);
    labelMaxAngles.setLookAndFeel(customLookAndFeel);
    labelMaxAngles.setEditable(false, false, false);
    addAndMakeVisible(labelMaxAngles);

    sliderMaxAngles.setName("sliderMaxAngles");
    sliderMaxAngles.setRange(-175, 175, 0.5);
    sliderMaxAngles.setValue(135);
    sliderMaxAngles.setDoubleClickReturnValue(true, 135);
    sliderMaxAngles.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    sliderMaxAngles.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    //sliderMaxAngles.setRotaryParameters(juce::degreesToRadians(-175.0F), juce::degreesToRadians(175.0F), true);
    sliderMaxAngles.setRotaryParameters(juce::degreesToRadians(0.0F), juce::degreesToRadians(350.F), true);
    sliderMaxAngles.setLookAndFeel(customLookAndFeel);
    sliderMaxAngles.setColour(juce::Slider::trackColourId, customLookAndFeel->getColorCustomLightGrey());
    sliderMaxAngles.setColour(juce::Slider::backgroundColourId, customLookAndFeel->getColorCustomDarkGrey());
    sliderMaxAngles.setColour(juce::Slider::thumbColourId, customLookAndFeel->getColorCustomLightGrey());
    sliderMaxAngles.setColour(juce::Slider::textBoxTextColourId, customLookAndFeel->getColorCustomDarkGrey().darker());
    sliderMaxAngles.setColour(juce::Label::backgroundColourId, customLookAndFeel->getColorCustomGrey());
    sliderMaxAngles.setTextBoxIsEditable(true);
    sliderMaxAngles.onValueChange = [this, minimalAngleBetween]()
        {
            if (sliderMaxAngles.getValue() - sliderMinAngles.getValue() <= minimalAngleBetween)
            {
                sliderMaxAngles.setValue(sliderMinAngles.getValue() + minimalAngleBetween);
            }
            maxAngleDegree = sliderMaxAngles.getValue();
        };
    addAndMakeVisible(sliderMaxAngles);


}

void MainComponent::setupSimulationKnob(CustomLookAndFeel* customLookAndFeel)
{
    simulationKnob.setName("simulationKnob");
    simulationKnob.setRange(0, 100, 1);
    simulationKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    simulationKnob.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    simulationKnob.setLookAndFeel(customLookAndFeel);
    simulationKnob.onValueChange = [this]() {};
    addAndMakeVisible(simulationKnob);
}

void MainComponent::resetDialog1()
{
    knobToggleWorksButton.setEnabled(true);
    sliderToggleWorksButton.setEnabled(true);

    addKnob.setVisible(false);
    addKnob.setEnabled(false);

    addKnobScale.setVisible(false);
    addKnobScale.setEnabled(false);

    addSliderTrack.setVisible(false);
    addSliderTrack.setEnabled(false);

    addSliderThumb.setVisible(false);
    addSliderThumb.setEnabled(false);

    addSliderScale.setVisible(false);
    addSliderScale.setEnabled(false);

    closeDialog1.setVisible(false);
    closeDialog1.setEnabled(false);
}


void MainComponent::fileChooserWindows(juce::String& inputPath)
{

    fileChooser.reset(new juce::FileChooser("Select a file", juce::File(), "*.png"));

    auto fileChooserFlags = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles;

    fileChooser->launchAsync(fileChooserFlags, [this, &inputPath](const juce::FileChooser& chooser)
        {
            juce::File selectedFile = chooser.getResult();

            if (selectedFile.existsAsFile())
            {
                inputPath = selectedFile.getFullPathName();

                if (selectedFile.hasFileExtension(".png"))
                {
                    DBG("Selected file is a valid PNG: " << inputPath);
                }
                else
                {
                    DBG("Selected file is NOT a PNG: " << inputPath);
                    inputPath.clear();  // Optionally clear the path if not valid
                }
            }
            else
            {
                DBG("No file selected");
                inputPath.clear();      // better than inputPath = "";
            }

            // Set openAddImage_Dialog1 to false after file selection
            openAddImage_Dialog1 = false;

            currentSlideWorksPage = PageState::PAGE2_WORKSPACE;

            resetDialog1();

            updateUI();

        }
    );
}

void MainComponent::updateUI()
{

    checkInputPathState();

    if (currentSlideWorksPage == PageState::PAGE1_GREETINGS)
    {
        SW_NewProjectButton.setEnabled(true);
        SW_NewProjectButton.setVisible(true);

        SW_ThemeButton.setEnabled(true);
        SW_ThemeButton.setVisible(true);
        
        SW_InfoButton.setEnabled(true);
        SW_InfoButton.setVisible(true);
        {
            groupDialog_2_Info.setEnabled(false);
            groupDialog_2_Info.setVisible(false);
        }

        browseButton.setEnabled(true);
        browseButton.setVisible(true);

        exportButton.setEnabled(false);
        exportButton.setVisible(false);

        sliderTotalFrames.setEnabled(false);
        sliderTotalFrames.setVisible(false);

        labelBoxTotalFrames.setEnabled(false);
        labelBoxTotalFrames.setVisible(false);

        horizontalButton.setEnabled(false);
        horizontalButton.setVisible(false);
        verticalButton.setEnabled(false);
        verticalButton.setVisible(false);

        labelMinAngles.setEnabled(false);
        labelMinAngles.setVisible(false);
        labelMaxAngles.setEnabled(false);
        labelMaxAngles.setVisible(false);
        sliderMinAngles.setEnabled(false);
        sliderMinAngles.setVisible(false);
        sliderMaxAngles.setEnabled(false);
        sliderMaxAngles.setVisible(false);

        //mode_SimulationButton.setEnabled(false);
        //mode_SimulationButton.setVisible(false);
        //mode_PreviewButton.setEnabled(false);
        //mode_PreviewButton.setVisible(false);
        //mode_EditButton.setEnabled(false);
        //mode_EditButton.setVisible(false);

        simulationKnob.setEnabled(false);
        simulationKnob.setVisible(false);
    }
    else if (currentSlideWorksPage == PageState::PAGE2_WORKSPACE)
    {
        {
            groupDialog_2_Info.setEnabled(false);
            groupDialog_2_Info.setVisible(false);
        }

        browseButton.setEnabled(false);
        browseButton.setVisible(false);

        exportButton.setEnabled(true);
        exportButton.setVisible(true);

        sliderTotalFrames.setEnabled(true);
        sliderTotalFrames.setVisible(true);

        labelBoxTotalFrames.setEnabled(true);
        labelBoxTotalFrames.setVisible(true);

        horizontalButton.setEnabled(true);
        horizontalButton.setVisible(true);
        verticalButton.setEnabled(true);
        verticalButton.setVisible(true);

        if (knobToggleWorksButton.getToggleState())
        {
            labelMinAngles.setEnabled(true);
            labelMinAngles.setVisible(true);
            labelMaxAngles.setEnabled(true);
            labelMaxAngles.setVisible(true);
            sliderMinAngles.setEnabled(true);
            sliderMinAngles.setVisible(true);
            sliderMaxAngles.setEnabled(true);
            sliderMaxAngles.setVisible(true);
        } 
        
        if (sliderToggleWorksButton.getToggleState())
        {
            labelMinAngles.setEnabled(false);
            labelMinAngles.setVisible(false);
            labelMaxAngles.setEnabled(false);
            labelMaxAngles.setVisible(false);
            sliderMinAngles.setEnabled(false);
            sliderMinAngles.setVisible(false);
            sliderMaxAngles.setEnabled(false);
            sliderMaxAngles.setVisible(false);
        }

        //mode_SimulationButton.setEnabled(true);
        //mode_SimulationButton.setVisible(true);
        //mode_PreviewButton.setEnabled(true);
        //mode_PreviewButton.setVisible(true);
        //mode_EditButton.setEnabled(true);
        //mode_EditButton.setVisible(true);

        //if (SlideWorksMode == ModeState::SIMULATION) 
        //{
        //    simulationKnob.setEnabled(true);
        //    simulationKnob.setVisible(true);
        //}
        //else if (SlideWorksMode == ModeState::PREVIEW)
        //{
        //    simulationKnob.setEnabled(false);
        //    simulationKnob.setVisible(false);
        //}
        //else if (SlideWorksMode == ModeState::EDIT)
        //{
        //    simulationKnob.setEnabled(false);
        //    simulationKnob.setVisible(false);
        //}

    }
    else if (currentSlideWorksPage == PageState::PAGE3_INFO)
    {
        {
            groupDialog_2_Info.setEnabled(true);
            groupDialog_2_Info.setVisible(true);
        }
    }

    // SYSTEM INI PERLU DIPERBAIKI
    {
        // Set openAddImage_Dialog1 to false after file selection
        openAddImage_Dialog1 = false;

        if (openAddImage_Dialog1 == false)
        {
            resetDialog1();
        }
    }

    repaint();
    DBG("REPAINT NOW");
}




void MainComponent::openDialog1(juce::Graphics& g)
{
    //DBG("OPEN DIALOG1");

    auto base_width = 200;
    auto base_height = 200;

    if (knobToggleWorksButton.getToggleState() == true)        base_height = 205;
    else if (sliderToggleWorksButton.getToggleState() == true) base_height = 260;

    // AUTOMATIC CENTER
    auto baseOpenDialog1{ base_Workspace.withSizeKeepingCentre(base_width, base_height) };

    //g.setColour(customLookAndFeel->getColorCustomLightGrey().brighter());
    //g.drawRoundedRectangle(baseOpenDialog1.toFloat(), 10.0F, 4.0F);

    auto groupDialog1Area = baseOpenDialog1.reduced(10);
    groupDialog1Area.removeFromBottom(40);
    groupDialog1.setBounds(groupDialog1Area);
    groupDialog1.paint(g);

    auto dialog1ButtonsArea = groupDialog1Area;
    dialog1ButtonsArea.removeFromTop(15);
    dialog1ButtonsArea = dialog1ButtonsArea.reduced(3); // 3 is indentation value of groupComponent line
    dialog1ButtonsArea = dialog1ButtonsArea.reduced(7);

    auto pad = 5;
    auto buttonW = 100 + (pad * 2);
    dialog1ButtonsArea = dialog1ButtonsArea.withSizeKeepingCentre(buttonW, dialog1ButtonsArea.getHeight());

    auto dialog1ButtonArea2 = dialog1ButtonsArea;

    if (knobToggleWorksButton.getToggleState() == true)
    {
        auto buttonHeight     = dialog1ButtonArea2.getHeight() / 2;
        auto addKnobRect      = dialog1ButtonArea2.removeFromTop(buttonHeight);
        auto addKnobScaleRect = dialog1ButtonArea2.removeFromTop(buttonHeight);

        addKnob.setBounds(addKnobRect.reduced(pad));
        addKnobScale.setBounds(addKnobScaleRect.reduced(pad));

        {
            knobToggleWorksButton.setEnabled(false);
            sliderToggleWorksButton.setEnabled(false);

            addKnob.setVisible(true);
            addKnob.setEnabled(true);

            addKnobScale.setVisible(true);
            addKnobScale.setEnabled(true);

            addSliderTrack.setVisible(false);
            addSliderTrack.setEnabled(false);

            addSliderThumb.setVisible(false);
            addSliderThumb.setEnabled(false);

            addSliderScale.setVisible(false);
            addSliderScale.setEnabled(false);
        }

    }
    else if (sliderToggleWorksButton.getToggleState() == true)
    {
        auto buttonHeight       = dialog1ButtonArea2.getHeight() / 3;
        auto addSliderTrackRect = dialog1ButtonArea2.removeFromTop(buttonHeight);
        auto addSliderThumbRect = dialog1ButtonArea2.removeFromTop(buttonHeight);
        auto addSliderScaleRect = dialog1ButtonArea2.removeFromTop(buttonHeight);

        addSliderTrack.setBounds(addSliderTrackRect.reduced(pad));
        addSliderThumb.setBounds(addSliderThumbRect.reduced(pad));
        addSliderScale.setBounds(addSliderScaleRect.reduced(pad));

        {
            sliderToggleWorksButton.setEnabled(false);
            knobToggleWorksButton.setEnabled(false);

            addKnob.setVisible(false);
            addKnob.setEnabled(false);

            addKnobScale.setVisible(false);
            addKnobScale.setEnabled(false);

            addSliderTrack.setVisible(true);
            addSliderTrack.setEnabled(true);

            addSliderThumb.setVisible(true);
            addSliderThumb.setEnabled(true);

            addSliderScale.setVisible(true);
            addSliderScale.setEnabled(true);
        }
    }

    //g.setColour(customLookAndFeel->getColorCustomGrey());
    //g.drawRoundedRectangle(dialog1ButtonsArea.toFloat(), 10.0F, 2.0);

    {
        // CLOSE BUTTON
        auto w = 100;
        auto h = 30;
        juce::Rectangle dialog1Close{
            baseOpenDialog1.getX() + (baseOpenDialog1.getWidth() - w) / 2,
            baseOpenDialog1.getBottom() - h - 10,
            w,
            h
        };
        //g.setColour(customLookAndFeel->getColorCustomDarkGrey());
        //g.drawRoundedRectangle(dialog1Close.toFloat(), 5.0F, 2.0F);
        closeDialog1.setBounds(dialog1Close);
    }


    repaint();
}