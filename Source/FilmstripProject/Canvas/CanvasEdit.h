/*
  ==============================================================================

    CanvasEdit.h
    Created: 10 Dec 2024 5:36:56pm
    Author:  UFTHaq

  ==============================================================================
*/

// Put this to -> Canvas
// inherit juce::Component

// The abstraction of Editing
// Such:
// Can control also follow the limit from MainControl Angles or Thumb Position
// Rectangle base of Render 
// Rectangle hold the image assets, follow the total of Assets
// Can drag the rects, only in knob everying is locked dead center
// Can also be controled the size or something from SubControl
// Maybe some buttons or labels sizes and min max

#pragma once

#include <JuceHeader.h>

#include "../Source/EnumClass.h"
#include "../Source/FilmstripProject/Asset.h"


class CanvasEdit
    : public juce::Component
{
protected:
    WorkingMode mode{ WorkingMode::EDIT_MODE };
    std::vector<std::unique_ptr<Asset>>& assets;  // Passing from New_FilmstripProject -> New_Canvas -> New_CanvasEdit
    FilmstripType filmstripType{};

    int lowestContraint{};
    juce::Rectangle<int> canvasConstraint{};

    // - real canvas size
    // - Contraint max width and max height virtual canvas
    // - virtual canvas size
    // - scaling factor to fit the real canvas to virtual canvas
    // - asset also use the scale
    //

    //juce::Rectangle<int> canvasContraint{};
    juce::Rectangle<int> realCanvas{};          // max size maybe 1000 x 1000;
    juce::Rectangle<int> virtualCanvas{};
    double scaleFactor{};

public:
    CanvasEdit(const FilmstripType& filmstripType, std::vector<std::unique_ptr<Asset>>& assets);
    ~CanvasEdit();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void setupDefaultRealCanvas(const FilmstripType& filmstripType);
    void resizeCanvasAssets();
    void calculateVirtualConstraint();
    void calculateScaleFactor();
    void calculateVirtualCanvas();

    WorkingMode getMode() const;
    void setCanvasBounds(const int width, const int height);

    void setRealCanvasWidth(int w);
    void setRealCanvasHeight(int h);
    juce::Point<int> getRealCanvasWH();

    // Make drag system based on mouseDown?
};

// - What if the realCanvas is smaller than virtualCanvas?
// 
// 
// - What if the realCanvas is bigger than virtualCanvas?
// 
// - Calculate the contraint size by reduced(30). then take the lowest value either width or height
//      auto area = getLocalBounds().reduced(30);
//      if (width < height) lowest = width;
//      else lowest = height;
//      canvasContraint = area.withSizeKeepingCentre(lowest, lowest);
// 
// - Default size of 
//     knob   = realCanvas is (300 x 300)
//     slider = realCanvas is (800 x 200)
// 
// - Calculate scale factor
//   Take the longest size from realCanvas either width or height and divide to contraint
//   example width = 1000, height = 300;
//   example the contraint width and height = 400;
//   longest = width = 1000
//     scaleFactor = 400/1000 = 4/10 = 0.4F;
// 
// - Calculate the virtualCanvas
//     width = 1000 X 0.4F = 400;
//     height = 300 X 0.4F = 120;
//   then the virtualCanvas
//     virtualCanvas = canvasConstraint.withSizeKeepingCentre(width, height);
//      
// - Calculate the asset in virtualCanvas
//   - KNOB PROJECT:
//     the knob is all of it in centre automatically, then just calculate the virtualSize
//     realAssetSize, width  = 200, 
//                    height = 200;
//     virtualAssetSize, width  = 200 x 0.4F = 80;
//                       height = 200 x 0.4F = 80;
//     And this virtualAssetSize can be control to resized if hovered to the corner of virtualAsset border
//     if drag move delta (3, 2) so the virtual size will expand left right up down symetrically:
//      width  = 80 + 6 = 86;
//      height = 80 + 4 = 84;
//     can also be lock the ratio
//     if drag move delta (4, 5) so the virtual size will expand with lock ratio only based on x movement and symetri;
//      width  = 80 + 8 = 88;
//      height = 80 + 8 = 88;
//     
//   - SLIDER PROJECT:
//     can move the virtual asset
//     can also resize the virtual asset with maybe double click to activate?
//     each movement in the virtual canvas
//     example move drag (20, 6)
//     in realCanvas the asset moved (20/0.4, 6/0.4) = (50, 15)
// 
//   - DO THE ASSET NEED INHERIT JUCE::COMPONENT? maybe no
// 
//   - When load button click, from assetManager can pass the realCanvas to the asset, 
//     and if the realCanvas and or virtualCanvas changed because of realCanvas resizing, 
//     then pass through loop to setAll the realCanvas to each asset
//     
//
