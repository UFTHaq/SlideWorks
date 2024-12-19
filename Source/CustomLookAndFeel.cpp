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
	setupColorMapStorage();
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

		return new LookAndFeel_V4_DocumentWindowButton("close", juce::Colours::red.darker(0.15F), shape, shape);
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
	auto bounds = button.getLocalBounds().toFloat();
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
			fillColor = getCurrentTheme().ButtonsID_01_ON;
		}
		else
		{
			fillColor = getCurrentTheme().ButtonsID_01_ON;

			if (shouldDrawButtonAsHighlighted)
			{
				fillColor = fillColor.brighter(0.2F);
			}
		}
	} 
	else if (buttonID == "Buttons_ID_02_Close_Group")
	{
		cornerSize = getRoundedCornerSize() * 2;

		fillColor = getCurrentTheme().Page_1;
		outlineColor = getCurrentTheme().CustomGroupComponent;
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
	else if (buttonID == "Buttons_ID_03_TAB")
	{
		cornerSize = 1;

		outlineColor = getColorCustomGrey();
		outlineThick = 0.4F;

		if (button.getToggleState() == 1)
		{
			fillColor = getCurrentTheme().TabButtonsID_03_ON;

		}
		else if (shouldDrawButtonAsDown)
		{
			fillColor = getCurrentTheme().TabButtonsID_03_ON;
		}
		else
		{
			fillColor = getCurrentTheme().TabButtonsID_03_OFF;
		}
	}
	else if (buttonID == "Buttons_ID_04_TAB_CLOSE")
	{
		cornerSize = 2.5F;
		bounds.reduce(2.5F, 2.5F);

		//outlineColor = getColorCustomGrey();
		outlineThick = 0.4F;

	    if (shouldDrawButtonAsDown || shouldDrawButtonAsHighlighted)
		{
			fillColor = juce::Colours::red.darker(0.15F);
		}
		else
		{
			fillColor = juce::Colours::black.withAlpha(0.1F);
		}
	}
	else if (buttonID == "Buttons_ID_05_MODE")
	{
		cornerSize = 1;

		outlineColor = getColorCustomGrey();
		outlineThick = 0.4F;

		if (button.getToggleState() == 1)
		{
			fillColor = getCurrentTheme().ModeButtonsID_05_ON;

		}
		else if (shouldDrawButtonAsDown)
		{
			fillColor = getCurrentTheme().ModeButtonsID_05_ON;
		}
		else
		{
			fillColor = getCurrentTheme().ModeButtonsID_05_OFF;
		}
	}
	else if (buttonID == "Buttons_ID_06_EXPORT")
	{
		cornerSize = 1;

		outlineColor = getColorCustomGrey();
		outlineThick = 1.0F;

		if (shouldDrawButtonAsDown)
		{
			fillColor = getCurrentTheme().CustomWhite.withAlpha(0.2F);
		}
		else
		{
			fillColor = getCurrentTheme().ButtonsID_01_ON;
		}
	}
	else if (buttonID == "Buttons_ID_07_NEW_ASSET")
	{
		cornerSize = 1;

		outlineColor = getCurrentTheme().CustomDarkGrey;
		outlineThick = 0.5F;

		if (shouldDrawButtonAsDown)
		{
			fillColor = getCurrentTheme().CustomLightGrey.withAlpha(0.2F);
		}
		else
		{
			fillColor = getCurrentTheme().ButtonsID_01_ON;
		}
	}
	else if (buttonID == "Buttons_ID_08_DEFAULT" || buttonID == "Buttons_ID_09_APPLY")
	{
		cornerSize = 2;

		outlineColor = getCurrentTheme().OutlineControl;
		outlineThick = 1.0F;

		if (shouldDrawButtonAsDown)
		{
			fillColor = getCurrentTheme().CustomLightGrey.withAlpha(0.2F);
		}
		else
		{
			fillColor = getCurrentTheme().TransparentWhite;
		}
	}
	else if (buttonID == "Buttons_ID_10_ORIENTATION")
	{
		cornerSize = 2;

		outlineColor = getCurrentTheme().OutlineControl;
		outlineThick = 1.0F;

		if (button.getToggleState() == 1 || shouldDrawButtonAsDown)
		{
			outlineThick = 1.5F;
			fillColor = getCurrentTheme().CustomLightGrey.withAlpha(0.1F);
		}
		else
		{
			fillColor = getCurrentTheme().TransparentWhite;
		}
	}
	else if (buttonID == "Buttons_ID_11_MAIN_ASSET")
	{
		cornerSize = 1;

		outlineColor = getCurrentTheme().OutlineControl.darker();
		outlineThick = 0.4F;

		if (button.getToggleState() == 1 || shouldDrawButtonAsDown)
		{
			fillColor = getCurrentTheme().NamingLabel;
		}
		else
		{
			fillColor = getCurrentTheme().TransparentWhite;
		}
	}
	else if (buttonID == "Buttons_ID_12_VISIBLE_ASSET")
	{
		cornerSize = 1;

		outlineColor = getCurrentTheme().OutlineControl.darker();
		outlineThick = 0.4F;

		fillColor = getCurrentTheme().SlideworksBaseColour;
	}
	else if (buttonID == "Buttons_ID_13_DELETE_ASSET")
	{
		cornerSize = 1;

		outlineColor = getCurrentTheme().OutlineControl.darker();
		outlineThick = 0.4F;

		fillColor = getCurrentTheme().SlideworksBaseColour;
	}
	else if (buttonID == "Buttons_ID_14_LOAD_ASSET")
	{
		cornerSize = 1;

		outlineColor = getCurrentTheme().OutlineControl;
		outlineThick = 0.4F;

		if (button.getToggleState() == 1 || shouldDrawButtonAsDown)
		{
			fillColor = getCurrentTheme().BannerFilmstripType.brighter();
		}
		else
		{
			fillColor = getCurrentTheme().BannerFilmstripType;
		}
	}
	

	g.setColour(fillColor);
	g.fillRoundedRectangle(bounds, cornerSize);

	g.setColour(outlineColor);
	g.drawRoundedRectangle(bounds.reduced(outlineThick * 1.0F), cornerSize, outlineThick);

	// DRAW IMAGE ON BUTTON
	auto imageBounds = button.getLocalBounds().reduced(4).toFloat();
	if (buttonID == "Buttons_ID_12_VISIBLE_ASSET")
	{
		if (button.getToggleState() == true)
			g.drawImage(iconOnVisible, imageBounds.reduced(-1), juce::RectanglePlacement::centred, false);
	}
	else if (buttonID == "Buttons_ID_13_DELETE_ASSET")
	{
		g.setColour(juce::Colours::grey.withAlpha(0.8F));
		g.drawImage(iconDelete, imageBounds, juce::RectanglePlacement::centred ,true);
	}
}

void CustomLookAndFeel::drawButtonText(juce::Graphics& g, juce::TextButton& button, bool isMouseOver, bool isButtonDown)
{
	juce::String buttonName = button.getName();
	juce::String buttonText = button.getButtonText();
	const juce::String buttonID = button.getComponentID();
	auto bounds = button.getLocalBounds();
	auto justification = juce::Justification::centred;
	juce::Font font{ juce::FontOptions{} };
	juce::Colour textColor{};
	juce::String text{ buttonText };

	//textColor = colorMapStorage.find("Buttons_ID_01_SW")
	//textColor = colorMapStorage.at("Buttons_ID_01_SW").at(juce::Label::textColourId);

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
	else if (buttonID == "Buttons_ID_03_TAB")
	{
		font = getFontRobotoCondensedRegular().withHeight(getFontSizeRegular());
		textColor = getCurrentTheme().CustomLightGrey.darker(0.1F);

		bounds.removeFromLeft(5);
		bounds.removeFromRight(25);
		justification = juce::Justification::centredLeft;

		if (isButtonDown || button.getToggleState() == 1)
		{
			textColor = getCurrentTheme().CustomGroupComponent;
		}
		else if (isMouseOver)
		{
			textColor = getCurrentTheme().CustomGrey;
		}
	}
	else if (buttonID == "Buttons_ID_04_TAB_CLOSE")
	{
		bounds.reduce(3, 3);

		juce::Path shape;
		auto crossThickness = 0.2F;

		shape.addLineSegment({ 0.0F, 0.0F, 1.0F, 1.0F }, crossThickness);   // Top Left -> Bottom Right
		shape.addLineSegment({ 0.0F, 1.0F, 1.0F, 0.0F, }, crossThickness);  // Bottom left -> Top Right

		auto reducedRect = bounds.reduced(int(bounds.getHeight() * 0.25F));
		g.setColour(getCurrentTheme().CustomWhite);
		g.fillPath(shape, shape.getTransformToScaleToFit(reducedRect.toFloat(), true));
	}
	else if (buttonID == "Buttons_ID_05_MODE")
	{
		font = getFontRobotoCondensedRegular().withHeight(getFontSizeRegular());
		textColor = getCurrentTheme().CustomLightGrey.darker(0.1F);

		justification = juce::Justification::centred;

		if (isButtonDown || button.getToggleState() == 1)
		{
			textColor = getCurrentTheme().CustomGroupComponent;
		}
		else if (isMouseOver)
		{
			textColor = getCurrentTheme().CustomGrey;
		}
	}
	else if (buttonID == "Buttons_ID_06_EXPORT")
	{
		font = getFontRobotoCondensedRegular().withHeight(getFontSizeRegular());
		textColor = getCurrentTheme().FontBlack;

		justification = juce::Justification::centred;
	}
	else if (buttonID == "Buttons_ID_07_NEW_ASSET")
	{
		bounds = bounds.withSizeKeepingCentre(bounds.getHeight(), bounds.getHeight());

		juce::Path shape;
		auto crossThickness = 0.175F;

		shape.addLineSegment({ 0.5F, 0.0F, 0.5F, 1.0F }, crossThickness);
		shape.addLineSegment({ 0.0F, 0.5F, 1.0F, 0.5F }, crossThickness);

		auto reducedRect = bounds.reduced(int(bounds.getHeight() * 0.25F));
		g.setColour(getCurrentTheme().CustomGrey);
		g.fillPath(shape, shape.getTransformToScaleToFit(reducedRect.toFloat(), true));
	}
	else if (buttonID == "Buttons_ID_08_DEFAULT" || buttonID == "Buttons_ID_09_APPLY")
	{
		font = getFontRobotoCondensedRegular().withHeight(getFontSizeRegular());
		textColor = getCurrentTheme().FontBlack;

		justification = juce::Justification::centred;
	}
	else if (buttonID == "Buttons_ID_10_ORIENTATION")
	{
		font = getFontRobotoCondensedRegular().withHeight(getFontSizeRegular());
		textColor = getCurrentTheme().FontBlack;

		justification = juce::Justification::centred;


		if (button.getToggleState() == 1 || isButtonDown)
		{
			textColor = getCurrentTheme().FontBlack;
		}
		else
		{
			textColor = getCurrentTheme().OutlineControl;
		}
	}
	else if (buttonID == "Buttons_ID_11_MAIN_ASSET")
	{
		font = getFontRobotoCondensedRegular().withHeight(getFontSizeRegular());
		textColor = getCurrentTheme().FontBlack;

		justification = juce::Justification::centredLeft;

		text = buttonName;

		bounds.removeFromLeft(5);
		bounds = bounds.removeFromLeft(35);

		if (button.getToggleState() == 1 || isButtonDown)
		{
			textColor = getCurrentTheme().FontWhite;
		}
		else
		{
			textColor = getCurrentTheme().FontBlack;
		}
	}
	else if (buttonID == "Buttons_ID_14_LOAD_ASSET")
	{
		font = getFontRobotoCondensedRegular().withHeight(getFontSizeRegular());
		textColor = getCurrentTheme().FontBlack;

		justification = juce::Justification::centred;


		if (button.getToggleState() == 1 || isButtonDown)
		{
			textColor = getCurrentTheme().FontBlack;
		}
		else
		{
			textColor = getCurrentTheme().FontBlack;
		}
	}
	

	g.setFont(font);
	g.setColour(textColor);
	g.drawFittedText(text, bounds, justification, 1);

	if (buttonID == "Buttons_ID_11_MAIN_ASSET")
	{
		bounds = button.getLocalBounds();
		text = ": " + buttonText;

		if (button.isEnabled())
		{
			bounds.removeFromLeft(45);
			bounds.removeFromRight(50);
			g.drawFittedText(text, bounds, justification, 1, 0.75F);
			//g.drawText(text, bounds, justification, 1);
		}
	}
}

void CustomLookAndFeel::drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle sytle, juce::Slider& slider)
{
	auto ID = slider.getComponentID();

	juce::Colour trackColour = {};
	juce::Colour thumbColour = {};

	//juce::Colour trackColour = slider.findColour(juce::Slider::trackColourId);
	//juce::Colour thumbColour = slider.findColour(juce::Slider::thumbColourId);
	juce::Colour outline = getCurrentTheme().CustomDarkest;

	// Move all the component.setColour() to customLookAndFeel.cpp
	// maybe too heavy computation?
	// I have change theme function maybe in here
	// So invoke the re setColour of each component there if change theme.
	// findColour also need to refactor as that.
	// updateThemeColorComponent(); update the colorMapStorage

	trackColour = colorMapStorage.at("Slider_ID_01_WithThumb").at(juce::Slider::trackColourId);
	thumbColour = colorMapStorage.at("Slider_ID_01_WithThumb").at(juce::Slider::thumbColourId);

	// Draw track
	float trackHeight = float(height * 1.F);
	float thumbSizeW  = float(trackHeight * 0.7F);
	float pad = float(trackHeight * 0.10F);

	auto track = juce::Rectangle<float>{ x - (thumbSizeW / 2) - pad, float(y), width + (pad * 2) + thumbSizeW, float(height) };
	g.setColour(trackColour);
	g.fillRoundedRectangle(track, 1);
	g.setColour(outline);
	g.drawRoundedRectangle(track.reduced(0.5F), 1, 0.3F);

	// Draw thumb
	float thumbWidth  = thumbSizeW;
	float thumbHeight = float(trackHeight * 0.8F);;
	float thumbX      = float(sliderPos - (thumbWidth / 2));
	auto thumb = juce::Rectangle<float>{ thumbX, y + ((height - thumbHeight) / 2), thumbWidth, thumbHeight };
	g.setColour(thumbColour);
	g.fillRoundedRectangle(thumb, getRoundedCornerSize());

	// Draw motif in thumb
	if (ID == "Slider_ID_01_WithThumb")
	{
		auto bounds = thumb;
		juce::Path shape;
		auto crossThickness = 0.225F;
		shape.addLineSegment({ 0.5F, 0.0F, 0.5F, 1.0F }, crossThickness);

		auto reducedRect = bounds.reduced(bounds.getHeight() * 0.235F);
		g.setColour(getCurrentTheme().CustomLightGrey.brighter(0.8F));
		g.fillPath(shape, shape.getTransformToScaleToFit(reducedRect.toFloat(), true));
	}
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
	auto ID = slider.getComponentID();

	if (ID == "Slider_ID_02_MIN_MAX_Rotary")
	{
		g.setColour(getCurrentTheme().CustomDarkGrey.withAlpha(0.5F));
		g.drawImage(knobScale, rectEllipse.reduced(-(rectEllipse.getHeight() * 0.25F)), juce::RectanglePlacement::centred, true);

		g.setColour(fillColour);
		g.fillEllipse(rectEllipse.reduced(-3.0F));

		g.setColour(lineColour);
		g.drawEllipse(rectEllipse, -1.F);

		{
			juce::Path p{};
			auto pointerLength = radius * 0.25F;
			auto pointerThickness = 2.0F;
			p.addRectangle(-pointerThickness * 0.5F, -radius, pointerThickness, pointerLength);
			p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

			g.setColour(tickColour);
			g.fillPath(p);
		}
	}



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
	auto outlineColour = juce::Colours::transparentWhite;
	auto fillColour = label.findColour(juce::Slider::backgroundColourId);
	auto bounds = label.getLocalBounds();
	auto ID = label.getComponentID();
	auto font = label.getFont();

	if (ID == "Label_ID_01_NamingEditor" || ID == "Label_ID_O1_Naming")
	{
		bounds.removeFromLeft(5);
		bounds.removeFromTop(1);

		outlineColour = label.findColour(juce::Label::outlineColourId);
	} 
	else if (ID == "Slider_ID_01_WithThumb")
	{
		outlineColour = label.findColour(juce::Label::outlineColourId);
	}
	else if (ID == "Label_ID_03_MIN_MAX_VALUE")
	{
		font = getFontRobotoCondensedRegular().withHeight(16.0F);
	}

	g.setColour(label.findColour(juce::Label::backgroundColourId));
	g.fillRoundedRectangle(label.getLocalBounds().toFloat(), 1.0F);

	// Set the text color and draw the text
	g.setFont(font);
	g.setColour(label.findColour(juce::Label::textColourId));
	g.drawText(label.getText(), bounds, label.getJustificationType(), true);

	g.setColour(outlineColour);
	g.drawRoundedRectangle(label.getLocalBounds().toFloat().reduced(0.5F), 1.0F, 0.4F);
}

void CustomLookAndFeel::fillTextEditorBackground(juce::Graphics& g, int width, int height, juce::TextEditor& editor)
{
	(void)width;
	(void)height;

	int topIndent{};
	int leftIndent{};
	auto Justification = editor.getJustificationType();

	auto ID = editor.getComponentID();

	bool caretActive{ true };
	if (editor.getHighlightedRegion().getLength() > 0) {
		caretActive = false;
	}
	editor.setCaretVisible(caretActive);

	if (ID == "Label_ID_01_NamingEditor")
	{
		editor.setTextToShowWhenEmpty("Untitled", getCurrentTheme().CustomDarkGrey);
		editor.setFont(getFontRobotoCondensedRegular().withHeight(16.0F));
		editor.setJustification(juce::Justification::verticallyCentred);
		topIndent = 0;
		leftIndent = editor.getLeftIndent();
	}
	else {
		editor.setJustification(juce::Justification::centred);
		topIndent = 0;
		leftIndent = editor.getLeftIndent();
	}

	editor.setIndents(leftIndent, topIndent);
	g.setColour(editor.findColour(juce::Label::backgroundWhenEditingColourId));
	g.fillRoundedRectangle(editor.getLocalBounds().toFloat(), getRoundedCornerSize());
}

void CustomLookAndFeel::drawTextEditorOutline(juce::Graphics& g, int width, int height, juce::TextEditor& editor)
{
	(void)g;
	(void)width;
	(void)height;
	//(void)editor;
	
	juce::Colour outlineColour{};
	outlineColour = editor.findColour(juce::TextEditor::outlineColourId);

	g.setColour(outlineColour);
	g.drawRoundedRectangle(editor.getLocalBounds().toFloat().reduced(0.5F), 1.0F, 0.4F);
}

void CustomLookAndFeel::drawScrollbar
(
	juce::Graphics& g, juce::ScrollBar& scrollbar, 
	int x, int y, int width, int height, bool isScrollbarVertical, int thumbStartPosition, int thumbSize, 
	bool isMouseOver, bool isMouseDown
)
{
	auto bounds = juce::Rectangle<int>{ x, y, width, height };
	auto barBounds = juce::Rectangle<int>{};
	auto* parentViewport = scrollbar.findParentComponentOfClass<juce::Viewport>();

	auto backgroundColor = getCurrentTheme().TransparentBlack;
	auto barColor = getCurrentTheme().TitleBar.brighter();

	if (parentViewport != nullptr)
	{
		auto ID = parentViewport->getComponentID();

		if (ID == "Viewport_O1_Main")
		{
			backgroundColor = getCurrentTheme().TransparentBlack;
			barColor = getCurrentTheme().CustomDarkGrey.brighter();
		}
		else if (ID == "Viewport_O2_SubControl")
		{

		}
	}

	if (isScrollbarVertical)
		barBounds = { x, thumbStartPosition, width, thumbSize };
	else
		barBounds = { thumbStartPosition, y, thumbSize, height };

	g.setColour(backgroundColor);
	g.fillRoundedRectangle(bounds.toFloat(), 1);

	g.setColour(barColor);
	g.fillRoundedRectangle(barBounds.toFloat().reduced(0.5), 1);
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

// NEED TO LOAD THE IMAGE BUTTON ICON FOR EYE VISIBLE AND DELETE BUTTON //
void CustomLookAndFeel::loadImages()
{
	iconOnVisible = juce::ImageCache::getFromMemory(BinaryData::icon_On_Visible_png, BinaryData::icon_On_Visible_pngSize);
	iconDelete    = juce::ImageCache::getFromMemory(BinaryData::icon_Delete_png, BinaryData::icon_Delete_pngSize);

	knobScale = juce::ImageCache::getFromMemory(BinaryData::small_scale_black_png, BinaryData::small_scale_black_pngSize);
}

void CustomLookAndFeel::updateThemeColorComponent()
{

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
		updateThemeColorComponent();

		break;
	case ThemeType::DarkNight:
		themeColoursNow = DarkNightTheme;
		updateThemeColorComponent();

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

void CustomLookAndFeel::setupColorMapStorage()
{
	juce::String ID{};

	ID = "Slider_ID_01_WithThumb";
	std::unordered_map<int, juce::Colour> setColours = {
		{juce::Slider::trackColourId, getCurrentTheme().SlideworksBaseColour},
		{juce::Slider::thumbColourId, getCurrentTheme().SliderThumbColour}
	};
	colorMapStorage.insert({ ID, setColours });
}

void CustomLookAndFeel::reloadColorMapStorage()
{
	juce::String ID{};

	ID = "Slider_ID_01_WithThumb";
	if (colorMapStorage.find(ID) != colorMapStorage.end())
	{
		colorMapStorage.at(ID).at(juce::Slider::trackColourId) = getCurrentTheme().SlideworksBaseColour;
		colorMapStorage.at(ID).at(juce::Slider::thumbColourId) = getCurrentTheme().SliderThumbColour;
	}
}

// TO LOAD THE LABELS COLORS
//void CustomLookAndFeel::drawLabel(juce::Graphics& g, juce::Label& label)
//{
//	auto labelColours = colorMapStorage.at(label.getComponentID());
//	g.setColour(labelColours.at(juce::Label::backgroundColourId));
//	g.fillAll();
//
//	g.setColour(labelColours.at(juce::Label::textColourId));
//	g.drawText(label.getText(), label.getLocalBounds(), label.getJustificationType());
//}

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

