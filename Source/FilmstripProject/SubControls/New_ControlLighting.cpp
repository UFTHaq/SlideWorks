/*
  ==============================================================================

    New_ControlLighting.cpp
    Created: 10 Dec 2024 5:50:02pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "New_ControlLighting.h"

ControlLighting::ControlLighting(const FilmstripType& filmstripType)
    : filmstripType(filmstripType)
    , customLookAndFeel(Globals::getCustomLookAndFeel())
{
    setupGroupComponent();
    setupDivider();

    setupXYPad();
    setupZPad();
    setupXYZLabel();

    setupLockLighting();
    setupColorChooser();
    setupIntensitySlider();
    setupBumpSlider();
    setupInvertButton();
}

ControlLighting::~ControlLighting()
{
}

void ControlLighting::paint(juce::Graphics& g)
{
    group.paint(g);
}

void ControlLighting::resized()
{
    group.setBounds(getLocalBounds());

    auto bounds = getLocalBounds();
    bounds.removeFromTop(13);

    auto w = bounds.getWidth() - 20;
    auto h = bounds.getHeight() - 20;
    bounds = bounds.withSizeKeepingCentre(w, h);

    auto lightControlArea = bounds;
    auto areaH = lightControlArea.getHeight() / totalDivider;

    {
        // XYPAD
        auto xyPadArea = lightControlArea.removeFromTop(areaH * 4);
        xyPadArea = xyPadArea.removeFromLeft(xyPadArea.getWidth() - 20);
        xyPad.setBounds(xyPadArea);

        auto zPadArea = juce::Rectangle<int>{ xyPadArea.getRight() + 5, xyPadArea.getY(), 15, xyPadArea.getHeight() };
        zPad.setBounds(zPadArea);

        auto labelArea = lightControlArea.removeFromTop(areaH * 1);
        labelArea.removeFromTop(5);
        auto xyLabelArea = labelArea.removeFromLeft(xyPad.getWidth());
        auto zLabelArea = labelArea.removeFromRight(15);

        xyLabel.setBounds(xyLabelArea);
        zLabel.setBounds(zLabelArea);
    }

    auto leftSide = int(lightControlArea.getWidth() * 0.425F);
    auto remove = 3;

    {
        // LOCK LIGHT RELATIVE TO THUMB
        if (filmstripType == FilmstripType::SLIDER)
        {
            auto area = lightControlArea.removeFromTop(int(areaH) * 1);
            area.removeFromTop(remove);
            area.removeFromBottom(remove);

            auto labelArea = area.removeFromLeft(area.getWidth() - area.getHeight());
            labelArea.removeFromLeft(5);

            auto mainArea = area;

            lockLabel.setBounds(labelArea);
            lockButton.setBounds(mainArea);
        }
    }

    {
        // COLOR CHOOSER
        auto area = lightControlArea.removeFromTop(int(areaH) * 1);
        area.removeFromTop(remove);
        area.removeFromBottom(remove);

        auto labelArea = area.removeFromLeft(leftSide);
        labelArea.removeFromLeft(5);

        auto mainArea = area.removeFromLeft(area.getWidth() - area.getHeight());
        mainArea.removeFromRight(4);
        auto labelValueArea = mainArea;
        auto copyButtonArea = area;

        colorLabel.setBounds(labelArea);
        colorButton.setBounds(mainArea);
        colorValue.setBounds(labelValueArea);
        copyValueButton.setBounds(copyButtonArea);
    }

    {
        // SLIDER INTENSITY
        auto area = lightControlArea.removeFromTop(int(areaH) * 1);
        area.removeFromTop(remove);
        area.removeFromBottom(remove);

        auto labelArea = area.removeFromLeft(leftSide);
        labelArea.removeFromLeft(5);

        auto mainArea = area;

        intensityLabel.setBounds(labelArea);
        intensity.setBounds(mainArea);
    }

    {
        // SLIDER BUMP
        auto area = lightControlArea.removeFromTop(int(areaH) * 1);
        area.removeFromTop(remove);
        area.removeFromBottom(remove);

        auto labelArea = area.removeFromLeft(leftSide);
        labelArea.removeFromLeft(5);

        auto mainArea = area;

        bumpLabel.setBounds(labelArea);
        bump.setBounds(mainArea);
    }

    {
        // INVERT BUMP BUTTON
        auto invertBumpArea = lightControlArea.removeFromBottom(int(areaH) * 1);
        invertBumpArea.removeFromTop(3);
        invertBump.setBounds(invertBumpArea);
    }

}

void ControlLighting::valueChanged(juce::Value& value)
{
    //if (value == xyPad.xValue)
        // OpenGLComponentCanvasEdit.lightPosition.x = (float)xyPad.getXValue();
    //else if (value == xyPad.yValue)
        // OpenGLComponentCanvasEdit.lightPositionly = (float)xyPad.getYValue();
}

void ControlLighting::setupGroupComponent()
{
    auto font = customLookAndFeel->getFontRobotoCondensedRegular().withHeight(16.0F);
    auto fontColor = customLookAndFeel->getCurrentTheme().CustomDarkGrey;
    auto outlineColor = customLookAndFeel->getCurrentTheme().OutlineControl;

    float indentation = 5.0F;
    float gap = 6.0F;
    float cornerSize = 5.0F;
    float lineThick = 1.0F;

    group.setText("Lighting");
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

void ControlLighting::setColourGroup()
{
    group.setFontColour(customLookAndFeel->getCurrentTheme().CustomDarkGrey);
    group.setOutlineColour(customLookAndFeel->getCurrentTheme().OutlineControl);
}

void ControlLighting::setupDivider()
{
    if (filmstripType == FilmstripType::KNOB)
        totalDivider = 9;
    else
        totalDivider = 10;
}

void ControlLighting::setupXYPad()
{
    addAndMakeVisible(xyPad);
    xyPad.xValue.addListener(this);
    xyPad.yValue.addListener(this);
}

void ControlLighting::setupZPad()
{
    zPad.setName("Z");
    zPad.setComponentID("Slider_ID_02_ZPad");
    zPad.setRange(0.0, 2.0, 0.01);
    zPad.setValue(0.5);
    zPad.setSliderStyle(juce::Slider::LinearBarVertical);
    zPad.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    zPad.setWantsKeyboardFocus(false);
    zPad.onValueChange = [this]()
        {
            // OpenGLComponentCanvasEdit.lightPosition.z = (float)zPad.getValue();
        };
    addAndMakeVisible(zPad);
}

void ControlLighting::setColourXYZPad()
{
    //zPad.setColour(juce::Slider::trackColourId, customLookAndFeel->getCurrentTheme().CustomLightGrey);
    //zPad.setColour(juce::Slider::textBoxOutlineColourId, customLookAndFeel->getCurrentTheme().CustomDarkGrey);
}

void ControlLighting::setupXYZLabel()
{
    xyLabel.setComponentID("Label_ID_04_XYZ_PAD");
    xyLabel.setText("X Y", juce::dontSendNotification);
    xyLabel.setJustificationType(juce::Justification::centredTop);
    addAndMakeVisible(xyLabel);

    zLabel.setComponentID("Label_ID_04_XYZ_PAD");
    zLabel.setText("Z", juce::dontSendNotification);
    zLabel.setJustificationType(juce::Justification::centredTop);
    addAndMakeVisible(zLabel);
}

void ControlLighting::setupLockLighting()
{
    if (filmstripType == FilmstripType::SLIDER)
    {
        lockLabel.setComponentID("Label_ID_05_LEFT_HAND_SIDE_LIGHTING");
        lockLabel.setText("Lock to Slider Thumb", juce::dontSendNotification);
        lockLabel.setJustificationType(juce::Justification::centredLeft);
        addAndMakeVisible(lockLabel);

        lockButton.setComponentID("Buttons_ID_18_LOCK_BUTTON");
        lockButton.setToggleable(true);
        lockButton.onClick = [this]()
            {
                lockButton.setToggleState(!lockButton.getToggleState(), juce::dontSendNotification);
            };
        addAndMakeVisible(lockButton);
    }
}

void ControlLighting::setupColorChooser()
{
    lightingColor = juce::Colours::lightgoldenrodyellow.brighter();
    colorText = lightingColor.toDisplayString(false).toLowerCase();

    colorLabel.setComponentID("Label_ID_05_LEFT_HAND_SIDE_LIGHTING");
    colorLabel.setText("Color", juce::dontSendNotification);
    colorLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(colorLabel);

    colorButton.setComponentID("Buttons_ID_17_COLOR_SELECTOR");
    colorButton.setColour(juce::TextButton::buttonColourId, lightingColor);
    colorButton.onClick = [this]()
        {
            showColorChooser();
        };
    addAndMakeVisible(colorButton);

    colorValue.setComponentID("Label_ID_06_COLOR_VALUE");
    colorValue.setText(colorText, juce::dontSendNotification);
    colorValue.setJustificationType(juce::Justification::centred);
    colorValue.setColour(juce::Label::textColourId, juce::Colours::black);
    colorValue.setInterceptsMouseClicks(false, false);
    addAndMakeVisible(colorValue);

    copyValueButton.setComponentID("Buttons_ID_19_COPY_COLOR");
    copyValueButton.onClick = [this]()
        {
            juce::SystemClipboard::copyTextToClipboard(colorValue.getText());
        };
    addAndMakeVisible(copyValueButton);
}

void ControlLighting::showColorChooser()
{
    bool native{ false };

    if (colourSelectorWindow)
    {
        colourSelectorWindow->closeButtonPressed();
        colourSelectorWindow.reset();
    }
    else
    {
        lightingColor = colorButton.findColour(juce::TextButton::buttonColourId);

        //colourSelectorWindow = std::make_unique<ColourSelectorWindow>("Lighting Color", lightingColor, juce::DocumentWindow::allButtons, colorButton, colorValue);
        colourSelectorWindow = std::make_unique<ColourSelectorWindow>("Lighting", lightingColor, juce::DocumentWindow::minimiseButton | juce::DocumentWindow::closeButton, colorButton, colorValue);
        
        juce::Rectangle<int> area{ 0,0,210,300 };
        
        juce::RectanglePlacement placement{ (native ? juce::RectanglePlacement::xLeft : juce::RectanglePlacement::xRight)
                                            | juce::RectanglePlacement::yMid 
                                            | juce::RectanglePlacement::doNotResize };
        
        auto displayArea = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay()->userArea.reduced(20);

        auto result = placement.appliedTo(area, displayArea);

        colourSelectorWindow->setBounds(result);
        colourSelectorWindow->setResizable(false, !native);
        colourSelectorWindow->setUsingNativeTitleBar(native);
        colourSelectorWindow->setVisible(true);
    }
}

void ControlLighting::setupIntensitySlider()
{
    intensityLabel.setComponentID("Label_ID_05_LEFT_HAND_SIDE_LIGHTING");
    intensityLabel.setJustificationType(juce::Justification::centredLeft);
    intensityLabel.setText("Intensity", juce::dontSendNotification);
    addAndMakeVisible(intensityLabel);

    intensity.setName("Intensity");
    intensity.setComponentID("Slider_ID_03_INTENSITY_BUMP_LIGHTING");
    intensity.setRange(0, 100, 1);
    intensity.setValue(40);
    intensity.setSliderStyle(juce::Slider::LinearBar);
    intensity.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    intensity.setLookAndFeel(customLookAndFeel.get());
    intensity.setWantsKeyboardFocus(false);
    intensity.onValueChange = [this]()
        {
            // OpenGLComponentCanvasEdit.lightIntensity = (float)intensity.getValue() / 10;
        };
    addAndMakeVisible(intensity);

}

void ControlLighting::setupBumpSlider()
{
    bumpLabel.setComponentID("Label_ID_05_LEFT_HAND_SIDE_LIGHTING");
    bumpLabel.setJustificationType(juce::Justification::centredLeft);
    bumpLabel.setText("Bump", juce::dontSendNotification);
    addAndMakeVisible(bumpLabel);

    bump.setName("Intensity");
    bump.setComponentID("Slider_ID_03_INTENSITY_BUMP_LIGHTING");
    bump.setRange(0, 100, 1);
    bump.setValue(25);
    bump.setSliderStyle(juce::Slider::LinearBar);
    bump.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    bump.setLookAndFeel(customLookAndFeel.get());
    bump.setWantsKeyboardFocus(false);
    bump.onValueChange = [this]()
        {
            // OpenGLComponentCanvasEdit.bumpHeight  = (float)bump.getValue() / 10;
        };
    addAndMakeVisible(bump);
}

void ControlLighting::setupInvertButton()
{
    invertBump.setButtonText("Invert Bump");
    invertBump.setComponentID("Buttons_ID_16_INVERT_BUMP");
    invertBump.setClickingTogglesState(true);
    invertBump.setToggleState(false, juce::dontSendNotification);
    invertBump.onStateChange = [this]()
        {
            // OpenGLComponentCanvasEdit.invertBump = invertBump.getToggelState();
        };
    addAndMakeVisible(invertBump);
}

void ControlLighting::resetCurrentTheme()
{
    setColourGroup();
    setColourXYZPad();
}
