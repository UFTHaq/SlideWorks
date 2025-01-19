/*
  ==============================================================================

    ControlAssetThumb.cpp
    Created: 10 Dec 2024 6:43:17pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "ControlAssetThumb.h"

ControlAssetThumb::ControlAssetThumb
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

ControlAssetThumb::~ControlAssetThumb()
{
}

void ControlAssetThumb::paint(juce::Graphics& g)
{
}

void ControlAssetThumb::resized()
{
}

void ControlAssetThumb::setOriginalAssetRatio(int imageWidth, int imageHeight)
{
    imageRatio = Ratio {
        .w = imageWidth,
        .h = imageHeight
    };
}

void ControlAssetThumb::calculateAssetRealAndVirtualBounds()
{
    // JIKA KNOB PROJECT SEMUA IMAGE DI EXPECTASIKAN UNTUK MEMILIKI IMAGE YANG SQUARE.
    // MAKA DI KOMPONENT ASSET DI SLIDER BUTUH YANG BISA FLEXIBLE RECTANGLE. PERLU MEMILIKI RATIO ASLI DARI TIAP ASSET.
    // SO HOW TO PUT ORIGINAL IMAGE RATIO TO THIS CONTROL?
}
