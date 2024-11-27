#pragma once
#include <JuceHeader.h>


class CustomGroupComponent : public juce::GroupComponent
{
public :
	CustomGroupComponent();
	~CustomGroupComponent();

	void paint(juce::Graphics& g) override;

	const juce::String getName();
	const juce::String getText();
	const juce::Justification getTextLabelPosition();

	const juce::Rectangle<int> getBounds();
	const float getCornerSize();
	const float getLineThickness();
	const float getTextLineGap();
	const float getIndentation();

	const juce::Font getFont();
	const juce::Colour getFontColour();
	const juce::Colour getOutlineColour();

	void setName(juce::String name);
	void setText(juce::String textTitle);
	void setTextLabelPosition(juce::Justification position);

	void setBounds(juce::Rectangle<int> bounds);
	void setCornerSize(float cornerSize);
	void setLineThickness(float lineThickness);
	void setTextLineGap(float textLineGap);
	void setIndentation(float indentation);
	
	void setFont(juce::Font font);
	void setFontColour(juce::Colour fontColour);
	void setOutlineColour(juce::Colour outlineColour);

private:
	juce::String groupName{};
	juce::String groupText{};
	juce::Justification groupTextPosition{ juce::Justification::centred };

	juce::Rectangle<int> groupBounds{};
	float groupCornerSize{};
	float groupLineThickness{};
	float groupTextLineGap{};
	float groupIndentation{};

	juce::Font groupFont{ juce::FontOptions{} };
	juce::Colour groupFontColour{};
	juce::Colour groupOutlineColour{};


};

