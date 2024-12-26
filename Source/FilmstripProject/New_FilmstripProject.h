/*
  ==============================================================================

    New_FilmstripProject.h
    Created: 10 Dec 2024 2:19:53pm
    Author:  UFTHaq

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "../Source/EnumClass.h"
#include "../Source/Globals.h"

#include "New_Asset.h"
#include "New_TabButton.h"
#include "New_NameAndMode.h"
#include "MainControls/New_MainControls.h"

#include "Canvas/New_Canvas.h"
#include "SubControls/New_SubControls.h"
#include "Footer/footer.h"

class New_FilmstripProject
{
protected:
    const int FOOTER_HEIGHT{ 25 };
    const int MAIN_CONTROL_W{ 240 };
    const int MODE_BUTTON_H{ 25 };
    const int SUB_CONTROL_W{ 190 };

    juce::Rectangle<int> boundary{};

    juce::String projectName{};
    FilmstripType filmstripType{};
    std::vector<std::unique_ptr<New_Asset>> assets{};
    
    New_TabButton tabButton{};
    New_NameAndMode nameAndMode{};
    New_MainControls mainControls;  // Default declaration

    New_Canvas canvas;  // Default declaration
    New_SubControls subControls{};
    Footer footer{};

    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(New_FilmstripProject)
public:
    New_FilmstripProject(const FilmstripType& filmstripType, juce::Rectangle<int> baseWorkspace);
    ~New_FilmstripProject();

    void resizing();

    void setupLayout(juce::Rectangle<int> baseWorkspace);
    void setupModeChanged(const juce::Rectangle<int> baseWorkspace);
    juce::Rectangle<int> getBaseWorkspace() const;

    void setupTabButtonAndEditorCallback();

    void setProjectName(juce::String& name);
    const juce::String& getProjectName() const;

    const FilmstripType& getFilmstripType() const;
    std::vector<std::unique_ptr<New_Asset>>& getAssets();
    void AddAsset(const AssetType& type);

    New_TabButton& getTabButton();
    New_NameAndMode& getNameAndModeControl();
    New_MainControls& getMainControls();
    New_Canvas& getCanvas();
    New_SubControls& getSubControls();
    Footer& getFooter();

    void resetCurrentTheme();
};
