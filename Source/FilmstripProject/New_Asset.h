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
};