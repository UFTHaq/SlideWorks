/*
  ==============================================================================

    New_CanvasEdit.h
    Created: 10 Dec 2024 5:36:56pm
    Author:  UFTHaq

  ==============================================================================
*/

// Put this to -> New_Canvas
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

class New_CanvasEdit
    : public juce::Component
{
protected:
    WorkingMode mode{ WorkingMode::EDIT_MODE };

public:
    New_CanvasEdit();
    ~New_CanvasEdit();

    WorkingMode getMode() const;
};