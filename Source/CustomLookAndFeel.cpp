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
	g.setFont(getFontRobotoMono().withHeight(getFontSizeTitle()));
	g.drawText(window.getName(), juce::Rectangle{ 0, 0, w, h }.toFloat(), juce::Justification::centred, true);
}

void CustomLookAndFeel::drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColor, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
	(void)backgroundColor;

	const juce::String buttonName = button.getName();
	juce::Colour fillColor{};

	if (buttonName == "knobWorks" || buttonName == "sliderWorks")
	{
		if (button.getToggleState() == 1)
		{
			fillColor = getColorCustomLightGrey();

		} 
		else if (shouldDrawButtonAsDown)
		{
			fillColor = getColorCustomLightGrey().darker(0.2F);
		}
		else
		{
			fillColor = getColorCustomGrey();

			if (shouldDrawButtonAsHighlighted)
			{
				fillColor = getColorCustomGrey().brighter(0.2F);
			}
		}
	}
	else if (buttonName == "BROWSE")
	{
		fillColor = getColorCustomLightGrey();

		if (shouldDrawButtonAsDown)
		{
			fillColor = getColorCustomLightGrey().darker(0.2F);
		} 
		else if (shouldDrawButtonAsHighlighted)
		{
			fillColor = fillColor.brighter(0.2F);
		}
	}

	g.setColour(fillColor);
	g.fillRoundedRectangle(button.getLocalBounds().toFloat(), getRoundedCornerSize());
}

void CustomLookAndFeel::drawButtonText(juce::Graphics& g, juce::TextButton& button, bool isMouseOver, bool isButtonDown)
{
	const juce::String buttonText = button.getButtonText();
	juce::Colour textColor{};

	if (buttonText == "KNOB" || buttonText == "SLIDER")
	{
		if (button.getToggleState() == 1)
		{
			textColor = getColorCustomDarkest();
		}
		else
		{
			textColor = getColorCustomWhite();
		}
	}
	else if (buttonText == "BROWSE")
	{
		textColor = getColorCustomDarkest();

		if (isButtonDown)
		{
			textColor = getColorCustomWhite();
		}
		else if (isMouseOver)
		{
			textColor = textColor;
		}
	}

	g.setFont(getFontRobotoCondensed().withHeight(getFontSizeRegular()));
	g.setColour(textColor);
	g.drawFittedText(buttonText, button.getLocalBounds(), juce::Justification::centred, 1);
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

const juce::Colour CustomLookAndFeel::getColorCustomLightGrey()
{
	return colorCustomLightGrey;
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



//////////////////////////////////////////////////////////////////////////////////
const float CustomLookAndFeel::getRoundedCornerSize()
{
	return roundedCornerSize;
}

const float CustomLookAndFeel::getFontSizeTitle()
{
	return fontSizeTitle;
}

const float CustomLookAndFeel::getFontSizeRegular()
{
	return fontSizeRegular;
}