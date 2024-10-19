#pragma once

#include <JuceHeader.h>

class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
	CustomLookAndFeel();
	~CustomLookAndFeel();

	// Override the drawDocumentWindowTitleBar to customize title bar
	void drawDocumentWindowTitleBar (juce::DocumentWindow& window, juce::Graphics& g, int w, int h, int titleSpaceX, int titleSpaceW, const juce::Image* icon, bool drawTitleTextOnLeft) override;

	// Return main color palette used in the projects;
	const juce::Colour getColorTitleBar();
	const juce::Colour getColorFontTitleBar();
	const juce::Colour getColorCustomDarkest();
	const juce::Colour getColorCustomDarkGrey();
	const juce::Colour getColorCustomGrey();
	const juce::Colour getColorCustomWhite();

private:
	juce::Colour colorTitleBar = juce::Colour::fromString("#ff181818");
	juce::Colour colorFontTitleBar = juce::Colour::fromString("#ffc3bfbf");
	juce::Colour colorCustomDarkest = juce::Colour::fromString("#ff181818");
	juce::Colour colorCustomDarkGrey = juce::Colour::fromString("#ff2a2a2c");
	juce::Colour colorCustomGrey = juce::Colour::fromString("#ffacadaf");
	juce::Colour colorCustomWhite = juce::Colour::fromString("#ffffffff");
};

