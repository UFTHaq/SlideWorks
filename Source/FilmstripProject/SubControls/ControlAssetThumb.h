/*
  ==============================================================================

    ControlAssetThumb.h
    Created: 10 Dec 2024 6:43:17pm
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

class ControlAssetThumb
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

    // When asset selected, can 
    // Rotate by 90 degree left, and right
    //

    // For all component of Sliders
    // All component will be in center. 
    // if (Horizontal = center X), so the component can be control up and down
    // if (Vertical = center Y), so the component can be control left and right
    // So need to track what the slider style is (horizontal / vertical) and track where the min side and the max side
    // Initial idea, (horizontal = left min, right max), (vertical = bottom min, top max)
    // Make the bounding box drawable to

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
    ControlAssetThumb
    (
        juce::Rectangle<int>& realCanvas
        , juce::Rectangle<int>& virtualCanvas
        , juce::Rectangle<int>& assetBoundsRealC
        , juce::Rectangle<int>& assetBoundsVirtC
    );
    ~ControlAssetThumb();

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