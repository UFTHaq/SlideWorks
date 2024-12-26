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

        // Default;
        auto virtualArea = virtualCanvas;
        if (assetType == AssetType::KNOB)
        {
            // set Default size
            //this->assetBoundsVirtC = juce::Rectangle<int>{ 0,0,200,200 };
            auto imageArea = int(virtualArea.getWidth() * 0.85F);

            this->assetBoundsVirtC = virtualArea.withSizeKeepingCentre(imageArea, imageArea);
        }
        else if (assetType == AssetType::KNOB_SCALE)
        {
            //this->assetBoundsVirtC = juce::Rectangle<int>{ 0,0,220,220 };
            auto imageArea = int(virtualArea.getWidth() * 0.9F);

            this->assetBoundsVirtC = virtualArea.withSizeKeepingCentre(imageArea, imageArea);
        }

        //this->assetBoundsRealC = juce::Rectangle<int> { 0,0,assetImage.getWidth(), assetImage.getHeight() };

        // Pada saat setelah load image, bagusnya assetBoundsRealC langsung berada di center dari realCanvas dan virtualCanvas
        // and to be able to do that need the realCanvas and or virtualCanvas from New_CanvasEdit
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

void New_Asset::makeVisible(const bool visible)
{
    this->assetVisible = visible;
}

bool New_Asset::getVisible() const
{
    return assetVisible;
}


void New_Asset::setAssetRealBounds(const juce::Rectangle<int> newBounds)
{
    // CanControlled by slider from subControl
    this->assetBoundsRealC = newBounds;
}

void New_Asset::setAssetVirtualBounds(const juce::Rectangle<int> newBounds)
{
    // CanControlled by drag from CanvasEdit Virtual Canvas
    this->assetBoundsVirtC = newBounds;
}

void New_Asset::setVirtualTopLeftPos(const juce::Point<int> newTopLeftPos, const float scaleFactor)
{
    this->assetBoundsVirtC.setPosition(newTopLeftPos);

    this->assetBoundsRealC.setPosition({ 
        int(newTopLeftPos.getX() / scaleFactor), 
        int(newTopLeftPos.getY() / scaleFactor)
        }
    );
}

void New_Asset::setVirtualCentrePos(const juce::Point<int> newCentrePos, const float scaleFactor)
{
    this->assetBoundsVirtC.setCentre(newCentrePos);

    this->assetBoundsRealC.setCentre({ 
        int(newCentrePos.getX() / scaleFactor), 
        int(newCentrePos.getY() / scaleFactor)
        }
    );
}

void New_Asset::setRealCanvas(const juce::Rectangle<int> realCanvas)
{
    this->realCanvas = realCanvas;
}

void New_Asset::setVirtualCanvas(const juce::Rectangle<int> virtualCanvas)
{
    this->virtualCanvas = virtualCanvas;

    auto virtualArea = virtualCanvas;
    if (assetType == AssetType::KNOB)
    {
        // set Default size
        //this->assetBoundsVirtC = juce::Rectangle<int>{ 0,0,200,200 };
        auto imageArea = int(virtualArea.getWidth() * 0.9F);

        this->assetBoundsVirtC = virtualArea.withSizeKeepingCentre(imageArea, imageArea);
    }
    else if (assetType == AssetType::KNOB_SCALE)
    {
        //this->assetBoundsVirtC = juce::Rectangle<int>{ 0,0,220,220 };
        auto imageArea = int(virtualArea.getWidth() * 0.95F);

        this->assetBoundsVirtC = virtualArea.withSizeKeepingCentre(imageArea, imageArea);
    }

    // for Sliders asset will be different with consideration of vertical or horizontal slider
}


juce::Rectangle<int> New_Asset::getAssetRealBounds() const
{
    return assetBoundsRealC;
}

juce::Point<int> New_Asset::getAssetRealTopLeftPos() const
{
    return assetBoundsRealC.getTopLeft();
}

juce::Point<int> New_Asset::getAssetRealCentrePos() const
{
    return assetBoundsRealC.getCentre();
}


juce::Rectangle<int> New_Asset::getAssetVirtualBounds() const
{
    return assetBoundsVirtC;
}

juce::Point<int> New_Asset::getAssetVirtualTopLeftPos() const
{
    return assetBoundsVirtC.getTopLeft();
}

juce::Point<int> New_Asset::getAssetVirtualAssetCentrePos() const
{
    return assetBoundsVirtC.getCentre();
}


void New_Asset::setAngleOffset(const double newAngleOffset)
{
    this->assetAngleOffset = newAngleOffset;
}

double New_Asset::getAngleOffset() const
{
    return assetAngleOffset;
}
