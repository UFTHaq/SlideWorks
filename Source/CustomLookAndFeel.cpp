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
			fillColor = juce::Colours::royalblue;
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


void CustomLookAndFeel::drawGroupComponentOutline(juce::Graphics& g, int width, int height, const juce::String& text, const juce::Justification& position, juce::GroupComponent& group)
{
	if (group.getName() == "DIALOG1")
	{
		//g.setColour(getColorCustomLightGrey());
		//g.drawRoundedRectangle(0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height), 10.0f, 4.0f);
		////auto outline = group.getLocalBounds();
		////outline.removeFromTop(15);
		////g.drawRoundedRectangle(outline.toFloat(), 10.0F, 6.0F);

		//// Call the default look-and-feel to draw the outline
		//g.setFont(getFontRobotoCondensed().withHeight(20.0F));
		//LookAndFeel_V4::drawGroupComponentOutline(g, width, height, text, position, group);

		//g.strokePath()

		//g.setColour(getColorCustomLightGrey());

		//auto textArea = juce::Rectangle<int>(0, -6, width, 30);  // Customize the title area
		////g.drawText(text, textArea, position);

		const float textH = 16.0f; // Height of the text
		const float indent = 3.0f; // Indentation for the outline
		const float textEdgeGap = 8.0f; // Gap around the text
		auto cornerSize = 5.0f; // Corner size for rounded edges

		// Use your custom font for the group component title
		//juce::Font f(withDefaultMetrics(FontOptions{ textH }));
		juce::Font f(getFontRobotoCondensed().withHeight(textH)); // Replace with your custom font method

		juce::Path outlinePath;
		auto x = indent;
		//auto y = f.getAscent() - 3.0f; // Y position based on font ascent
		auto y = f.getAscent() - (textH / 4); // Y position based on font ascent	// Somehow textH/4 make the text centre to line.
		auto w = juce::jmax(0.0f, (float)width - x * 2.0f);
		auto h = juce::jmax(0.0f, (float)height - y - indent);
		cornerSize = juce::jmin(cornerSize, w * 0.5f, h * 0.5f);
		auto cornerSize2 = 2.0f * cornerSize;

		// Calculate text width and position
		auto textWidth = text.isEmpty() ? 0
			: juce::jlimit(0.0f, juce::jmax(0.0f, w - cornerSize2 - textEdgeGap * 2),
				(float)juce::GlyphArrangement::getStringWidthInt(f, text) + textEdgeGap * 2.0f);
		auto textX = cornerSize + textEdgeGap;

		if (position.testFlags(juce::Justification::horizontallyCentred))
			textX = cornerSize + (w - cornerSize2 - textWidth) * 0.5f;
		else if (position.testFlags(juce::Justification::right))
			textX = w - cornerSize - textWidth - textEdgeGap;

		// Start drawing the outline path
		outlinePath.startNewSubPath(x + textX + textWidth, y);
		outlinePath.lineTo(x + w - cornerSize, y);

		outlinePath.addArc(x + w - cornerSize2, y, cornerSize2, cornerSize2, 0, juce::MathConstants<float>::halfPi);
		outlinePath.lineTo(x + w, y + h - cornerSize);

		outlinePath.addArc(x + w - cornerSize2, y + h - cornerSize2, cornerSize2, cornerSize2,
			juce::MathConstants<float>::halfPi, juce::MathConstants<float>::pi);
		outlinePath.lineTo(x + cornerSize, y + h);

		outlinePath.addArc(x, y + h - cornerSize2, cornerSize2, cornerSize2,
			juce::MathConstants<float>::pi, juce::MathConstants<float>::pi * 1.5f);
		outlinePath.lineTo(x, y + cornerSize);

		outlinePath.addArc(x, y, cornerSize2, cornerSize2,
			juce::MathConstants<float>::pi * 1.5f, juce::MathConstants<float>::twoPi);
		outlinePath.lineTo(x + textX, y);

		auto alpha = group.isEnabled() ? 1.0f : 0.5f;

		// Set color and stroke the outline path
		//g.setColour(group.findColour(juce::GroupComponent::outlineColourId).withMultipliedAlpha(alpha));
		g.setColour(getColorCustomLightGrey());
		g.strokePath(outlinePath, juce::PathStrokeType(2.0f));

		// Draw the text at the specified position
		//g.setColour(group.findColour(juce::GroupComponent::textColourId).withMultipliedAlpha(alpha));
		g.setColour(getColorCustomLightGrey().brighter());
		g.setFont(f);
		g.drawText(text, juce::roundToInt(x + textX), 0, juce::roundToInt(textWidth), juce::roundToInt(textH), juce::Justification::centred, true);
	}
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