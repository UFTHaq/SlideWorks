/*
  ==============================================================================

    CustomSlider.cpp
    Created: 4 Jan 2025 7:52:29pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "CustomSlider.h"

CustomSlider::CustomSlider()
    : customLookAndFeel(Globals::getCustomLookAndFeel())
{
    singleClickDelay = 250;
    setupLabel();
}

CustomSlider::~CustomSlider()
{
}

void CustomSlider::paint(juce::Graphics& g)
{
    // Base
    g.setColour(attribute.baseColor);
    g.fillRoundedRectangle(bounds.toFloat(), attribute.cornerSize);

    // Outline
    g.setColour(attribute.outlineColor);
    g.drawRoundedRectangle(bounds.toFloat().reduced(attribute.outlineThick), attribute.cornerSize, attribute.outlineThick);

    // Bar
    g.setColour(attribute.barColor);
    g.fillRoundedRectangle(bar.toFloat(), attribute.cornerSize - 0.5F);

    // Text
    g.setColour(attribute.textColor);
    g.setFont(attribute.font);
    g.drawText(attribute.valueText, bounds.toFloat(), juce::Justification::centred);
}

void CustomSlider::resized()
{
    bounds = getLocalBounds();
    barBase = bounds.toDouble().reduced(2);
    bar = barBase;

    bar.setX(barBase.getX());
    bar.setRight(barRight);

    DBG("CUSTOM_SLIDER SET VALUE BAR WIDTH : " << barBase.getRight());

    attribute.valueLabel.setBounds(barBase.toNearestInt());
}

void CustomSlider::mouseDown(const juce::MouseEvent& event)
{
    if (event.getNumberOfClicks() == 2)
    {
        stopTimer();
        handleDoubleClick(event);
    } 
    else if (event.getNumberOfClicks() == 1)
    {
        myMouseEvent = std::make_unique<juce::MouseEvent>(event);
        startTimer(singleClickDelay);
    }             
}

void CustomSlider::mouseDrag(const juce::MouseEvent& event)
{
    bar.setX(barBase.getX());

    barRight = (double)event.getPosition().getX();

    if (barRight > barBase.getRight()) barRight = barBase.getRight();
    if (barRight < barBase.getX()) barRight = barBase.getX();

    bar.setRight(barRight);

    calculateTheValue();
    repaint();

    if (onValueChange)
        onValueChange();
}

void CustomSlider::mouseUp(const juce::MouseEvent& event)
{
    repaint();
}

void CustomSlider::mouseWheelMove(const juce::MouseEvent& event, const juce::MouseWheelDetails& wheel)
{
    double delta = 25;

    if (wheel.deltaY > 0)
    {
        // Scroll UP
        attribute.value += delta;
        attribute.value = juce::jmin(attribute.value, attribute.range.max);
    }
    else if (wheel.deltaY < 0)
    {
        // Scroll DOWN
        attribute.value -= delta;
        attribute.value = juce::jmax(attribute.value, attribute.range.min);
    }

    setBarWidth();
    repaint();

    if (onValueChange)
        onValueChange();
}

void CustomSlider::timerCallback()
{
    stopTimer();
    if (myMouseEvent)
    {
        handleSingleClick(*myMouseEvent);
        myMouseEvent.reset();
    }
}

void CustomSlider::initializeBounds()
{
    if (positionInit == false)
    {
        positionInit = true;

        bounds = getLocalBounds();
        barBase = bounds.toDouble().reduced(2);
        bar = barBase;

        bar.setX(barBase.getX());

        setBarWidth();
    }
}

void CustomSlider::setBarWidth()
{
    auto val = attribute.value;
    auto min = attribute.range.min;
    auto max = attribute.range.max;

    auto barW = (barBase.getWidth()) * ((val - min) / (max - min));

    barRight = barW + barBase.getX();
    bar.setRight(barRight);

    attribute.valueText = juce::String(juce::roundToInt(attribute.value)) + attribute.postfix;
    attribute.valueLabel.setText(juce::String(juce::roundToInt(attribute.value)), juce::dontSendNotification);
}

void CustomSlider::calculateTheValue()
{
    auto newValue = static_cast<int>((bar.getWidth() / barBase.getWidth()) * (attribute.range.max - attribute.range.min) + attribute.range.min);

    attribute.value = newValue;
    attribute.valueText = juce::String(newValue) + attribute.postfix;
    attribute.valueLabel.setText(attribute.valueText, juce::dontSendNotification);
    
}

void CustomSlider::setFont(const juce::Font& font)
{
    this->attribute.font = font;
}

void CustomSlider::setColourBase(const juce::Colour& color)
{
    this->attribute.baseColor = color;
}

void CustomSlider::setColourOutline(const juce::Colour& color)
{
    this->attribute.outlineColor = color;
}

void CustomSlider::setColourBar(const juce::Colour& color)
{
    this->attribute.barColor = color;
}

void CustomSlider::setColourText(const juce::Colour& color)
{
    this->attribute.textColor = color;
}

void CustomSlider::setCornerSize(const float& size)
{
    this->attribute.cornerSize = size;
}

void CustomSlider::setOutlineThick(const float& thickness)
{
    this->attribute.outlineThick = thickness;
}

void CustomSlider::setPostfix(const juce::String& unit)
{
    this->attribute.postfix = " " + unit;
}

void CustomSlider::setRange(double min, double max, double interval)
{
    this->attribute.range.min = min;
    this->attribute.range.max = max;
    this->attribute.range.interval = interval;
}

void CustomSlider::setValue(double value)
{
    this->attribute.value = value;
}

double CustomSlider::getValue() const
{
    return attribute.value;
}

void CustomSlider::setupLabel()
{
    attribute.valueLabel.setFont(customLookAndFeel->getFontRobotoCondensedRegular().withHeight(16.0F));
    attribute.valueLabel.setColour(juce::Label::backgroundWhenEditingColourId, customLookAndFeel->getCurrentTheme().SlideworksBaseColour.brighter());
    attribute.valueLabel.setColour(juce::Label::textWhenEditingColourId, customLookAndFeel->getCurrentTheme().FontBlack);
    attribute.valueLabel.setColour(juce::TextEditor::highlightColourId, customLookAndFeel->getCurrentTheme().TitleBar);

    attribute.valueLabel.setEditable(true, true, true);

    // FOR PRESS ENTER
    attribute.valueLabel.onTextChange = [this]()
        {
            auto newText = attribute.valueLabel.getText();
            auto newVal = juce::roundToInt(newText.getDoubleValue());

            auto min = juce::roundToInt(attribute.range.min);
            auto max = juce::roundToInt(attribute.range.max);

            newVal = juce::jlimit(min, max, newVal);
            newText = juce::String(newVal);

            attribute.value = newVal;
            attribute.valueLabel.setText(newText, juce::dontSendNotification);
            attribute.valueText = newText + attribute.postfix;

            attribute.valueLabel.setEnabled(false);
            attribute.valueLabel.setVisible(false);

            setBarWidth();

            if (onValueChange)
                onValueChange();
        };

    // FOR LOST FOCUS
    attribute.valueLabel.onEditorHide = [this]()
        {
            attribute.valueLabel.setEnabled(false);
            attribute.valueLabel.setVisible(false);
        };

    addAndMakeVisible(attribute.valueLabel);

    attribute.valueLabel.setEnabled(false);
    attribute.valueLabel.setVisible(false);
}

void CustomSlider::handleSingleClick(const juce::MouseEvent& event)
{
    barRight = (double)event.getMouseDownPosition().getX();
    bar.setRight(barRight);
    calculateTheValue();
    repaint();

    if (onValueChange)
        onValueChange();
}

void CustomSlider::handleDoubleClick(const juce::MouseEvent& event)
{
    attribute.valueLabel.setEnabled(true);
    attribute.valueLabel.setVisible(true);
    attribute.valueLabel.showEditor();
    repaint();
}
