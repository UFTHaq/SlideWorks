#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize(800, 540);   // This is mandatory to not trigger error in debug mode


    setupLayoutUI();
    //setupButtons(&customLookAndFeel);
    setupButtons(Globals::getCustomLookAndFeel().get());

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
    //g.fillAll(customLookAndFeel.getColorCustomDarkGrey());
    g.fillAll(juce::Colour::fromString("ffbebebe"));

    if (SlideWorksPage == PAGE1)
    {
        g.setColour(customLookAndFeel.getColorCustomLightGrey());
        g.fillRoundedRectangle(base_WorkSpace.toFloat(), 2);

        if (openAddImage_Dialog1 == false)
        {
            g.setFont(customLookAndFeel.getFontRobotoCondensedBold().withHeight(customLookAndFeel.getFontSizeTitle()));
            g.setColour(customLookAndFeel.getColorCustomDarkGrey());

            g.drawText("DRAG DROP NOT WORKING FOR NOW", base_WorkSpace, juce::Justification::centred, true);
        }

        if (openAddImage_Dialog1 == true)
        {
            openDialog1(g);
        }
    }
    
    if (SlideWorksPage == PAGE2)
    {
        g.setColour(customLookAndFeel.getColorCustomLightGrey());

        g.fillRoundedRectangle(left_WorkSpace.toFloat(), customLookAndFeel.getRoundedCornerSize());
        g.fillRoundedRectangle(right_WorkSpace.toFloat(), customLookAndFeel.getRoundedCornerSize());

        g.setColour(customLookAndFeel.getColorCustomDarkGrey());
        g.fillRoundedRectangle(filmstripBanner.toFloat(), customLookAndFeel.getRoundedCornerSize());

        g.setFont(customLookAndFeel.getFontRobotoCondensedBold().withHeight(18));
        g.setColour(customLookAndFeel.getColorCustomWhite());
        g.drawText("FILMSTRIP", filmstripBanner, juce::Justification::centred, true);

        if (knobToggleWorksButton.getToggleState())
        {
            groupTotalFrames.paint(g);
            groupOrientation.paint(g);
            groupKnobAngles.paint(g);
        }

        if (sliderToggleWorksButton.getToggleState())
        {
            groupTotalFrames.paint(g);
            groupOrientation.paint(g);
            groupSliderThumbPositions.paint(g);
        }

        // debug only
        g.setColour(customLookAndFeel.getColorCustomGrey());
        //g.drawRoundedRectangle(debugOutlineTotalFrames.toFloat().reduced(debugOutlineTotalFrames.getWidth() * 0.01F), 5.0F, 1.0F);
        //g.drawRoundedRectangle(debugOutlineLeftTotalFrames.toFloat().reduced(debugOutlineTotalFrames.getWidth() * 0.01F), 5.0F, 1.0F);
        //g.drawRoundedRectangle(debugOutlineRightTotalFrames.toFloat().reduced(debugOutlineTotalFrames.getWidth() * 0.01F), 5.0F, 1.0F);

        //g.drawRoundedRectangle(debugOutlineOrientation.toFloat().reduced(debugOutlineOrientation.getWidth() * 0.01F), 5.0F, 1.0F);
        //g.drawRoundedRectangle(debugOutlineOrientationHorizontal.toFloat().reduced(debugOutlineOrientation.getWidth() * 0.01F), 5.0F, 1.0F);
        //g.drawRoundedRectangle(debugOutlineOrientationVertical.toFloat().reduced(debugOutlineOrientation.getWidth() * 0.01F), 5.0F, 1.0F);
        
        //g.drawRoundedRectangle(debugOutlineAngles.toFloat().reduced(debugOutlineAngles.getWidth() * 0.01F), 5.0F, 1.0F);
        //g.drawRoundedRectangle(debugOutlineAnglesMin.toFloat().reduced(debugOutlineAnglesMin.getWidth() * 0.01F), 5.0F, 1.0F);
        //g.drawRoundedRectangle(debugOutlineAnglesMax.toFloat().reduced(debugOutlineAnglesMax.getWidth() * 0.01F), 5.0F, 1.0F);

        //g.drawRoundedRectangle(debugOutlineAnglesMinTop.toFloat().reduced(debugOutlineAnglesMinTop.getWidth() * 0.01F), 5.0F, 1.0F);
        //g.drawRoundedRectangle(debugOutlineAnglesMinKnob.toFloat().reduced(debugOutlineAnglesMinKnob.getWidth() * 0.01F), 5.0F, 1.0F);

        //g.drawRoundedRectangle(debugOutlineAnglesMaxTop.toFloat().reduced(debugOutlineAnglesMaxTop.getWidth() * 0.01F), 5.0F, 1.0F);
        //g.drawRoundedRectangle(debugOutlineAnglesMaxKnob.toFloat().reduced(debugOutlineAnglesMaxKnob.getWidth() * 0.01F), 5.0F, 1.0F);

        if (SlideWorksMode == SIMULATION)
        {
            g.setColour(customLookAndFeel.getColorCustomWhite());
            g.drawRoundedRectangle(debugOutlineSimulationArea.toFloat(), 3.0F, 0.5F);
        }

    }


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

/////////////////////////////////////////////////////////////////////
void MainComponent::setupLayoutUI()
{
    ///////////////// NEW PLAN PAGE 1 COMPONENT /////////////////
    base_SlideWorks = getLocalBounds().reduced(5);
    int componentSpace = 2;

    juce::Rectangle<int> area_NewProjectButton{ base_SlideWorks.getX(), base_SlideWorks.getY(), 50, 20 };
    juce::Rectangle<int> area_ThemeButton{ area_NewProjectButton.getRight() + componentSpace, area_NewProjectButton.getY(), area_NewProjectButton.getWidth(), area_NewProjectButton.getHeight() };
    juce::Rectangle<int> area_InfoButton{ area_ThemeButton.getRight() + componentSpace, area_NewProjectButton.getY(), area_NewProjectButton.getWidth(), area_NewProjectButton.getHeight() };

    SW_NewProjectButton.setBounds(area_NewProjectButton);
    SW_ThemeButton.setBounds(area_ThemeButton);
    SW_InfoButton.setBounds(area_InfoButton);

    base_WorkSpace = base_SlideWorks;
    base_WorkSpace.removeFromTop(SW_NewProjectButton.getHeight() + componentSpace);



    ///////////////// PAGE 1 COMPONENT /////////////////
    base_SlideWorks = getLocalBounds().reduced(10);

    knobToggleWorksButton.setBounds(
        { base_SlideWorks.getX(), 
        base_SlideWorks.getY(), 
        75, 25 
        }
    );
    sliderToggleWorksButton.setBounds(
        {
            knobToggleWorksButton.getX() + knobToggleWorksButton.getWidth() + 5,
            knobToggleWorksButton.getY(),
            knobToggleWorksButton.getWidth(),
            knobToggleWorksButton.getHeight()
        }
    );
    browseButton.setBounds(
        {
            base_SlideWorks.getRight() - knobToggleWorksButton.getWidth(),
            knobToggleWorksButton.getY(),
            knobToggleWorksButton.getWidth(),
            knobToggleWorksButton.getHeight()
        }
    );

    //base_WorkSpace = base_SlideWorks;
    //base_WorkSpace.removeFromTop(knobToggleWorksButton.getHeight() + 5);

    ///////////////// PAGE 2 COMPONENT /////////////////
    {
        auto buttonW = 90;
            modeSimulationButton.setBounds
            (
                {
                    base_SlideWorks.getRight() - buttonW,
                    knobToggleWorksButton.getY(),
                    buttonW,
                    knobToggleWorksButton.getHeight()
                }
        );

        modePreviewButton.setBounds
        (
            {
                modeSimulationButton.getX() - buttonW - 5,
                modeSimulationButton.getY(),
                modeSimulationButton.getWidth(),
                modeSimulationButton.getHeight()
            }
        );

        modeResizeButton.setBounds
        (
            {
                modePreviewButton.getX() - buttonW - 5,
                modeSimulationButton.getY(),
                modeSimulationButton.getWidth(),
                modeSimulationButton.getHeight()
            }
        );
    }


    auto area = base_WorkSpace;
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

void MainComponent::checkInputPathState()
{
    if (inputPathKnob.isNotEmpty() ||
        inputPathKnobScale.isNotEmpty() ||
        inputPathSliderTrack.isNotEmpty() ||
        inputPathSliderThumb.isNotEmpty() ||
        inputPathSliderScale.isNotEmpty()
        )
    {
        SlideWorksPage = PAGE2;

        loadSimulationImage();
    }
    else
    {
        SlideWorksPage = PAGE1;
    }


}

void MainComponent::loadSimulationImage()
{
    if (isSimulationImageLoaded == false && inputPathKnob.isNotEmpty()) {
        juce::Image image{ juce::ImageFileFormat::loadFrom(inputPathKnob) };
        int totalStrip = 11;
        customLookAndFeel.setSimulationKnobImage(image, totalStrip, filmstripIsVertical, -135, 135);

        openGLComponent.setBounds(0, 0, image.getWidth(), image.getHeight() * totalStrip);
        openGLComponent.drawFilmstripKnobImage(image, totalStrip, filmstripIsVertical, -135, 135);
        customLookAndFeel.setFilmStripKnob(openGLComponent.getFilmstrip());

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


    setupKnobToggleButton();
    setupSliderToggleButton();
    setupBrowseButton();
    setupExportButton();

    setupSimulationButton();
    setupPreviewButton();
    setupResizeButton();

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
    addAndMakeVisible(SW_NewProjectButton);

    SW_ThemeButton.setButtonText("Theme");
    SW_ThemeButton.setComponentID("Buttons_ID_01_SW");
    SW_ThemeButton.setLookAndFeel(customLookAndFeel);
    SW_ThemeButton.onClick = [&, customLookAndFeel, this] ()
        {
            ThemeType currentTheme = customLookAndFeel->getCurrentThemeType();

            juce::PopupMenu menu;
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

                    //triggerRepaint();

                    //setVisible(false);
                    //setVisible(true);

                    //if (auto* mainComp = dynamic_cast<MainComponent*>(getParentComponent()))
                    //{
                    //    mainComp->repaint();
                    //    
                    //}
                }
            );
        };
    addAndMakeVisible(SW_ThemeButton);

    SW_InfoButton.setButtonText("Info");
    SW_InfoButton.setComponentID("Buttons_ID_01_SW");
    SW_InfoButton.setLookAndFeel(customLookAndFeel);
    addAndMakeVisible(SW_InfoButton);
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
    addAndMakeVisible(browseButton);
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
    modeSimulationButton.setButtonText("SIMULATION");
    modeSimulationButton.setName("modeSimulationButton");
    modeSimulationButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    modeSimulationButton.onClick = [this]() 
        {
            SlideWorksMode = SIMULATION;
            togglingButtons(modeSimulationButton, modePreviewButton, modeResizeButton);
        };
    addAndMakeVisible(modeSimulationButton);
}

void MainComponent::setupPreviewButton()
{
    modePreviewButton.setButtonText("PREVIEW");
    modePreviewButton.setName("modePreviewButton");
    modePreviewButton.setToggleState(false, juce::NotificationType::dontSendNotification);
    modePreviewButton.onClick = [this]() 
        {
            SlideWorksMode = PREVIEW;
            togglingButtons(modePreviewButton, modeSimulationButton, modeResizeButton);
        };
    addAndMakeVisible(modePreviewButton);
}

void MainComponent::setupResizeButton()
{
    modeResizeButton.setButtonText("RESIZE");
    modeResizeButton.setName("modeResizeButton");
    modeResizeButton.setToggleState(false, juce::NotificationType::dontSendNotification);
    modeResizeButton.onClick = [this]() 
        {
            SlideWorksMode = RESIZE;
            togglingButtons(modeResizeButton, modeSimulationButton, modePreviewButton);
        };
    addAndMakeVisible(modeResizeButton);
}

void MainComponent::togglingButtons(juce::TextButton& activeButton, juce::TextButton& inactiveButton)
{
    activeButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    inactiveButton.setToggleState(false, juce::NotificationType::dontSendNotification);

    updateUI();
}

void MainComponent::togglingButtons(juce::TextButton& activeButton, juce::TextButton& inactiveButton1, juce::TextButton& inactiveButton2)
{
    activeButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    inactiveButton1.setToggleState(false, juce::NotificationType::dontSendNotification);
    inactiveButton2.setToggleState(false, juce::NotificationType::dontSendNotification);
    
    updateUI();
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
    closeDialog1.onClick = [this]() 
        { 
            openAddImage_Dialog1 = false;

            resetDialog1();
        };
    addAndMakeVisible(closeDialog1);
}

void MainComponent::setupCustomGroupComponents()
{
    groupDialog1.setName("DIALOG1");
    groupDialog1.setText("ADD IMAGES");
    groupDialog1.setTextLabelPosition(juce::Justification::centred);
    groupDialog1.setFont(customLookAndFeel.getFontRobotoCondensedBold().withHeight(17.0F));
    groupDialog1.setFontColour(customLookAndFeel.getColorCustomDarkGrey());
    groupDialog1.setOutlineColour(customLookAndFeel.getColorCustomDarkGrey());
    groupDialog1.setCornerSize(10.0F);
    groupDialog1.setIndentation(3);
    groupDialog1.setTextLineGap(8.0F);
    groupDialog1.setLineThickness(2.0F);
    addAndMakeVisible(groupDialog1);

    auto indentation = 5.0F;
    auto gap = 6.0F;
    groupTotalFrames.setName("TOTAL FRAMES");
    groupTotalFrames.setText("TOTAL FRAMES");
    groupTotalFrames.setTextLabelPosition(juce::Justification::centred);
    groupTotalFrames.setFont(customLookAndFeel.getFontRobotoCondensedBold().withHeight(17.0F));
    groupTotalFrames.setFontColour(customLookAndFeel.getColorCustomDarkGrey().darker());
    groupTotalFrames.setOutlineColour(customLookAndFeel.getColorCustomDarkGrey());
    groupTotalFrames.setCornerSize(10.0F);
    groupTotalFrames.setIndentation(indentation);
    groupTotalFrames.setTextLineGap(gap);
    groupTotalFrames.setLineThickness(2.0F);
    addAndMakeVisible(groupTotalFrames);

    groupOrientation.setName("ORIENTATION");
    groupOrientation.setText("ORIENTATION");
    groupOrientation.setTextLabelPosition(juce::Justification::centred);
    groupOrientation.setFont(customLookAndFeel.getFontRobotoCondensedBold().withHeight(17.0F));
    groupOrientation.setFontColour(customLookAndFeel.getColorCustomDarkGrey().darker());
    groupOrientation.setOutlineColour(customLookAndFeel.getColorCustomDarkGrey());
    groupOrientation.setCornerSize(10.0F);
    groupOrientation.setIndentation(indentation);
    groupOrientation.setTextLineGap(gap);
    groupOrientation.setLineThickness(2.0F);
    addAndMakeVisible(groupOrientation);

    groupKnobAngles.setName("ANGLES");
    groupKnobAngles.setText("ANGLES");
    groupKnobAngles.setTextLabelPosition(juce::Justification::centred);
    groupKnobAngles.setFont(customLookAndFeel.getFontRobotoCondensedBold().withHeight(17.0F));
    groupKnobAngles.setFontColour(customLookAndFeel.getColorCustomDarkGrey().darker());
    groupKnobAngles.setOutlineColour(customLookAndFeel.getColorCustomDarkGrey());
    groupKnobAngles.setCornerSize(10.0F);
    groupKnobAngles.setIndentation(indentation);
    groupKnobAngles.setTextLineGap(gap);
    groupKnobAngles.setLineThickness(2.0F);
    addAndMakeVisible(groupKnobAngles);

    groupSliderThumbPositions.setName("THUMB POSITION");
    groupSliderThumbPositions.setText("THUMB POSITION");
    groupSliderThumbPositions.setTextLabelPosition(juce::Justification::centred);
    groupSliderThumbPositions.setFont(customLookAndFeel.getFontRobotoCondensedBold().withHeight(17.0F));
    groupSliderThumbPositions.setFontColour(customLookAndFeel.getColorCustomDarkGrey().darker());
    groupSliderThumbPositions.setOutlineColour(customLookAndFeel.getColorCustomDarkGrey());
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

            SlideWorksPage = PAGE2;

            resetDialog1();

            updateUI();

        }
    );
}

void MainComponent::updateUI()
{

    checkInputPathState();

    if (SlideWorksPage == PAGE1) 
    {
        SW_NewProjectButton.setEnabled(true);
        SW_NewProjectButton.setVisible(true);

        SW_ThemeButton.setEnabled(1);
        SW_ThemeButton.setVisible(1);
        
        SW_InfoButton.setEnabled(1);
        SW_InfoButton.setVisible(1);


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

        modeSimulationButton.setEnabled(false);
        modeSimulationButton.setVisible(false);
        modePreviewButton.setEnabled(false);
        modePreviewButton.setVisible(false);
        modeResizeButton.setEnabled(false);
        modeResizeButton.setVisible(false);

        simulationKnob.setEnabled(false);
        simulationKnob.setVisible(false);
    }
    else
    {
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

        modeSimulationButton.setEnabled(true);
        modeSimulationButton.setVisible(true);
        modePreviewButton.setEnabled(true);
        modePreviewButton.setVisible(true);
        modeResizeButton.setEnabled(true);
        modeResizeButton.setVisible(true);

        if (SlideWorksMode == SIMULATION) 
        {
            simulationKnob.setEnabled(true);
            simulationKnob.setVisible(true);
        }
        else if (SlideWorksMode == PREVIEW)
        {
            simulationKnob.setEnabled(false);
            simulationKnob.setVisible(false);
        }
        else if (SlideWorksMode == RESIZE)
        {
            simulationKnob.setEnabled(false);
            simulationKnob.setVisible(false);
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
    auto baseOpenDialog1{ base_WorkSpace.withSizeKeepingCentre(base_width, base_height) };

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