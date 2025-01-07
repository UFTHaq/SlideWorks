/*
  ==============================================================================

    XYPad.h
    Created: 31 Dec 2024 6:10:53pm
    Author:  UFTHaq

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "../Source/Globals.h"
#include "../Source/CustomComponents/CustomLookAndFeel.h"

class XYPad
    : public juce::Component
{
protected:
    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(XYPad)

public:

    class Thumb
        : public juce::Component
    {
    protected:
        std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};

        juce::ComponentDragger dragger{};
        int thumbSize = 14;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Thumb)

    public:
        Thumb();
        ~Thumb();

        void paint(juce::Graphics& g) override;
        void mouseDown(const juce::MouseEvent& event) override;
        void mouseDrag(const juce::MouseEvent& event) override;
        
        void setTheValue();

        juce::ComponentBoundsConstrainer constrainer{};

        double snapToStep(const double value, const double step);
    };

    XYPad();
    ~XYPad();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void mouseDown(const juce::MouseEvent& event) override;
    void mouseDrag(const juce::MouseEvent& event) override;

    void setXValue(const double x);
    void setYValue(const double y);

    double getXValue() const;
    double getYValue() const;

    Thumb thumb{};
    juce::Value xValue{ 0.5 }, yValue{ 0.5 };
    int thumbSize = 14;

    double relativeX = 0.5;  // Default to center
    double relativeY = 0.5;  // Default to center

    juce::Line<float> verticalLine{}, horizontalLine{};
};