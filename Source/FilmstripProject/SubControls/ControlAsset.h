/*
  ==============================================================================

    ControlAsset.h
    Created: 28 Dec 2024 5:54:08pm
    Author:  UFTHaq

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "../Source/EnumClass.h"

class ControlAsset
    : public juce::Component
{
protected:
    juce::Rectangle<int>& realCanvas;
    juce::Rectangle<int>& virtualCanvas;
    juce::Rectangle<int>& assetBoundsRealC;
    juce::Rectangle<int>& assetBoundsVirtC;

    Ratio imageRatio{};
    //int originalImageWidth{};
    //int originalImageHeight{};


public:
    ControlAsset
    (
        juce::Rectangle<int>& realCanvas
        , juce::Rectangle<int>& virtualCanvas
        , juce::Rectangle<int>& assetBoundsRealC
        , juce::Rectangle<int>& assetBoundsVirtC
    );
    ~ControlAsset();

    void paint(juce::Graphics& g) override;
    void resized() override;

    std::function<void()> onVirtBoundsChange{};

    virtual const int getAreaHeight() const;

    virtual double getAssetVirtualWidthPercentage() const;
    virtual double getAssetVirtualHeightPercentage() const;

    virtual void setOriginalAssetRatio(int imageWidth, int imageHeight);
    virtual void calculateAssetRealAndVirtualBounds();

    virtual bool isAssetCanChangeColor() const;
    virtual juce::Colour getAssetAlphaColor() const;

    std::function<void()> onColorChange{};
};