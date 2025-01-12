/*
  ==============================================================================

    CanvasSimulation.h
    Created: 10 Dec 2024 5:37:37pm
    Author:  UFTHaq

  ==============================================================================
*/

// Put this to -> Canvas
// inherit juce::Component

// The abstraction of Simulation of dragging KNOB OR SLIDER
// Maybe some buttons or labels

#pragma once

#include <JuceHeader.h>

#include "../Source/EnumClass.h"

class CanvasSimulation
    : public juce::Component
{
protected:
    WorkingMode mode{ WorkingMode::SIMULATION_MODE };

public:
    CanvasSimulation();
    ~CanvasSimulation();

    WorkingMode getMode() const;
};


// This will have same area as sub control edit.
// Knob:
// - setting knob control rotary vertical drag, rotary horizontal drag, rotary horizontal vertical drag. 