/*
  ==============================================================================

    Asset.cpp
    Created: 10 Dec 2024 2:22:34pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "Asset.h"

Asset::Asset(const AssetType& type)
    : assetType(type)
{
    switch (type)
    {
    case AssetType::KNOB:
        assetTypeStr = "Knob";
        controlAsset = std::make_unique<ControlAssetKnob>( realCanvas
                                                         , virtualCanvas
                                                         , assetBoundsRealC
                                                         , assetBoundsVirtC );
        break;

    case AssetType::KNOB_SCALE:
        assetTypeStr = "Scale";
        //controlAsset = std::make_unique<ControlAssetKnobScale>();
        controlAsset = std::make_unique<ControlAssetKnobScale>( realCanvas
                                                              , virtualCanvas
                                                              , assetBoundsRealC
                                                              , assetBoundsVirtC );
        break;

    case AssetType::THUMB:
        assetTypeStr = "Thumb";
        //controlAsset = std::make_unique<ControlAssetThumb>();
        controlAsset = std::make_unique<ControlAssetThumb>( realCanvas
                                                          , virtualCanvas
                                                          , assetBoundsRealC
                                                          , assetBoundsVirtC );
        break;

    case AssetType::TRACK:
        assetTypeStr = "Track";
        //controlAsset = std::make_unique<ControlAssetTrack>();
        controlAsset = std::make_unique<ControlAssetTrack>( realCanvas
                                                          , virtualCanvas
                                                          , assetBoundsRealC
                                                          , assetBoundsVirtC );
        break;

    case AssetType::TRACK_SCALE:
        assetTypeStr = "Scale";
        //controlAsset = std::make_unique<ControlAssetTrackScale>();
        controlAsset = std::make_unique<ControlAssetTrackScale>( realCanvas
                                                               , virtualCanvas
                                                               , assetBoundsRealC
                                                               , assetBoundsVirtC );
        break;

    default:
        assetTypeStr = "Error";
        break;
    }

}

Asset::~Asset()
{
}

AssetType Asset::getAssetType() const
{
    return assetType;
}

const juce::String& Asset::getAssetTypeStr() const
{
    return assetTypeStr;
}

const juce::File& Asset::getAssetFilePath() const
{
    return assetFilePath;
}

const juce::String& Asset::getAssetName() const
{
    return assetName;
}

juce::Image Asset::getAssetImage() const
{
    return assetImage;
} 

void Asset::setAssetFilePathAndLoadImage(const juce::File& filePath)
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

        //auto virtualArea = virtualCanvas;

        //int w = assetImage.getWidth();
        //int h = assetImage.getHeight();



        //if (assetType == AssetType::KNOB)
        //{
        //    // set Default size
        //    //this->assetBoundsVirtC = juce::Rectangle<int>{ 0,0,200,200 };
        //    auto imageArea = int(virtualArea.getWidth() * 0.85F);

        //    w = int(w * 0.85);
        //    h = int(h * 0.85);

        //    this->assetBoundsVirtC = virtualArea.withSizeKeepingCentre(imageArea, imageArea);
        //}
        //else if (assetType == AssetType::KNOB_SCALE)
        //{
        //    //this->assetBoundsVirtC = juce::Rectangle<int>{ 0,0,220,220 };
        //    auto imageArea = int(virtualArea.getWidth() * 0.9F);

        //    this->assetBoundsVirtC = virtualArea.withSizeKeepingCentre(imageArea, imageArea);
        //}

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

void Asset::setAssetName(const juce::String& name)
{
    this->assetName = name;
}

void Asset::makeVisible(const bool visible)
{
    this->assetVisible = visible;
}

bool Asset::getVisible() const
{
    return assetVisible;
}


void Asset::setAssetRealBounds(const juce::Rectangle<int> newBounds)
{
    // CanControlled by slider from subControl
    this->assetBoundsRealC = newBounds;
}

void Asset::setAssetVirtualBounds(const juce::Rectangle<int> newBounds)
{
    // CanControlled by drag from CanvasEdit Virtual Canvas
    this->assetBoundsVirtC = newBounds;
}

void Asset::setVirtualTopLeftPos(const juce::Point<int> newTopLeftPos, const float scaleFactor)
{
    this->assetBoundsVirtC.setPosition(newTopLeftPos);

    this->assetBoundsRealC.setPosition({ 
        int(newTopLeftPos.getX() / scaleFactor), 
        int(newTopLeftPos.getY() / scaleFactor)
        }
    );
}

void Asset::setVirtualCentrePos(const juce::Point<int> newCentrePos, const float scaleFactor)
{
    this->assetBoundsVirtC.setCentre(newCentrePos);

    this->assetBoundsRealC.setCentre({ 
        int(newCentrePos.getX() / scaleFactor), 
        int(newCentrePos.getY() / scaleFactor)
        }
    );
}

void Asset::setRealCanvas(const juce::Rectangle<int> newRealCanvas)
{
    this->realCanvas = newRealCanvas;
}

void Asset::setVirtualCanvas(const juce::Rectangle<int> newVirtualCanvas)
{
    this->virtualCanvas = newVirtualCanvas;

    int w{ virtualCanvas.getWidth() };
    int h{ virtualCanvas.getHeight() };

    auto virtualCanvasCopy = virtualCanvas;
    auto virtualAreaOfAsset = virtualCanvasCopy;

    if (assetType == AssetType::KNOB)
    {
        if (virtualCanvas.getWidth() < virtualCanvas.getHeight())
        {
            w = virtualCanvas.getWidth();
            h = w;
        }
        else
        {
            h = virtualCanvas.getHeight();
            w = h;
        }

        virtualCanvasCopy = virtualCanvas;
        virtualAreaOfAsset = virtualCanvasCopy.withSizeKeepingCentre(w, h);

        auto width = getControlAsset()->getAssetVirtualWidthPercentage() * virtualAreaOfAsset.getWidth();
        auto height = getControlAsset()->getAssetVirtualHeightPercentage() * virtualAreaOfAsset.getHeight();
        this->assetBoundsVirtC = virtualAreaOfAsset.withSizeKeepingCentre(width, height);
    }
    else if (assetType == AssetType::KNOB_SCALE)
    {
        virtualCanvasCopy = virtualCanvas;
        virtualAreaOfAsset = virtualCanvasCopy.withSizeKeepingCentre(w, h);

        auto width = getControlAsset()->getAssetVirtualWidthPercentage() * virtualAreaOfAsset.getWidth();
        auto height = getControlAsset()->getAssetVirtualHeightPercentage() * virtualAreaOfAsset.getHeight();
        this->assetBoundsVirtC = virtualAreaOfAsset.withSizeKeepingCentre(width, height);
    }

    // for Sliders asset will be different with consideration of vertical or horizontal slider
}


juce::Rectangle<int> Asset::getAssetRealBounds() const
{
    return assetBoundsRealC;
}

juce::Point<int> Asset::getAssetRealTopLeftPos() const
{
    return assetBoundsRealC.getTopLeft();
}

juce::Point<int> Asset::getAssetRealCentrePos() const
{
    return assetBoundsRealC.getCentre();
}


juce::Rectangle<int> Asset::getAssetVirtualBounds() const
{
    return assetBoundsVirtC;
}

juce::Point<int> Asset::getAssetVirtualTopLeftPos() const
{
    return assetBoundsVirtC.getTopLeft();
}

juce::Point<int> Asset::getAssetVirtualAssetCentrePos() const
{
    return assetBoundsVirtC.getCentre();
}

std::unique_ptr<ControlAsset>& Asset::getControlAsset()
{
    return controlAsset;
}


void Asset::setAngleOffset(const double newAngleOffset)
{
    this->assetAngleOffset = newAngleOffset;
}

double Asset::getAngleOffset() const
{
    return assetAngleOffset;
}
