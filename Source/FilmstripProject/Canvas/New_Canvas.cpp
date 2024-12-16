/*
  ==============================================================================

    New_Canvas.cpp
    Created: 10 Dec 2024 6:15:51pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "New_Canvas.h"

New_Canvas::New_Canvas()
	: customLookAndFeel(Globals::getCustomLookAndFeel())
{
}

New_Canvas::~New_Canvas()
{
}

void New_Canvas::paint(juce::Graphics& g)
{
	drawBackground(g);
}

void New_Canvas::resized()
{
	bounds = getLocalBounds();
}

void New_Canvas::drawBackground(juce::Graphics& g)
{
	g.setColour(customLookAndFeel->getCurrentTheme().SlideworksBaseColour);
	g.fillRoundedRectangle(bounds.toFloat(), 1);

	g.setColour(customLookAndFeel->getCurrentTheme().CustomDarkGrey);
	g.drawRoundedRectangle(bounds.toFloat().reduced(0.3F), 1, 0.3F);
}

void New_Canvas::setMode(WorkingMode mode)
{
	switch (mode)
	{
	case WorkingMode::EDIT_MODE:

		canvasEdit.setEnabled(true);
		canvasEdit.setVisible(true);

		canvasPreview.setEnabled(false);
		canvasPreview.setVisible(false);

		canvasSimulation.setEnabled(false);
		canvasSimulation.setVisible(false);
		
		break;

	case WorkingMode::PREVIEW_MODE:

		canvasEdit.setEnabled(false);
		canvasEdit.setVisible(false);

		canvasPreview.setEnabled(true);
		canvasPreview.setVisible(true);

		canvasSimulation.setEnabled(false);
		canvasSimulation.setVisible(false);

		break;

	case WorkingMode::SIMULATION_MODE:

		canvasEdit.setEnabled(false);
		canvasEdit.setVisible(false);

		canvasPreview.setEnabled(false);
		canvasPreview.setVisible(false);

		canvasSimulation.setEnabled(true);
		canvasSimulation.setVisible(true);

		break;
	default:
		break;
	}
}
