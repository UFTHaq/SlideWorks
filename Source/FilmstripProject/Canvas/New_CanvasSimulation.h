/*
  ==============================================================================

    New_CanvasSimulation.h
    Created: 10 Dec 2024 5:37:37pm
    Author:  UFTHaq

  ==============================================================================
*/

// Put this to -> New_Canvas
// inherit juce::Component

// The abstraction of Simulation of dragging KNOB OR SLIDER
// Maybe some buttons or labels

#pragma once

#include <JuceHeader.h>

#include "../Source/EnumClass.h"

class New_CanvasSimulation
    : public juce::Component
{
protected:
    WorkingMode mode{ WorkingMode::SIMULATION_MODE };

public:
    New_CanvasSimulation();
    ~New_CanvasSimulation();

    WorkingMode getMode() const;
};