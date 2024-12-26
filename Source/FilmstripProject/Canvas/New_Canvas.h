/*
  ==============================================================================

    New_Canvas.h
    Created: 10 Dec 2024 6:15:51pm
    Author:  UFTHaq

  ==============================================================================
*/

// Put this to -> New_FilmstripProject
// inherit juce::Component

#pragma once

#include <JuceHeader.h>

#include "../Source/Globals.h"
#include "../Source/EnumClass.h"
#include "../Source/CustomLookAndFeel.h"
#include "../Source/FilmstripProject/New_Asset.h"

#include "New_CanvasEdit.h"
#include "New_CanvasPreview.h"
#include "New_CanvasSimulation.h"

class New_Canvas
    : public juce::Component
{
protected:
    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};
    std::vector<std::unique_ptr<New_Asset>>& assets;  // Passing from New_FilmstripProject -> New_Canvas -> New_CanvasEdit
    FilmstripType filmstripType{};

    WorkingMode mode{ WorkingMode::EDIT_MODE };

    juce::Rectangle<int> bounds{};

    New_CanvasEdit canvasEdit;         // Default Declaration
    New_CanvasPreview canvasPreview{};
    New_CanvasSimulation canvasSimulation{};

public:
    New_Canvas(const FilmstripType& filmstripType, std::vector<std::unique_ptr<New_Asset>>& assets);
    ~New_Canvas();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void drawBackground(juce::Graphics& g);
    void setMode(WorkingMode mode);
    WorkingMode getMode() const;

    New_CanvasEdit& getCanvasEdit();
    New_CanvasPreview& getCanvasPreview();
    New_CanvasSimulation& getCanvasSimulation();
};