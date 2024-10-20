#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize(800, 540);   // This is mandatory to not trigger error in debug mode

    // Assign the pointer of customLookAndFeel
    customLookAndFeel = std::make_unique<CustomLookAndFeel>();

    setupButtons();

    startTimer(debugInterval);
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
        g.fillRoundedRectangle(baseWorkSpace.toFloat(), customLookAndFeel->getRoundedCornerSize());

        g.setFont(customLookAndFeel->getFontRobotoCondensed().withHeight(customLookAndFeel->getFontSizeTitle()));
        g.setColour(customLookAndFeel->getColorCustomDarkGrey());
        g.drawText("DRAG DROP HERE", baseWorkSpace, juce::Justification::centred, true);
    }

}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

    baseSlideWorks = getLocalBounds().reduced(10);

    //juce::Rectangle<int> knobButtonPage{ baseSlideWorks.getX(), baseSlideWorks.getY(), 75, 25 };
    knobToggleWorksButton.setBounds({ baseSlideWorks.getX(), baseSlideWorks.getY(), 75, 25 });
    
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
            baseSlideWorks.getRight() - knobToggleWorksButton.getWidth(),
            knobToggleWorksButton.getY(),
            knobToggleWorksButton.getWidth(),
            knobToggleWorksButton.getHeight()
        }
    );

    baseWorkSpace = baseSlideWorks;
    baseWorkSpace.removeFromTop(knobToggleWorksButton.getHeight() + 5);


    repaint();
}


void MainComponent::timerCallback()
{
    debugTime += debugInterval;
    DBG("debugTime: " << debugTime);

    if (debugTime % 5000 == 0)
    {
        DBG("Should toggling the isInputEmpty");
        inputPathState = checkInputPathState();
        debugTime = 0;
        inputPathKnob = "";
        inputPathSliderTrack = "";
        updateUI();

        repaint();
    }

}


void MainComponent::buttonClicked(juce::Button* button)
{
    if (button == &browseButton)
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
    browseButton.onClick = [this]() { buttonClicked(&browseButton); }; // TODO: Add browse functionality.
    addAndMakeVisible(browseButton);
}

void MainComponent::toggleButtons(juce::TextButton& activeButton, juce::TextButton& inactiveButton)
{
    activeButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    inactiveButton.setToggleState(false, juce::NotificationType::dontSendNotification);
}

void MainComponent::updateUI()
{
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