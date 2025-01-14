/*
  ==============================================================================

    MainControls.h
    Created: 10 Dec 2024 4:01:39pm
    Author:  UFTHaq

  ==============================================================================
*/

// Put this to -> FilmstripProject
// inherit juce::Component

// Banner
// Export Button

#pragma once

#include <JuceHeader.h>

#include "../Source/EnumClass.h"
#include "../Source/Globals.h"
#include "../Source/CustomComponents/CustomLookAndFeel.h"
#include "../Source/FilmstripProject/Asset.h"

#include "AssetsManager.h"
#include "TotalFrames.h"
#include "FilmstripOrientation.h"
#include "KnobAngles.h"
#include "ThumbPositions.h"

#include "../Source/FilmstripProject/Canvas/Canvas.h"
#include "../Source/FilmstripProject/SubControls/SubControls.h"

class MainControls
    : public juce::Component
{
protected:
    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};
    FilmstripType filmstripType{};

    std::vector<std::unique_ptr<Asset>>& assets;               // Hold Ref Passing from FilmstripProject -> MainControls -> AssetsManager
    std::vector<std::unique_ptr<AssetButtons>>& assetButtons;  // Hold Ref
    Canvas& canvas;                                            // Hold Ref
    SubControls& subControls;                                  // Hold Ref

    juce::Rectangle<int> bounds{};
    juce::Rectangle<int> bannerRect{};

    juce::Rectangle<int> bannerTextBounds{};
    juce::Label banner{};
    juce::Font fontBanner{ juce::FontOptions{} };
    juce::TextButton exportButton{};

    AssetsManager assetsManager;                               // Default declaration
    TotalFrames totalFramesControl{};
    FilmstripOrientation orientationControl{};
    KnobAngles anglesControls{};
    ThumbPositions thumbControls{};

    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainControls)

public:
    MainControls
    (
        const FilmstripType& type
        , std::vector<std::unique_ptr<Asset>>& assets
        , std::vector<std::unique_ptr<AssetButtons>>& assetButtons
        , Canvas& canvas
        , SubControls& subControls
    );
    ~MainControls();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void drawBackground(juce::Graphics& g);
    void drawBanner(juce::Graphics& g);

    void setupBanner(const juce::String& text);
    void setupExportButton();

    AssetsManager& getAssetsManager();
    FilmstripOrientation& getOrientationControl();
    KnobAngles& getAnglesControls();
    ThumbPositions& getThumbControls();

    Canvas& getCanvas();
    SubControls& getSubControls();

    int getTotalFrames() const;

    void resetCurrentTheme();

    void setupControlsCallback();
    std::function<void()> onSizeChangeForFooter{};
};