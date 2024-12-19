/*
  ==============================================================================

    New_KnobAngles.cpp
    Created: 10 Dec 2024 4:14:06pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "New_KnobAngles.h"

New_KnobAngles::New_KnobAngles()
    : customLookAndFeel(Globals::getCustomLookAndFeel())
{
    setupGroupComponent();
    setupAngleControls();
}

New_KnobAngles::~New_KnobAngles()
{
}

void New_KnobAngles::paint(juce::Graphics& g)
{
    group.paint(g);
}

void New_KnobAngles::resized()
{
    group.setBounds(getLocalBounds());

    auto bounds = getLocalBounds();
    bounds.removeFromTop(5);
    bounds = bounds.reduced(5);

    auto area = bounds;

    auto minArea = area.removeFromLeft(area.getWidth() / 2);
    auto maxArea = area;

    auto textAreaH = 20;
    auto space = 0;

    auto minTextArea = minArea.removeFromTop(textAreaH);
    minArea.removeFromTop(space);
    auto minKnobArea = minArea;
    auto minValueArea = minKnobArea.withSizeKeepingCentre(30, 20);

    auto maxTextArea = maxArea.removeFromTop(textAreaH);
    maxArea.removeFromTop(space);
    auto maxKnobArea = maxArea;
    auto maxValueArea = maxKnobArea.withSizeKeepingCentre(30, 20);

    minText_Label.setBounds(minTextArea);
    minAngle.setBounds(minKnobArea);
    minValue_Label.setBounds(minValueArea);

    maxText_Label.setBounds(maxTextArea);
    maxAngle.setBounds(maxKnobArea);
    maxValue_Label.setBounds(maxValueArea);
}

void New_KnobAngles::mouseDown(const juce::MouseEvent& event)
{
}

void New_KnobAngles::mouseDoubleClick(const juce::MouseEvent& event)
{
    if (event.eventComponent == &minAngle)
    {
        minValue_Label.setInterceptsMouseClicks(true, true);
        minValue_Label.setReadOnly(false);
        minValue_Label.grabKeyboardFocus();
        minValue_Label.setEnabled(true);
    }

    if (event.eventComponent == &maxAngle)
    {
        maxValue_Label.setInterceptsMouseClicks(true, true);
        maxValue_Label.setReadOnly(false);
        maxValue_Label.grabKeyboardFocus();
    }
}

void New_KnobAngles::setupGroupComponent()
{
    auto font = customLookAndFeel->getFontRobotoCondensedRegular().withHeight(16.0F);
    auto fontColor = customLookAndFeel->getCurrentTheme().CustomDarkGrey;
    auto outlineColor = customLookAndFeel->getCurrentTheme().OutlineControl;

    float indentation = 5.0F;
    float gap = 6.0F;
    float cornerSize = 5.0F;
    float lineThick = 1.0F;

    group.setText("Angles");
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

void New_KnobAngles::setColourGroup()
{
    group.setFontColour(customLookAndFeel->getCurrentTheme().CustomDarkGrey);
    group.setOutlineColour(customLookAndFeel->getCurrentTheme().OutlineControl);
}

void New_KnobAngles::setupAngleControls()
{
    double interval = 1;
    double threshold = 175;
    double defaultVal = 135;
    double minAngleBetween = 45;

    auto font = customLookAndFeel->getFontRobotoCondensedRegular().withHeight(16.0F);

    {
        minText_Label.setFont(font);
        minText_Label.setText("Min", juce::dontSendNotification);
        minText_Label.setComponentID("Label_ID_03_MIN_MAX_TEXT");
        minText_Label.setJustificationType(juce::Justification::centredBottom);
        minText_Label.setEditable(false, false);
        addAndMakeVisible(minText_Label);

        minAngle.setComponentID("Slider_ID_02_MIN_MAX_Rotary");
        minAngle.setRange(-threshold, threshold, interval);
        minAngle.setValue(-defaultVal);
        minAngle.setSliderStyle(juce::Slider::RotaryVerticalDrag);
        minAngle.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
        //minAngle.setRotaryParameters(juce::degreesToRadians((float)-threshold), juce::degreesToRadians((float)threshold), true);
        minAngle.setRotaryParameters(juce::degreesToRadians(0.0F), juce::degreesToRadians(350.0F), true);
        minAngle.setTextBoxIsEditable(false);
        minAngle.onValueChange = [this, minAngleBetween]()
            {
                if (maxAngle.getValue() - minAngle.getValue() <= minAngleBetween)
                    minAngle.setValue(maxAngle.getValue() - minAngleBetween);

                double value = minAngle.getValue();
                minValue_Label.setText(juce::String(value), juce::dontSendNotification);
            };
        minAngle.addMouseListener(this, true);
        addAndMakeVisible(minAngle);

        minValue_Label.setFont(font);
        minValue_Label.setText("-135", juce::dontSendNotification);
        minValue_Label.setComponentID("Label_ID_03_MIN_MAX_VALUE");
        minValue_Label.setReadOnly(true);
        minValue_Label.setInterceptsMouseClicks(false, false);
        minValue_Label.onReturnKey = [this]()
            {
                minValue_Label.giveAwayKeyboardFocus();
                minValue_Label.setReadOnly(true);
                minValue_Label.setInterceptsMouseClicks(false, false);

                minValue_Label.setText(juce::String(minAngle.getValue()), juce::dontSendNotification);
            };
        minValue_Label.onTextChange = [this, threshold, minAngleBetween]()
            {
                double newValue = minValue_Label.getText().getDoubleValue();

                double minValue = -threshold;
                double maxValue = threshold;

                if (newValue >= minValue && newValue <= maxValue)
                    newValue = newValue;
                else if (newValue <= minValue)
                    newValue = minValue;
                else if (newValue >= maxValue)
                    newValue = maxValue;
                else
                    newValue = minValue;

                if (maxAngle.getValue() - newValue <= minAngleBetween)
                    newValue = (maxAngle.getValue() - minAngleBetween);

                minAngle.setValue(newValue, juce::dontSendNotification);
            };
        addAndMakeVisible(minValue_Label);

        setColourMinAngle();
    }

    {
        maxText_Label.setFont(font);
        maxText_Label.setText("Max", juce::dontSendNotification);
        maxText_Label.setComponentID("Label_ID_03_MIN_MAX_TEXT");
        maxText_Label.setJustificationType(juce::Justification::centredBottom);
        maxText_Label.setEditable(false, false);
        addAndMakeVisible(maxText_Label);

        maxAngle.setComponentID("Slider_ID_02_MIN_MAX_Rotary");
        maxAngle.setRange(-threshold, threshold, interval);
        maxAngle.setValue(defaultVal);
        maxAngle.setSliderStyle(juce::Slider::RotaryVerticalDrag);
        maxAngle.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
        //maxAngle.setRotaryParameters(juce::degreesToRadians((float)-threshold), juce::degreesToRadians((float)threshold), true);
        maxAngle.setRotaryParameters(juce::degreesToRadians(0.0F), juce::degreesToRadians(350.0F), true);
        maxAngle.setTextBoxIsEditable(false);
        maxAngle.onValueChange = [this, minAngleBetween]() 
            {
                if (maxAngle.getValue() - minAngle.getValue() <= minAngleBetween)
                    maxAngle.setValue(minAngle.getValue() + minAngleBetween);

                double value = maxAngle.getValue();
                maxValue_Label.setText(juce::String(value), juce::dontSendNotification);
            };
        maxAngle.addMouseListener(this, true);
        addAndMakeVisible(maxAngle);

        maxValue_Label.setFont(font);
        maxValue_Label.setText("135", juce::dontSendNotification);
        maxValue_Label.setComponentID("Label_ID_03_MIN_MAX_VALUE");
        maxValue_Label.setReadOnly(true);
        maxValue_Label.setInterceptsMouseClicks(false, false);
        maxValue_Label.onReturnKey = [this]()
            {
                maxValue_Label.giveAwayKeyboardFocus();
                maxValue_Label.setReadOnly(true);
                maxValue_Label.setInterceptsMouseClicks(false, false);

                maxValue_Label.setText(juce::String(maxAngle.getValue()), juce::dontSendNotification);
            };
        maxValue_Label.onTextChange = [this, threshold, minAngleBetween]()
            {
                double newValue = maxValue_Label.getText().getDoubleValue();

                double minValue = -threshold;
                double maxValue = threshold;

                if (newValue >= minValue && newValue <= maxValue)
                    newValue = newValue;
                else if (newValue <= minValue)
                    newValue = minValue;
                else if (newValue >= maxValue)
                    newValue = maxValue;
                else
                    newValue = minValue;

                if (newValue - minAngle.getValue() <= minAngleBetween)
                    newValue = (minAngle.getValue() + minAngleBetween);

                maxAngle.setValue(newValue, juce::dontSendNotification);
            };
        addAndMakeVisible(maxValue_Label);

        setColourMaxAngle();
    }
}

void New_KnobAngles::setColourMinAngle()
{
    minText_Label.setColour(juce::Label::textColourId, customLookAndFeel->getCurrentTheme().FontBlack);

    minAngle.setColour(juce::Slider::trackColourId, customLookAndFeel->getColorCustomLightGrey());
    minAngle.setColour(juce::Slider::backgroundColourId, customLookAndFeel->getCurrentTheme().CustomGrey);
    minAngle.setColour(juce::Slider::thumbColourId, customLookAndFeel->getCurrentTheme().CustomWhite);
    minAngle.setColour(juce::Slider::textBoxTextColourId, customLookAndFeel->getColorCustomDarkGrey().darker());
    minAngle.setColour(juce::TextEditor::backgroundColourId, customLookAndFeel->getColorCustomGrey());

    minValue_Label.setColour(juce::Label::backgroundColourId, customLookAndFeel->getCurrentTheme().CustomGrey);
    minValue_Label.setColour(juce::Label::textColourId, customLookAndFeel->getCurrentTheme().FontWhite);
    minValue_Label.setColour(juce::Label::backgroundWhenEditingColourId, customLookAndFeel->getCurrentTheme().CustomGrey);
    minValue_Label.setColour(juce::Label::outlineWhenEditingColourId, customLookAndFeel->getCurrentTheme().TransparentBlack);
    minValue_Label.setColour(juce::TextEditor::highlightColourId, customLookAndFeel->getCurrentTheme().CustomDarkest);
    minValue_Label.setColour(juce::TextEditor::highlightedTextColourId, customLookAndFeel->getCurrentTheme().CustomWhite);
    minValue_Label.setColour(juce::TextEditor::outlineColourId, customLookAndFeel->getCurrentTheme().TransparentBlack);
    minValue_Label.setColour(juce::CaretComponent::caretColourId, customLookAndFeel->getCurrentTheme().CustomDarkest);
}

void New_KnobAngles::setColourMaxAngle()
{
    maxText_Label.setColour(juce::Label::textColourId, customLookAndFeel->getCurrentTheme().FontBlack);

    maxAngle.setColour(juce::Slider::trackColourId, customLookAndFeel->getColorCustomLightGrey());
    maxAngle.setColour(juce::Slider::backgroundColourId, customLookAndFeel->getCurrentTheme().CustomGrey);
    maxAngle.setColour(juce::Slider::thumbColourId, customLookAndFeel->getCurrentTheme().CustomWhite);
    maxAngle.setColour(juce::Slider::textBoxTextColourId, customLookAndFeel->getColorCustomDarkGrey().darker());
    maxAngle.setColour(juce::TextEditor::backgroundColourId, customLookAndFeel->getColorCustomGrey());

    maxValue_Label.setColour(juce::Label::backgroundColourId, customLookAndFeel->getCurrentTheme().CustomGrey);
    maxValue_Label.setColour(juce::Label::textColourId, customLookAndFeel->getCurrentTheme().FontWhite);
    maxValue_Label.setColour(juce::Label::backgroundWhenEditingColourId, customLookAndFeel->getCurrentTheme().CustomGrey);
    maxValue_Label.setColour(juce::Label::outlineWhenEditingColourId, customLookAndFeel->getCurrentTheme().TransparentBlack);
    maxValue_Label.setColour(juce::TextEditor::highlightColourId, customLookAndFeel->getCurrentTheme().CustomDarkest);
    maxValue_Label.setColour(juce::TextEditor::highlightedTextColourId, customLookAndFeel->getCurrentTheme().CustomWhite);
    maxValue_Label.setColour(juce::TextEditor::outlineColourId, customLookAndFeel->getCurrentTheme().TransparentBlack);
    maxValue_Label.setColour(juce::CaretComponent::caretColourId, customLookAndFeel->getCurrentTheme().CustomDarkest);
}

double New_KnobAngles::getMinAngle() const
{
    return minAngle.getValue();
}

double New_KnobAngles::getMaxAngle() const
{
    return maxAngle.getValue();
}

void New_KnobAngles::resetCurrentTheme()
{
    setColourGroup();
    setColourMinAngle();
    setColourMaxAngle();
}
