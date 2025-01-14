/*
  ==============================================================================

    ColourSelectorWindow.cpp
    Created: 3 Jan 2025 9:40:40pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "CustomColourSelectorWindow.h"

CustomColourSelectorWindow::CustomColourSelectorWindow
(
    const juce::String& name 
    , juce::Colour backgroundColor
    , int buttonsNeeded
    , juce::TextButton& colorButton
    , juce::Label& colorValue
)
    : juce::DocumentWindow(name, backgroundColor, buttonsNeeded)
    , colorButton(colorButton)
    , colorValue(colorValue)
    , customLookAndFeel(Globals::getCustomLookAndFeel())
{
    setTitleBarHeight(30);
    setLookAndFeel(customLookAndFeel.get());

    selector.setMainHEXFont(customLookAndFeel->getFontRobotoCondensedBold().withHeight(17.F));
    selector.setRGBFont(customLookAndFeel->getFontRobotoCondensedBold().withHeight(16.0F));

    selector.setCurrentColour(backgroundColor);
    selector.setColour(CustomColourSelector::backgroundColourId, juce::Colours::transparentWhite);
    selector.addChangeListener(this);
    setContentOwned(&selector, false);
}

CustomColourSelectorWindow::~CustomColourSelectorWindow()
{
    selector.removeChangeListener(this);
}

void CustomColourSelectorWindow::closeButtonPressed()
{
    setVisible(false);
}

void CustomColourSelectorWindow::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &selector)
    {
        this->color = selector.getCurrentColour();
        auto colorText = color.toDisplayString(false).toLowerCase();
        auto textColor = autoTextColor(color);

        setBackgroundColour(color);
        selector.setColour(CustomColourSelector::backgroundColourId, color);

        colorButton.setColour(juce::TextButton::buttonColourId, color);
        
        colorValue.setText(colorText, juce::sendNotification);
        colorValue.setColour(juce::Label::textColourId, textColor);
    }
}

juce::Colour CustomColourSelectorWindow::autoTextColor(juce::Colour& color)
{
    float luminance = (0.2126F * color.getRed()) +
        (0.7152F * color.getGreen()) +
        (0.0722F * color.getBlue());

    auto textColor{ (luminance > 128.0F) ? juce::Colours::black : juce::Colours::white };

    return textColor;
}
