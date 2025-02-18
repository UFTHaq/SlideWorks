/*
  ==============================================================================

    ControlCanvas.cpp
    Created: 10 Dec 2024 5:50:36pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "ControlCanvas.h"

ControlCanvas::ControlCanvas(const FilmstripType& type, Canvas& canvas)
    : filmstripType(type)
    , canvas(canvas)
    , customLookAndFeel(Globals::getCustomLookAndFeel())
{
    setupGroupComponent();

    setupLockRatio();
    setupWidthSlider();
    setupHeightSlider();
    setupColorChooser();
}

ControlCanvas::~ControlCanvas()
{
}

void ControlCanvas::paint(juce::Graphics& g)
{
    group.paint(g);
}

void ControlCanvas::resized()
{
    group.setBounds(getLocalBounds());

    auto bounds = getLocalBounds();
    bounds.removeFromTop(13);

    auto w = bounds.getWidth() - 20;
    auto h = bounds.getHeight() - 20;
    bounds = bounds.withSizeKeepingCentre(w, h);

    auto controlArea = bounds;
    auto areaH = controlArea.getHeight() / 4;

    auto leftSide = int(controlArea.getWidth() * 0.425F);
    auto remove = 3;

    {
        // LOCK RATIO
        auto area = controlArea.removeFromTop(int(areaH) * 1);
        area.removeFromTop(remove);
        area.removeFromBottom(remove);

        auto labelArea = area.removeFromLeft(area.getWidth() - area.getHeight());
        labelArea.removeFromLeft(5);

        auto mainArea = area;

        lockLabel.setBounds(labelArea);
        lockRatio.setBounds(mainArea);
    }

    {
        // CANVAS WIDTH
        auto area = controlArea.removeFromTop(int(areaH) * 1);
        area.removeFromTop(remove);
        area.removeFromBottom(remove);

        auto labelArea = area.removeFromLeft(leftSide);
        labelArea.removeFromLeft(5);

        auto mainArea = area;

        widthLabel.setBounds(labelArea);
        width.setBounds(mainArea);
        width.initializeBounds();
    }

    {
        // CANVAS HEIGHT
        auto area = controlArea.removeFromTop(int(areaH) * 1);
        area.removeFromTop(remove);
        area.removeFromBottom(remove);

        auto labelArea = area.removeFromLeft(leftSide);
        labelArea.removeFromLeft(5);

        auto mainArea = area;

        heightLabel.setBounds(labelArea);
        height.setBounds(mainArea);
        height.initializeBounds();
    }

    {
        // COLOR CHOOSER
        auto area = controlArea.removeFromTop(int(areaH) * 1);
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
}

void ControlCanvas::setupGroupComponent()
{
    auto font = customLookAndFeel->getFontRobotoCondensedRegular().withHeight(16.0F);
    auto fontColor = customLookAndFeel->getCurrentTheme().CustomDarkGrey;
    auto outlineColor = customLookAndFeel->getCurrentTheme().OutlineControl;

    float indentation = 5.0F;
    float gap = 6.0F;
    float cornerSize = 5.0F;
    float lineThick = 1.0F;

    group.setText("Canvas");
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

void ControlCanvas::setColourGroup()
{
    group.setFontColour(customLookAndFeel->getCurrentTheme().CustomDarkGrey);
    group.setOutlineColour(customLookAndFeel->getCurrentTheme().OutlineControl);
}

void ControlCanvas::setupLockRatio()
{
    lockLabel.setComponentID("Label_ID_05_LEFT_HAND_SIDE_LIGHTING");
    lockLabel.setText("Lock Canvas Ratio", juce::dontSendNotification);
    lockLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(lockLabel);

    lockRatio.setComponentID("Buttons_ID_20_LOCK_RATIO_BUTTON");
    lockRatio.setToggleable(true);
    lockRatio.onClick = [this]()
        {
            lockRatio.setToggleState(!lockRatio.getToggleState(), juce::dontSendNotification);

            if (lockRatio.getToggleState() == true)
            {
                controlRatio = Ratio { 
                    .w = (int)width.getValue(),
                    .h = (int)height.getValue()
                };
            }
        };
    addAndMakeVisible(lockRatio);
}

void ControlCanvas::setupWidthSlider()
{
    widthLabel.setComponentID("Label_ID_05_LEFT_HAND_SIDE_LIGHTING");
    widthLabel.setText("Width", juce::dontSendNotification);
    widthLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(widthLabel);

    width.setFont(customLookAndFeel->getFontRobotoCondensedRegular().withHeight(16.0F));
    width.setColourBase(customLookAndFeel->getCurrentTheme().SlideworksBaseColour.brighter());
    width.setColourOutline(customLookAndFeel->getCurrentTheme().CustomDarkGrey.brighter());
    width.setColourBar(customLookAndFeel->getCurrentTheme().CustomLightGrey.brighter());
    width.setColourText(customLookAndFeel->getCurrentTheme().FontBlack);
    width.setCornerSize(2.0F);
    width.setOutlineThick(0.8F);
    width.setPostfix("PX");
    width.setRange(50, 1000, 1);
    width.setScrollStep(25);
    width.setValue(static_cast<double>(canvas.getCanvasEdit().getRealCanvasWH().getX()));
    //width.setValue(300);
    width.onValueChange = [this]()
        {
            if (lockRatio.getToggleState() == false)
                canvas.getCanvasEdit().setRealCanvasWidth(static_cast<int>(width.getValue()));
            else
            {
                int newValueW = (int)width.getValue();
                int newValueH = int((double)newValueW / controlRatio.w * controlRatio.h);

                int minValueW = (int)width.getMinRange();
                int maxValueW = (int)width.getMaxRange();

                int minValueH = (int)height.getMinRange();
                int maxValueH = (int)height.getMaxRange();

                if (controlRatio.h > controlRatio.w)
                {
                    if (newValueW < minValueW)
                    {
                        newValueW = minValueW;
                        newValueH = int((double)newValueW / controlRatio.w * controlRatio.h);
                    }
                    else if (newValueH > maxValueH)
                    {
                        newValueH = maxValueH;
                        newValueW = int((double)newValueH * controlRatio.w / controlRatio.h);
                    }
                }
                else
                {
                    if (newValueH < minValueH)
                    {
                        newValueH = minValueH;
                        newValueW = int((double)newValueH * controlRatio.w / controlRatio.h);
                    }
                    else if (newValueW > maxValueW)
                    {
                        newValueW = maxValueW;
                        newValueH = int((double)newValueW / controlRatio.w * controlRatio.h);
                    }
                }

                height.setValue(newValueH);
                width.setValue(newValueW);

                canvas.getCanvasEdit().setRealCanvasHeight(newValueH);
                canvas.getCanvasEdit().setRealCanvasWidth(newValueW);
            }

            canvas.getCanvasEdit().calculateAllAssetRealVirtualBounds();

            if (onSizeChangeForFooter)
                onSizeChangeForFooter();

        };
    addAndMakeVisible(width);
}

void ControlCanvas::setupHeightSlider()
{
    heightLabel.setComponentID("Label_ID_05_LEFT_HAND_SIDE_LIGHTING");
    heightLabel.setText("Height", juce::dontSendNotification);
    heightLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(heightLabel);

    height.setFont(customLookAndFeel->getFontRobotoCondensedRegular().withHeight(16.0F));
    height.setColourBase(customLookAndFeel->getCurrentTheme().SlideworksBaseColour.brighter());
    height.setColourOutline(customLookAndFeel->getCurrentTheme().CustomDarkGrey.brighter());
    height.setColourBar(customLookAndFeel->getCurrentTheme().CustomLightGrey.brighter());
    height.setColourText(customLookAndFeel->getCurrentTheme().FontBlack);
    height.setCornerSize(2.0F);
    height.setOutlineThick(0.8F);
    height.setPostfix("PX");
    height.setRange(50, 1000, 1);
    height.setScrollStep(25);
    height.setValue(static_cast<double>(canvas.getCanvasEdit().getRealCanvasWH().getY()));
    //height.setValue(300);
    height.onValueChange = [this]()
        {
            if (lockRatio.getToggleState() == false)
                canvas.getCanvasEdit().setRealCanvasHeight(static_cast<int>(height.getValue()));
            else
            {
                int newValueH = (int)height.getValue();
                int newValueW = int((double)newValueH * controlRatio.w / controlRatio.h);

                int minValueW = (int)width.getMinRange();
                int maxValueW = (int)width.getMaxRange();

                int minValueH = (int)height.getMinRange();
                int maxValueH = (int)height.getMaxRange();

                if (controlRatio.h > controlRatio.w)
                {
                    if (newValueW < minValueW)
                    {
                        newValueW = minValueW;
                        newValueH = int((double)newValueW / controlRatio.w * controlRatio.h);
                    } 
                    else if (newValueH > maxValueH)
                    {
                        newValueH = maxValueH;
                        newValueW = int((double)newValueH * controlRatio.w / controlRatio.h);
                    }
                }
                else
                {
                    if (newValueH < minValueH)
                    {
                        newValueH = minValueH;
                        newValueW = int((double)newValueH * controlRatio.w / controlRatio.h);
                    }
                    else if (newValueW > maxValueW)
                    {
                        newValueW = maxValueW;
                        newValueH = int((double)newValueW / controlRatio.w * controlRatio.h);
                    }
                }

                height.setValue(newValueH);
                width.setValue(newValueW);

                canvas.getCanvasEdit().setRealCanvasHeight(newValueH);
                canvas.getCanvasEdit().setRealCanvasWidth(newValueW);
            }

            canvas.getCanvasEdit().calculateAllAssetRealVirtualBounds();

            if (onSizeChangeForFooter)
                onSizeChangeForFooter();
        };
    addAndMakeVisible(height);
}

void ControlCanvas::setupColorChooser()
{
    canvasColor = customLookAndFeel->getCurrentTheme().SlideworksBaseColour;
    colorText = canvasColor.toDisplayString(false).toLowerCase();

    colorLabel.setComponentID("Label_ID_05_LEFT_HAND_SIDE_LIGHTING");
    colorLabel.setText("Color", juce::dontSendNotification);
    colorLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(colorLabel);

    colorButton.setComponentID("Buttons_ID_17_COLOR_SELECTOR");
    colorButton.setColour(juce::TextButton::buttonColourId, canvasColor);
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
    colorValue.onTextChange = [this]()  // This is called from ColourSelectorWindow.cpp when colorValue.setText() on ColourSelectorWindow::changeListenerCallback
        {
            canvas.setCanvasColor(colorButton.findColour(juce::TextButton::buttonColourId));
        };
    addAndMakeVisible(colorValue);

    copyValueButton.setComponentID("Buttons_ID_19_COPY_COLOR");
    copyValueButton.onClick = [this]()
        {
            juce::SystemClipboard::copyTextToClipboard(colorValue.getText());
        };
    addAndMakeVisible(copyValueButton);
}

void ControlCanvas::showColorChooser()
{
    bool native{ false };

    if (colourSelectorWindow)
    {
        colourSelectorWindow->closeButtonPressed();
        colourSelectorWindow.reset();
    }
    else
    {
        canvasColor = colorButton.findColour(juce::TextButton::buttonColourId);

        colourSelectorWindow = std::make_unique<CustomColourSelectorWindow>
            (
                "Canvas" 
                , canvasColor
                , juce::DocumentWindow::minimiseButton | juce::DocumentWindow::closeButton
                , colorButton 
                , colorValue
            );

        juce::Rectangle<int> area{ 0,0,210,310 };

        juce::RectanglePlacement placement{ (native ? juce::RectanglePlacement::xLeft : juce::RectanglePlacement::xRight)
                                            | juce::RectanglePlacement::yMid
                                            | juce::RectanglePlacement::doNotResize };

        auto displayArea = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay()->userArea.reduced(20);

        auto result = placement.appliedTo(area, displayArea);

        colourSelectorWindow->setBounds(result);
        colourSelectorWindow->setResizable(false, !native);
        colourSelectorWindow->setUsingNativeTitleBar(native);
        colourSelectorWindow->setVisible(true);
        colourSelectorWindow->setComponentID("WINDOW_CANVAS");
    }
}

void ControlCanvas::resetCurrentTheme()
{
    setColourGroup();
}

double ControlCanvas::getValueWidth() const
{
    return width.getValue();
}

double ControlCanvas::getValueHeight() const
{
    return height.getValue();
}
