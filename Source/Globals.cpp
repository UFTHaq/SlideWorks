/*
  ==============================================================================

    Globals.cpp
    Created: 21 Nov 2024 11:34:13am
    Author:  UFTHaq

  ==============================================================================
*/

#include "Globals.h"

// Define the static shared_ptr for the singleton.
std::shared_ptr<CustomLookAndFeel> Globals::getCustomLookAndFeel()
{
    // Initialize the shared_ptr only once and reuse it.
    static auto globalLookAndFeel = std::make_shared<CustomLookAndFeel>();
    return globalLookAndFeel;
}

bool Globals::repaintTitleBar = false;