/*
  ==============================================================================

    Globals.h
    Created: 21 Nov 2024 11:34:13am
    Author:  UFTHaq

  ==============================================================================
*/

#pragma once

#include <memory>
#include "CustomLookAndFeel.h"

class Globals
{
public:
    static std::shared_ptr<CustomLookAndFeel> getCustomLookAndFeel();

    // Static flag to control repainting of the title bar
    static bool repaintTitleBar;
private:
    Globals() = default; // Prevent instantiation

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Globals)
};