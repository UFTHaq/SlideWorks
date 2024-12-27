/*
  ==============================================================================

    New_AssetButtons.cpp
    Created: 10 Dec 2024 5:22:46pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "New_AssetButtons.h"

New_AssetButtons::New_AssetButtons(const juce::String& type)
    : type(type), customLookAndFeel(Globals::getCustomLookAndFeel())
{
    visibleButton.setComponentID("Buttons_ID_12_VISIBLE_ASSET");
    visibleButton.setToggleState(false, juce::dontSendNotification);
    addAndMakeVisible(visibleButton);

    deleteButton.setComponentID("Buttons_ID_13_DELETE_ASSET");
    deleteButton.setToggleState(false, juce::dontSendNotification);
    addAndMakeVisible(deleteButton);

    loadButton.setButtonText("Load Image");
    loadButton.setComponentID("Buttons_ID_14_LOAD_ASSET");
    loadButton.setToggleState(false, juce::dontSendNotification);
    addAndMakeVisible(loadButton);

    visibleButton.setEnabled(false);

    font = customLookAndFeel->getFontRobotoCondensedRegular().withHeight(16.0F);
}

New_AssetButtons::~New_AssetButtons()
{
}

void New_AssetButtons::paint(juce::Graphics& g)
{
    g.setColour(isSelected ? customLookAndFeel->getCurrentTheme().NamingLabel : customLookAndFeel->getCurrentTheme().SlideworksBaseColour);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 1);

    g.setColour(customLookAndFeel->getCurrentTheme().OutlineControl.darker());
    g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(0.4F), 1, 0.4F);

    g.setColour(isSelected ? customLookAndFeel->getCurrentTheme().FontWhite: customLookAndFeel->getCurrentTheme().FontBlack);
    g.setFont(font);
    g.drawFittedText(type, boundsType, juce::Justification::centredLeft, 1);
    g.drawFittedText(fileName, boundsFile, juce::Justification::centredLeft, 1, 0.75F);
}

void New_AssetButtons::resized()
{
    auto bounds = getLocalBounds();
    auto center = bounds;
    auto buttonWidth = bounds.getHeight();

    auto deleteArea = bounds.removeFromRight(buttonWidth);
    deleteButton.setBounds(deleteArea.reduced(1));

    auto visibleArea = bounds.removeFromRight(buttonWidth);
    visibleArea.setX(visibleArea.getX() + 1);
    visibleButton.setBounds(visibleArea.reduced(1));

    auto loadArea = bounds.removeFromRight(120);
    loadArea.setX(loadArea.getX() + 1);
    loadArea = loadArea.withSizeKeepingCentre(loadArea.getWidth(), loadArea.getHeight() - 2);
    loadButton.setBounds(loadArea);

    // Text Bounds
    boundsType = getLocalBounds();
    boundsType.removeFromLeft(5);
    boundsType = boundsType.removeFromLeft(35);

    boundsFile = getLocalBounds();
    boundsFile.removeFromLeft(45);
    boundsFile.removeFromRight(50);
}

void New_AssetButtons::mouseDown(const juce::MouseEvent& event)
{
    dragStartPos = event.getPosition();
    isDragging = false;
}

void New_AssetButtons::mouseDrag(const juce::MouseEvent& event)
{
    auto delta = event.getPosition() - dragStartPos;

    if (delta.getDistanceFromOrigin() > 4) isDragging = true;

    if (isDragging)
    {
        auto parentBounds = getParentComponent()->getLocalBounds();
        auto currentBounds = getBounds();

        auto newY = juce::jlimit(parentBounds.getY(), parentBounds.getBottom() - currentBounds.getHeight(), currentBounds.getY() + delta.getY());
        setBounds(currentBounds.withY(newY));

        if (onDragCallback)
            onDragCallback(this, getBounds().getCentre());

        toFront(false);
    }
}

void New_AssetButtons::mouseUp(const juce::MouseEvent& event)
{
    if (!isDragging)
    {
        if (clickThis)
            clickThis(this);
    }
    else
    {
        if (onDragCallback)
            onDragCallback(this, getBounds().getCentre());

        setBounds(getBounds().withPosition(1, int(getIndex()) * (getHeight() + 1) + 1));
    }

    isDragging = false;
}

bool New_AssetButtons::isThisSelected() const
{
    return isSelected;
}

void New_AssetButtons::selectThis(const bool select)
{
    isSelected = select;
    repaint();
}

juce::TextButton& New_AssetButtons::getLoadImageButton()
{
    return loadButton;
}

juce::TextButton& New_AssetButtons::getVisibleButton()
{
    return visibleButton;
}

juce::TextButton& New_AssetButtons::getDeleteButton()
{
    return deleteButton;
}

void New_AssetButtons::setNameDisplay(const juce::String& fileName)
{
    if (fileName.isNotEmpty())
    {
        this->fileName = ": " + fileName;

        loadButton.setVisible(false);
        loadButton.setEnabled(false);
    }
    else
    {
        jassertfalse;
    }
}

juce::String New_AssetButtons::getNameDisplay() const
{
    return fileName;
}

void New_AssetButtons::setIndex(const size_t index)
{
    this->index = index;
}

const size_t& New_AssetButtons::getIndex() const
{
    return index;
}
