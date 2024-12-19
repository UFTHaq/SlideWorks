/*
  ==============================================================================

    New_MainControls.h
    Created: 10 Dec 2024 4:01:39pm
    Author:  UFTHaq

  ==============================================================================
*/

// Put this to -> New_FilmstripProject
// inherit juce::Component

// Banner
// Export Button

#pragma once

#include <JuceHeader.h>

#include "New_MainControls.h"

#include "../Source/EnumClass.h"
#include "../Source/Globals.h"
#include "../Source/FilmstripProject/New_Asset.h"

#include "New_AssetsManager.h"
#include "New_TotalFrames.h"
#include "New_FilmstripOrientation.h"
#include "New_KnobAngles.h"
#include "New_ThumbPositions.h"

class New_MainControls
    : public juce::Component
{
protected:
    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};
    std::vector<std::unique_ptr<New_Asset>>& assets;  // Passing from New_FilmstripProject -> New_MainControls -> New_AssetsManager
    FilmstripType filmstripType{};
    juce::Rectangle<int> bounds{};

    juce::Rectangle<int> bannerRect{};
    juce::Rectangle<int> bannerTextBounds{};
    juce::Label banner{};
    juce::Font fontBanner{ juce::FontOptions{} };
    juce::TextButton exportButton{};

    New_AssetsManager assetsManager; // Default declaration
    New_TotalFrames totalFramesControl{};
    New_FilmstripOrientation orientationControl{};
    New_KnobAngles anglesControls{};
    New_ThumbPositions thumbControls{};

    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(New_MainControls)

public:
    New_MainControls(const FilmstripType& filmstripType, std::vector<std::unique_ptr<New_Asset>>& assets);
    ~New_MainControls();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void drawBackground(juce::Graphics& g);
    void drawBanner(juce::Graphics& g);

    void setupBanner(const juce::String& text);
    void setupExportButton();

    New_AssetsManager& getAssetsManager();
    New_FilmstripOrientation& getOrientationControl();
    New_KnobAngles& getAnglesControls();
    New_ThumbPositions& getThumbControls();

    void resetCurrentTheme();
};