/*
  ==============================================================================

    Asset.cpp
    Created: 29 Nov 2024 4:25:37pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "Asset.h"

Asset::Asset(const juce::String& type)
    : assetType(type)
{
}

Asset::~Asset()
{
}

juce::String Asset::getAssetType() const
{
    return assetType;
}

juce::String Asset::getAssetFileName() const
{
    return assetFileName;
}

juce::File Asset::getAssetFilePath() const
{
    return assetFilePath;
}

bool Asset::getAssetVisibility() const
{
    return assetVisible;
}

void Asset::setAssetType(const juce::String& type)
{
    this->assetType = type;
}

void Asset::setAssetFileName(const juce::String& name)
{
    this->assetFileName = name;
}

void Asset::setAssetFilePath(const juce::File& path)
{
    this->assetFilePath = path;
}

void Asset::setAssetVisibility(bool visible)
{
    this->assetVisible = visible;
}

