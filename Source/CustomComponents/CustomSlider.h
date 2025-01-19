/*
  ==============================================================================

    CustomSlider.h
    Created: 4 Jan 2025 7:52:29pm
    Author:  UFTHaq

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "CustomLookAndFeel.h"
#include "../Source/Globals.h"

struct CustomSliderAttribute
{
    juce::Font font{ juce::FontOptions{} };

    juce::Colour baseColor{};
    juce::Colour outlineColor{};
    juce::Colour barColor{};
    juce::Colour textColor{};

    float cornerSize{};
    float outlineThick{};

    juce::String postfix{};

    struct Range { double min{}, max{}, interval{}; };
    Range range{};
    double value{};
    juce::String valueText{};

    juce::Label valueLabel{};
};

class CustomSlider
    : public juce::Component
    , public juce::Timer
{
protected:
    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};

    juce::Rectangle<int> bounds{};
    juce::Rectangle<double> barBase{};
    juce::Rectangle<double> bar{};
    double barRight{};

    CustomSliderAttribute attribute{};

    bool positionInit{ false };

    std::unique_ptr<juce::MouseEvent> myMouseEvent{};
    int singleClickDelay{};

    bool isDecimal{};
    int digitDecimal{};

    double stepValue{};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomSlider)
public:
    CustomSlider();
    ~CustomSlider();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void mouseDown(const juce::MouseEvent& event) override;
    void mouseDrag(const juce::MouseEvent& event) override;
    void mouseUp(const juce::MouseEvent& event) override;
    void mouseWheelMove(const juce::MouseEvent& event, const juce::MouseWheelDetails& wheel) override;
    void timerCallback() override;

    void initializeBounds();
    void setBarWidth();
    void calculateTheValue();

    void setFont(const juce::Font& font);
    void setColourBase(const juce::Colour& color);
    void setColourOutline(const juce::Colour& color);
    void setColourBar(const juce::Colour& color);
    void setColourText(const juce::Colour& color);

    void setCornerSize(const float& size);
    void setOutlineThick(const float& thickness);

    void setPostfix(const juce::String& unit);
    void setRange(double min, double max, double interval);
    double getMinRange() const;
    double getMaxRange() const;
    double getInterval() const;

    void setValue(double value);
    double getValue() const;

    void setTextFormatDecimal(bool decimal = false);
    void setTextFormatDecimal(bool decimal = true, int digitDecimalPrecision = 1);
    void setScrollStep(double step);

    void setupLabel();
    void handleSingleClick(const juce::MouseEvent& event);
    void handleDoubleClick(const juce::MouseEvent& event);

    std::function<void()> onValueChange;
};