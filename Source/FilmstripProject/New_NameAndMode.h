/*
  ==============================================================================

    New_NameAndMode.h
    Created: 13 Dec 2024 5:18:53pm
    Author:  UFTHaq

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "../Source/CustomComponents/CustomLookAndFeel.h"
#include "../Source/Globals.h"
#include "../Source/EnumClass.h"

class New_NameAndMode
    : public juce::Component
{
protected:
    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};

    WorkingMode mode{ WorkingMode::EDIT_MODE };

    const int NAME_WIDTH{ 55 };
    const int NAME_EDITOR_WIDTH{ 200 };

    juce::Label nameLabel{};
    juce::TextEditor nameEditor{};

    const int MODE_BUTTON_WIDTH{ 80 };

    juce::TextButton simulationButton{};
    juce::TextButton previewButton{};
    juce::TextButton editButton{};

    void notifyModeChange();

public:
    New_NameAndMode();
    ~New_NameAndMode();

    void resized() override;
    void mouseDown(const juce::MouseEvent& event) override;
    void mouseDoubleClick(const juce::MouseEvent& event) override;

    void setupNameEditor();
    void setupModeButtons();
    void togglingButtons(juce::TextButton& toActive, juce::TextButton& toDeactive1, juce::TextButton& toDeactive2);
    void setToggling(WorkingMode Workmode);

    WorkingMode getMode() const;
    std::function<void()> onModeChange{};

    std::function<void(const juce::String&)> onTextChangedCallback{};
    juce::TextEditor& getNameEditor();

    juce::TextButton& getSimulationButton();
    juce::TextButton& getPreviewButton();
    juce::TextButton& getEditButton();

};