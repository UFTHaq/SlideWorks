/*
  ==============================================================================

    CanvasEdit.cpp
    Created: 10 Dec 2024 5:36:56pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "CanvasEdit.h"

CanvasEdit::CanvasEdit(const FilmstripType& type, std::vector<std::unique_ptr<Asset>>& assets)
    : filmstripType(type), assets(assets)
{
    setupDefaultRealCanvas(type);

    calculateVirtualConstraint();

    setupNewAsset();
}

CanvasEdit::~CanvasEdit()
{
}

void CanvasEdit::paint(juce::Graphics& g)
{
    //g.setColour(juce::Colours::black);
    //g.fillRoundedRectangle(getLocalBounds().toFloat(), 1);

    //g.setColour(juce::Colours::black.brighter());
    //g.drawRoundedRectangle(canvasConstraint.toFloat(), 0, 0.2F);

    auto bounds = virtualCanvas;
    
    g.setColour(outlineColor);
    g.drawRoundedRectangle(bounds.toFloat().reduced(0.4F), 0, 0.25F);

    //DBG("Canvas_Edit paint : " << bounds.toString());

    // Iterate backwards
    for (auto it = assets.rbegin(); it != assets.rend(); it++)
    {
        auto& asset = *it;

        //asset->getControlAsset()->onVirtBoundsChange = [this]()
        //    {
        //        repaint();
        //    };

        if (asset->getVisible())
        {
            g.saveState();

            if (asset->getControlAsset()->isAssetCanChangeColor() == true)
            {
                g.setColour(asset->getControlAsset()->getAssetAlphaColor());
                g.drawImage(asset->getAssetImage(), asset->getAssetVirtualBounds().toFloat(), juce::RectanglePlacement::stretchToFit, true);
            }
            else
            {
                g.drawImage(asset->getAssetImage(), asset->getAssetVirtualBounds().toFloat(), juce::RectanglePlacement::stretchToFit, false);
            }
            g.restoreState();

            //g.drawImage(asset->getAssetImage(), asset->getAssetVirtualBounds().toFloat(), juce::RectanglePlacement::centred);
            //g.drawImage(asset->getAssetImage(), asset->getAssetVirtualBounds().toFloat(), juce::RectanglePlacement::stretchToFit);
            //g.drawImage(asset->getAssetImage(), virtualCanvas.toFloat(), juce::RectanglePlacement::centred);
            // Need to make the getAssetsVirtualBounds to works.
        }
    }
}

void CanvasEdit::resized()
{
    calculateVirtualConstraint();

    calculateScaleFactor();

    calculateVirtualCanvas();

    //resizeCanvasAssets();

    //calculateRealCanvas()? or 
    //just resizing the realCanvas through member func and invoke the calculate virtualCanvas


    for (auto& asset : assets)
    {
        if (filmstripType == FilmstripType::KNOB)
        {
            resizeCanvasAssets();

            //asset->setVirtualBounds({ 0,0,asset->getAssetImage().getWidth(), asset->getAssetImage().getHeight() });

            // all asset should be in center
            //asset->setVirtualCentrePos(virtualCanvas.getCentre(), scaleFactor);
        }
        else
        {
            resizeCanvasAssets();
            // only track will be in center?
        }
    }


    //// Set the asset to have coordinate based on here
    //for (auto& asset : assets)
    //{
    //    auto assetBounds = asset->getAssetRealBounds();

    //    auto assetBoundsHere = canvasConstraint;
    //    //assetBoundsHere = assetBoundsHere.withSizeKeepingCentre(assetBounds.getWidth(), assetBounds.getHeight());
    //    //assetBoundsHere = assetBoundsHere.withSizeKeepingCentre(200, 200);
    //    assetBoundsHere = assetBoundsHere.withSizeKeepingCentre(assetBounds.getWidth(), assetBounds.getHeight());

    //    //asset->setAssetVirtualBounds(assetBoundsHere);
    //}

    calculateAllAssetRealVirtualBounds();
}

void CanvasEdit::calculateAllAssetRealVirtualBounds()
{
    for (auto& asset : assets)
    {
        asset->getControlAsset()->calculateAssetRealAndVirtualBounds();
    }
}

void CanvasEdit::setupDefaultRealCanvas(const FilmstripType& type)
{
    switch (type)
    {
    case FilmstripType::KNOB:
        realCanvas = { 0,0,200,200 };
        break;
    case FilmstripType::SLIDER:
        realCanvas = { 0,0,800,150 };
        //realCanvas = { 0,0,150,800 };
        break;
    default:
        realCanvas = {0,0,0,0};
        break;
    }
}

void CanvasEdit::resizeCanvasAssets()
{
    for (auto& asset : assets)
    {
        asset->setRealCanvas(realCanvas);
        asset->setVirtualCanvas(virtualCanvas);
    }
}

void CanvasEdit::calculateVirtualConstraint()
{
    auto area = getLocalBounds().reduced(20);

    if (filmstripType == FilmstripType::KNOB)
    {
        if (area.getWidth() < area.getHeight()) lowestContraint = area.getWidth();
        else lowestContraint = area.getHeight();

        canvasConstraint = area.withSizeKeepingCentre(lowestContraint, lowestContraint);
    }
    else
    {
        canvasConstraint = area;
    }

    //DBG("Canvas_Edit setup : " << canvasConstraint.toString());

    // TODO:
    // - constraint if project is Slider, and if vertical or horizontal
}

void CanvasEdit::calculateScaleFactor()
{
    // - Calculate scale factor
    //   Take the longest size from realCanvas either width or height and divide to contraint
    //   example width = 1000, height = 300;
    //   example the contraint width and height = 400;
    //   longest = width = 1000
    //     scaleFactor = 400/1000 = 4/10 = 0.4F;

    int longestRealCanvas{};
    int longestVirtConstraint{};

    if (realCanvas.getWidth() > realCanvas.getHeight()) longestRealCanvas = realCanvas.getWidth();
    else longestRealCanvas = realCanvas.getHeight();

    if (canvasConstraint.getWidth() > canvasConstraint.getHeight()) longestVirtConstraint = canvasConstraint.getWidth();
    else longestVirtConstraint = canvasConstraint.getHeight();

    scaleFactor = double(longestVirtConstraint) / longestRealCanvas;

    if (filmstripType == FilmstripType::SLIDER)
    {
        double shortestConstraint{};
        if (realCanvas.getHeight() > realCanvas.getWidth())
            shortestConstraint = canvasConstraint.getHeight();
        else
            shortestConstraint = canvasConstraint.getWidth();

        scaleFactor = double(shortestConstraint) / longestRealCanvas;
    }

    // if slider vertical maka pembilang virt constraint bukan terpanjang. tapi constraintHeight
    // if slider horizontal maka pembilang virt constraint adalah constraintWidth

}

void CanvasEdit::calculateVirtualCanvas()
{
    // - Calculate the virtualCanvas
    //     width = 1000 X 0.4F = 400;
    //     height = 300 X 0.4F = 120;
    //   then the virtualCanvas
    //     virtualCanvas = canvasConstraint.withSizeKeepingCentre(width, height);

    int width = int(realCanvas.getWidth() * scaleFactor);
    int height = int(realCanvas.getHeight() * scaleFactor);
    virtualCanvas = canvasConstraint.withSizeKeepingCentre(width, height);
}

WorkingMode CanvasEdit::getMode() const
{
    return mode;
}

void CanvasEdit::setCanvasBounds(const int width, const int height)
{
    // Only need widht and height cause this will always in centred
    canvasConstraint = canvasConstraint.withSizeKeepingCentre(width, height);
}

void CanvasEdit::setRealCanvasWidth(int w)
{
    realCanvas.setWidth(w);

    calculateVirtualConstraint();

    calculateScaleFactor();

    calculateVirtualCanvas();

    resizeCanvasAssets();
    
    repaint();
}

void CanvasEdit::setRealCanvasHeight(int h)
{
    realCanvas.setHeight(h);

    calculateVirtualConstraint();

    calculateScaleFactor();

    calculateVirtualCanvas();

    resizeCanvasAssets();

    repaint();
}

juce::Point<int> CanvasEdit::getRealCanvasWH() const
{
    return juce::Point<int>{ realCanvas.getWidth(), realCanvas.getHeight() };
}

void CanvasEdit::setVirtualCanvasOutlineColor(const juce::Colour newColor)
{
    auto color = newColor;

    float luminance = (0.2126F * color.getRed()) +
        (0.7152F * color.getGreen()) +
        (0.0722F * color.getBlue());

    auto autoColor{ (luminance > 128.0F) ? juce::Colours::black : juce::Colours::white };

    this->outlineColor = autoColor;
}

void CanvasEdit::setupNewAsset()
{
    for (auto& asset : assets)
    {
        asset->getControlAsset()->onColorChange = [this]()
            {
                repaint();
            };

        asset->getControlAsset()->onVirtBoundsChange = [this]()
            {
                repaint();
            };
    }
}
