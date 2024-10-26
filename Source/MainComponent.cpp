#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize(800, 540);   // This is mandatory to not trigger error in debug mode


    // Assign the pointer of customLookAndFeel
    customLookAndFeel = std::make_unique<CustomLookAndFeel>();

    setupLayoutUI();
    setupButtons();
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
    g.fillAll(customLookAndFeel->getColorCustomDarkGrey());

    if (SlideWorksPage == PAGE1)
    {
        g.setColour(customLookAndFeel->getColorCustomLightGrey());
        g.fillRoundedRectangle(base_WorkSpace.toFloat(), customLookAndFeel->getRoundedCornerSize());

        if (openAddImage_Dialog1 == false)
        {
            g.setFont(customLookAndFeel->getFontRobotoCondensed().withHeight(customLookAndFeel->getFontSizeTitle()));
            g.setColour(customLookAndFeel->getColorCustomDarkGrey());

            g.drawText("DRAG DROP NOT WORKING FOR NOW", base_WorkSpace, juce::Justification::centred, true);
        }

        if (openAddImage_Dialog1 == true)
        {
            openDialog1(g);
        }
    }
    
    if (SlideWorksPage == PAGE2)
    {
        g.setColour(customLookAndFeel->getColorCustomLightGrey());

        g.fillRoundedRectangle(left_WorkSpace.toFloat(), customLookAndFeel->getRoundedCornerSize());
        g.fillRoundedRectangle(right_WorkSpace.toFloat(), customLookAndFeel->getRoundedCornerSize());

        g.setColour(customLookAndFeel->getColorCustomDarkGrey());
        g.fillRoundedRectangle(filmstripBanner.toFloat(), customLookAndFeel->getRoundedCornerSize());

        g.setFont(customLookAndFeel->getFontRobotoCondensed().withHeight(18));
        g.setColour(customLookAndFeel->getColorCustomWhite());
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
        g.setColour(customLookAndFeel->getColorCustomGrey());
        //g.drawRoundedRectangle(debugOutline.toFloat().reduced(debugOutline.getWidth() * 0.01F), 10.0F, 2.0F);
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

    base_WorkSpace = base_SlideWorks;
    base_WorkSpace.removeFromTop(knobToggleWorksButton.getHeight() + 5);

    ///////////////// PAGE 2 COMPONENT /////////////////
    auto area = base_WorkSpace;
    //left_WorkSpace = area.removeFromLeft(275);
    left_WorkSpace = area.removeFromLeft(int(area.getWidth() * 0.35F));
    area.removeFromLeft(5);
    right_WorkSpace = area;

    auto left_area = left_WorkSpace.reduced(5);
    auto left_area_H = left_area.getHeight();
    //auto spacing = 15;
    auto spacing = int(left_area_H * 0.035F);

    filmstripBanner = left_area.removeFromTop(25);
    left_area = left_area.withSizeKeepingCentre(left_area.getWidth() - 25, left_area.getHeight());
    left_area.removeFromTop(int(spacing * 1.5));

    //auto groupTotalFramesArea = left_area.removeFromTop(75);
    auto groupTotalFramesArea = left_area.removeFromTop(int(left_area_H * 0.160F));
    groupTotalFrames.setBounds(groupTotalFramesArea);
    left_area.removeFromTop(spacing);

    auto control1Area = groupTotalFramesArea;
    control1Area.removeFromTop(int(spacing * 0.70F));
    control1Area = control1Area.withSizeKeepingCentre(int(control1Area.getWidth() * 0.825F), control1Area.getHeight());
    debugOutline = control1Area;
    control1Area.removeFromRight(int(control1Area.getWidth() * 0.075F));
    sliderTotalFrames.setBounds(control1Area);

    //auto groupOrientationArea = left_area.removeFromTop(95);
    auto groupOrientationArea = left_area.removeFromTop(int(left_area_H * 0.225F));
    groupOrientation.setBounds(groupOrientationArea);
    left_area.removeFromTop(spacing);

    //auto groupAnglesArea = left_area.removeFromTop(160);
    auto groupAnglesArea = left_area.removeFromTop(int(left_area_H * 0.370F));
    groupKnobAngles.setBounds(groupAnglesArea);

    auto groupThumbPosArea = groupAnglesArea;
    groupSliderThumbPositions.setBounds(groupThumbPosArea);

    left_area.removeFromTop(spacing/2);

    auto exportButtonArea = left_area.withSizeKeepingCentre(100, 25);
    exportButton.setBounds(exportButtonArea);

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

    }
    else
    {
        SlideWorksPage = PAGE1;
    }
}

bool MainComponent::getInputPathState()
{
    return inputPathState;
}

void MainComponent::setupButtons()
{
    setupKnobToggleButton();
    setupSliderToggleButton();
    setupBrowseButton();
    setupExportButton();

    setupAddKnobButton();
    setupAddKnobScaleButton();
    setupAddSliderTrackButton();
    setupAddSliderThumbButton();
    setupAddSliderScaleButton();
    setupCloseDialog1Button();

    setupFilmstripControls();
}

void MainComponent::setupKnobToggleButton()
{
    knobToggleWorksButton.setButtonText("KNOB");
    knobToggleWorksButton.setName("knobWorks");
    knobToggleWorksButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    knobToggleWorksButton.onClick = [this]() { toggleButtons(knobToggleWorksButton, sliderToggleWorksButton); };
    addAndMakeVisible(knobToggleWorksButton);
}

void MainComponent::setupSliderToggleButton()
{
    sliderToggleWorksButton.setButtonText("SLIDER");
    sliderToggleWorksButton.setName("sliderWorks");
    sliderToggleWorksButton.setToggleState(false, juce::NotificationType::dontSendNotification);
    sliderToggleWorksButton.onClick = [this]() { toggleButtons(sliderToggleWorksButton, knobToggleWorksButton); };
    addAndMakeVisible(sliderToggleWorksButton);
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

void MainComponent::toggleButtons(juce::TextButton& activeButton, juce::TextButton& inactiveButton)
{
    activeButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    inactiveButton.setToggleState(false, juce::NotificationType::dontSendNotification);

    repaint();
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
    groupDialog1.setFont(customLookAndFeel->getFontRobotoCondensed().withHeight(17.0F));
    groupDialog1.setFontColour(customLookAndFeel->getColorCustomDarkGrey());
    groupDialog1.setOutlineColour(customLookAndFeel->getColorCustomDarkGrey());
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
    groupTotalFrames.setFont(customLookAndFeel->getFontRobotoCondensed().withHeight(17.0F));
    groupTotalFrames.setFontColour(customLookAndFeel->getColorCustomDarkGrey().darker());
    groupTotalFrames.setOutlineColour(customLookAndFeel->getColorCustomDarkGrey());
    groupTotalFrames.setCornerSize(10.0F);
    groupTotalFrames.setIndentation(indentation);
    groupTotalFrames.setTextLineGap(gap);
    groupTotalFrames.setLineThickness(2.0F);
    addAndMakeVisible(groupTotalFrames);

    groupOrientation.setName("ORIENTATION");
    groupOrientation.setText("ORIENTATION");
    groupOrientation.setTextLabelPosition(juce::Justification::centred);
    groupOrientation.setFont(customLookAndFeel->getFontRobotoCondensed().withHeight(17.0F));
    groupOrientation.setFontColour(customLookAndFeel->getColorCustomDarkGrey().darker());
    groupOrientation.setOutlineColour(customLookAndFeel->getColorCustomDarkGrey());
    groupOrientation.setCornerSize(10.0F);
    groupOrientation.setIndentation(indentation);
    groupOrientation.setTextLineGap(gap);
    groupOrientation.setLineThickness(2.0F);
    addAndMakeVisible(groupOrientation);

    groupKnobAngles.setName("ANGLES");
    groupKnobAngles.setText("ANGLES");
    groupKnobAngles.setTextLabelPosition(juce::Justification::centred);
    groupKnobAngles.setFont(customLookAndFeel->getFontRobotoCondensed().withHeight(17.0F));
    groupKnobAngles.setFontColour(customLookAndFeel->getColorCustomDarkGrey().darker());
    groupKnobAngles.setOutlineColour(customLookAndFeel->getColorCustomDarkGrey());
    groupKnobAngles.setCornerSize(10.0F);
    groupKnobAngles.setIndentation(indentation);
    groupKnobAngles.setTextLineGap(gap);
    groupKnobAngles.setLineThickness(2.0F);
    addAndMakeVisible(groupKnobAngles);

    groupSliderThumbPositions.setName("THUMB POSITION");
    groupSliderThumbPositions.setText("THUMB POSITION");
    groupSliderThumbPositions.setTextLabelPosition(juce::Justification::centred);
    groupSliderThumbPositions.setFont(customLookAndFeel->getFontRobotoCondensed().withHeight(17.0F));
    groupSliderThumbPositions.setFontColour(customLookAndFeel->getColorCustomDarkGrey().darker());
    groupSliderThumbPositions.setOutlineColour(customLookAndFeel->getColorCustomDarkGrey());
    groupSliderThumbPositions.setCornerSize(10.0F);
    groupSliderThumbPositions.setIndentation(indentation);
    groupSliderThumbPositions.setTextLineGap(gap);
    groupSliderThumbPositions.setLineThickness(2.0F);
    addAndMakeVisible(groupSliderThumbPositions);
}

void MainComponent::setupFilmstripControls()
{
    sliderTotalFrames.setName("sliderTotalFrames");
    sliderTotalFrames.setRange(3.0, 180.0, 1.0);
    sliderTotalFrames.setLookAndFeel(customLookAndFeel.get());
    sliderTotalFrames.setValue(69.0);
    sliderTotalFrames.setSliderStyle(juce::Slider::LinearHorizontal);
    sliderTotalFrames.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    sliderTotalFrames.setColour(juce::Slider::trackColourId, customLookAndFeel->getColorCustomDarkGrey());
    sliderTotalFrames.setColour(juce::Slider::thumbColourId, customLookAndFeel->getColorCustomWhite());
    sliderTotalFrames.setColour(juce::Slider::textBoxBackgroundColourId, customLookAndFeel->getColorCustomDarkGrey());
    sliderTotalFrames.setColour(juce::Slider::textBoxTextColourId, customLookAndFeel->getColorCustomLightGrey().brighter());
    sliderTotalFrames.setMouseClickGrabsKeyboardFocus(false);
    sliderTotalFrames.setTextBoxIsEditable(true);
    sliderTotalFrames.onValueChange = [this]() 
        {
            filmstripTotalFrames = int(sliderTotalFrames.getValue()); 
        };
    addAndMakeVisible(sliderTotalFrames);
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
        browseButton.setEnabled(true);
        browseButton.setVisible(true);

        exportButton.setEnabled(false);
        exportButton.setVisible(false);

        sliderTotalFrames.setEnabled(false);
        sliderTotalFrames.setVisible(false);
    }
    else
    {
        browseButton.setEnabled(false);
        browseButton.setVisible(false);

        exportButton.setEnabled(true);
        exportButton.setVisible(true);

        sliderTotalFrames.setEnabled(true);
        sliderTotalFrames.setVisible(true);
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
        DBG("buttonHeight: " << buttonHeight);
        auto addKnobRect      = dialog1ButtonArea2.removeFromTop(buttonHeight);
        auto addKnobScaleRect = dialog1ButtonArea2.removeFromTop(buttonHeight);

        addKnob.setBounds(addKnobRect.reduced(pad));
        addKnobScale.setBounds(addKnobScaleRect.reduced(pad));

        {
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
        DBG("buttonHeight: " << buttonHeight);
        auto addSliderTrackRect = dialog1ButtonArea2.removeFromTop(buttonHeight);
        auto addSliderThumbRect = dialog1ButtonArea2.removeFromTop(buttonHeight);
        auto addSliderScaleRect = dialog1ButtonArea2.removeFromTop(buttonHeight);

        addSliderTrack.setBounds(addSliderTrackRect.reduced(pad));
        addSliderThumb.setBounds(addSliderThumbRect.reduced(pad));
        addSliderScale.setBounds(addSliderScaleRect.reduced(pad));

        {
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