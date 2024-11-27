#include "CustomGroupComponent.h"

CustomGroupComponent::CustomGroupComponent()
{
	DBG("CustomGroupComponent constructed");
}

CustomGroupComponent::~CustomGroupComponent()
{

}

void CustomGroupComponent::paint(juce::Graphics& g)
{
	//DBG("CustomGroupComponent paint called");

	const float textH = getFont().getHeight(); // Height of the text
	const float indent = getIndentation(); // Indentation for the outline
	const float textEdgeGap = getTextLineGap(); // Gap around the text
	auto cornerSize = getCornerSize(); // Corner size for rounded edges
	auto width  = getBounds().getWidth();
	auto height = getBounds().getHeight();
	auto textTitle = getText();

	g.saveState();

	g.setOrigin(groupBounds.getX(), groupBounds.getY());

	// Use your custom font for the group component title
	juce::Font f(getFont()); // Replace with your custom font method

	juce::Path outlinePath{};
	auto x = indent;
	auto y = f.getAscent() - (textH / 4); // Y position based on font ascent	// Somehow textH/4 make the text centre to line.
	auto w = juce::jmax(0.0f, (float)width - x * 2.0f);
	auto h = juce::jmax(0.0f, (float)height - y - indent);
	cornerSize = juce::jmin(cornerSize, w * 0.5f, h * 0.5f);
	auto cornerSize2 = 2.0f * cornerSize;

	// Calculate text width and position
	auto textWidth = textTitle.isEmpty() ? 0
		: juce::jlimit(0.0f, juce::jmax(0.0f, w - cornerSize2 - textEdgeGap * 2),
			(float)juce::GlyphArrangement::getStringWidthInt(f, textTitle) + textEdgeGap * 2.0f);
	auto textX = cornerSize + textEdgeGap;

	auto position = getTextLabelPosition();
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
	g.setColour(getOutlineColour());
	g.strokePath(outlinePath, juce::PathStrokeType(getLineThickness()));

	// Draw the text at the specified position
	g.setColour(getFontColour());
	g.setFont(f);
	g.drawText(textTitle, juce::roundToInt(x + textX), 0, juce::roundToInt(textWidth), juce::roundToInt(textH), juce::Justification::centred, true);


	// Make it normal again
	g.restoreState();
}

const juce::String CustomGroupComponent::getName()
{
	return groupName;
}
const juce::String CustomGroupComponent::getText()
{
	return groupText;
}
const juce::Justification CustomGroupComponent::getTextLabelPosition()
{
	return groupTextPosition;
}

const juce::Rectangle<int> CustomGroupComponent::getBounds()
{
	return groupBounds;
}

const float CustomGroupComponent::getCornerSize()
{
	return groupCornerSize;
}
const float CustomGroupComponent::getLineThickness()
{
	return groupLineThickness;
}
const float CustomGroupComponent::getTextLineGap()
{
	return groupTextLineGap;
}
const float CustomGroupComponent::getIndentation()
{
	return groupIndentation;
}

const juce::Font CustomGroupComponent::getFont()
{
	return groupFont;
}
const juce::Colour CustomGroupComponent::getFontColour()
{
	return groupFontColour;
}
const juce::Colour CustomGroupComponent::getOutlineColour()
{
	return groupOutlineColour;
}



void CustomGroupComponent::setName(juce::String name)
{
	this->groupName = name;
}
void CustomGroupComponent::setText(juce::String textTitle)
{
	this->groupText = textTitle;
}
void CustomGroupComponent::setTextLabelPosition(juce::Justification position)
{
	this->groupTextPosition = position;
}

void CustomGroupComponent::setBounds(juce::Rectangle<int> bounds)
{
	this->groupBounds = bounds;
}
void CustomGroupComponent::setCornerSize(float cornerSize)
{
	this->groupCornerSize = cornerSize;
}
void CustomGroupComponent::setLineThickness(float lineThickness)
{
	this->groupLineThickness = lineThickness;
}
void CustomGroupComponent::setTextLineGap(float textLineGap)
{
	this->groupTextLineGap = textLineGap;
}
void CustomGroupComponent::setIndentation(float indentation)
{
	this->groupIndentation = indentation;
}

void CustomGroupComponent::setFont(juce::Font font)
{
	this->groupFont = font;
}
void CustomGroupComponent::setFontColour(juce::Colour fontColour)
{
	this->groupFontColour = fontColour;
}
void CustomGroupComponent::setOutlineColour(juce::Colour outlineColour)
{
	this->groupOutlineColour = outlineColour;
}

