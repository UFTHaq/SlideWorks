/*
  ==============================================================================

    FilmstripProject.cpp
    Created: 22 Nov 2024 2:26:03pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "FilmstripProject.h"

FilmstripProject::FilmstripProject()
{
}

FilmstripProject::~FilmstripProject()
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
