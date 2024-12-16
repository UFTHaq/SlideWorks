/*
  ==============================================================================

    New_Asset.cpp
    Created: 10 Dec 2024 2:22:34pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "New_Asset.h"

New_Asset::New_Asset(const AssetType& type)
    : assetType(type)
{
    switch (type)
    {
    case AssetType::KNOB:
        assetTypeStr = "Knob";
        break;
    case AssetType::KNOB_SCALE:
        assetTypeStr = "Scale";
        break;
    case AssetType::THUMB:
        assetTypeStr = "Thumb";
        break;
    case AssetType::TRACK:
        assetTypeStr = "Track";
        break;
    case AssetType::TRACK_SCALE:
        assetTypeStr = "Scale";
        break;

    default:
        assetTypeStr = "Error";
        break;
    }
}

New_Asset::~New_Asset()
{
}

AssetType New_Asset::getAssetType() const
{
    return assetType;
}

const juce::String& New_Asset::getAssetTypeStr() const
{
    return assetTypeStr;
}

const juce::File& New_Asset::getAssetFilePath() const
{
    return assetFilePath;
}

const juce::String& New_Asset::getAssetName() const
{
    return assetName;
}

juce::Image New_Asset::getAssetImage() const
{
    return assetImage;
}

void New_Asset::setAssetFilePathAndLoadImage(const juce::File& filePath)
{
    if (filePath.existsAsFile()) 
    {
        this->assetFilePath = filePath;

        this->assetImage = juce::PNGImageFormat::loadFrom(assetFilePath);

        if (assetImage.isNull())
        {
            jassertfalse;
        }
    }
    else
    {
        jassertfalse;
        DBG("Invalid file path: " << filePath.getFullPathName());
    }
}

void New_Asset::setAssetName(const juce::String& name)
{
    this->assetName = name;
}
