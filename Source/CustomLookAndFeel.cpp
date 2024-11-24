#include "CustomLookAndFeel.h"
#include "Globals.h"


class LookAndFeel_V4_DocumentWindowButton final : public juce::Button,
	                                              public CustomLookAndFeel
{
public:
	LookAndFeel_V4_DocumentWindowButton(const juce::String& name, juce::Colour c, const juce::Path& normal, const juce::Path& toggled)
		: Button(name), colour(c), normalShape(normal), toggledShape(toggled)
	{
	}

	void paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
	{
		auto background = juce::Colours::grey;

		if (auto* rw = findParentComponentOfClass<juce::ResizableWindow>())
			if (auto lf = dynamic_cast<juce::LookAndFeel_V4*> (&rw->getLookAndFeel()))
				background = lf->getCurrentColourScheme().getUIColour(juce::LookAndFeel_V4::ColourScheme::widgetBackground);

		g.fillAll(background);

		g.setColour((!isEnabled() || shouldDrawButtonAsDown) ? colour.withAlpha(0.6f) : colour);

		if (shouldDrawButtonAsHighlighted)
		{
			g.fillAll();
			g.setColour(background);
		}

		auto& p = getToggleState() ? toggledShape : normalShape;

		auto reducedRect = juce::Justification(juce::Justification::centred)
			.appliedToRectangle(juce::Rectangle<int>(getHeight(), getHeight()), getLocalBounds())
			.toFloat()
			.reduced((float)getHeight() * 0.3f);
		g.setColour(getColorCustomWhite());
		g.fillPath(p, p.getTransformToScaleToFit(reducedRect, true));
	}

private:
	juce::Colour colour;
	juce::Path normalShape, toggledShape;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LookAndFeel_V4_DocumentWindowButton)
};


////////////////////////// ========= CUSTOM LOOKANDFEEL CONSTRUCTOR ========= //////////////////////////
CustomLookAndFeel::CustomLookAndFeel()
{
	auto& colorscheme = getCurrentColourScheme();
	colorscheme.setUIColour(juce::LookAndFeel_V4::ColourScheme::widgetBackground, getCurrentTheme().TitleBar);

	LoadFonts();
	loadImages();
}

CustomLookAndFeel::~CustomLookAndFeel()
{

}

std::vector<std::unique_ptr<LookAndFeel_V4_DocumentWindowButton>> docsdf;

////////////////////////// ========= OVERRIDER FUNTIONS ========= //////////////////////////
juce::Button* CustomLookAndFeel::createDocumentWindowButton(int buttonType)
{
	juce::Path shape;
	auto crossThickness = 0.135F;

	if (buttonType == juce::DocumentWindow::closeButton)
	{
		shape.addLineSegment({ 0.0F, 0.0F, 1.0F, 1.0F }, crossThickness);
		shape.addLineSegment({ 1.0F, 0.0F, 0.0F, 1.0F }, crossThickness);

		return new LookAndFeel_V4_DocumentWindowButton("close", juce::Colours::red.darker(0.1F), shape, shape);
	}
	else if (buttonType == juce::DocumentWindow::minimiseButton)
	{
		shape.addLineSegment({ 0.0F, 0.5F, 1.0F, 0.5F }, crossThickness);

		return new LookAndFeel_V4_DocumentWindowButton("minimise", getCurrentTheme().CustomWhite.withAlpha(0.1F), shape, shape);
	}
	else if (buttonType == juce::DocumentWindow::maximiseButton)
	{
		crossThickness = 0.125F;
		shape.addLineSegment({ 0.0F, 0.0F, 1.0F, 0.0F }, crossThickness);
		shape.addLineSegment({ 1.0F, 0.0F, 1.0F, 1.0F }, crossThickness);
		shape.addLineSegment({ 1.0F, 1.0F, 0.0F, 1.0F }, crossThickness);
		shape.addLineSegment({ 0.0F, 1.0F, 0.0F, 0.0F }, crossThickness);

		juce::Path fullscreenShape;
		fullscreenShape.startNewSubPath(45.0F, 100.0F);
		fullscreenShape.lineTo(0.0F, 100.0F);
		fullscreenShape.lineTo(0.0F, 0.0F);
		fullscreenShape.lineTo(100.0F, 0.0F);
		fullscreenShape.lineTo(100.0F, 45.0F);
		fullscreenShape.addRectangle(45.0F, 45.0F, 100.0F, 100.0F);
		juce::PathStrokeType(15.0F).createStrokedPath(fullscreenShape, fullscreenShape);

		return new LookAndFeel_V4_DocumentWindowButton("maximise", getCurrentTheme().CustomWhite.withAlpha(0.1F), shape, fullscreenShape);
	}

	jassertfalse;
	return nullptr;
}

void CustomLookAndFeel::positionDocumentWindowButtons(juce::DocumentWindow&, int titleBarX, int titleBarY, int titleBarW, int titleBarH, juce::Button* minimiseButton, juce::Button* maximiseButton, juce::Button* closeButton, bool positionTitleBarButtonsOnLeft)
{
	auto buttonW = static_cast<int> (titleBarH * 1.2);

	auto x = positionTitleBarButtonsOnLeft ? titleBarX
		: titleBarX + titleBarW - buttonW;

	if (closeButton != nullptr)
	{
		closeButton->setBounds(x, titleBarY, buttonW, titleBarH);
		x += positionTitleBarButtonsOnLeft ? buttonW : -buttonW;
	}

	if (positionTitleBarButtonsOnLeft)
		std::swap(minimiseButton, maximiseButton);

	if (maximiseButton != nullptr)
	{
		maximiseButton->setBounds(x, titleBarY, buttonW, titleBarH);
		x += positionTitleBarButtonsOnLeft ? buttonW : -buttonW;
	}

	if (minimiseButton != nullptr)
		minimiseButton->setBounds(x, titleBarY, buttonW, titleBarH);
}

void CustomLookAndFeel::drawDocumentWindowTitleBar (juce::DocumentWindow& window, 
													juce::Graphics& g, int w, int h, int titleSpaceX, int titleSpaceW, 
													const juce::Image* icon, bool drawTitleTextOnLeft)
{
	(void)titleSpaceX;
	(void)titleSpaceW;
	(void)icon;
	(void)drawTitleTextOnLeft;

	//auto isActive = window.isActiveWindow();

	if (Globals::repaintTitleBar == true)
	{
		Globals::repaintTitleBar = false;

		window.repaint();
	}

	if (w * h == 0) return;

	// Coloring the title bar
	//g.fillAll(getColorTitleBar());
	g.fillAll(getCurrentTheme().TitleBar);

	// Draw and coloring the title text
	//g.setColour(getColorFontTitleBar());
	g.setColour(getCurrentTheme().FontTitleBar);
	//g.setFont(getFontRobotoMono().withHeight(getFontSizeTitle()));
	g.setFont(getFontRobotoCondensedBold().withHeight(getFontSizeTitle()));
	//g.drawText(window.getName(), juce::Rectangle{ 0, 0, w, h }.toFloat(), juce::Justification::centred, true);
	g.drawText(window.getName().toUpperCase(), juce::Rectangle{0, 0, w, h}.toFloat(), juce::Justification::centred, true);
	//g.drawText(window.getName().toUpperCase(), juce::Rectangle{10, 0, w-10, h}.toFloat(), juce::Justification::centredLeft, true);
}

void CustomLookAndFeel::drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColor, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
	(void)backgroundColor;

	const juce::String buttonName = button.getName();
	const juce::String buttonID = button.getComponentID();
	juce::Colour fillColor{};
	juce::Colour outlineColor{};
	float cornerSize{};
	float outlineThick{};

	if (buttonID == "Buttons_ID_01_SW")
	{
		cornerSize = 1;

		//if (button.getToggleState() == 1)
		//{
		//	fillColor = getColorCustomLightGrey();

		//}

		outlineColor = getColorCustomGrey();
		outlineThick = 0.4F;

		if (shouldDrawButtonAsDown)
		{
			fillColor = getColorTitleBar();
		}
		else
		{
			fillColor = themeColoursNow.ButtonsID_01;

			if (shouldDrawButtonAsHighlighted)
			{
				fillColor = fillColor.brighter(0.2F);
			}
		}
	} 
	else if (buttonID == "Buttons_ID_02_Close_Group")
	{
		cornerSize = getRoundedCornerSize() * 2;

		fillColor = themeColoursNow.Page_1;
		outlineColor = themeColoursNow.CustomGroupComponent;
		outlineThick = 1.5F;

		if (shouldDrawButtonAsDown)
		{
			fillColor = fillColor.darker(0.2F);
		}
		else if (shouldDrawButtonAsHighlighted)
		{
			fillColor = fillColor.brighter();
		}
	}



	if (buttonName == "knobWorks" || buttonName == "sliderWorks" || buttonName == "modeSimulationButton" || buttonName == "modePreviewButton" || buttonName == "modeResizeButton")
	{
		cornerSize = getRoundedCornerSize();

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
	else if (buttonName == "browseButton")
	{
		cornerSize = getRoundedCornerSize();
		
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
	else if (buttonName == "addKnob" || buttonName == "addKnobScale" || buttonName == "addSliderTrack" || buttonName == "addSliderThumb" || buttonName == "addSliderScale")
	{
		cornerSize = getRoundedCornerSize() * 2;

		fillColor    = getColorCustomLightGrey();
		outlineColor = getColorCustomDarkGrey();

		if (shouldDrawButtonAsDown)
		{
			fillColor = getColorCustomLightGrey().darker(0.2F);
		}
		else if (shouldDrawButtonAsHighlighted)
		{
			fillColor = getColorCustomLightGrey().brighter();
		}
	}
	else if (buttonName == "exportButton")
	{
		cornerSize = getRoundedCornerSize();

		fillColor = getColorCustomDarkGrey();

		if (shouldDrawButtonAsDown)
		{
			fillColor = getColorCustomDarkGrey().brighter();
			fillColor = juce::Colours::royalblue;
		}
		else if (shouldDrawButtonAsHighlighted)
		{
			fillColor = getColorCustomDarkGrey().brighter(0.2F);
		}
	}
	else if (buttonName == "closeDialog1")
	{
		cornerSize = getRoundedCornerSize() * 2;

		fillColor    = getColorCustomLightGrey();
		outlineColor = getColorCustomDarkGrey();
		
		if (shouldDrawButtonAsDown)
		{
			fillColor = getColorCustomLightGrey().darker(0.2F);
		}
		else if (shouldDrawButtonAsHighlighted)
		{
			fillColor = getColorCustomLightGrey().brighter();
		}
	}
	else if (buttonName == "horizontalButton" || buttonName == "verticalButton")
	{
		cornerSize = getRoundedCornerSize() * 2;

		if (button.getToggleState() == 1)
		{
			fillColor = getColorCustomDarkGrey();
			outlineColor = fillColor;

		}
		else if (shouldDrawButtonAsDown)
		{
			fillColor = getColorCustomDarkGrey().darker(0.2F);
		}
		else
		{
			fillColor = getColorCustomLightGrey();
			outlineColor = getColorCustomDarkGrey();

			if (shouldDrawButtonAsHighlighted)
			{
				fillColor = getColorCustomLightGrey().brighter(0.2F);
			}
		}
	}

	g.setColour(fillColor);
	g.fillRoundedRectangle(button.getLocalBounds().toFloat(), cornerSize);

	g.setColour(outlineColor);
	//g.drawRoundedRectangle(button.getLocalBounds().toFloat().reduced(1.1F), cornerSize, 2.0F);
	//g.drawRoundedRectangle(button.getLocalBounds().toFloat().reduced(0.2F), cornerSize, outlineThick);
	g.drawRoundedRectangle(button.getLocalBounds().toFloat().reduced(outlineThick/2), cornerSize, outlineThick);
}

void CustomLookAndFeel::drawButtonText(juce::Graphics& g, juce::TextButton& button, bool isMouseOver, bool isButtonDown)
{
	const juce::String buttonName = button.getName();
	const juce::String buttonText = button.getButtonText();
	const juce::String buttonID = button.getComponentID();
	juce::Font font{ juce::FontOptions{} };
	juce::Colour textColor{};


	if (buttonID == "Buttons_ID_01_SW")
	{
		font = getFontRobotoCondensedRegular().withHeight(getFontSizeRegular());
		textColor = themeColoursNow.ButtonsID_01_Text;

		if (isButtonDown || button.getToggleState() == 1)
		{
			textColor = themeColoursNow.ButtonsID_01_Text;
		}
		else if (isMouseOver)
		{
			textColor = textColor.brighter();
		}
	}
	else if (buttonID == "Buttons_ID_02_Close_Group")
	{
		font = getFontRobotoCondensedBold().withHeight(getFontSizeRegular());
		textColor = themeColoursNow.CustomGroupComponent;

		if (isButtonDown)
		{
			textColor = getColorCustomWhite();
		}
	}




	if (buttonName == "knobWorks" || buttonName == "sliderWorks" || buttonName == "modeSimulationButton" || buttonName == "modePreviewButton" || buttonName == "modeResizeButton")
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
	else if (buttonName == "browseButton")
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
	else if (buttonName == "addKnob" || buttonName == "addKnobScale" || buttonName == "addSliderTrack" || buttonName == "addSliderThumb" || buttonName == "addSliderScale")
	{
		textColor = getColorCustomDarkGrey();

		if (isButtonDown)
		{
			textColor = getColorCustomWhite();
		}
	}
	else if (buttonName == "exportButton")
	{
		textColor = getColorCustomWhite();

		if (isButtonDown)
		{
			textColor = getColorCustomWhite();
		}
	}
	else if (buttonName == "closeDialog1")
	{
		textColor = getColorCustomDarkGrey();

		if (isButtonDown)
		{
			textColor = getColorCustomWhite();
		}
	}
	else if (buttonName == "horizontalButton" || buttonName == "verticalButton")
	{
		if (button.getToggleState() == 1)
		{
			textColor = getColorCustomWhite().darker(0.1F);
		}
		else
		{
			textColor = getColorCustomDarkGrey();

			if (isButtonDown)
			{
				textColor = getColorCustomWhite().darker(0.1F);
			}
		}
	}

	//g.setFont(getFontRobotoCondensedBold().withHeight(getFontSizeRegular()));
	g.setFont(font);
	g.setColour(textColor);
	g.drawFittedText(buttonText, button.getLocalBounds(), juce::Justification::centred, 1);
}


void CustomLookAndFeel::drawGroupComponentOutline(juce::Graphics& g, int width, int height, const juce::String& text, const juce::Justification& position, juce::GroupComponent& group)
{
	if (group.getName() == "DIALOG1d")
	{
		const float textH = getFontSizeRegular(); // Height of the text
		const float indent = 3.0f; // Indentation for the outline
		const float textEdgeGap = 8.0f; // Gap around the text
		auto cornerSize = 10.0f; // Corner size for rounded edges

		// Use your custom font for the group component title
		juce::Font f(getFontRobotoCondensedBold().withHeight(textH)); // Replace with your custom font method

		juce::Path outlinePath;
		auto x = indent;
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

		//auto alpha = group.isEnabled() ? 1.0f : 0.5f;

		// Set color and stroke the outline path
		g.setColour(getColorCustomDarkGrey());
		g.strokePath(outlinePath, juce::PathStrokeType(2.0f));

		// Draw the text at the specified position
		g.setColour(getColorCustomDarkGrey().darker());
		g.setFont(f);
		g.drawText(text, juce::roundToInt(x + textX), 0, juce::roundToInt(textWidth), juce::roundToInt(textH), juce::Justification::centred, true);
	}
}

void CustomLookAndFeel::drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle sytle, juce::Slider& slider)
{
	juce::Colour trackColour = getColorCustomDarkGrey();
	juce::Colour thumbColour = getColorCustomLightGrey().brighter();

	// Draw track
	float trackHeight = float(height * 1.F);
	float thumbSizeW  = float(trackHeight * 0.6F);
	float pad = float(trackHeight * 0.10F);

	juce::Rectangle<float> track{ x - (thumbSizeW / 2) - pad, float(y), width + (pad * 2) + thumbSizeW, float(height) };
	g.setColour(trackColour);
	g.fillRoundedRectangle(track, getRoundedCornerSize());

	// Draw thumb
	float thumbWidth  = thumbSizeW;
	float thumbHeight = float(trackHeight * 0.8F);;
	float thumbX      = float(sliderPos - (thumbWidth / 2));
	juce::Rectangle<float> thumb{ thumbX, y + ((height - thumbHeight) / 2), thumbWidth, thumbHeight };
	g.setColour(thumbColour);
	g.fillRoundedRectangle(thumb, getRoundedCornerSize());
}

void CustomLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
{
	auto lineColour = slider.findColour(juce::Slider::trackColourId);
	auto fillColour = slider.findColour(juce::Slider::backgroundColourId);
	auto tickColour = slider.findColour(juce::Slider::thumbColourId);

	auto radius = (float)juce::jmin(width / 2, height / 2) - (height * 0.2F);
	auto centreX = (float)(x + width * 0.5F);
	auto centreY = (float)(y + height * 0.5F);
	auto rx = centreX - radius;
	auto ry = centreY - radius;
	auto rw = radius * 2.0F;
	auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
	auto rectEllipse = juce::Rectangle{ rx, ry, rw, rw };

	auto sliderName = slider.getName();
	if (sliderName == "sliderMinAngles" || sliderName == "sliderMaxAngles")
	{
		g.setColour(getColorCustomDarkGrey().withAlpha(0.75F));
		g.drawImage(knobScale, rectEllipse.reduced(-(rectEllipse.getHeight() * 0.3F)), juce::RectanglePlacement::centred, true);

		g.setColour(fillColour);
		g.fillEllipse(rectEllipse.reduced(-3.0F));

		g.setColour(lineColour);
		g.drawEllipse(rectEllipse, -1.F);

		{
			juce::Path p{};
			auto pointerLength = radius * 0.65F;
			auto pointerThickness = 2.0F;
			p.addRectangle(-pointerThickness * 0.5F, -radius, pointerThickness, pointerLength);
			p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

			g.setColour(tickColour);
			g.fillPath(p);
		}
	}

	if (sliderName == "simulationKnob")
	{

		if (simulationKnobImage.isValid()) 
		{

			int frameIndex = int(std::round(sliderPos * (simulationKnobTotalFrames - 1)));

			if (frameIndex >= 0 && frameIndex < simulationKnobTotalFrames)
			{
				int knobSize = juce::jmin(width, height) - int(height * 0.65F);
				int drawX = x + (width - knobSize) / 2;
				int drawY = y + (height - knobSize) / 2;

				if (simulationKnobIsVertical) {
					int frameW = simulationKnobImage.getWidth();
					int frameH = simulationKnobImage.getHeight() / simulationKnobTotalFrames;
					g.drawImage(simulationKnobImage, 
						drawX, drawY, knobSize, knobSize, 
						0, frameIndex * frameH, frameW, frameH);
				}

			}

		}
		else {
			DBG("Simulation KNOB IMAGE NOT VALID");
		}
	}
}

void CustomLookAndFeel::drawLabel(juce::Graphics& g, juce::Label& label)
{
	// Drawing only works for local bounds, such fillAll, or using getLocalBounds();

	g.setColour(label.findColour(juce::Label::backgroundColourId));
	g.fillRoundedRectangle(label.getLocalBounds().toFloat(), 3.0F);		

	// Set the text color and draw the text
	g.setColour(label.findColour(juce::Label::textColourId));
	//g.setFont(getFontRobotoCondensedBold().withHeight(17.50F));
	g.setFont(label.getFont());
	//g.drawText(label.getText(), label.getLocalBounds(), juce::Justification::centred, true);
	g.drawText(label.getText(), label.getLocalBounds(), label.getJustificationType(), true);
}

void CustomLookAndFeel::fillTextEditorBackground(juce::Graphics& g, int width, int height, juce::TextEditor& editor)
{
	(void)width;
	(void)height;

	editor.setJustification(juce::Justification::centred);
	editor.setIndents(editor.getLeftIndent(), 0);	// keep the leftIndent the same, and set topIndent to 0

	g.setColour(editor.findColour(juce::Label::backgroundWhenEditingColourId));
	g.fillRoundedRectangle(editor.getLocalBounds().toFloat(), getRoundedCornerSize());
}

void CustomLookAndFeel::drawTextEditorOutline(juce::Graphics& g, int width, int height, juce::TextEditor& editor)
{
	(void)g;
	(void)width;
	(void)height;
	(void)editor;
}


////////////////////////// ========= LOAD FONTS ========= //////////////////////////
void CustomLookAndFeel::LoadFonts()
{
	auto fontRobotoMonoData         { BinaryData::RobotoMonoMedium_ttf };
	auto fontRobotoMonoSize         { BinaryData::RobotoMonoMedium_ttfSize };

	auto fontRobotoCondensedBoldData       { BinaryData::RobotoCondensedSemiBold_ttf };
	auto fontRobotoCondensedBoldSize       { BinaryData::RobotoCondensedSemiBold_ttfSize };
	auto fontRobotoCondensedRegularData    { BinaryData::RobotoCondensedRegular_ttf };
	auto fontRobotoCondensedRegularSize    { BinaryData::RobotoCondensedRegular_ttfSize };

	juce::Typeface::Ptr customFontRobotoMono             { juce::Typeface::createSystemTypefaceFor(fontRobotoMonoData, fontRobotoMonoSize) };
	juce::Typeface::Ptr customFontRobotoCondensedBold    { juce::Typeface::createSystemTypefaceFor(fontRobotoCondensedBoldData, fontRobotoCondensedBoldSize) };
	juce::Typeface::Ptr customFontRobotoCondensedRegular { juce::Typeface::createSystemTypefaceFor(fontRobotoCondensedRegularData, fontRobotoCondensedRegularSize) };

	fontRobotoMono             = juce::FontOptions{ customFontRobotoMono };
	fontRobotoCondensedBold    = juce::FontOptions{ customFontRobotoCondensedBold };
	fontRobotoCondensedRegular = juce::FontOptions{ customFontRobotoCondensedRegular };
}

void CustomLookAndFeel::loadImages()
{
	knobScale = juce::ImageCache::getFromMemory(BinaryData::small_scale_black_png, BinaryData::small_scale_black_pngSize);
}


////////////////////////// ========= GET COLOURS ========= //////////////////////////
const juce::Colour CustomLookAndFeel::getColorTitleBar()
{
	return themeColoursNow.TitleBar;
}

const juce::Colour CustomLookAndFeel::getColorFontTitleBar()
{
	return themeColoursNow.FontTitleBar;
}

const juce::Colour CustomLookAndFeel::getBackgroundColour()
{
	return themeColoursNow.BackgroundColour;
}

const juce::Colour CustomLookAndFeel::getColorCustomDarkest()
{
	return themeColoursNow.CustomDarkest;
}

const juce::Colour CustomLookAndFeel::getColorCustomDarkGrey()
{
	return themeColoursNow.CustomDarkGrey;
}

const juce::Colour CustomLookAndFeel::getColorCustomGrey()
{
	return themeColoursNow.CustomGrey;
}

const juce::Colour CustomLookAndFeel::getColorCustomLightGrey()
{
	return themeColoursNow.CustomLightGrey;
}

const juce::Colour CustomLookAndFeel::getColorCustomWhite()
{
	return themeColoursNow.CustomWhite;
}

////////////////////////// ========= GET FONTS ========= //////////////////////////
const juce::Font CustomLookAndFeel::getFontRobotoMono()
{
	return fontRobotoMono;
}

const juce::Font CustomLookAndFeel::getFontRobotoCondensedBold()
{
	return fontRobotoCondensedBold;
}

const juce::Font CustomLookAndFeel::getFontRobotoCondensedRegular()
{
	return fontRobotoCondensedRegular;
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

void CustomLookAndFeel::setTheme(ThemeType themeType)
{


	themeTypeNow = themeType;

	switch (themeType)
	{
	case ThemeType::OfficeLight:
		themeColoursNow = OfficeLightTheme;
		break;
	case ThemeType::DarkNight:
		themeColoursNow = DarkNightTheme;
		break;

	default:
		break;
	}

	auto& colorscheme = getCurrentColourScheme();
	colorscheme.setUIColour(juce::LookAndFeel_V4::ColourScheme::widgetBackground, getCurrentTheme().TitleBar);
}

const ThemeType& CustomLookAndFeel::getCurrentThemeType()
{
	// TODO: insert return statement here
	return themeTypeNow;
}

const ThemeColours& CustomLookAndFeel::getCurrentTheme()
{
	return themeColoursNow;
}


/////////////////////////////////////////////////////////////////////////////////
void CustomLookAndFeel::setSimulationKnobImage(juce::Image image, int totalFrames, bool isVertical, double startAngle, double endAngle)
{
	//int frameW = image.getWidth();
	//int frameH = image.getHeight();
	//double range = std::abs(startAngle) + std::abs(endAngle);
	//double angleInterval = range / (totalFrames - 1);

	//juce::Image filmstripImage;

	//if (isVertical) 
	//	filmstripImage = juce::Image(juce::Image::PixelFormat::ARGB, frameW, frameH * totalFrames, true);
	//else 
	//	filmstripImage = juce::Image(juce::Image::PixelFormat::ARGB, frameW * totalFrames, frameH, true);

	//juce::Graphics g(filmstripImage);
	//juce::Image rotary(juce::Image::PixelFormat::ARGB, frameW, frameH, true);

	//for (size_t i = 0; i < totalFrames; i++) 
	//{
	//	rotary.clear(rotary.getBounds(), juce::Colours::transparentBlack);

	//	juce::Rectangle<int> dest{};

	//	if (isVertical) {
	//		int yPos = (int)i * frameH;
	//		dest = { 0, yPos, frameW, frameH };
	//	}
	//	else {
	//		int xPos = (int)i * frameW;
	//		dest = { xPos, 0, frameW, frameH };
	//	}

	//	double angleNow = int(i) * angleInterval;
	//	double angleRadian = juce::degreesToRadians(startAngle + angleNow);

	//	juce::Rectangle<int> temp{ 0,0,frameW, frameH };
	//	juce::AffineTransform rotating = juce::AffineTransform::rotation((float)angleRadian, temp.getCentreX(), temp.getCentreY());

	//	//juce::Image rotary(juce::Image::PixelFormat::ARGB, frameW, frameH, true);
	//	juce::Graphics frames(rotary);

	//	frames.addTransform(rotating);
	//	frames.drawImage(image, temp.toFloat(), juce::RectanglePlacement::centred, false);
	//	
	//	g.drawImage(rotary, dest.toFloat(), juce::RectanglePlacement::centred, false);

	//	juce::Rectangle<int> ellipse{ dest.reduced(dest.getHeight() * 0.35F) };
	//	g.setColour(getColorCustomDarkest());
	//	g.fillEllipse(ellipse.toFloat());

	//	auto numText = std::to_string(i + 1);
	//	g.setFont(getFontRobotoCondensed().withHeight(ellipse.getHeight() * 0.60F));
	//	g.setColour(getColorCustomWhite());
	//	g.drawText(numText, ellipse.toFloat(), juce::Justification::centred, true);

	//}


	this->simulationKnobIsVertical = isVertical;
	this->simulationKnobTotalFrames = totalFrames;
	//this->simulationKnobImage = filmstripImage;
}

void CustomLookAndFeel::ClearSimulationKnobImage()
{
	this->simulationKnobImage = juce::Image{};
}

void CustomLookAndFeel::setSimulationKnobScaleImage(juce::Image image)
{
	this->simulationKnobScale = image;
}

void CustomLookAndFeel::ClearSimulationKnobScaleImage()
{
	this->simulationKnobScale = juce::Image{};
}

void CustomLookAndFeel::setFilmStripKnob(juce::Image image)
{
	this->simulationKnobImage = image;
}

