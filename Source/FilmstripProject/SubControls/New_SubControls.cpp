/*
  ==============================================================================

    New_SubControls.cpp
    Created: 10 Dec 2024 5:46:26pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "New_SubControls.h"

New_SubControls::New_SubControls()
    : customLookAndFeel(Globals::getCustomLookAndFeel())
{
    addAndMakeVisible(subControlContainer);

    subControlViewport.setComponentID("Viewport_O2_SubControl");
    subControlViewport.setViewedComponent(&subControlContainer, false);
    subControlViewport.setScrollBarsShown(true, false);
    addAndMakeVisible(subControlViewport);

    subControlContainer.addAndMakeVisible(controlLighting);
    subControlContainer.addAndMakeVisible(controlCanvas);
}

New_SubControls::~New_SubControls()
{
}

void New_SubControls::paint(juce::Graphics& g)
{
    drawBackground(g);
}

void New_SubControls::resized()
{
    bounds = getLocalBounds();

    auto copyBounds = bounds;

    // example
    controlLighting.setBounds(copyBounds.removeFromTop(300));
    copyBounds = copyBounds.withHeight(200);
    controlCanvas.setBounds(copyBounds);

    resizeViewport();
    resizeContainer();
}

void New_SubControls::drawBackground(juce::Graphics& g)
{
    g.setColour(customLookAndFeel->getCurrentTheme().ButtonsID_01_ON);
    g.fillRoundedRectangle(bounds.toFloat(), 1);

    g.setColour(customLookAndFeel->getCurrentTheme().CustomDarkGrey);
    g.drawRoundedRectangle(bounds.toFloat().reduced(0.3F), 1, 0.3F);
}

void New_SubControls::resizeViewport()
{
    auto viewportBounds = getLocalBounds();
    viewportBounds.removeFromTop(1);
    viewportBounds.removeFromBottom(1);
    subControlViewport.setBounds(viewportBounds);
}

void New_SubControls::resizeContainer()
{
    int containerWidth = bounds.getWidth();
    int controlWidth{ bounds.getWidth() };
    int totalHeight{};
    int thickness{ 4 };
    int y{};
    int space = 5;

    for (int i = 0; i < subControlContainer.getNumChildComponents(); ++i)
    {
        auto* child = subControlContainer.getChildComponent(i);
        int height = child->getHeight();
        totalHeight += height + space;
    }
    totalHeight += space;

    if (totalHeight < subControlViewport.getHeight())
    {
        thickness = 0;
        controlWidth = bounds.getWidth() - (space * 2);
    }
    else
    {
        thickness = 8;
        controlWidth = bounds.getWidth() - space - 3 - thickness;
    }

    totalHeight = 0;
    for (int i = 0; i < subControlContainer.getNumChildComponents(); ++i)
    {
        auto* child = subControlContainer.getChildComponent(i);
        int height = child->getHeight();
        int y = totalHeight + space;
        auto bounds = juce::Rectangle<int>{ space, y, controlWidth, height };
        child->setBounds(bounds);
        totalHeight += height + space;
    }
    totalHeight += space;


    subControlContainer.setSize(containerWidth, totalHeight);
    subControlViewport.setScrollBarThickness(thickness);
}

void New_SubControls::displayDefaultSubControl()
{
    subControlContainer.removeAllChildren();      // reset

    subControlContainer.addAndMakeVisible(controlLighting);
    subControlContainer.addAndMakeVisible(controlCanvas);

    resizeContainer();
}

void New_SubControls::displayToSubControl(std::unique_ptr<ControlAsset>& controlAsset)
{
    subControlContainer.removeAllChildren();      // reset

    subControlContainer.addAndMakeVisible(controlAsset.get());

    //subControlContainer.addAndMakeVisible(controlLighting);
    //subControlContainer.addAndMakeVisible(controlCanvas);

    resizeContainer();
}

void New_SubControls::removeFromSubControl(std::unique_ptr<ControlAsset>& controlAsset)
{
    subControlContainer.removeChildComponent(controlAsset.get());

    //subControlContainer.removeChildComponent(&controlCanvas);

    displayDefaultSubControl();
    resizeContainer();
}
