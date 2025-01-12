/*
  ==============================================================================

    SubControls.cpp
    Created: 10 Dec 2024 5:46:26pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "SubControls.h"

SubControls::SubControls
(
    const FilmstripType& type
    , ControlSliderStyle& controlSliderStyle
    , ControlLighting& controlLighting
    , ControlCanvas& controlCanvas
)
    : filmstripType(type)
    , controlSliderStyle(controlSliderStyle)
    , controlLighting(controlLighting)
    , controlCanvas(controlCanvas)
    , customLookAndFeel(Globals::getCustomLookAndFeel())
{
    setupViewportAndContainer();
    setupSubControlsBase(filmstripType);

}

SubControls::~SubControls()
{
}

void SubControls::paint(juce::Graphics& g)
{
    drawBackground(g);
}

void SubControls::resized()
{
    bounds = getLocalBounds();

    auto copyBounds = bounds;

    // example
    copyBounds = copyBounds.withHeight(controlSliderStyleHeight);
    controlSliderStyle.setBounds(copyBounds);

    copyBounds = copyBounds.withHeight(controlLightingHeight);
    controlLighting.setBounds(copyBounds);

    copyBounds = copyBounds.withHeight(controlCanvasHeight);
    controlCanvas.setBounds(copyBounds);

    resizeViewport();
    resizeContainer();
}

void SubControls::drawBackground(juce::Graphics& g)
{
    g.setColour(customLookAndFeel->getCurrentTheme().ButtonsID_01_ON);
    g.fillRoundedRectangle(bounds.toFloat(), 1);

    g.setColour(customLookAndFeel->getCurrentTheme().CustomDarkGrey);
    g.drawRoundedRectangle(bounds.toFloat().reduced(0.3F), 1, 0.3F);
}

void SubControls::setupViewportAndContainer()
{
    addAndMakeVisible(subControlContainer);

    subControlViewport.setComponentID("Viewport_O2_SubControl");
    subControlViewport.setViewedComponent(&subControlContainer, false);
    subControlViewport.setScrollBarsShown(true, false);
    addAndMakeVisible(subControlViewport);
}

void SubControls::setupSubControlsBase(const FilmstripType& type)
{
    int padding = 13;
    int componentH = 28;
    int titleH = 20;

    switch (type)
    {
    case (FilmstripType::KNOB):
        controlLightingHeight = (componentH * 9) + titleH + padding;

        subControlContainer.addAndMakeVisible(controlLighting);
        subControlContainer.addAndMakeVisible(controlCanvas);

        break;
    case (FilmstripType::SLIDER):
        controlLightingHeight = (componentH * 10) + titleH + padding;

        subControlContainer.addAndMakeVisible(controlSliderStyle);
        subControlContainer.addAndMakeVisible(controlLighting);
        subControlContainer.addAndMakeVisible(controlCanvas);
        break;
    default:
        break;
    }

    controlCanvasHeight = (componentH * 4) + titleH + padding;
    controlSliderStyleHeight = int(componentH * 1.125F) + titleH + padding;
}

void SubControls::resizeViewport()
{
    auto viewportBounds = getLocalBounds();
    viewportBounds.removeFromTop(1);
    viewportBounds.removeFromBottom(1);
    subControlViewport.setBounds(viewportBounds);
}

void SubControls::resizeContainer()
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

        y = totalHeight + space;
        auto rect = juce::Rectangle<int>{ space, y, controlWidth, height };
        child->setBounds(rect);
        totalHeight += height + space;
    }
    totalHeight += space;


    subControlContainer.setSize(containerWidth, totalHeight);
    subControlViewport.setScrollBarThickness(thickness);
}

void SubControls::displayDefaultSubControl()
{
    subControlContainer.removeAllChildren();      // reset

    if (filmstripType == FilmstripType::KNOB)
    {
        subControlContainer.addAndMakeVisible(controlLighting);
        subControlContainer.addAndMakeVisible(controlCanvas);
    }
    else
    {
        subControlContainer.addAndMakeVisible(controlSliderStyle);
        subControlContainer.addAndMakeVisible(controlLighting);
        subControlContainer.addAndMakeVisible(controlCanvas);
    }

    resizeContainer();
}

void SubControls::displayToSubControl(std::unique_ptr<ControlAsset>& controlAsset)
{
    subControlContainer.removeAllChildren();      // reset

    subControlContainer.addAndMakeVisible(controlAsset.get());

    //subControlContainer.addAndMakeVisible(controlLighting);
    //subControlContainer.addAndMakeVisible(controlCanvas);

    resizeContainer();
}

void SubControls::removeFromSubControl(std::unique_ptr<ControlAsset>& controlAsset)
{
    subControlContainer.removeChildComponent(controlAsset.get());

    //subControlContainer.removeChildComponent(&controlCanvas);

    displayDefaultSubControl();
    resizeContainer();
}
