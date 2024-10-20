#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
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

    //isInputPathEmpty = inputPathEmptyCheck();

    if (isInputPathEmpty) 
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

    if (debugTime >= 2000)
    {
        DBG("Should toggling the isInputEmpty");
        isInputPathEmpty = !isInputPathEmpty;
        debugTime = 0;
        updateUI();

        repaint();
    }

}


/////////////////////////////////////////////////////////////////////

bool MainComponent::inputPathEmptyCheck()
{
    // TODO: Check if input path for knobs and slider with their derivatives has VALID image path.
    if (knobToggleWorksButton.getToggleState())
    {
        if (inputPathKnob.isNotEmpty() || inputPathKnobScale.isNotEmpty()) {
            isInputPathEmpty = false;
            return isInputPathEmpty;
        }
    }
    else if (sliderToggleWorksButton.getToggleState())
    {
        if (inputPathSliderTrack.isNotEmpty() || inputPathSliderThumb.isNotEmpty() || inputPathSliderScale.isNotEmpty())
        {
            isInputPathEmpty = false;
            return isInputPathEmpty;
        }
    }

    return true;
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
    knobToggleWorksButton.setToggleState(false, juce::NotificationType::dontSendNotification);
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
    browseButton.onClick = [this]() {}; // TODO: Add browse functionality.
    addAndMakeVisible(browseButton);
}

void MainComponent::toggleButtons(juce::TextButton& activeButton, juce::TextButton& inactiveButton)
{
    activeButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    inactiveButton.setToggleState(false, juce::NotificationType::dontSendNotification);
}

void MainComponent::updateUI()
{
    if (!isInputPathEmpty) 
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