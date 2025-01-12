/*
  ==============================================================================

    FilmstripProject.h
    Created: 10 Dec 2024 2:19:53pm
    Author:  UFTHaq

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "../Source/EnumClass.h"
#include "../Source/Globals.h"

#include "Asset.h"
#include "TabButton.h"
#include "NameAndMode.h"
#include "MainControls/MainControls.h"

#include "Canvas/Canvas.h"
#include "SubControls/SubControls.h"
#include "Footer/footer.h"

#include "../Source/FilmstripProject/SubControls/ControlLighting.h"
#include "../Source/FilmstripProject/SubControls/ControlCanvas.h"
#include "../Source/FilmstripProject/SubControls/ControlSliderStyle.h"

class FilmstripProject
{
protected:
    const int FOOTER_HEIGHT{ 25 };
    const int MAIN_CONTROL_W{ 240 };
    const int MODE_BUTTON_H{ 25 };
    const int SUB_CONTROL_W{ 190 };

    juce::Rectangle<int> boundary{};

    juce::String projectName{};
    FilmstripType filmstripType{};
    std::vector<std::unique_ptr<Asset>> assets{};
    std::vector<std::unique_ptr<AssetButtons>> assetsButtons{};
    
    TabButton tabButton;                   // Default Declaration
    NameAndMode nameAndMode;               // Default Declaration

    MainControls mainControls;             // Default Declaration
    Canvas canvas;                         // Default Declaration
    Footer footer;                         // Default Declaration

    ControlSliderStyle controlSliderStyle; // Default Declaration
    ControlLighting controlLighting;       // Default Declaration
    ControlCanvas controlCanvas;           // Default Declaration

    SubControls subControls;               // Default Declaration

    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(New_FilmstripProject)
public:
    FilmstripProject(const FilmstripType& type, juce::Rectangle<int> baseWorkspace);
    ~FilmstripProject();

    void resizing();        // Im forget what this for about to do

    void setupLayout(juce::Rectangle<int> baseWorkspace);
    void setupModeChanged(const juce::Rectangle<int> baseWorkspace);
    juce::Rectangle<int> getBaseWorkspace() const;

    void setupTabButtonAndEditorCallback();

    void setProjectName(juce::String& name);
    const juce::String& getProjectName() const;

    const FilmstripType& getFilmstripType() const;
    std::vector<std::unique_ptr<Asset>>& getAssets();
    void AddAsset(const AssetType& type);

    TabButton& getTabButton();
    NameAndMode& getNameAndModeControl();
    MainControls& getMainControls();
    Canvas& getCanvas();
    SubControls& getSubControls();
    Footer& getFooter();

    void resetCurrentTheme();
};
