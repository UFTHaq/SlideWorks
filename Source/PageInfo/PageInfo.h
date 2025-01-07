/*
  ==============================================================================

    PageInfo.h
    Created: 17 Dec 2024 3:04:51pm
    Author:  UFTHaq

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "../Source/CustomComponents/CustomGroupComponent.h"
#include "../Source/CustomComponents/CustomLookAndFeel.h"
#include "../Source/EnumClass.h"
#include "../Source/Globals.h"

class PageInfo
    : public juce::Component
{
protected:
    std::shared_ptr<CustomLookAndFeel> customLookAndFeel{};

    juce::Rectangle<int> bounds{};

    CustomGroupComponent group{};
    juce::Label author_param{};
    juce::Label author_arg{};
    juce::Label version_param{};
    juce::Label version_arg{};
    juce::Label release_param{};
    juce::Label release_arg{};
    juce::Label license_param{};
    juce::Label license_arg{};
    juce::Label juceVersion_arg{};
    juce::TextButton closeButton{};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PageInfo)
public:

    PageInfo();
    ~PageInfo();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void setupComponent();
    void setupGroup();
    void setupLabel();
    void setupCloseButton();

    juce::TextButton& getCloseButton();
};