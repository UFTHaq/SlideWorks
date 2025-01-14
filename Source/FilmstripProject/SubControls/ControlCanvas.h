/*
  ==============================================================================

    New_ControlCanvas.h
    Created: 10 Dec 2024 5:50:36pm
    Author:  UFTHaq

  ==============================================================================
*/

// Put this to -> New_SubControls
// inherit juce::Component

// Control Canvas
// Canvas render work size
// - Knob : only size when has same width height, 
//     or just use both, and lock the aspect ratio
// - Slider : width and height, lock the aspect ratio
//   rotate button to determine the min max orientiation flow
// Color chooser
// 
// XY PAD, Z lighting
// Color chooser
// Intensity
// Bump
// Button Invert Bump

#pragma once

#include <JuceHeader.h>

#include "../Source/Globals.h"
#include "../Source/EnumClass.h"
#include "../Source/CustomComponents/CustomLookAndFeel.h"
#include "../Source/CustomComponents/CustomGroupComponent.h"
#include "../Source/CustomComponents/CustomColourSelectorWindow.h"
#include "../Source/CustomComponents/CustomSlider.h"

#include "../Source/FilmstripProject/Canvas/Canvas.h"

// Forward Declaration
class Canvas;

class ControlCanvas
    : public juce::Component
{
protected:
    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};
    FilmstripType filmstripType{};

    Canvas& canvas;

    CustomGroupComponent group{};

    juce::Label lockLabel{};
    juce::TextButton lockRatio{};

    juce::Label widthLabel{};
    CustomSlider width{};

    juce::Label heightLabel{};
    CustomSlider height{};

    juce::Label colorLabel{};
    juce::Label colorValue{};
    juce::TextButton colorButton{};
    juce::Colour canvasColor{};
    juce::String colorText{};
    std::unique_ptr<CustomColourSelectorWindow> colourSelectorWindow{};
    juce::TextButton copyValueButton{};


    // OpenGLComponentCanvas wil pass to here from FilmstripProject.h

    // Radio or toggle to lock ratio
    // Size width px slider
    // Size height px slider
    // Color chooser
    // 4 x 28 = 112 + title = 132


public:
    ControlCanvas(const FilmstripType& type, Canvas& canvas);
    ~ControlCanvas();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void setupGroupComponent();
    void setColourGroup();

    void setupLockRatio();
    void setupWidthSlider();
    void setupHeightSlider();
    void setupColorChooser();
    void showColorChooser();

    void resetCurrentTheme();

    double getValueWidth() const;
    double getValueHeight() const;

    std::function<void()> onSizeChangeForFooter{};
};
