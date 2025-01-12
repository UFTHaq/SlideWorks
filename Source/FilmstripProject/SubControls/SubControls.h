/*
  ==============================================================================

    SubControls.h
    Created: 10 Dec 2024 5:46:26pm
    Author:  UFTHaq

  ==============================================================================
*/

// Put this to -> New_FilmstripProject
// inherit juce::Component
// Only On when in Edit Mode
// Disabled when not in Edit Mode

// Container
// viewport for CustomGroupComponent Implementations
// Can control to reload what implementation would be in viewport 
//   based on the active asset, such penpot editing:
//   - No active/select in Knob, will display -> Lighting and Canvas
//   - No active/select in Slider, will display -> Lighting and Canvas with 
//       Orientation of Slider such: Vertical or Horizontal Slider 
//   - active: Knob, Knob
//   - active: Scale, Scale
//   - active: Track, Track
//   - active: Thumb, Thumb
//   - active: Generated Scale
//
//   by doing resetting reload the setBounds of each ClassControl using big long rect
//   example: if (nothing active)
//              Lightrect = longRect.removeFromTop()
//              Canvasrect = longRect.removeFromTop()
//            if (knob active)
//              Knobrect = longRect.removeFromTop()
//              Canvasrect = longRect.removeFromTop()
//     
// And the SubControls member can control the Canvas Edit such Size or Color

#pragma once

#include <JuceHeader.h>

#include "../Source/EnumClass.h"
#include "../Source/Globals.h"
#include "../Source/CustomComponents/CustomLookAndFeel.h"
#include "../Source/CustomComponents/Easing.h"

//#include "ControlAsset.h"

#include "ControlLighting.h"
#include "ControlCanvas.h"
#include "ControlSliderStyle.h"

#include "ControlAssetKnob.h"
#include "ControlAssetKnobScale.h"
#include "ControlAssetThumb.h"
#include "ControlAssetTrack.h"
#include "ControlAssetTrackScale.h"

//#include "../Source/FilmstripProject/Canvas/Canvas.h"
//
//class Canvas;
class ControlCanvas;

class SubControls
    : public juce::Component
{
protected:
    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};
    FilmstripType filmstripType{};

    //Canvas* canvas;                                                 // Hold Ref

    juce::Rectangle<int> bounds{};

    juce::Viewport subControlViewport{};
    juce::Component subControlContainer{};

    ControlSliderStyle& controlSliderStyle;          // Hold Ref
    ControlLighting& controlLighting;                // Hold Ref
    ControlCanvas& controlCanvas;                    // Hold Ref

    int controlLightingHeight{};
    int controlCanvasHeight{};
    int controlSliderStyleHeight{};

public:
    SubControls
    (
        const FilmstripType& type
        , ControlSliderStyle& controlSliderStyle
        , ControlLighting& controlLighting
        , ControlCanvas& controlCanvas
    );
    ~SubControls();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void drawBackground(juce::Graphics& g);

    void setupViewportAndContainer();
    void setupSubControlsBase(const FilmstripType& type);

    void resizeViewport();
    void resizeContainer();

    void displayDefaultSubControl();
    void displayToSubControl(std::unique_ptr<ControlAsset>& controlAsset);
    void removeFromSubControl(std::unique_ptr<ControlAsset>& controlAsset);
};
