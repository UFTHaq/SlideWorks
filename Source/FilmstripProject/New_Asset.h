/*
  ==============================================================================

    New_Asset.h
    Created: 10 Dec 2024 2:22:34pm
    Author:  UFTHaq

  ==============================================================================
*/

// Put this to -> New_FilmstripProject

// Not inherit juce::Component
// Only Asset, such:
// path
// file name
// image

#pragma once

#include <JuceHeader.h>

#include "../Source/EnumClass.h"

class New_Asset
{
protected:
    AssetType assetType{};
    juce::String assetTypeStr{};
    juce::File assetFilePath{};
    juce::String assetName{};
    juce::Image assetImage{};
    bool assetVisible{};
    double assetAngleOffset{};
    int assetWidth{};
    int assetHeight{};

    juce::Rectangle<int> realCanvas{};
    juce::Rectangle<int> virtualCanvas{};
    juce::Rectangle<int> assetBoundsRealC{};
    juce::Rectangle<int> assetBoundsVirtC{};

public:
    New_Asset(const AssetType& type);
    ~New_Asset();

    AssetType getAssetType() const;
    const juce::String& getAssetTypeStr() const;
    const juce::File& getAssetFilePath() const;
    const juce::String& getAssetName() const;
    juce::Image getAssetImage() const;

    void setAssetFilePathAndLoadImage(const juce::File& filePath);
    void setAssetName(const juce::String& name);
    void makeVisible(const bool visible);
    bool getVisible() const;

    void setAssetRealBounds(const juce::Rectangle<int> newBounds);
    void setAssetVirtualBounds(const juce::Rectangle<int> newBounds);
    void setVirtualTopLeftPos(const juce::Point<int> newTopLeftPos, const float scaleFactor);
    void setVirtualCentrePos(const juce::Point<int> newCentrePos, const float scaleFactor);

    void setRealCanvas(const juce::Rectangle<int> realCanvas);
    void setVirtualCanvas(const juce::Rectangle<int> virtualCanvas);

    juce::Rectangle<int> getAssetRealBounds() const;
    juce::Point<int> getAssetRealTopLeftPos() const;
    juce::Point<int> getAssetRealCentrePos() const;

    juce::Rectangle<int> getAssetVirtualBounds() const;
    juce::Point<int> getAssetVirtualTopLeftPos() const;
    juce::Point<int> getAssetVirtualAssetCentrePos() const;

    void setAngleOffset(const double newAngleOffset);
    double getAngleOffset() const;
};