#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Assign the pointer of customLookAndFeel
    customLookAndFeel = std::make_unique<CustomLookAndFeel>();
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(customLookAndFeel->getColorCustomDarkGrey());

    g.setFont(customLookAndFeel->getFontRobotoCondensed().withHeight(20.0F));
    g.setColour(juce::Colours::white);
    g.drawText("DRAG DROP HERE", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

    repaint();
}
