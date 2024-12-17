/*
  ==============================================================================

    PageInfo.cpp
    Created: 17 Dec 2024 3:04:51pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "PageInfo.h"

PageInfo::PageInfo()
    : customLookAndFeel(Globals::getCustomLookAndFeel())
{
    setupComponent();
}

PageInfo::~PageInfo()
{
}

void PageInfo::paint(juce::Graphics& g)
{
    g.setColour(customLookAndFeel->getCurrentTheme().Page_1);
    g.fillRoundedRectangle(bounds.toFloat(), 1);

    group.paint(g);
}

void PageInfo::resized()
{
    bounds = getLocalBounds();

    auto baseArea = bounds.withSizeKeepingCentre(275, 240);
    auto groupArea = baseArea.reduced(10);
    groupArea.removeFromBottom(40); // For button close placement
    group.setBounds(groupArea);

    auto infoArea = groupArea;
    infoArea.removeFromTop(8);
    infoArea = infoArea.reduced(20);
    infoArea = infoArea.withSizeKeepingCentre(150, infoArea.getHeight());

    auto contentH = infoArea.getHeight() / 5;
    auto author = infoArea.removeFromTop(contentH);
    auto version = infoArea.removeFromTop(contentH);
    auto release = infoArea.removeFromTop(contentH);
    auto license = infoArea.removeFromTop(contentH);
    auto juceVer = infoArea.removeFromTop(contentH);

    auto paramW = int(infoArea.getWidth() * 0.4F);
    
    author_param.setBounds(author.removeFromLeft(paramW));
    author_arg.setBounds(author);

    version_param.setBounds(version.removeFromLeft(paramW));
    version_arg.setBounds(version);

    release_param.setBounds(release.removeFromLeft(paramW));
    release_arg.setBounds(release);

    license_param.setBounds(license.removeFromLeft(paramW));
    license_arg.setBounds(license);

    juceVersion_arg.setBounds(juceVer);

    auto buttonW = 100;
    auto buttonH = 30;
    auto closeButtonArea = juce::Rectangle<int>{
        baseArea.getX() + (baseArea.getWidth() - buttonW) / 2,
        baseArea.getBottom() - buttonH - 10,
        buttonW,
        buttonH
    };

    closeButton.setBounds(closeButtonArea);
}

void PageInfo::setupComponent()
{
    setupGroup();
    setupLabel();
    setupCloseButton();
}

void PageInfo::setupGroup()
{
    auto indentation = 3.0F;
    auto gap = 8.0F;
    auto cornerSize = 10.0F;
    auto lineThick = 1.5F;
    auto fontSize = 16.0F;
    auto font = customLookAndFeel->getFontRobotoCondensedBold().withHeight(18.0F);
    auto fontColor = customLookAndFeel->getCurrentTheme().CustomGroupComponent;
    auto outlineColor = customLookAndFeel->getCurrentTheme().CustomGroupComponent;

    group.setText("SLIDEWORKS");
    group.setTextLabelPosition(juce::Justification::centred);
    group.setFont(font);
    group.setFontColour(fontColor);
    group.setOutlineColour(outlineColor);
    group.setCornerSize(cornerSize);
    group.setIndentation(indentation);
    group.setTextLineGap(gap);
    group.setLineThickness(lineThick);
    addAndMakeVisible(group);
}

void PageInfo::setupLabel()
{
    auto font = customLookAndFeel->getFontRobotoCondensedBold().withHeight(17.0F);
    auto justification = juce::Justification::centredLeft;
    auto backgroundColor = customLookAndFeel->getCurrentTheme().TransparentBlack;
    auto textColor = customLookAndFeel->getCurrentTheme().CustomGroupComponent;

    author_param.setText("Author", juce::dontSendNotification);
    author_param.setJustificationType(justification);
    author_param.setFont(font);
    author_param.setColour(juce::Label::backgroundColourId, backgroundColor);
    author_param.setColour(juce::Label::textColourId, textColor);
    author_param.setLookAndFeel(customLookAndFeel.get());
    addAndMakeVisible(author_param);
    author_arg.setText(":  UFTHaq", juce::dontSendNotification);
    author_arg.setJustificationType(justification);
    author_arg.setFont(font);
    author_arg.setColour(juce::Label::backgroundColourId, backgroundColor);
    author_arg.setColour(juce::Label::textColourId, textColor);
    author_arg.setLookAndFeel(customLookAndFeel.get());
    addAndMakeVisible(author_arg);

    version_param.setText("Version", juce::dontSendNotification);
    version_param.setJustificationType(justification);
    version_param.setFont(font);
    version_param.setColour(juce::Label::backgroundColourId, backgroundColor);
    version_param.setColour(juce::Label::textColourId, textColor);
    version_param.setLookAndFeel(customLookAndFeel.get());
    addAndMakeVisible(version_param);
    version_arg.setText(":  1.0", juce::dontSendNotification);
    version_arg.setJustificationType(justification);
    version_arg.setFont(font);
    version_arg.setColour(juce::Label::backgroundColourId, backgroundColor);
    version_arg.setColour(juce::Label::textColourId, textColor);
    version_arg.setLookAndFeel(customLookAndFeel.get());
    addAndMakeVisible(version_arg);

    release_param.setText("Release", juce::dontSendNotification);
    release_param.setJustificationType(justification);
    release_param.setFont(font);
    release_param.setColour(juce::Label::backgroundColourId, backgroundColor);
    release_param.setColour(juce::Label::textColourId, textColor);
    release_param.setLookAndFeel(customLookAndFeel.get());
    addAndMakeVisible(release_param);
    release_arg.setText(":  1/1/2025", juce::dontSendNotification);
    release_arg.setJustificationType(justification);
    release_arg.setFont(font);
    release_arg.setColour(juce::Label::backgroundColourId, backgroundColor);
    release_arg.setColour(juce::Label::textColourId, textColor);
    release_arg.setLookAndFeel(customLookAndFeel.get());
    addAndMakeVisible(release_arg);

    license_param.setText("License", juce::dontSendNotification);
    license_param.setJustificationType(justification);
    license_param.setFont(font);
    license_param.setColour(juce::Label::backgroundColourId, backgroundColor);
    license_param.setColour(juce::Label::textColourId, textColor);
    license_param.setLookAndFeel(customLookAndFeel.get());
    addAndMakeVisible(license_param);
    license_arg.setText(":  AGPLv3", juce::dontSendNotification);
    license_arg.setJustificationType(justification);
    license_arg.setFont(font);
    license_arg.setColour(juce::Label::backgroundColourId, backgroundColor);
    license_arg.setColour(juce::Label::textColourId, textColor);
    license_arg.setLookAndFeel(customLookAndFeel.get());
    addAndMakeVisible(license_arg);

    juceVersion_arg.setText("Created with JUCE 8.0.3", juce::dontSendNotification);
    juceVersion_arg.setJustificationType(juce::Justification::centredBottom);
    juceVersion_arg.setFont(font);
    juceVersion_arg.setColour(juce::Label::backgroundColourId, backgroundColor);
    juceVersion_arg.setColour(juce::Label::textColourId, textColor);
    juceVersion_arg.setLookAndFeel(customLookAndFeel.get());
    addAndMakeVisible(juceVersion_arg);
}

void PageInfo::setupCloseButton()
{
    closeButton.setButtonText("CLOSE");
    closeButton.setComponentID("Buttons_ID_02_Close_Group");
    closeButton.onClick = [this]() {};
    addAndMakeVisible(closeButton);
}

juce::TextButton& PageInfo::getCloseButton()
{
    return closeButton;
}
