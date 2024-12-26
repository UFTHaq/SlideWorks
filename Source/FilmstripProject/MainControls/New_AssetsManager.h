/*
  ==============================================================================

    New_AssetsManager.h
    Created: 10 Dec 2024 2:44:48pm
    Author:  UFTHaq

  ==============================================================================
*/

// Put this to -> New_MainControls
// inherit juce::Component

// Has Add new asset button
// Container
// viewport
// Has vector of buttons for viewport

#pragma once

#include <JuceHeader.h>

#include "../Source/EnumClass.h"
#include "../Source/CustomLookAndFeel.h"
#include "../Source/Globals.h"

#include "New_AssetButtons.h"

#include "../Source/FilmstripProject/New_Asset.h"
#include "../Source/FilmstripProject/Canvas/New_Canvas.h"

class New_AssetsManager
    : public juce::Component
{
protected:
    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};

    FilmstripType filmstripType{};
    juce::TextButton addNewAssetButton{};
    juce::Viewport assetsViewport{};
    juce::Rectangle<int> viewportRect{};
    juce::Component assetsContainer{};
    std::unique_ptr<juce::FileChooser> fileChooser{};

    std::vector<std::unique_ptr<New_Asset>>& assets;
    std::vector<std::unique_ptr<New_AssetButtons>> assetsButtons{};
    New_Canvas& canvas;

public:
    New_AssetsManager(const FilmstripType& filmstripType, std::vector<std::unique_ptr<New_Asset>>& assets, New_Canvas& canvas);
    void setupAssetsViewport();
    void setupAddNewAssetButton();
    void addAssetsSystem();
    ~New_AssetsManager();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void resizeViewport();

    juce::TextButton& getAddNewAssetButton();
    std::vector<std::unique_ptr<New_AssetButtons>>& getAssetButtons();
    std::vector<std::unique_ptr<New_Asset>>& getAssets();

    void addAssetButton(const juce::String& type);
    void fileChooserFunction(std::function<void(juce::String)> onFileSelected);
};