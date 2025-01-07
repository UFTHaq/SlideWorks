/*
  ==============================================================================

    New_SubControls.h
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

//#include "../Source/FilmstripProject/Canvas/New_Canvas.h"

#include "New_ControlLighting.h"
#include "New_ControlCanvas.h"

#include "New_ControlAsset.h"

#include "New_ControlAssetKnob.h"
#include "New_ControlAssetKnobScale.h"
#include "New_ControlAssetThumb.h"
#include "New_ControlAssetTrack.h"
#include "New_ControlAssetTrackScale.h"
#include "New_ControlSliderStyle.h"

// FORWARD DECLARATION OF OTHER CLASS CAUSE OF CIRCULAR DEPENDENCIES CAUSE OF NEEEDED EACH OTHER REFERENCE
//class New_Canvas;
//class ControlCanvas;

class New_SubControls
    : public juce::Component
{
protected:
    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};
    //New_Canvas* canvas;    // Hold reference

    FilmstripType filmstripType{};

    juce::Rectangle<int> bounds{};

    juce::Viewport subControlViewport{};
    juce::Component subControlContainer{};

    ControlLighting controlLighting;              // Default declaration
    ControlCanvas controlCanvas{};                // Default declaration
    ControlSliderStyle controlSliderStyle{};

    int controlLightingHeight{};
    int controlCanvasHeight{};
    int controlSliderStyleHeight{};

public:
    //New_SubControls(const FilmstripType& filmstripType, New_Canvas& canvas);
    New_SubControls(const FilmstripType& filmstripType);
    ~New_SubControls();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void drawBackground(juce::Graphics& g);

    void setupViewportAndContainer();
    void setupSubControlsBase(const FilmstripType& filmstripType);

    void resizeViewport();
    void resizeContainer();

    void displayDefaultSubControl();
    void displayToSubControl(std::unique_ptr<ControlAsset>& controlAsset);
    void removeFromSubControl(std::unique_ptr<ControlAsset>& controlAsset);
};
