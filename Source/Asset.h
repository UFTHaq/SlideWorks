/*
  ==============================================================================

    Asset.h
    Created: 29 Nov 2024 4:25:37pm
    Author:  UFTHaq

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Asset
{
private:
    juce::String assetType{};
    juce::String assetFileName{};
    juce::File assetFilePath{};
    bool assetVisible{ true };

public:
    Asset(const juce::String& type);
    ~Asset();

    juce::String getAssetType() const;
    juce::String getAssetFileName() const;
    juce::File getAssetFilePath() const;
    bool getAssetVisibility() const;

    void setAssetType(const juce::String& type);
    void setAssetFileName(const juce::String& name);
    void setAssetFilePath(const juce::File& path);
    void setAssetVisibility(bool visible);
};