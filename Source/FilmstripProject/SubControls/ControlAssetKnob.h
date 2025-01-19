/*
  ==============================================================================

    ControlAssetKnob.h
    Created: 10 Dec 2024 6:42:46pm
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
#include "../Source/EnumClass.h"

#include "ControlAsset.h"

class ControlAssetKnob
    : public ControlAsset
{
protected:
    std::shared_ptr <CustomLookAndFeel> customLookAndFeel{};

    CustomGroupComponent group{};

    // Still not sure if i need to put value min max for simulation here or in the simulation section.
    // Alright, just move the simulation control in simulation

    // Size width px slider  or maybe percentage is better? cause the sizing can be changed.
    // Size height px slider or maybe percentage is better? cause the sizing can be changed.
    // Angle offset slider

    // When asset selected, can 
    // Rotate by 90 degree left, and right
    // "Angle" (Label value) button 90+ left, 90+ right

    // 1. ANGLE INPUT
    // 2. ROTATE BUTTONS
    // 3. LOCK RATIO
    // 4. WIDTH
    // 5. HEIGHT

    // padding = 13;
    // componentH = 28;
    // titleH = 20;
    // 5 x 28 = 140 + 20 + 13 = 173

    const int AREA_HEIGHT{ 173 };

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


public:
    ControlAssetKnob
    (
        juce::Rectangle<int>& realCanvas
        , juce::Rectangle<int>& virtualCanvas
        , juce::Rectangle<int>& assetBoundsRealC
        , juce::Rectangle<int>& assetBoundsVirtC
    );
    ~ControlAssetKnob();

    void paint(juce::Graphics& g) override;
    void resized() override;

    const int getAreaHeight() const override;
    
    double getAssetVirtualWidthPercentage() const override;
    double getAssetVirtualHeightPercentage() const override;

    void setOriginalAssetRatio(int imageWidth, int imageHeight) override;
    void calculateAssetRealAndVirtualBounds() override;

    bool isAssetCanChangeColor() const override;

    void setupGroupComponent();
    void setColourGroup();

    void setupAngleOffsetComponents();
    void setupRotateComponents();
    void setupLockRatio();
    void setupWidthSlider();
    void setupHeightSlider();

    void recalibrateAngle();

    void resetCurrentTheme();
};