/*
  ==============================================================================

    Canvas.cpp
    Created: 10 Dec 2024 6:15:51pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "Canvas.h"

Canvas::Canvas
(
	const FilmstripType& filmstripType
	, std::vector<std::unique_ptr<Asset>>& assets
	, std::vector<std::unique_ptr<AssetButtons>>& assetsButtons
	, SubControls& subControls
)
	: filmstripType(filmstripType)
	, assets(assets)
	, assetsButtons(assetsButtons)
	, subControls(subControls)
	, canvasEdit(filmstripType, assets)
	, customLookAndFeel(Globals::getCustomLookAndFeel())
{
	setMode(mode);
	addAndMakeVisible(canvasEdit);
	canvasEdit.setInterceptsMouseClicks(false, true);
}

Canvas::~Canvas()
{
}

void Canvas::paint(juce::Graphics& g)
{
	drawBackground(g);
}

void Canvas::resized()
{
	bounds = getLocalBounds();

	canvasEdit.setBounds(bounds);

	canvasEdit.resized();
	canvasPreview.resized();
	canvasSimulation.resized();
}

void Canvas::mouseDown(const juce::MouseEvent& event)
{
	for (auto& btn : assetsButtons)
	{
		btn->selectThis(false);
	}

	subControls.displayDefaultSubControl();
}

void Canvas::drawBackground(juce::Graphics& g)
{
	g.setColour(customLookAndFeel->getCurrentTheme().SlideworksBaseColour);
	g.fillRoundedRectangle(bounds.toFloat(), 1);

	g.setColour(customLookAndFeel->getCurrentTheme().CustomDarkGrey);
	g.drawRoundedRectangle(bounds.toFloat().reduced(0.3F), 1, 0.3F);
}

void Canvas::setMode(WorkingMode mode)
{
	this->mode = mode;

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

WorkingMode Canvas::getMode() const
{
	return mode;
}


CanvasEdit& Canvas::getCanvasEdit()
{
	return canvasEdit;
}

CanvasPreview& Canvas::getCanvasPreview()
{
	return canvasPreview;
}

CanvasSimulation& Canvas::getCanvasSimulation()
{
	return canvasSimulation;
}
