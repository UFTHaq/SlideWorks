#pragma once

#include <JuceHeader.h>
#include "ThemeColours.h"

class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
	CustomLookAndFeel();
	~CustomLookAndFeel();

	// =============== ALL OVERRIDER FUNCITONS ===============
	// 
	// Override the drawDocumentWindowTitleBar to customize title bar
	juce::Button* createDocumentWindowButton(int buttonType) override;
	void positionDocumentWindowButtons(juce::DocumentWindow&,
		int titleBarX, int titleBarY,
		int titleBarW, int titleBarH,
		juce::Button* minimiseButton,
		juce::Button* maximiseButton,
		juce::Button* closeButton,
		bool positionTitleBarButtonsOnLeft) override;
	void drawDocumentWindowTitleBar(juce::DocumentWindow& window, juce::Graphics& g, int w, int h, int titleSpaceX, int titleSpaceW, const juce::Image* icon, bool drawTitleTextOnLeft) override;

	// Override button draw
	void drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColor, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
	void drawButtonText(juce::Graphics& g, juce::TextButton& button, bool isMouseOver, bool isButtonDown) override;

	void drawGroupComponentOutline(juce::Graphics& g, int width, int height, const juce::String& text, const juce::Justification& position, juce::GroupComponent& group) override;

	void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle sytle, juce::Slider& slider) override;
	void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;

	void drawLabel(juce::Graphics& g, juce::Label& label) override;
	void fillTextEditorBackground(juce::Graphics& g, int width, int height, juce::TextEditor& editor) override;
	void drawTextEditorOutline(juce::Graphics& g, int width, int height, juce::TextEditor& editor) override;

	// Load all fonts
	void LoadFonts();

	void loadImages();

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
	const juce::Font getFontRobotoCondensedBold();
	const juce::Font getFontRobotoCondensedRegular();

	const float getRoundedCornerSize();
	const float getFontSizeTitle();
	const float getFontSizeRegular();


	
	void setSimulationKnobImage(juce::Image image, int totalFrames, bool isVertical, double startAngle, double endAngle);
	void ClearSimulationKnobImage();
	void setSimulationKnobScaleImage(juce::Image image);
	void ClearSimulationKnobScaleImage();

	void setFilmStripKnob(juce::Image image);

	void setTheme(ThemeType themeType);
	const ThemeType& getCurrentThemeType();
	const ThemeColours& getCurrentTheme();

private:

	ThemeColours OfficeLightTheme 
	{
		.TitleBar          = juce::Colour::fromString("#ff0063b1"),
		.FontTitleBar      = juce::Colour::fromString("#ffffffff"),
		.ButtonsID_01      = juce::Colour::fromString("#ffe1e2e6"),
		.ButtonsID_01_Text = juce::Colour::fromString("#ff262525"),
		.FontBlack         = juce::Colour::fromString("#ff262525"),
		.CustomDarkest     = juce::Colour::fromString("#ff181818"),
		.CustomDarkGrey    = juce::Colour::fromString("#ff2a2a2c"),
		.CustomGrey        = juce::Colour::fromString("#ff535354"),
		.CustomLightGrey   = juce::Colour::fromString("#ffacadaf"),
		.CustomWhite       = juce::Colour::fromString("#ffffffff")
	};

	ThemeColours DarkNightTheme
	{
		.TitleBar          = juce::Colour::fromString("#ff181818"),
		.FontTitleBar      = juce::Colour::fromString("#ffffffff"),
		.ButtonsID_01      = juce::Colour::fromString("#ff181818"),
		.ButtonsID_01_Text = juce::Colour::fromString("#ffffffff"),
		.CustomDarkest     = juce::Colour::fromString("#ff181818"),
		.CustomDarkGrey    = juce::Colour::fromString("#ff2a2a2c"),
		.CustomGrey        = juce::Colour::fromString("#ff535354"),
		.CustomLightGrey   = juce::Colour::fromString("#ffacadaf"),
		.CustomWhite       = juce::Colour::fromString("#ff2a2a2c")
	};

	ThemeColours themeColoursNow{ OfficeLightTheme };
	ThemeType themeTypeNow{ ThemeType::OfficeLight };

	//juce::Colour colorTitleBar          { juce::Colour::fromString("#ff181818") };
	juce::Colour colorTitleBar          { juce::Colour::fromString("#ff0063B1") };
	//juce::Colour colorTitleBar          { juce::Colour::fromString("#ff185ABD") };
	//juce::Colour colorFontTitleBar      { juce::Colour::fromString("#ffc3bfbf") };
	juce::Colour colorFontTitleBar      { juce::Colour::fromString("#ffffffff") };
	juce::Colour colorCustomDarkest     { juce::Colour::fromString("#ff181818") };
	juce::Colour colorCustomDarkGrey    { juce::Colour::fromString("#ff2a2a2c") };
	juce::Colour colorCustomGrey        { juce::Colour::fromString("#ff535354") };
	juce::Colour colorCustomLightGrey   { juce::Colour::fromString("#ffacadaf") };
	juce::Colour colorCustomWhite       { juce::Colour::fromString("#ffffffff") };

	juce::Font fontRobotoMono             { juce::FontOptions{} };
	juce::Font fontRobotoCondensedBold    { juce::FontOptions{} };
	juce::Font fontRobotoCondensedRegular { juce::FontOptions{} };

	float roundedCornerSize{ 2.5F };
	float fontSizeTitle{ 19.0F };
	//float fontSizeRegular{ 16.50F };
	float fontSizeRegular{ 16.0F };

	juce::Image knobScale{};

	juce::Image simulationKnobImage{};
	juce::Image simulationKnobScale{};
	int simulationKnobTotalFrames{};
	bool simulationKnobIsVertical{};
};

