/*
  ==============================================================================

    New_TotalFrames.cpp
    Created: 10 Dec 2024 4:04:55pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "New_TotalFrames.h"

New_TotalFrames::New_TotalFrames()
    : customLookAndFeel(Globals::getCustomLookAndFeel())
{
    setupGroupComponent();
    setupTotalFramesControl();
}

New_TotalFrames::~New_TotalFrames()
{
}

void New_TotalFrames::paint(juce::Graphics& g)
{
    group.paint(g);
}

void New_TotalFrames::resized()
{
    group.setBounds(getLocalBounds());

    auto bounds = getLocalBounds().reduced(13);
    bounds.removeFromTop(10);
    
    auto area = bounds;
    auto height = 23;
    auto totalWidth = int(area.getWidth() * 0.95F);
    area = area.withSizeKeepingCentre(totalWidth, height);

    auto sliderArea = area.removeFromLeft(int(area.getWidth() * 0.8F));
    auto labelArea = area;

    totalFrames.setBounds(sliderArea.reduced(2));
    totalFrames_Label.setBounds(labelArea.reduced(2));
}


int New_TotalFrames::getTotalFrames() const
{
    return int(totalFrames.getValue());
}

void New_TotalFrames::setupGroupComponent()
{
    auto font = customLookAndFeel->getFontRobotoCondensedRegular().withHeight(16.0F);
    auto fontColor = customLookAndFeel->getCurrentTheme().CustomDarkGrey;
    auto outlineColor = customLookAndFeel->getCurrentTheme().OutlineControl;

    float indentation = 5.0F;
    float gap = 6.0F;
    float cornerSize = 5.0F;
    float lineThick = 1.0F;

    group.setText("Total Frames");
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

void New_TotalFrames::setColourGroup()
{
    group.setFontColour(customLookAndFeel->getCurrentTheme().CustomDarkGrey);
    group.setOutlineColour(customLookAndFeel->getCurrentTheme().OutlineControl);
}

void New_TotalFrames::setupTotalFramesControl()
{
    int minFrames = 1;
    int maxFrames = 150;
    int inverval = 1;

    totalFrames.setComponentID("Slider_ID_01_WithThumb");
    totalFrames.setRange(minFrames, maxFrames, inverval);
    totalFrames.setValue(69);
    totalFrames.setSliderStyle(juce::Slider::LinearHorizontal);
    totalFrames.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    totalFrames.setMouseClickGrabsKeyboardFocus(false);
    totalFrames.setTextBoxIsEditable(false);
    totalFrames.onValueChange = [this]() 
        {
            auto value = int(totalFrames.getValue());
            totalFrames_Label.setText(juce::String(value), juce::dontSendNotification);
        };
    addAndMakeVisible(totalFrames);

    totalFrames_Label.setComponentID("Slider_ID_01_WithThumb");
    totalFrames_Label.setText(juce::String(totalFrames.getValue()), juce::dontSendNotification);
    totalFrames_Label.setFont(customLookAndFeel->getFontRobotoCondensedRegular().withHeight(17.F));
    totalFrames_Label.setJustificationType(juce::Justification::centred);
    totalFrames_Label.setEditable(false, true);
    totalFrames_Label.onTextChange = [this, minFrames, maxFrames]()
        {
            auto newValue = totalFrames_Label.getText().getIntValue();

            auto minValue = minFrames;
            auto maxValue = maxFrames;

            newValue = juce::jlimit(minValue, maxValue, newValue);

            //if (newValue >= minValue && newValue <= maxValue)
            //    newValue = newValue;
            //else if (newValue <= minValue)
            //    newValue = minValue;
            //else if (newValue >= maxValue)
            //    newValue = maxValue;
            //else
            //    newValue = minValue;

            totalFrames.setValue(newValue, juce::sendNotification);
            totalFrames_Label.setText(juce::String(newValue), juce::dontSendNotification);

        };
    addAndMakeVisible(totalFrames_Label);
    setColourTotalFrames();
}

void New_TotalFrames::setColourTotalFrames()
{
    totalFrames.setColour(juce::Slider::trackColourId, customLookAndFeel->getCurrentTheme().SlideworksBaseColour);
    totalFrames.setColour(juce::Slider::thumbColourId, customLookAndFeel->getCurrentTheme().SliderThumbColour);
    //totalFrames.setColour(juce::Slider::textBoxBackgroundColourId, customLookAndFeel->getColorCustomDarkGrey());
    //totalFrames.setColour(juce::Slider::textBoxTextColourId, customLookAndFeel->getColorCustomLightGrey().brighter());

    totalFrames_Label.setColour(juce::Label::backgroundColourId, customLookAndFeel->getCurrentTheme().SlideworksBaseColour);
    totalFrames_Label.setColour(juce::Label::textColourId, customLookAndFeel->getCurrentTheme().CustomDarkGrey);
    totalFrames_Label.setColour(juce::Label::backgroundWhenEditingColourId, customLookAndFeel->getCurrentTheme().SlideworksBaseColour);
    totalFrames_Label.setColour(juce::Label::textWhenEditingColourId, customLookAndFeel->getCurrentTheme().CustomDarkGrey);
    totalFrames_Label.setColour(juce::Label::outlineColourId, customLookAndFeel->getCurrentTheme().CustomDarkest);
    totalFrames_Label.setColour(juce::TextEditor::outlineColourId, customLookAndFeel->getCurrentTheme().CustomDarkest);
    totalFrames_Label.setColour(juce::TextEditor::highlightColourId, customLookAndFeel->getCurrentTheme().TitleBar);
    totalFrames_Label.setColour(juce::TextEditor::highlightedTextColourId, customLookAndFeel->getCurrentTheme().CustomWhite);
    totalFrames_Label.setColour(juce::CaretComponent::caretColourId, customLookAndFeel->getCurrentTheme().CustomDarkGrey);
}

void New_TotalFrames::resetCurrentTheme()
{
    setColourGroup();
    setColourTotalFrames();
}
