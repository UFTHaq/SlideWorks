/*
  ==============================================================================

    New_MainControls.cpp
    Created: 10 Dec 2024 4:01:40pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "New_MainControls.h"

//New_MainControls::New_MainControls(const FilmstripType& filmstripType, std::vector<New_Asset>& assets)
New_MainControls::New_MainControls(const FilmstripType& filmstripType, std::vector<std::unique_ptr<New_Asset>>& assets)
    : filmstripType(filmstripType), assets(assets), assetsManager(filmstripType, assets), customLookAndFeel(Globals::getCustomLookAndFeel())
{
    setLookAndFeel(customLookAndFeel.get());
    
    fontBanner = customLookAndFeel->getFontRobotoCondensedBold().withHeight(17.0F);

    juce::String text{};
    if (filmstripType == FilmstripType::KNOB)
    {
        addAndMakeVisible(anglesControls);
        text = "FILMSTRIP : KNOB";
    }

    else
    {
        addAndMakeVisible(thumbControls);
        text = "FILMSTRIP : SLIDER";
    }

    setupBanner(text);
    setupExportButton();

    addAndMakeVisible(orientationControl);
    addAndMakeVisible(totalFramesControl);
    addAndMakeVisible(assetsManager);

}

New_MainControls::~New_MainControls()
{
}

void New_MainControls::paint(juce::Graphics& g)
{
    drawBackground(g);
    drawBanner(g);
}

void New_MainControls::resized()
{
    bounds = getLocalBounds();

    auto area = bounds;

    // Area Banner & Export Button
    auto BannerArea = area.removeFromTop(35).reduced(2);
    bannerRect = BannerArea;

    bannerTextBounds = BannerArea;
    bannerTextBounds.removeFromLeft(7);

    auto exportArea = BannerArea;
    exportArea = exportArea.removeFromRight(60);
    exportButton.setBounds(exportArea.reduced(3));
    
    area.removeFromLeft(5);
    area.removeFromRight(5);
    area.removeFromBottom(3);

    // Area Control Min Max Angles or Thumb Positions
    auto ControlArea = area.removeFromBottom(110);

    if (filmstripType == FilmstripType::KNOB)
        anglesControls.setBounds(ControlArea);

    else
        thumbControls.setBounds(ControlArea);

    // Area Control Orientaiton
    auto OrientationArea = area.removeFromBottom(70);
    orientationControl.setBounds(OrientationArea);

    // Area Control Total Frames
    auto TotalFramesArea = area.removeFromBottom(60);
    totalFramesControl.setBounds(TotalFramesArea);

    // Area Assets Manager
    auto AssetsManagerArea = area;
    AssetsManagerArea.removeFromBottom(8);
    assetsManager.setBounds(AssetsManagerArea);
}

void New_MainControls::drawBackground(juce::Graphics& g)
{
    g.setColour(customLookAndFeel->getCurrentTheme().ButtonsID_01_ON);
    g.fillRoundedRectangle(bounds.toFloat(), 1);

    g.setColour(customLookAndFeel->getCurrentTheme().CustomDarkGrey);
    //g.drawRoundedRectangle(bounds.toFloat().reduced(0.3F), 1, 0.3F);
}

void New_MainControls::drawBanner(juce::Graphics& g)
{
    g.setColour(customLookAndFeel->getCurrentTheme().BannerFilmstripType);
    g.fillRoundedRectangle(bannerRect.toFloat(), 2);

    g.setColour(customLookAndFeel->getCurrentTheme().BannerFilmstripType.darker());
    g.drawRoundedRectangle(bannerRect.toFloat().reduced(1), 2, 1);

    g.setFont(fontBanner);
    g.setColour(customLookAndFeel->getCurrentTheme().FontBlack);
    g.drawText(banner.getText(), bannerTextBounds.toFloat(), juce::Justification::centredLeft);
}

void New_MainControls::setupBanner(const juce::String& text)
{
    banner.setText(text, juce::dontSendNotification);
    banner.setComponentID("Label_ID_02_FilmstripType");
    banner.setFont(customLookAndFeel->getFontRobotoCondensedBold().withHeight(17.0F));
    banner.setColour(juce::Label::textColourId, customLookAndFeel->getCurrentTheme().FontBlack);
    banner.setJustificationType(juce::Justification::centredLeft);
    banner.setEditable(false, false);
    addAndMakeVisible(banner);
}

void New_MainControls::setupExportButton()
{
    exportButton.setButtonText("Export");
    exportButton.setComponentID("Buttons_ID_06_EXPORT");
    exportButton.onClick = [this]() {};
    addAndMakeVisible(exportButton);
}

New_AssetsManager& New_MainControls::getAssetsManager()
{
    return assetsManager;
}

New_FilmstripOrientation& New_MainControls::getOrientationControl()
{
    return orientationControl;
}

New_KnobAngles& New_MainControls::getAnglesControls()
{
    return anglesControls;
}

New_ThumbPositions& New_MainControls::getThumbControls()
{
    return thumbControls;
}