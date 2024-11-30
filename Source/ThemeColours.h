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
	juce::Colour SlideworksBaseColour{};

	juce::Colour ButtonsID_01_ON{};
	juce::Colour ButtonsID_01_Text{};

	juce::Colour TabButtonsID_03_ON{};
	juce::Colour TabButtonsID_03_OFF{};
	juce::Colour NamingLabel{};

	juce::Colour ModeButtonsID_05_ON{};
	juce::Colour ModeButtonsID_05_OFF{};

	juce::Colour OutlineControl{};

	juce::Colour BannerFilmstripType{};

	juce::Colour CustomGroupComponent{};

	juce::Colour SliderThumbColour{};

	juce::Colour FontBlack{};
	juce::Colour FontWhite{};

	juce::Colour TransparentBlack{};
	juce::Colour TransparentWhite{};

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