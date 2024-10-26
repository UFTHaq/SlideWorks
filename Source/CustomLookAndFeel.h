#pragma once

#include <JuceHeader.h>

class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
	CustomLookAndFeel();
	~CustomLookAndFeel();

	// =============== ALL OVERRIDER FUNCITONS ===============
	// 
	// Override the drawDocumentWindowTitleBar to customize title bar
	void drawDocumentWindowTitleBar(juce::DocumentWindow& window, juce::Graphics& g, int w, int h, int titleSpaceX, int titleSpaceW, const juce::Image* icon, bool drawTitleTextOnLeft) override;

	// Override button draw
	void drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColor, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
	void drawButtonText(juce::Graphics& g, juce::TextButton& button, bool isMouseOver, bool isButtonDown) override;

	void drawGroupComponentOutline(juce::Graphics& g, int width, int height, const juce::String& text, const juce::Justification& position, juce::GroupComponent& group) override;

	void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle sytle, juce::Slider& slider) override;

	void drawLabel(juce::Graphics& g, juce::Label& label) override;
	void fillTextEditorBackground(juce::Graphics& g, int width, int height, juce::TextEditor& editor) override;
	void drawTextEditorOutline(juce::Graphics& g, int width, int height, juce::TextEditor& editor) override;


	// Load all fonts
	void LoadFonts();

	// Return main color palette used in the projects;
	const juce::Colour getColorTitleBar();
	const juce::Colour getColorFontTitleBar();
	const juce::Colour getColorCustomDarkest();
	const juce::Colour getColorCustomDarkGrey();
	const juce::Colour getColorCustomGrey();
	const juce::Colour getColorCustomLightGrey();
	const juce::Colour getColorCustomWhite();

	// Return Fonts
	const juce::Font getFontRobotoMono();
	const juce::Font getFontRobotoCondensed();

	const float getRoundedCornerSize();
	const float getFontSizeTitle();
	const float getFontSizeRegular();

private:
	juce::Colour colorTitleBar          { juce::Colour::fromString("#ff181818") };
	juce::Colour colorFontTitleBar      { juce::Colour::fromString("#ffc3bfbf") };
	juce::Colour colorCustomDarkest     { juce::Colour::fromString("#ff181818") };
	juce::Colour colorCustomDarkGrey    { juce::Colour::fromString("#ff2a2a2c") };
	juce::Colour colorCustomGrey        { juce::Colour::fromString("#ff535354") };
	juce::Colour colorCustomLightGrey   { juce::Colour::fromString("#ffacadaf") };
	juce::Colour colorCustomWhite       { juce::Colour::fromString("#ffffffff") };

	juce::Font fontRobotoMono           { juce::FontOptions{} };
	juce::Font fontRobotoCondensed      { juce::FontOptions{} };

	float roundedCornerSize{ 2.5F };
	float fontSizeTitle{ 21.0F };
	float fontSizeRegular{ 16.50F };
};

