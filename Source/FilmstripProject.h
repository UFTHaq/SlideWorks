/*
  ==============================================================================

    FilmstripProject.h
    Created: 22 Nov 2024 2:26:03pm
    Author:  UFTHaq

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomLookAndFeel.h"
#include "Globals.h"

enum class FilmstripOrientation
{
    VERTICAL_FILMSTRIP,
    HORIZONTAL_FILMSTRIP
};

enum class WorkingMode
{
    EDIT_MODE,
    PREVIEW_MODE,
    SIMULATION_MODE
};



class FilmstripProject
    : public juce::Component
{
protected:
    juce::String name{ "Untitled" };
    juce::TextButton closeButton{};

    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};

    int totalFrames{ 0 };
    FilmstripOrientation orientation{ FilmstripOrientation::VERTICAL_FILMSTRIP };
    WorkingMode workingMode{ WorkingMode::EDIT_MODE };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilmstripProject)

public:
    FilmstripProject();
    ~FilmstripProject();

    void resized() override;
    void paint(juce::Graphics& g) override;

    virtual double getFilmstripSizeCalc();
    virtual juce::String getFilmstripSizeStatus();

    juce::String getProjectName();
    void setProjectName(juce::String newName);

    juce::TextButton tabButton{};
    std::function<void(FilmstripProject*)> onDeleteRequest{};
};