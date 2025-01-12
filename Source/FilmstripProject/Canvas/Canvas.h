/*
  ==============================================================================

    Canvas.h
    Created: 10 Dec 2024 6:15:51pm
    Author:  UFTHaq

  ==============================================================================
*/

// Put this to -> FilmstripProject
// inherit juce::Component

#pragma once

#include <JuceHeader.h>

#include "../Source/Globals.h"
#include "../Source/EnumClass.h"
#include "../Source/CustomComponents/CustomLookAndFeel.h"
#include "../Source/FilmstripProject/Asset.h"
#include "../Source/FilmstripProject/MainControls/AssetButtons.h"
#include "../Source/FilmstripProject/SubControls/SubControls.h"

#include "CanvasEdit.h"
#include "CanvasPreview.h"
#include "CanvasSimulation.h"

class SubControls;

class Canvas
    : public juce::Component
{
protected:
    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};
    FilmstripType filmstripType{};

    std::vector<std::unique_ptr<Asset>>& assets;                // Hold Ref Passing from FilmstripProject -> Canvas -> CanvasEdit
    std::vector<std::unique_ptr<AssetButtons>>& assetsButtons;  // Hold Ref
    SubControls& subControls;                                   // Hold Ref

    WorkingMode mode{ WorkingMode::EDIT_MODE };

    juce::Rectangle<int> bounds{};

    CanvasEdit canvasEdit;                    // Default Declaration 
    CanvasPreview canvasPreview;              // Default Declaration 
    CanvasSimulation canvasSimulation;        // Default Declaration 

public:
    Canvas 
    (
        const FilmstripType& filmstripType
        , std::vector<std::unique_ptr<Asset>>& assets
        , std::vector<std::unique_ptr<AssetButtons>>& assetsButtons
        , SubControls& subControls
    );
    ~Canvas();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void mouseDown(const juce::MouseEvent& event) override;

    void drawBackground(juce::Graphics& g);
    void setMode(WorkingMode mode);
    WorkingMode getMode() const;

    CanvasEdit& getCanvasEdit();
    CanvasPreview& getCanvasPreview();
    CanvasSimulation& getCanvasSimulation();
};
