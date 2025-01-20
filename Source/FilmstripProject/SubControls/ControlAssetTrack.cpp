/*
  ==============================================================================

    ControlAssetTrack.cpp
    Created: 10 Dec 2024 6:43:38pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "ControlAssetTrack.h"

ControlAssetTrack::ControlAssetTrack
(
    juce::Rectangle<int>& realCanvas
    , juce::Rectangle<int>& virtualCanvas
    , juce::Rectangle<int>& assetBoundsRealC
    , juce::Rectangle<int>& assetBoundsVirtC
)
    : ControlAsset(realCanvas, virtualCanvas, assetBoundsRealC, assetBoundsVirtC)
    , customLookAndFeel(Globals::getCustomLookAndFeel())
{
    setupGroupComponent();

    setupAngleOffsetComponents();
    setupRotateComponents();
    setupLockRatio();
    setupWidthSlider();
    setupHeightSlider();
}

ControlAssetTrack::~ControlAssetTrack()
{
}

void ControlAssetTrack::paint(juce::Graphics& g)
{
    group.paint(g);
}

void ControlAssetTrack::resized()
{
    group.setBounds(getLocalBounds());

    auto bounds = getLocalBounds();
    bounds.removeFromTop(13);

    auto w = bounds.getWidth() - 20;
    auto h = bounds.getHeight() - 20;
    bounds = bounds.withSizeKeepingCentre(w, h);

    auto controlArea = bounds;
    auto areaH = controlArea.getHeight() / 5;

    auto leftSide = int(controlArea.getWidth() * 0.425F);
    auto remove = 3;

    {
        // ANGLE COMPONENTS
        auto area = controlArea.removeFromTop(int(areaH) * 1);
        area.removeFromTop(remove);
        area.removeFromBottom(remove);

        auto labelArea = area.removeFromLeft(leftSide);
        labelArea.removeFromLeft(5);

        auto mainArea = area;

        angleLabel.setBounds(labelArea);
        angleOffsetInput.setBounds(mainArea);
    }

    {
        // ROTATE COMPONENTS
        auto area = controlArea.removeFromTop(int(areaH) * 1);
        area.removeFromTop(remove);
        area.removeFromBottom(remove);

        auto labelArea = area.removeFromLeft(leftSide);
        labelArea.removeFromLeft(5);

        int pad = 1;
        auto mainArea = area.reduced(-pad);
        auto areaButtonW = int((double)mainArea.getWidth() / 4);

        auto turn1LArea = mainArea.removeFromLeft(areaButtonW).reduced(pad);
        auto turn1RArea = mainArea.removeFromLeft(areaButtonW).reduced(pad);

        auto turn90RArea = mainArea.removeFromRight(areaButtonW).reduced(pad);
        auto turn90LArea = mainArea.removeFromRight(areaButtonW).reduced(pad);

        rotateLabel.setBounds(labelArea);
        turn1L.setBounds(turn1LArea);
        turn1R.setBounds(turn1RArea);
        turn90L.setBounds(turn90LArea);
        turn90R.setBounds(turn90RArea);
    }

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
        // ASSET WIDTH
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
        // ASSET HEIGHT
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
}

const int ControlAssetTrack::getAreaHeight() const
{
    return AREA_HEIGHT;
}

double ControlAssetTrack::getAssetVirtualWidthPercentage() const
{
    return width.getValue() / 100;
}

double ControlAssetTrack::getAssetVirtualHeightPercentage() const
{
    return height.getValue() / 100;
}

void ControlAssetTrack::setOriginalAssetRatio(int imageWidth, int imageHeight)
{
    imageRatio = Ratio {
        .w = imageWidth,
        .h = imageHeight
    };
}

void ControlAssetTrack::calculateAssetRealAndVirtualBounds()
{
    {
        int w = realCanvas.getWidth();
        int h = realCanvas.getHeight();

        if (imageRatio.w != 0 && imageRatio.h != 0)
        {
            double aspectRatio = (double)imageRatio.w / imageRatio.h;

            if (w / aspectRatio <= h)
            {
                h = int(w / aspectRatio);
            }
            else
            {
                w = int(h * aspectRatio);
            }
        }

        auto realCanvasCopy = realCanvas;
        auto realAreaOfAsset = realCanvasCopy.withSizeKeepingCentre(w, h);

        int newRealWidth = int(realCanvas.getWidth() * width.getValue() / 100);
        int newRealHeight = int(realCanvas.getHeight() * height.getValue() / 100);
        assetBoundsRealC = realCanvas.withSizeKeepingCentre(newRealWidth, newRealHeight);
    }

    {
        int w = virtualCanvas.getWidth();
        int h = virtualCanvas.getHeight();

        if (imageRatio.w != 0 && imageRatio.h != 0)
        {
            double aspectRatio = (double)imageRatio.w / imageRatio.h;

            if (w / aspectRatio <= h)
            {
                h = int(w / aspectRatio);
            }
            else
            {
                w = int(h * aspectRatio);
            }
        }

        auto virtualCanvasCopy = virtualCanvas;
        auto virtualAreaOfAsset = virtualCanvasCopy.withSizeKeepingCentre(w, h);

        int newVirtWidth = int(virtualAreaOfAsset.getWidth() * width.getValue() / 100);
        int newVirtHeight = int(virtualAreaOfAsset.getHeight() * height.getValue() / 100);
        assetBoundsVirtC = virtualAreaOfAsset.withSizeKeepingCentre(newVirtWidth, newVirtHeight);
    }

    //DBG("ASSET KNOB_SCALE BOUNDS IN REAL CANVAS : " << assetBoundsRealC.toString());
    //DBG("ASSET KNOB_SCALE BOUNDS IN VIRTUAL CANVAS : " << assetBoundsVirtC.toString());

    if (onVirtBoundsChange)
        onVirtBoundsChange();
}

bool ControlAssetTrack::isAssetCanChangeColor() const
{
    return false;
}

void ControlAssetTrack::setupGroupComponent()
{
    auto font = customLookAndFeel->getFontRobotoCondensedRegular().withHeight(16.0F);
    auto fontColor = customLookAndFeel->getCurrentTheme().CustomDarkGrey;
    auto outlineColor = customLookAndFeel->getCurrentTheme().OutlineControl;

    float indentation = 5.0F;
    float gap = 6.0F;
    float cornerSize = 5.0F;
    float lineThick = 1.0F;

    group.setText("Slider Track");
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

void ControlAssetTrack::setColourGroup()
{
    group.setFontColour(customLookAndFeel->getCurrentTheme().CustomDarkGrey);
    group.setOutlineColour(customLookAndFeel->getCurrentTheme().OutlineControl);
}

void ControlAssetTrack::setupAngleOffsetComponents()
{
    angleLabel.setComponentID("Label_ID_05_LEFT_HAND_SIDE_LIGHTING");
    angleLabel.setText("Angle", juce::dontSendNotification);
    angleLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(angleLabel);

    angleOffsetInput.setComponentID("Label_ID_08_ANGLE_INPUT");
    angleOffsetInput.setText(juce::String(AngleOffset), juce::dontSendNotification);
    angleOffsetInput.setFont(customLookAndFeel->getFontRobotoCondensedRegular().withHeight(16.0F));
    angleOffsetInput.setJustificationType(juce::Justification::centred);
    angleOffsetInput.setColour(juce::Label::backgroundColourId, juce::Colours::transparentBlack);
    angleOffsetInput.setColour(juce::Label::backgroundWhenEditingColourId, juce::Colours::black);
    angleOffsetInput.setColour(juce::Label::textWhenEditingColourId, juce::Colours::white);
    angleOffsetInput.setColour(juce::TextEditor::outlineColourId, juce::Colours::transparentBlack);
    angleOffsetInput.setColour(juce::TextEditor::highlightColourId, juce::Colours::royalblue);
    angleOffsetInput.setColour(juce::Label::textColourId, customLookAndFeel->getCurrentTheme().FontBlack);
    angleOffsetInput.setColour(juce::Label::outlineColourId, customLookAndFeel->getCurrentTheme().FontBlack);
    angleOffsetInput.setEditable(false, true);
    angleOffsetInput.onTextChange = [this]()
        {
            juce::String text = angleOffsetInput.getText();

            double value = text.getDoubleValue();

            AngleOffset = value;
            recalibrateAngle();
        };

    addAndMakeVisible(angleOffsetInput);
}

void ControlAssetTrack::setupRotateComponents()
{
    rotateLabel.setComponentID("Label_ID_05_LEFT_HAND_SIDE_LIGHTING");
    rotateLabel.setText("Rotate", juce::dontSendNotification);
    rotateLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(rotateLabel);

    turn1L.setComponentID("Buttons_ID_21_ROTATE_ASSET_BUTTON");
    turn1L.setName("1L");
    turn1L.onClick = [this]()
        {
            AngleOffset -= 1;
            recalibrateAngle();
        };
    addAndMakeVisible(turn1L);

    turn1R.setComponentID("Buttons_ID_21_ROTATE_ASSET_BUTTON");
    turn1R.setName("1R");
    turn1R.onClick = [this]()
        {
            AngleOffset += 1;
            recalibrateAngle();
        };
    addAndMakeVisible(turn1R);

    turn90L.setComponentID("Buttons_ID_21_ROTATE_ASSET_BUTTON");
    turn90L.setName("90L");
    turn90L.onClick = [this]()
        {
            AngleOffset -= 90;
            recalibrateAngle();
        };
    addAndMakeVisible(turn90L);

    turn90R.setComponentID("Buttons_ID_21_ROTATE_ASSET_BUTTON");
    turn90R.setName("90R");
    turn90R.onClick = [this]()
        {
            AngleOffset += 90;
            recalibrateAngle();
        };
    addAndMakeVisible(turn90R);
}

void ControlAssetTrack::setupLockRatio()
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
                controlRatio = Ratio{
                    .w = (int)width.getValue(),
                    .h = (int)height.getValue()
                };
            }
        };
    addAndMakeVisible(lockRatio);
}

void ControlAssetTrack::setupWidthSlider()
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
    width.setPostfix("%");
    width.setTextFormatDecimal(true, 1);
    width.setRange(5, 100, 1);
    width.setScrollStep(2.5);
    width.setValue(80);
    width.onValueChange = [this]()
        {
            if (lockRatio.getToggleState() == false)
            {
                calculateAssetRealAndVirtualBounds();
            }
            else
            {
                double newValueW = width.getValue();
                double newValueH = (double)newValueW / controlRatio.w * controlRatio.h;

                double minValueW = width.getMinRange();
                double maxValueW = width.getMaxRange();

                double minValueH = height.getMinRange();
                double maxValueH = height.getMaxRange();

                if (controlRatio.h > controlRatio.w)
                {
                    if (newValueW < minValueW)
                    {
                        newValueW = minValueW;
                        newValueH = ((double)newValueW / controlRatio.w * controlRatio.h);
                    }
                    else if (newValueH > maxValueH)
                    {
                        newValueH = maxValueH;
                        newValueW = ((double)newValueH * controlRatio.w / controlRatio.h);
                    }
                }
                else
                {
                    if (newValueH < minValueH)
                    {
                        newValueH = minValueH;
                        newValueW = ((double)newValueH * controlRatio.w / controlRatio.h);
                    }
                    else if (newValueW > maxValueW)
                    {
                        newValueW = maxValueW;
                        newValueH = ((double)newValueW / controlRatio.w * controlRatio.h);
                    }
                }

                height.setValue(newValueH);
                width.setValue(newValueW);

                calculateAssetRealAndVirtualBounds();
            }

        };
    addAndMakeVisible(width);

    calculateAssetRealAndVirtualBounds();
}

void ControlAssetTrack::setupHeightSlider()
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
    height.setPostfix("%");
    height.setTextFormatDecimal(true, 1);
    height.setRange(5, 100, 1);
    height.setScrollStep(2.5);
    height.setValue(80);
    height.onValueChange = [this]()
        {
            if (lockRatio.getToggleState() == false)
            {
                calculateAssetRealAndVirtualBounds();
            }
            else
            {
                double newValueH = height.getValue();
                double newValueW = (double)newValueH * controlRatio.w / controlRatio.h;

                double minValueW = width.getMinRange();
                double maxValueW = width.getMaxRange();

                double minValueH = height.getMinRange();
                double maxValueH = height.getMaxRange();

                if (controlRatio.h > controlRatio.w)
                {
                    if (newValueW < minValueW)
                    {
                        newValueW = minValueW;
                        newValueH = ((double)newValueW / controlRatio.w * controlRatio.h);
                    }
                    else if (newValueH > maxValueH)
                    {
                        newValueH = maxValueH;
                        newValueW = ((double)newValueH * controlRatio.w / controlRatio.h);
                    }
                }
                else
                {
                    if (newValueH < minValueH)
                    {
                        newValueH = minValueH;
                        newValueW = ((double)newValueH * controlRatio.w / controlRatio.h);
                    }
                    else if (newValueW > maxValueW)
                    {
                        newValueW = maxValueW;
                        newValueH = ((double)newValueW / controlRatio.w * controlRatio.h);
                    }
                }

                height.setValue(newValueH);
                width.setValue(newValueW);

                calculateAssetRealAndVirtualBounds();
            }

        };
    addAndMakeVisible(height);
}

void ControlAssetTrack::recalibrateAngle()
{
    AngleOffset = std::fmod(AngleOffset, 360);

    if (AngleOffset < 0)
    {
        AngleOffset += 360;
    }

    angleOffsetInput.setText(juce::String(AngleOffset), juce::dontSendNotification);
}

void ControlAssetTrack::resetCurrentTheme()
{
    setColourGroup();
}
