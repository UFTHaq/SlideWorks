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
#include "../Source/FilmstripProject/SubControls/New_SubControls.h"

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

    std::vector<std::unique_ptr<New_Asset>>& assets;    // hold the reference 
    std::vector<std::unique_ptr<New_AssetButtons>>& assetsButtons; // hold the reference
    New_Canvas& canvas;                                 // hold the reference 
    New_SubControls& subControls;                       // hold the reference

public:
    New_AssetsManager(
        const FilmstripType& type
        , std::vector<std::unique_ptr<New_Asset>>& assets
        , std::vector<std::unique_ptr<New_AssetButtons>>& assetsButtons
        , New_Canvas& canvas
        , New_SubControls& subControls
    );
    ~New_AssetsManager();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void setupAddNewAssetButton();
    void setupAssetsViewport();
    void setupDefaultAssets();
    void addAssetsSystem();
    void handleDrag(New_AssetButtons* draggedButton, juce::Point<int> dropPoint);

    void resizeViewport(juce::Rectangle<int>& bounds);
    void resizeContainer();

    juce::TextButton& getAddNewAssetButton();
    std::vector<std::unique_ptr<New_AssetButtons>>& getAssetButtons();
    std::vector<std::unique_ptr<New_Asset>>& getAssets();
    New_SubControls& getSubControls();

    void addAssetButton(const juce::String& type);
    void fileChooserFunction(std::function<void(juce::String)> onFileSelected);
};