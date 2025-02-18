/*
  ==============================================================================

    AssetButtons.h
    Created: 10 Dec 2024 5:22:46pm
    Author:  UFTHaq

  ==============================================================================
*/

// Put this to -> AssetsManager
// inherit juce::Component

// Same as AssetButtons

#pragma once

#include <JuceHeader.h>

#include "../Source/CustomComponents/CustomLookAndFeel.h"
#include "../Source/Globals.h"

class AssetButtons
    : public juce::Component
{
protected:
    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};

    juce::Font font{ juce::FontOptions{} };
    juce::String type{};
    juce::String fileName{};

    juce::TextButton loadButton{};
    juce::TextButton visibleButton{};
    juce::TextButton deleteButton{};

    juce::Rectangle<int> boundsType{};
    juce::Rectangle<int> boundsFile{};

    size_t index{};

    bool isSelected{ false };
    bool isDragging{ false };
    juce::Point<int> dragStartPos{};

public:
    AssetButtons(const juce::String& type);
    ~AssetButtons();

    void paint(juce::Graphics& g) override;
    void resized() override;
    
    void mouseDown(const juce::MouseEvent& event) override;
    void mouseDrag(const juce::MouseEvent& event) override;
    void mouseUp(const juce::MouseEvent& event) override;

    std::function<void(AssetButtons*)> clickThis{};
    bool isThisSelected() const;
    void selectThis(const bool select);
    juce::TextButton& getLoadImageButton();
    juce::TextButton& getVisibleButton();
    juce::TextButton& getDeleteButton();

    void setNameDisplay(const juce::String& fileName);
    juce::String getNameDisplay() const;

    void setIndex(const size_t index);
    const size_t& getIndex() const;

    std::function<void(AssetButtons*, juce::Point<int>)> onDragCallback{};

};