#include "CustomLookAndFeel.h"

CustomLookAndFeel::CustomLookAndFeel()
{
	auto& colorscheme = getCurrentColourScheme();
	colorscheme.setUIColour(juce::LookAndFeel_V4::ColourScheme::widgetBackground, colorTitleBar);

	LoadFonts();
}

CustomLookAndFeel::~CustomLookAndFeel()
{

}

////////////////////////// ========= OVERRIDER FUNTIONS ========= //////////////////////////
void CustomLookAndFeel::drawDocumentWindowTitleBar (juce::DocumentWindow& window, 
													juce::Graphics& g, int w, int h, int titleSpaceX, int titleSpaceW, 
													const juce::Image* icon, bool drawTitleTextOnLeft)
{
	(void)titleSpaceX;
	(void)titleSpaceW;
	(void)icon;
	(void)drawTitleTextOnLeft;

	//auto isActive = window.isActiveWindow();

	if (w * h == 0) return;

	// Coloring the title bar
	g.fillAll(getColorTitleBar());

	// Draw and coloring the title text
	g.setColour(getColorFontTitleBar());
	g.setFont(getFontRobotoMono().withHeight(20.0F));
	g.drawText(window.getName(), juce::Rectangle{ 0, 0, w, h }.toFloat(), juce::Justification::centred, true);
}


////////////////////////// ========= LOAD FONTS ========= //////////////////////////
void CustomLookAndFeel::LoadFonts()
{
	auto fontRobotoMonoData         { BinaryData::RobotoMonoMedium_ttf };
	auto fontRobotoMonoSize         { BinaryData::RobotoMonoMedium_ttfSize };

	auto fontRobotoCondensedData    { BinaryData::RobotoCondensedSemiBold_ttf };
	auto fontRobotoCondensedSize    { BinaryData::RobotoCondensedSemiBold_ttfSize };

	juce::Typeface::Ptr customFontRobotoMono      { juce::Typeface::createSystemTypefaceFor(fontRobotoMonoData, fontRobotoMonoSize) };
	juce::Typeface::Ptr customFontRobotoCondensed { juce::Typeface::createSystemTypefaceFor(fontRobotoCondensedData, fontRobotoCondensedSize) };

	fontRobotoMono      = juce::FontOptions{ customFontRobotoMono };
	fontRobotoCondensed = juce::FontOptions{ customFontRobotoCondensed };
}


////////////////////////// ========= GET COLOURS ========= //////////////////////////
const juce::Colour CustomLookAndFeel::getColorTitleBar()
{
	return colorTitleBar;
}

const juce::Colour CustomLookAndFeel::getColorFontTitleBar()
{
	return colorFontTitleBar;
}

const juce::Colour CustomLookAndFeel::getColorCustomDarkest()
{
	return colorCustomDarkest;
}

const juce::Colour CustomLookAndFeel::getColorCustomDarkGrey()
{
	return colorCustomDarkGrey;
}

const juce::Colour CustomLookAndFeel::getColorCustomGrey()
{
	return colorCustomGrey;
}

const juce::Colour CustomLookAndFeel::getColorCustomWhite()
{
	return colorCustomWhite;
}

////////////////////////// ========= GET FONTS ========= //////////////////////////
const juce::Font CustomLookAndFeel::getFontRobotoMono()
{
	return fontRobotoMono;
}

const juce::Font CustomLookAndFeel::getFontRobotoCondensed()
{
	return fontRobotoCondensed;
}