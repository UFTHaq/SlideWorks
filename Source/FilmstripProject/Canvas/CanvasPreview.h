/*
  ==============================================================================

    CanvasPreview.h
    Created: 10 Dec 2024 5:37:14pm
    Author:  UFTHaq

  ==============================================================================
*/

// Put this to -> Canvas
// inherit juce::Component

// The abstraction of Preview the Filmstrip
// Such:
// Rectangle base of Filmstrip project result like in Zen Pixel
// Maybe some buttons or labels
// If controls is changed in preview mode, then it will open Apply Change or Refresh button

// juce::TextButton Refresh

#pragma once

#include <JuceHeader.h>

#include "../Source/EnumClass.h"

class CanvasPreview
    : public juce::Component
{
protected:
    WorkingMode mode{ WorkingMode::PREVIEW_MODE };


public:
    CanvasPreview();
    ~CanvasPreview();

    WorkingMode getMode() const;
};