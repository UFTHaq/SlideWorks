/*
  ==============================================================================

    ThumbPositions.cpp
    Created: 10 Dec 2024 4:14:47pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "ThumbPositions.h"

ThumbPositions::ThumbPositions()
    : customLookAndFeel(Globals::getCustomLookAndFeel())
{
    setupGroupComponent();
    setupThumbControls();
}

ThumbPositions::~ThumbPositions()
{
}

void ThumbPositions::paint(juce::Graphics& g)
{
    group.paint(g);
}

void ThumbPositions::resized()
{
    group.setBounds(getLocalBounds());

    auto bounds = getLocalBounds().reduced(13);

    auto area = bounds;
    auto totalWidth = int(area.getWidth() * 0.95F);
    area = area.withSizeKeepingCentre(totalWidth, area.getHeight());
    area.removeFromTop(10);

    auto minArea = area.removeFromTop(area.getHeight() / 2);
    auto maxArea = area;

    auto height = 23;
    minArea = minArea.withSizeKeepingCentre(minArea.getWidth(), height);
    maxArea = maxArea.withSizeKeepingCentre(maxArea.getWidth(), height);

    auto textAreaW = 30;
    auto space = 2;
    auto ratio = 0.735;

    auto minTextArea = minArea.removeFromLeft(textAreaW);
    minArea.removeFromLeft(space);
    auto minSliderArea = minArea.removeFromLeft(int(minArea.getWidth() * ratio));
    auto minValueArea = minArea;

    auto maxTextArea = maxArea.removeFromLeft(textAreaW);
    maxArea.removeFromLeft(space);
    auto maxSliderArea = maxArea.removeFromLeft(int(maxArea.getWidth() * ratio));
    auto maxValueArea = maxArea;

    minText_Label.setBounds(minTextArea.reduced(2));
    minThumbPos.setBounds(minSliderArea.reduced(2));
    minValue_Label.setBounds(minValueArea.reduced(2));

    maxText_Label.setBounds(maxTextArea.reduced(2));
    maxThumbPos.setBounds(maxSliderArea.reduced(2));
    maxValue_Label.setBounds(maxValueArea.reduced(2));
}

void ThumbPositions::setupGroupComponent()
{
    auto font = customLookAndFeel->getFontRobotoCondensedRegular().withHeight(16.0F);
    auto fontColor = customLookAndFeel->getCurrentTheme().CustomDarkGrey;
    auto outlineColor = customLookAndFeel->getCurrentTheme().OutlineControl;

    float indentation = 5.0F;
    float gap = 6.0F;
    float cornerSize = 5.0F;
    float lineThick = 1.0F;

    group.setText("Thumb Positions");
    group.setTextLabelPosition(juce::Justification::centred);
    group.setFont(font);
    group.setFontColour(fontColor);
    group.setOutlineColour(outlineColor);
    group.setIndentation(indentation);
    group.setTextLineGap(gap);
    group.setCornerSize(cornerSize);
    group.setLineThickness(lineThick);
    addAndMakeVisible(group);

    setColourGroup();
}

void ThumbPositions::setColourGroup()
{
    group.setFontColour(customLookAndFeel->getCurrentTheme().CustomDarkGrey);
    group.setOutlineColour(customLookAndFeel->getCurrentTheme().OutlineControl);
}

void ThumbPositions::setupThumbControls()
{
    double interval = 0.01;
    double defaultValue = 0.15;
    double minPosBetween = 0.2;


    auto font = customLookAndFeel->getFontRobotoCondensedRegular().withHeight(16.0F);
    
    {
        // MIN
        minText_Label.setText("Min", juce::dontSendNotification);
        minText_Label.setComponentID("Label_ID_03_MIN_MAX_TEXT");
        minText_Label.setFont(font);
        minText_Label.setJustificationType(juce::Justification::centredLeft);
        minText_Label.setEditable(false, false);
        addAndMakeVisible(minText_Label);

        minThumbPos.setComponentID("Slider_ID_01_WithThumb");
        minThumbPos.setRange(0, 1, interval);
        minThumbPos.setValue(defaultValue);
        minThumbPos.setSliderStyle(juce::Slider::LinearHorizontal);
        minThumbPos.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
        minThumbPos.setMouseClickGrabsKeyboardFocus(false);
        minThumbPos.setTextBoxIsEditable(false);
        minThumbPos.onValueChange = [this, minPosBetween]() 
            {
                if (maxThumbPos.getValue() - minThumbPos.getValue() <= minPosBetween)
                    minThumbPos.setValue(maxThumbPos.getValue() - minPosBetween);

                double value = minThumbPos.getValue();
                minValue_Label.setText(juce::String(value), juce::dontSendNotification);
            };
        addAndMakeVisible(minThumbPos);

        minValue_Label.setComponentID("Slider_ID_01_WithThumb");
        minValue_Label.setText(juce::String(minThumbPos.getValue()), juce::dontSendNotification);
        minValue_Label.setFont(customLookAndFeel->getFontRobotoCondensedRegular().withHeight(17.F));
        minValue_Label.setJustificationType(juce::Justification::centred);
        minValue_Label.setEditable(false, true);
        minValue_Label.onTextChange = [this, minPosBetween]()
            {
                double newValue = minValue_Label.getText().getDoubleValue();

                double minValue = 0;
                double maxValue = 1;

                if (newValue >= minValue && newValue <= maxValue)
                    newValue = newValue;
                else if (newValue <= minValue)
                    newValue = minValue;
                else if (newValue >= maxValue)
                    newValue = maxValue;
                else
                    newValue = minValue;

                if (maxThumbPos.getValue() - newValue <= minPosBetween)
                    newValue = (maxThumbPos.getValue() - minPosBetween);

                newValue = rounded_2Digit(newValue);
                minThumbPos.setValue(newValue, juce::dontSendNotification);
                minValue_Label.setText(juce::String(newValue), juce::dontSendNotification);
            };
        addAndMakeVisible(minValue_Label);
        
        setColourMinPos();
    }

    {
        // MAX
        maxText_Label.setText("Max", juce::dontSendNotification);
        maxText_Label.setComponentID("Label_ID_03_MIN_MAX_TEXT");
        maxText_Label.setFont(font);
        maxText_Label.setJustificationType(juce::Justification::centredLeft);
        maxText_Label.setEditable(false, false);
        addAndMakeVisible(maxText_Label);

        maxThumbPos.setComponentID("Slider_ID_01_WithThumb");
        maxThumbPos.setRange(0, 1, interval);
        maxThumbPos.setValue(1 - defaultValue);
        maxThumbPos.setSliderStyle(juce::Slider::LinearHorizontal);
        maxThumbPos.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
        maxThumbPos.setMouseClickGrabsKeyboardFocus(false);
        maxThumbPos.setTextBoxIsEditable(false);
        maxThumbPos.onValueChange = [this, minPosBetween]() 
            {
                if (maxThumbPos.getValue() - minThumbPos.getValue() <= minPosBetween)
                    maxThumbPos.setValue(minThumbPos.getValue() + minPosBetween);

                double value = maxThumbPos.getValue();
                maxValue_Label.setText(juce::String(value), juce::dontSendNotification);
            };
        addAndMakeVisible(maxThumbPos);

        maxValue_Label.setComponentID("Slider_ID_01_WithThumb");
        maxValue_Label.setText(juce::String(maxThumbPos.getValue()), juce::dontSendNotification);
        maxValue_Label.setFont(customLookAndFeel->getFontRobotoCondensedRegular().withHeight(17.F));
        maxValue_Label.setJustificationType(juce::Justification::centred);
        maxValue_Label.setEditable(false, true);
        maxValue_Label.onTextChange = [this, minPosBetween]()
            {
                double newValue = maxValue_Label.getText().getDoubleValue();

                double minValue = 0;
                double maxValue = 1;

                if (newValue >= minValue && newValue <= maxValue)
                    newValue = newValue;
                else if (newValue <= minValue)
                    newValue = minValue;
                else if (newValue >= maxValue)
                    newValue = maxValue;
                else
                    newValue = minValue;

                if (newValue - minThumbPos.getValue() <= minPosBetween)
                    newValue = (minThumbPos.getValue() + minPosBetween);

                newValue = rounded_2Digit(newValue);
                maxThumbPos.setValue(newValue, juce::dontSendNotification);
                maxValue_Label.setText(juce::String(newValue), juce::dontSendNotification);
            };
        addAndMakeVisible(maxValue_Label);
        
        setColourMaxPos();
    }
}

void ThumbPositions::setColourMinPos()
{
    minText_Label.setColour(juce::Label::textColourId, customLookAndFeel->getCurrentTheme().FontBlack);

    minThumbPos.setColour(juce::Slider::trackColourId, customLookAndFeel->getCurrentTheme().SlideworksBaseColour);
    minThumbPos.setColour(juce::Slider::thumbColourId, customLookAndFeel->getCurrentTheme().SliderThumbColour);
    minThumbPos.setColour(juce::Slider::textBoxBackgroundColourId, customLookAndFeel->getColorCustomDarkGrey());
    minThumbPos.setColour(juce::Slider::textBoxTextColourId, customLookAndFeel->getColorCustomLightGrey().brighter());

    minValue_Label.setColour(juce::Label::backgroundColourId, customLookAndFeel->getCurrentTheme().SlideworksBaseColour);
    minValue_Label.setColour(juce::Label::textColourId, customLookAndFeel->getCurrentTheme().CustomDarkGrey);
    minValue_Label.setColour(juce::Label::backgroundWhenEditingColourId, customLookAndFeel->getCurrentTheme().SlideworksBaseColour);
    minValue_Label.setColour(juce::Label::textWhenEditingColourId, customLookAndFeel->getCurrentTheme().CustomDarkGrey);
    minValue_Label.setColour(juce::Label::outlineColourId, customLookAndFeel->getCurrentTheme().CustomDarkest);
    minValue_Label.setColour(juce::TextEditor::outlineColourId, customLookAndFeel->getCurrentTheme().CustomDarkest);
    minValue_Label.setColour(juce::TextEditor::highlightColourId, customLookAndFeel->getCurrentTheme().TitleBar);
    minValue_Label.setColour(juce::TextEditor::highlightedTextColourId, customLookAndFeel->getCurrentTheme().CustomWhite);
    minValue_Label.setColour(juce::CaretComponent::caretColourId, customLookAndFeel->getCurrentTheme().CustomDarkGrey);
}

void ThumbPositions::setColourMaxPos()
{
    maxText_Label.setColour(juce::Label::textColourId, customLookAndFeel->getCurrentTheme().FontBlack);

    maxThumbPos.setColour(juce::Slider::trackColourId, customLookAndFeel->getCurrentTheme().SlideworksBaseColour);
    maxThumbPos.setColour(juce::Slider::thumbColourId, customLookAndFeel->getCurrentTheme().SliderThumbColour);
    maxThumbPos.setColour(juce::Slider::textBoxBackgroundColourId, customLookAndFeel->getColorCustomDarkGrey());
    maxThumbPos.setColour(juce::Slider::textBoxTextColourId, customLookAndFeel->getColorCustomLightGrey().brighter());

    maxValue_Label.setColour(juce::Label::backgroundColourId, customLookAndFeel->getCurrentTheme().SlideworksBaseColour);
    maxValue_Label.setColour(juce::Label::textColourId, customLookAndFeel->getCurrentTheme().CustomDarkGrey);
    maxValue_Label.setColour(juce::Label::backgroundWhenEditingColourId, customLookAndFeel->getCurrentTheme().SlideworksBaseColour);
    maxValue_Label.setColour(juce::Label::textWhenEditingColourId, customLookAndFeel->getCurrentTheme().CustomDarkGrey);
    maxValue_Label.setColour(juce::Label::outlineColourId, customLookAndFeel->getCurrentTheme().CustomDarkest);
    maxValue_Label.setColour(juce::TextEditor::outlineColourId, customLookAndFeel->getCurrentTheme().CustomDarkest);
    maxValue_Label.setColour(juce::TextEditor::highlightColourId, customLookAndFeel->getCurrentTheme().TitleBar);
    maxValue_Label.setColour(juce::TextEditor::highlightedTextColourId, customLookAndFeel->getCurrentTheme().CustomWhite);
    maxValue_Label.setColour(juce::CaretComponent::caretColourId, customLookAndFeel->getCurrentTheme().CustomDarkGrey);
}

double ThumbPositions::getMinThumbPos() const
{
    return minThumbPos.getValue();
}

double ThumbPositions::getMaxThumbPos() const
{
    return maxThumbPos.getValue();
}

double ThumbPositions::rounded_2Digit(double value)
{
    double factor = std::pow(10, 2);
    return std::round(value * factor) / factor;
}

void ThumbPositions::resetCurrentTheme()
{
    setColourGroup();
    setColourMinPos();
    setColourMaxPos();
}
