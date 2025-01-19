/*
  ==============================================================================

    ControlAsset.cpp
    Created: 28 Dec 2024 5:54:08pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "ControlAsset.h"

ControlAsset::ControlAsset
(
    juce::Rectangle<int>& realCanvas
    , juce::Rectangle<int>& virtualCanvas
    , juce::Rectangle<int>& assetBoundsRealC
    , juce::Rectangle<int>& assetBoundsVirtC
)
    : realCanvas(realCanvas)
    , virtualCanvas(virtualCanvas)
    , assetBoundsRealC(assetBoundsRealC)
    , assetBoundsVirtC(assetBoundsVirtC)
{
}

ControlAsset::~ControlAsset()
{
}

void ControlAsset::paint(juce::Graphics& g)
{
}

void ControlAsset::resized()
{
}

const int ControlAsset::getAreaHeight() const
{
    return 20;
}

double ControlAsset::getAssetVirtualWidthPercentage() const
{
    return 0.0;
}

double ControlAsset::getAssetVirtualHeightPercentage() const
{
    return 0.0;
}

void ControlAsset::setOriginalAssetRatio(int imageWidth, int imageHeight)
{
}

void ControlAsset::calculateAssetRealAndVirtualBounds()
{
}

bool ControlAsset::isAssetCanChangeColor() const
{
    return false;
}

juce::Colour ControlAsset::getAssetAlphaColor() const
{
    return juce::Colour();
}
