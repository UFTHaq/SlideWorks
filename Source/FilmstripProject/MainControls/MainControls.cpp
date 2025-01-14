/*
  ==============================================================================

    MainControls.cpp
    Created: 10 Dec 2024 4:01:40pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "MainControls.h"

MainControls::MainControls
(
    const FilmstripType& type
    , std::vector<std::unique_ptr<Asset>>& assets
    , std::vector<std::unique_ptr<AssetButtons>>& assetButtons
    , Canvas& canvas
    , SubControls& subControls
)
    : filmstripType(type)
    , assets(assets)
    , assetButtons(assetButtons)
    , canvas(canvas)
    , subControls(subControls)
    , assetsManager(type, assets, assetButtons, canvas, subControls)
    , customLookAndFeel(Globals::getCustomLookAndFeel())
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

    setupControlsCallback();
}

MainControls::~MainControls()
{
}

void MainControls::paint(juce::Graphics& g)
{
    drawBackground(g);
    drawBanner(g);
}

void MainControls::resized()
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

void MainControls::drawBackground(juce::Graphics& g)
{
    g.setColour(customLookAndFeel->getCurrentTheme().ButtonsID_01_ON);
    g.fillRoundedRectangle(bounds.toFloat(), 1);

    g.setColour(customLookAndFeel->getCurrentTheme().CustomDarkGrey);
    //g.drawRoundedRectangle(bounds.toFloat().reduced(0.3F), 1, 0.3F);
}

void MainControls::drawBanner(juce::Graphics& g)
{
    g.setColour(customLookAndFeel->getCurrentTheme().BannerFilmstripType);
    g.fillRoundedRectangle(bannerRect.toFloat(), 2);

    g.setColour(customLookAndFeel->getCurrentTheme().BannerFilmstripType.darker());
    g.drawRoundedRectangle(bannerRect.toFloat().reduced(1), 2, 1);

    g.setFont(fontBanner);
    g.setColour(customLookAndFeel->getCurrentTheme().FontBlack);
    g.drawText(banner.getText(), bannerTextBounds.toFloat(), juce::Justification::centredLeft);
}

void MainControls::setupBanner(const juce::String& text)
{
    banner.setText(text, juce::dontSendNotification);
    banner.setComponentID("Label_ID_02_FilmstripType");
    banner.setFont(customLookAndFeel->getFontRobotoCondensedBold().withHeight(17.0F));
    banner.setColour(juce::Label::textColourId, customLookAndFeel->getCurrentTheme().FontBlack);
    banner.setJustificationType(juce::Justification::centredLeft);
    banner.setEditable(false, false);
    addAndMakeVisible(banner);
}

void MainControls::setupExportButton()
{
    exportButton.setButtonText("Export");
    exportButton.setComponentID("Buttons_ID_06_EXPORT");
    exportButton.onClick = [this]() {};
    addAndMakeVisible(exportButton);
}

AssetsManager& MainControls::getAssetsManager()
{
    return assetsManager;
}

FilmstripOrientation& MainControls::getOrientationControl()
{
    return orientationControl;
}

KnobAngles& MainControls::getAnglesControls()
{
    return anglesControls;
}

ThumbPositions& MainControls::getThumbControls()
{
    return thumbControls;
}

Canvas& MainControls::getCanvas()
{
    return canvas;
}

SubControls& MainControls::getSubControls()
{
    return subControls;
}

int MainControls::getTotalFrames() const
{
    return totalFramesControl.getTotalFrames();
}

void MainControls::resetCurrentTheme()
{
    totalFramesControl.resetCurrentTheme();

    if (filmstripType == FilmstripType::KNOB)
        anglesControls.resetCurrentTheme();
    else
        thumbControls.resetCurrentTheme();

    //assetsManager.resetCurrentTheme();
    //orientationControl.resetCurrentTheme();
}

void MainControls::setupControlsCallback()
{
    totalFramesControl.onSizeChange = [this]()
        {
            if (onSizeChangeForFooter)
                onSizeChangeForFooter();
        };
}