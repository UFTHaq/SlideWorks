/*
  ==============================================================================

    Footer.h
    Created: 15 Dec 2024 8:52:43pm
    Author:  UFTHaq

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "../Source/Globals.h"
#include "../Source/EnumClass.h"
#include "../Source/CustomComponents/CustomLookAndFeel.h"
#include "../Source/FilmstripProject/MainControls/MainControls.h"
#include "../Source/FilmstripProject/SubControls/ControlCanvas.h"

class Footer
    : public juce::Component
{
protected:
    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};
    FilmstripType filmstripType{};

    MainControls& mainControls;        // Hold Ref
    ControlCanvas& controlCanvas;      // Hold Ref

    juce::Rectangle<int> bounds{};
    juce::String text{};

    juce::Rectangle<int> recomendedSize{};
    juce::String recomendedSizeStr{ "Recomended size : 5 to 8 MB" };

    juce::Rectangle<int> projectSize{};
    juce::String projectSizeStr{ "Size : 300 x 300 x 121 = 10.890.000 PX = 10.8 MB" };
    juce::Rectangle<int> notification{};
    juce::String notificationStr{ "Still Okay" };
    juce::Rectangle<int> date{};
    juce::String dateStr{ "15/12/2024" };

    juce::Font font{ juce::FontOptions{} };

public:
    Footer(const FilmstripType& type, MainControls& mainControls, ControlCanvas& controlCanvas);
    ~Footer();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void setupDate();

    void drawBackground(juce::Graphics& g);

    void setupSizeControlsCallback();
    juce::String formatWithDots(juce::String textSizeTotalPixel);
    juce::String updateSizingText();

    void drawRecomendedSize(juce::Graphics& g);
    void drawProjectSize(juce::Graphics& g);
    void drawNotification(juce::Graphics& g);
    void drawDate(juce::Graphics& g);
};