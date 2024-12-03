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
#include "Asset.h"
#include "EnumClass.h"


class FilmstripProject
    : public juce::Component
{
protected:
    juce::String name{ "Untitled" };
    juce::TextButton closeButton{};

    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};

    std::vector< std::unique_ptr<Asset>> assets{};

    int minFrames{ 7 };
    int maxFrames{ 150 };
    int totalFrames{ 121 };

    FilmstripOrientation orientation{ FilmstripOrientation::VERTICAL_FILMSTRIP };
    WorkingMode workingMode{ WorkingMode::EDIT_MODE };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilmstripProject)

public:
    FilmstripProject();
    ~FilmstripProject();

    void resized() override;
    void paint(juce::Graphics& g) override;

    virtual juce::String getFilmstripType();
    virtual double getFilmstripSizeCalc();
    virtual juce::String getFilmstripSizeStatus();

    juce::String getProjectName();
    void setProjectName(juce::String newName);

    WorkingMode getWorkingMode();
    void setWorkingMode(WorkingMode mode);

    int getMinFrames() const;
    int getMaxFrames() const;
    int getTotalFrames() const;
    void setTotalFrames(int newValue);

    FilmstripOrientation getOrientation() const;
    void setOrientation(FilmstripOrientation orientation);

    juce::TextButton tabButton{};
    std::function<void(FilmstripProject*)> onDeleteRequest{};

    const std::vector<std::unique_ptr<Asset>>& getAsset() const;
    void addAsset(const juce::String& type);
    virtual void initializeAssets() = 0;

    virtual juce::String getAnglesOrThumbPosText();
    virtual AnglesOrThumbPos getAnglesOrThumbPos();
};