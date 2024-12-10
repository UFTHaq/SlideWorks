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
//   - No active in Knob, Lighting and Canvas
//   - No active in Slider, Lighting and Canvas with 
//       Orientation of Slider such: Vertical or Horizontal Slider 
//   - active: Knob, Knob
//   - active: Scale, Scale
//   - active: Track, Track
//   - active: Thumb, Thumb
//   - active: Generated Scale
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
