/*
  ==============================================================================

    XYPad.cpp
    Created: 31 Dec 2024 6:10:53pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "XYPad.h"

XYPad::XYPad()
    : customLookAndFeel(Globals::getCustomLookAndFeel())
{
    addAndMakeVisible(thumb);
}

XYPad::~XYPad()
{
}

void XYPad::paint(juce::Graphics& g)
{
    // Draw XYPad Area
    //g.setColour(customLookAndFeel->getCurrentTheme().CustomDarkest.brighter(0.125F));
    g.setColour(customLookAndFeel->getCurrentTheme().SlideworksBaseColour);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 4.0F);

    float thick = 0.8F;
    g.setColour(customLookAndFeel->getCurrentTheme().OutlineControl);
    g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(thick), 4.0F, thick);

    juce::Point<float> start, end;

    // Draw Horizontal Line
    start = { (float)getLocalBounds().getX() , (float)thumb.getBounds().getCentreY() };
    end = { (float)getLocalBounds().getRight(), start.getY() };
    horizontalLine = { start, end };

    g.setColour(juce::Colours::pink.darker());
    g.drawLine(horizontalLine, 0.6F);

    // Draw Vertical Line
    start = { (float)thumb.getBounds().getCentreX(), (float)getLocalBounds().getY(), };
    end = { start.getX(), (float)getLocalBounds().getBottom() };
    verticalLine = { start, end };

    g.setColour(juce::Colours::aqua.darker());
    g.drawLine(verticalLine, 0.6F);
}

void XYPad::resized()
{
    auto area = getLocalBounds();
    juce::Point center = { (int)(relativeX * area.getWidth()), (int)((1 - relativeY) * area.getHeight()) };

    thumb.setCentrePosition(center);
}

void XYPad::mouseDown(const juce::MouseEvent& event)
{
    thumb.setCentrePosition(event.getMouseDownPosition());
    thumb.setTheValue();
    thumb.mouseDown(event);

    repaint();
}

void XYPad::mouseDrag(const juce::MouseEvent& event)
{
    thumb.mouseDrag(event);
}

void XYPad::setXValue(const double x)
{
    xValue.setValue(x);
}

void XYPad::setYValue(const double y)
{
    yValue.setValue(y);
}

double XYPad::getXValue() const
{
    return xValue.getValue();
}

double XYPad::getYValue() const
{
    return yValue.getValue();
}



XYPad::Thumb::Thumb()
    : customLookAndFeel(Globals::getCustomLookAndFeel())
{
    setSize(thumbSize, thumbSize);
    constrainer.setMinimumOnscreenAmounts(thumbSize, thumbSize, thumbSize, thumbSize);
}

XYPad::Thumb::~Thumb()
{
}

void XYPad::Thumb::paint(juce::Graphics& g)
{
    g.setColour(customLookAndFeel->getCurrentTheme().CustomGrey.brighter());
    g.fillEllipse(getLocalBounds().toFloat().reduced(1.2F));
}

void XYPad::Thumb::mouseDown(const juce::MouseEvent& event)
{
    setTheValue();
    dragger.startDraggingComponent(this, event);
}

void XYPad::Thumb::mouseDrag(const juce::MouseEvent& event)
{
    dragger.dragComponent(this, event, &constrainer);
    setTheValue();

    getParentComponent()->repaint();
}

void XYPad::Thumb::setTheValue()
{
    if (auto* parent = dynamic_cast<XYPad*>(getParentComponent()))
    {
        auto area = parent->getLocalBounds();

        double thumbX = getBounds().getCentreX();
        double thumbY = getBounds().getCentreY();

        double minX = area.getX() + (thumbSize * 0.5);
        double maxX = area.getWidth() - (thumbSize * 0.5 * 2);
        double minY = area.getY() + (thumbSize * 0.5);
        double maxY = area.getHeight() - (thumbSize * 0.5 * 2);

        double normalizedX = (thumbX - minX) / maxX;
        double normalizedY = 1 - ((thumbY - minY) / maxY);

        double stepSize = 0.005;
        normalizedX = snapToStep(normalizedX, stepSize);
        normalizedY = snapToStep(normalizedY, stepSize);

        parent->relativeX = normalizedX;
        parent->relativeY = normalizedY;

        double sliderXValue = normalizedX * (2 - (-1)) + (-1);
        double sliderYValue = normalizedY * (2 - (-1)) + (-1);

        parent->setXValue(sliderXValue);
        parent->setYValue(sliderYValue);

    }
}

double XYPad::Thumb::snapToStep(const double value, const double step)
{
    return std::round(value / step) * step;
}
