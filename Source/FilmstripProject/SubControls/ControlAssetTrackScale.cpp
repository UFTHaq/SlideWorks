/*
  ==============================================================================

    ControlAssetTrackScale.cpp
    Created: 10 Dec 2024 6:44:01pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "ControlAssetTrackScale.h"

ControlAssetTrackScale::ControlAssetTrackScale
(
    juce::Rectangle<int>& realCanvas
    , juce::Rectangle<int>& virtualCanvas
    , juce::Rectangle<int>& assetBoundsRealC
    , juce::Rectangle<int>& assetBoundsVirtC
)
    : ControlAsset(realCanvas, virtualCanvas, assetBoundsRealC, assetBoundsVirtC)
    , customLookAndFeel(Globals::getCustomLookAndFeel())
{
}

ControlAssetTrackScale::~ControlAssetTrackScale()
{
}

void ControlAssetTrackScale::paint(juce::Graphics& g)
{
}

void ControlAssetTrackScale::resized()
{
}

void ControlAssetTrackScale::setOriginalAssetRatio(int imageWidth, int imageHeight)
{
    imageRatio = Ratio {
        .w = imageWidth,
        .h = imageHeight
    };
}
