/*
  ==============================================================================

    ThemeColours.h
    Created: 20 Nov 2024 5:52:43pm
    Author:  UFTHaq

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

struct ThemeColours
{
	juce::Colour TitleBar{};
	juce::Colour FontTitleBar{};
	juce::Colour BackgroundColour{};
	juce::Colour Page_1{};

	juce::Colour ButtonsID_01{};
	juce::Colour ButtonsID_01_Text{};

	juce::Colour CustomGroupComponent{};

	juce::Colour FontBlack{};
	juce::Colour FontWhite{};

	juce::Colour CustomDarkest{};
	juce::Colour CustomDarkGrey{};
	juce::Colour CustomGrey{};
	juce::Colour CustomLightGrey{};
	juce::Colour CustomWhite{};
	juce::Colour CustomTransparent{};
};


enum class ThemeType
{
	OfficeLight,
	DarkNight
};