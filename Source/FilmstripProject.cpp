/*
  ==============================================================================

    FilmstripProject.cpp
    Created: 22 Nov 2024 2:26:03pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "FilmstripProject.h"

FilmstripProject::FilmstripProject() : customLookAndFeel(Globals::getCustomLookAndFeel())
{
    tabButton.setButtonText(name);
    tabButton.setComponentID("Buttons_ID_03_TAB");
    tabButton.setToggleState(true, juce::dontSendNotification);
    tabButton.setLookAndFeel(customLookAndFeel.get());
    addAndMakeVisible(tabButton);

    closeButton.setButtonText("");
    closeButton.setComponentID("Buttons_ID_04_TAB_CLOSE");
    closeButton.setLookAndFeel(customLookAndFeel.get());
    closeButton.onClick = [this]()
        {
            if (onDeleteRequest)
                onDeleteRequest(this);
        };
    addAndMakeVisible(closeButton);
}

FilmstripProject::~FilmstripProject()
{

}

void FilmstripProject::resized()
{
    tabButton.setBounds(getLocalBounds());

    auto space = 5;
    auto copyLocalBounds = getLocalBounds();
    auto closeButtonArea = copyLocalBounds.removeFromRight(copyLocalBounds.getHeight());
    closeButton.setBounds(closeButtonArea);
}

void FilmstripProject::paint(juce::Graphics& g)
{
}

juce::String FilmstripProject::getFilmstripType()
{
    return juce::String("BASE CLASS NOT HAVE TYPE");
}

double FilmstripProject::getFilmstripSizeCalc()
{
    return 0.0;
}

juce::String FilmstripProject::getFilmstripSizeStatus()
{
    return juce::String("OKAY TESTING");
}

juce::String FilmstripProject::getProjectName()
{
    return this->name;
}

void FilmstripProject::setProjectName(juce::String newName)
{
    this->name = newName;
    this->tabButton.setButtonText(newName);
}

WorkingMode FilmstripProject::getWorkingMode()
{
    return workingMode;
}

void FilmstripProject::setWorkingMode(WorkingMode mode)
{
    this->workingMode = mode;
}

int FilmstripProject::getMinFrames() const
{
    return minFrames;
}

int FilmstripProject::getMaxFrames() const
{
    return maxFrames;
}

int FilmstripProject::getTotalFrames() const
{
    return totalFrames;
}

void FilmstripProject::setTotalFrames(int newValue)
{
    this->totalFrames = newValue;
}

FilmstripOrientation FilmstripProject::getOrientation() const
{
    return FilmstripOrientation(orientation);
}

void FilmstripProject::setOrientation(FilmstripOrientation orientation)
{
    this->orientation = orientation;
}

std::vector<Asset>& FilmstripProject::getAssets()
{
    return assets;
}

void FilmstripProject::addAsset(const juce::String& type)
{
    assets.emplace_back(type);
}

juce::String FilmstripProject::getAnglesOrThumbPosText()
{
    return juce::String();
}

AnglesOrThumbPos FilmstripProject::getAnglesOrThumbPos()
{
    return AnglesOrThumbPos();
}
