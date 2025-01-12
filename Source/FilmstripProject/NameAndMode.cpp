/*
  ==============================================================================

    NameAndMode.cpp
    Created: 13 Dec 2024 5:18:54pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "NameAndMode.h"

NameAndMode::NameAndMode(const FilmstripType& type)
    : filmstripType(type)
    , customLookAndFeel(Globals::getCustomLookAndFeel())
{
    setupNameEditor();
    setupModeButtons();
}

NameAndMode::~NameAndMode()
{
}

void NameAndMode::resized()
{
    auto area = getLocalBounds();

    // NAME AND EDITOR
    auto nameArea = juce::Rectangle<int>{ area.getX(), area.getY(), NAME_WIDTH, area.getHeight() };
    nameLabel.setBounds(nameArea.reduced(1));

    auto editorArea = juce::Rectangle<int>{ area.getX() + (NAME_WIDTH - 1), area.getY(), NAME_EDITOR_WIDTH, area.getHeight() };
    nameEditor.setBounds(editorArea.reduced(1));

    // MODE BUTTONS
    auto modeButtonsArea = juce::Rectangle<int>{ area.getWidth() - MODE_BUTTON_WIDTH, area.getY(), MODE_BUTTON_WIDTH, area.getHeight() };
    simulationButton.setBounds(modeButtonsArea.reduced(1));

    modeButtonsArea.setX(modeButtonsArea.getX() - (MODE_BUTTON_WIDTH - 1));
    previewButton.setBounds(modeButtonsArea.reduced(1));

    modeButtonsArea.setX(modeButtonsArea.getX() - (MODE_BUTTON_WIDTH - 1));
    editButton.setBounds(modeButtonsArea.reduced(1));
}

void NameAndMode::mouseDown(const juce::MouseEvent& event)
{
    if (nameEditor.isMouseButtonDown())
    {
        nameEditor.grabKeyboardFocus();
    }
    else if (nameEditor.isMouseButtonDownAnywhere())
    {
        nameEditor.giveAwayKeyboardFocus();
        nameEditor.setReadOnly(true);
    }
}

void NameAndMode::mouseDoubleClick(const juce::MouseEvent& event)
{
    if (event.eventComponent == &nameEditor)
    {
        nameEditor.setReadOnly(false);
        nameEditor.grabKeyboardFocus();

        DBG("CLICK FROM NAME EDITOR");
    }
}

void NameAndMode::setupNameEditor()
{
    auto font = customLookAndFeel->getFontRobotoCondensedRegular().withHeight(16.0F);

    nameLabel.setFont(font);
    nameLabel.setText("Name :", juce::dontSendNotification);
    nameLabel.setComponentID("Label_ID_O1_Naming");
    nameLabel.setJustificationType(juce::Justification::centredLeft);
    nameLabel.setColour(juce::Label::backgroundColourId, customLookAndFeel->getCurrentTheme().NamingLabel);
    nameLabel.setEditable(false, false);
    addAndMakeVisible(nameLabel);

    nameEditor.setFont(font);
    nameEditor.setText("", juce::dontSendNotification);
    nameEditor.setTextToShowWhenEmpty("Untitled", customLookAndFeel->getCurrentTheme().CustomDarkGrey);
    nameEditor.setComponentID("Label_ID_01_NamingEditor");
    nameEditor.setColour(juce::Label::backgroundWhenEditingColourId, customLookAndFeel->getCurrentTheme().TransparentBlack);
    nameEditor.setColour(juce::TextEditor::outlineColourId, customLookAndFeel->getCurrentTheme().CustomGrey.brighter());
    nameEditor.setColour(juce::TextEditor::highlightColourId, customLookAndFeel->getCurrentTheme().TitleBar);
    nameEditor.setColour(juce::TextEditor::textColourId, customLookAndFeel->getCurrentTheme().CustomDarkGrey);
    nameEditor.setColour(juce::CaretComponent::caretColourId, customLookAndFeel->getCurrentTheme().TitleBar.darker());
    nameEditor.setReadOnly(true);
    nameEditor.setMultiLine(false, false);
    nameEditor.onReturnKey = [this]()
        {
            nameEditor.giveAwayKeyboardFocus();
            nameEditor.setReadOnly(true);
        };
    nameEditor.onTextChange = [this]()
        {
            if (onTextChangedCallback)
                onTextChangedCallback(nameEditor.getText());
        };
    nameEditor.addMouseListener(this, true);
    addAndMakeVisible(nameEditor);
}

void NameAndMode::setupModeButtons()
{
    editButton.setButtonText("Edit");
    editButton.setComponentID("Buttons_ID_05_MODE");
    editButton.setToggleState(true, juce::dontSendNotification);
    editButton.onClick = [this]()
        {
            mode = WorkingMode::EDIT_MODE;
            setToggling(mode);
            notifyModeChange();
        };
    addAndMakeVisible(editButton);

    previewButton.setButtonText("Preview");
    previewButton.setComponentID("Buttons_ID_05_MODE");
    previewButton.setToggleState(false, juce::dontSendNotification);
    previewButton.onClick = [this]()
        {
            mode = WorkingMode::PREVIEW_MODE;
            setToggling(mode);
            notifyModeChange();
        };
    addAndMakeVisible(previewButton);

    simulationButton.setButtonText("Simulation");
    simulationButton.setComponentID("Buttons_ID_05_MODE");
    simulationButton.setToggleState(false, juce::dontSendNotification);
    simulationButton.onClick = [this]() 
        { 
            mode = WorkingMode::SIMULATION_MODE;
            setToggling(mode);
            notifyModeChange();
        };
    addAndMakeVisible(simulationButton);
}

void NameAndMode::togglingButtons(juce::TextButton& toActive, juce::TextButton& toDeactive1, juce::TextButton& toDeactive2)
{
    toActive.setToggleState(true, juce::NotificationType::dontSendNotification);
    toDeactive1.setToggleState(false, juce::NotificationType::dontSendNotification);
    toDeactive2.setToggleState(false, juce::NotificationType::dontSendNotification);
}

void NameAndMode::setToggling(WorkingMode Workmode)
{
    switch (Workmode)
    {
    case WorkingMode::EDIT_MODE:
        togglingButtons(editButton, previewButton, simulationButton);
        break;
    case WorkingMode::PREVIEW_MODE:
        togglingButtons(previewButton, simulationButton, editButton);
        break;
    case WorkingMode::SIMULATION_MODE:
        togglingButtons(simulationButton, editButton, previewButton);
        break;
    default:
        break;
    }
}

void NameAndMode::notifyModeChange()
{
    if (onModeChange)
        onModeChange();
}

WorkingMode NameAndMode::getMode() const
{
    return mode;
}

juce::TextEditor& NameAndMode::getNameEditor()
{
    return nameEditor;
}

juce::TextButton& NameAndMode::getSimulationButton()
{
    return simulationButton;
}

juce::TextButton& NameAndMode::getPreviewButton()
{
    return previewButton;
}

juce::TextButton& NameAndMode::getEditButton()
{
    return editButton;
}
