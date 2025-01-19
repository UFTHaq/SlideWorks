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
}

ControlAssetTrack::~ControlAssetTrack()
{
}

void ControlAssetTrack::paint(juce::Graphics& g)
{
}

void ControlAssetTrack::resized()
{
}

void ControlAssetTrack::setOriginalAssetRatio(int imageWidth, int imageHeight)
{
    imageRatio = Ratio {
        .w = imageWidth,
        .h = imageHeight
    };
}
