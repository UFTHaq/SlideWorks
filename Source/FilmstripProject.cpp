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
