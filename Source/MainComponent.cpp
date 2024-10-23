#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize(800, 540);   // This is mandatory to not trigger error in debug mode

    // Assign the pointer of customLookAndFeel
    customLookAndFeel = std::make_unique<CustomLookAndFeel>();

    setupButtons();

    updateUI();

    groupDialog1.setName("DIALOG1");
    groupDialog1.setText("ADD IMAGES");
    groupDialog1.setTextLabelPosition(juce::Justification::centred);
    groupDialog1.setColour(juce::GroupComponent::outlineColourId, customLookAndFeel->getColorCustomLightGrey());
    addAndMakeVisible(groupDialog1);

    groupDialog1Test.setName("DIALOG1");
    groupDialog1Test.setText("ADD IMAGES");
    groupDialog1Test.setTextLabelPosition(juce::Justification::centred);
    groupDialog1Test.setFont(customLookAndFeel->getFontRobotoCondensed().withHeight(17.0F));
    groupDialog1Test.setFontColour(customLookAndFeel->getColorCustomDarkGrey().darker());
    groupDialog1Test.setOutlineColour(customLookAndFeel->getColorCustomDarkGrey());
    groupDialog1Test.setCornerSize(10.0F);
    groupDialog1Test.setIndentation(3);
    groupDialog1Test.setTextLineGap(8.0F);
    groupDialog1Test.setLineThickness(3.0F);
    addAndMakeVisible(groupDialog1Test);
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

    if (getInputPathState() == false)
    {
        g.setColour(customLookAndFeel->getColorCustomLightGrey());
        g.fillRoundedRectangle(base_WorkSpace.toFloat(), customLookAndFeel->getRoundedCornerSize());

        g.setFont(customLookAndFeel->getFontRobotoCondensed().withHeight(customLookAndFeel->getFontSizeTitle()));
        g.setColour(customLookAndFeel->getColorCustomDarkGrey());

        if (!openAddImage_Dialog1)
        {
            g.drawText("DRAG DROP NOT WORKING FOR NOW", base_WorkSpace, juce::Justification::centred, true);
        }
    }

    if (openAddImage_Dialog1 == true)
    {
        openDialog1(g);

        repaint();
    }
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

    base_SlideWorks = getLocalBounds().reduced(10);

    //juce::Rectangle<int> knobButtonPage{ baseSlideWorks.getX(), baseSlideWorks.getY(), 75, 25 };
    knobToggleWorksButton.setBounds({ base_SlideWorks.getX(), base_SlideWorks.getY(), 75, 25 });
    
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


    repaint();
}


void MainComponent::timerCallback()
{

}


void MainComponent::buttonClicked(juce::Button* button)
{
    if (button == &browseButton)
    {
        //fileChooserWindows();

        /////////////// HOW CONTROL THIS IF OPEN WINDOW DIALOG
        //openAddImage_Dialog1 = true;
        //DBG("SHOULD BE OPEN DIALOG1");


        // THIS POPUP CAN BE OUTSIDE OF WINDOW, WHICH NOT WHAT I WANT, BUT GOOD TO KNOW THIS.
        //auto contentComp = std::make_unique<juce::Component>();
        //contentComp->setSize(250, 250);
        //juce::Rectangle<int> area = base_WorkSpace.withSizeKeepingCentre(250, 250);
        //juce::CallOutBox::launchAsynchronously(std::move(contentComp), area, nullptr);
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
            repaint();

            DBG("getInputPathState: " << (getInputPathState() ? "true" : "false"));
        }
    }

    juce::MouseCursor normalCursor = juce::MouseCursor(juce::MouseCursor::StandardCursorType::NormalCursor);
    juce::Desktop::getInstance().getMainMouseSource().showMouseCursor(normalCursor);
}

/////////////////////////////////////////////////////////////////////

bool MainComponent::checkInputPathState()
{
    // TODO: Check if input path for knobs and slider with their derivatives has VALID image path.
    if (knobToggleWorksButton.getToggleState())
    {
        return inputPathKnob.isNotEmpty() || inputPathKnobScale.isNotEmpty();
    }
    else if (sliderToggleWorksButton.getToggleState())
    {
        return inputPathSliderTrack.isNotEmpty() || inputPathSliderThumb.isNotEmpty() || inputPathSliderScale.isNotEmpty();
    }

    return false;
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

    setupAddKnobButton();
    setupAddKnobScaleButton();
    setupAddSliderTrackButton();
    setupAddSliderThumbButton();
    setupAddSliderScaleButton();
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
    browseButton.setName("BROWSE");
    browseButton.onClick = [this]() { openAddImage_Dialog1 = true; }; // TODO: Add browse functionality.
    addAndMakeVisible(browseButton);
}

void MainComponent::toggleButtons(juce::TextButton& activeButton, juce::TextButton& inactiveButton)
{
    activeButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    inactiveButton.setToggleState(false, juce::NotificationType::dontSendNotification);
}


void MainComponent::setupAddKnobButton()
{
    addKnob.setButtonText("KNOB");
    addKnob.setName("addKnob");
    addKnob.onClick = [this]() {};
    addAndMakeVisible(addKnob);
}

void MainComponent::setupAddKnobScaleButton() 
{
    addKnobScale.setButtonText("SCALE");
    addKnobScale.setName("addKnobScale");
    addKnobScale.onClick = [this]() {};
    addAndMakeVisible(addKnobScale);
}

void MainComponent::setupAddSliderTrackButton() 
{
    addSliderTrack.setButtonText("TRACK");
    addSliderTrack.setName("addSliderTrack");
    addSliderTrack.onClick = [this]() {};
    addAndMakeVisible(addSliderTrack);
}
void MainComponent::setupAddSliderThumbButton() 
{
    addSliderThumb.setButtonText("THUMB");
    addSliderThumb.setName("addSliderThumb");
    addSliderThumb.onClick = [this]() {};
    addAndMakeVisible(addSliderThumb);
}
void MainComponent::setupAddSliderScaleButton() 
{
    addSliderScale.setButtonText("SCALE");
    addSliderScale.setName("addSliderScale");
    addSliderScale.onClick = [this]() {};
    addAndMakeVisible(addSliderScale);
}



void MainComponent::fileChooserWindows()
{
    fileChooser.reset(new juce::FileChooser("Select a file", juce::File(), "*.png"));

    auto fileChooserFlags = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles;

    fileChooser->launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser)
        {
            juce::File selectedFile = chooser.getResult();
            if (selectedFile.existsAsFile())
            {
                juce::String path = selectedFile.getFullPathName();
                DBG("Selected file: " << path);

                if (knobToggleWorksButton.getToggleState())
                {
                    inputPathKnob = path;
                    DBG("inpuPath: " << inputPathKnob);
                }

                if (sliderToggleWorksButton.getToggleState())
                {
                    inputPathSliderTrack = path;
                    DBG("inpuPath: " << inputPathSliderTrack);
                }

                auto text = "empty";
                auto tes = getInputPathState();
                if (tes) text = "true";
                else text = "false";

                DBG("getInputPathState: " << text);

            }
            else
            {
                DBG("No file selected");
            }
        }
    );
}

void MainComponent::updateUI()
{
    base_SlideWorks = getLocalBounds().reduced(10);

    knobToggleWorksButton.setBounds({ base_SlideWorks.getX(), base_SlideWorks.getY(), 75, 25 });

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


    if (getInputPathState()) 
    {
        browseButton.setEnabled(false);
        browseButton.setVisible(false);
    }
    else
    {
        browseButton.setEnabled(true);
        browseButton.setVisible(true);
    }
}


void MainComponent::openDialog1(juce::Graphics& g)
{
    DBG("OPEN DIALOG1");

    auto base_width = 200;
    auto base_height = 280;

    // AUTOMATIC CENTER
    auto baseOpenDialog1{ base_WorkSpace.withSizeKeepingCentre(base_width, base_height) };

    //g.setColour(customLookAndFeel->getColorCustomLightGrey());
    //g.fillRoundedRectangle(baseOpenDialog1.toFloat(), customLookAndFeel->getRoundedCornerSize());

    g.setColour(customLookAndFeel->getColorCustomLightGrey().brighter());
    g.drawRoundedRectangle(baseOpenDialog1.toFloat(), 10.0F, 4.0F);

    auto groupDialog1Area = baseOpenDialog1.reduced(10);
    groupDialog1Area.removeFromBottom(30);
    groupDialog1.setBounds(groupDialog1Area);

    //g.setColour(juce::Colours::ghostwhite);
    //g.fillRoundedRectangle(groupDialog1Area.toFloat(), 5.0F);

    ////auto dialog1Close{ baseOpenDialog1.withSizeKeepingCentre(100,30).translated(0, baseOpenDialog1.getHeight()/2-15) };
    //auto dialog1Close{ baseOpenDialog1.withSize(100,30).withBottom(30)};
    //g.setColour(customLookAndFeel->getColorCustomDarkGrey());
    //g.drawRoundedRectangle(dialog1Close.toFloat(), customLookAndFeel->getRoundedCornerSize() * 3, 2.0F);

    groupDialog1Test.setBounds(groupDialog1Area);
    groupDialog1Test.paint(g);

    repaint();
}