/*
  ==============================================================================

    ControlAssetTrackScale.h
    Created: 10 Dec 2024 6:44:01pm
    Author:  UFTHaq

  ==============================================================================
*/

// Put this to -> SubControls
// inherit juce::Component

#pragma once

#include <JuceHeader.h>

#include "../Source/Globals.h"
#include "../Source/CustomComponents/CustomLookAndFeel.h"
#include "../Source/CustomComponents/CustomGroupComponent.h"
#include "../Source/CustomComponents/CustomSlider.h"
#include "../Source/CustomComponents/CustomColourSelectorWindow.h"
#include "../Source/EnumClass.h"

#include "ControlAsset.h"

class ControlAssetTrackScale
    : public ControlAsset
{
protected:
    std::shared_ptr <CustomLookAndFeel> customLookAndFeel{};

    CustomGroupComponent group{};

    // Still not sure if i need to put value min max for simulation here or in the simulation section.
    // Alright, just move the simulation control in simulation

    // Size width px slider
    // Size height px slider
    // Angle offset slider

    // 1. ANGLE INPUT
    // 2. ROTATE BUTTONS
    // 3. LOCK RATIO
    // 4. WIDTH
    // 5. HEIGHT
    // 6. COLOUR SELECTOR
    // 7. ALPHA

    // padding = 13;
    // componentH = 28;
    // titleH = 20;
    // 7 x 28 = 196 + 20 + 13 = 229

    const int AREA_HEIGHT{ 229 };

    Ratio imageRatio{};

    juce::Label angleLabel{};
    juce::Label angleOffsetInput{};
    double AngleOffset{};

    juce::Label rotateLabel{};
    juce::TextButton turn1L{};
    juce::TextButton turn1R{};
    juce::TextButton turn90L{};
    juce::TextButton turn90R{};

    juce::Label lockLabel{};
    juce::TextButton lockRatio{};
    Ratio controlRatio{};

    juce::Label widthLabel{};
    CustomSlider width{};           // In percentage

    juce::Label heightLabel{};
    CustomSlider height{};          // In percentage

    juce::Label colorLabel{};
    juce::Label colorValue{};
    juce::TextButton colorButton{};
    juce::Colour alphaColor{};
    juce::String colorText{};
    std::unique_ptr<CustomColourSelectorWindow> colourSelectorWindow{};
    juce::TextButton copyValueButton{};

    juce::Label alphaLabel{};
    CustomSlider alpha{};

public:
    ControlAssetTrackScale
    (
        juce::Rectangle<int>& realCanvas
        , juce::Rectangle<int>& virtualCanvas
        , juce::Rectangle<int>& assetBoundsRealC
        , juce::Rectangle<int>& assetBoundsVirtC
    );
    ~ControlAssetTrackScale();

    void paint(juce::Graphics& g) override;
    void resized() override;

    const int getAreaHeight() const override;

    double getAssetVirtualWidthPercentage() const override;
    double getAssetVirtualHeightPercentage() const override;

    void setOriginalAssetRatio(int imageWidth, int imageHeight) override;
    void calculateAssetRealAndVirtualBounds() override;

    bool isAssetCanChangeColor() const override;
    juce::Colour getAssetAlphaColor() const override;

    void setupGroupComponent();
    void setColourGroup();

    void setupAngleOffsetComponents();
    void setupRotateComponents();
    void setupLockRatio();
    void setupWidthSlider();
    void setupHeightSlider();
    void setupColorChooser();
    void showColorChooser();
    void setupAlphaSlider();

    void recalibrateAngle();

    void resetCurrentTheme();
};