/*
  ==============================================================================

    ControlLighting.h
    Created: 10 Dec 2024 5:50:02pm
    Author:  UFTHaq

  ==============================================================================
*/

// Put this to -> SubControls
// inherit juce::Component

// CustomGroupComponent
// Control Lighting
// XY PAD, Z lighting
// Color chooser
// Intensity
// Bump
// Button Invert Bump

#pragma once

#include <JuceHeader.h>

#include "../Source/CustomComponents/CustomGroupComponent.h"
#include "../Source/CustomComponents/CustomLookAndFeel.h"
#include "../Source/CustomComponents/CustomColourSelectorWindow.h"
#include "../Source/EnumClass.h"
#include "../Source/Globals.h"

#include "XYPad.h"

class ControlLighting
    : public juce::Component
    , public juce::Value::Listener
{
protected:
    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};
    FilmstripType filmstripType{};

    int totalDivider{};

    CustomGroupComponent group{};

    XYPad xyPad{};                // Control XY LIGHTING
    juce::Slider zPad{};          // Control Z LIGHTING

    juce::Label xyLabel{};        // XY LABEL
    juce::Label zLabel{};         // Z LABEL

    juce::TextButton lockButton{};
    juce::Label lockLabel{};

    juce::Label colorLabel{};
    juce::Label colorValue{};
    juce::TextButton colorButton{};
    juce::Colour lightingColor{};
    juce::String colorText{};
    std::unique_ptr<CustomColourSelectorWindow> colourSelectorWindow{};
    juce::TextButton copyValueButton{};

    juce::Slider intensity{};
    juce::Label intensityLabel{};
    
    juce::Slider bump{};
    juce::Label bumpLabel{};

    juce::TextButton invertBump{};


    // OpenGLComponentCanvas wil pass to here from FilmstripProject.h

    // XY                                 = 4 + 1 (label) = 5
    // Z slider                           
    // Color label                        = 1
    // Color Chooser with hex code        
    // Intensity label                    = 1
    // Intensity slider
    // Bump label                         = 1
    // Bump slider
    // juce::TextButton invertBump{};     = 1
    // 9 x 28 = 252 + title = 272

    // if FilmstripType == Slider.
    // we can lock put the light on base canvas or follow through the thumb pos
    // 10 x 28 = 280 + title = 300

public:
    ControlLighting(const FilmstripType& type);
    ~ControlLighting();

    void paint(juce::Graphics& g) override;
    void resized() override;
    void valueChanged(juce::Value& value) override;

    void setupGroupComponent();
    void setColourGroup();

    void setupDivider();

    void setupXYPad();
    void setupZPad();
    void setColourXYZPad();  // This is not necessary, will be deleted
    void setupXYZLabel();
    void setupLockLighting();
    void setupColorChooser();
    void showColorChooser();
    void setupIntensitySlider();
    void setupBumpSlider();
    void setupInvertButton();

    void resetCurrentTheme();
};