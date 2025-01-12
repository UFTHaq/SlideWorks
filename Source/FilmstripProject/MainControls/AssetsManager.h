/*
  ==============================================================================

    AssetsManager.h
    Created: 10 Dec 2024 2:44:48pm
    Author:  UFTHaq

  ==============================================================================
*/

// Put this to -> MainControls
// inherit juce::Component

// Has Add new asset button
// Container
// viewport
// Has vector of buttons for viewport

#pragma once

#include <JuceHeader.h>

#include "../Source/EnumClass.h"
#include "../Source/CustomComponents/CustomLookAndFeel.h"
#include "../Source/Globals.h"

#include "AssetButtons.h"

#include "../Source/FilmstripProject/Asset.h"
#include "../Source/FilmstripProject/Canvas/Canvas.h"
#include "../Source/FilmstripProject/SubControls/SubControls.h"

class AssetsManager
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

    std::vector<std::unique_ptr<Asset>>& assets;               // Hold Ref
    std::vector<std::unique_ptr<AssetButtons>>& assetsButtons; // Hold Ref
    Canvas& canvas;                                            // Hold Ref
    SubControls& subControls;                                  // Hold Ref

public:
    AssetsManager(
        const FilmstripType& type
        , std::vector<std::unique_ptr<Asset>>& assets
        , std::vector<std::unique_ptr<AssetButtons>>& assetsButtons
        , Canvas& canvas
        , SubControls& subControls
    );
    ~AssetsManager();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void setupAddNewAssetButton();
    void setupAssetsViewport();
    void setupDefaultAssets();
    void addAssetsSystem();
    void handleDrag(AssetButtons* draggedButton, juce::Point<int> dropPoint);

    void resizeViewport(juce::Rectangle<int>& bounds);
    void resizeContainer();

    juce::TextButton& getAddNewAssetButton();
    std::vector<std::unique_ptr<AssetButtons>>& getAssetButtons();
    std::vector<std::unique_ptr<Asset>>& getAssets();
    SubControls& getSubControls() const;

    void addAssetButton(const juce::String& type);
    void fileChooserFunction(std::function<void(juce::String)> onFileSelected);
};