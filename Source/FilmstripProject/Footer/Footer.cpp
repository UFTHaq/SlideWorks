/*
  ==============================================================================

    Footer.cpp
    Created: 15 Dec 2024 8:52:43pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "Footer.h"

Footer::Footer
(
    const FilmstripType& type
    , MainControls& mainControls
    , ControlCanvas& controlCanvas
)
    : filmstripType(type)
    , mainControls(mainControls)
    , controlCanvas(controlCanvas)
    , customLookAndFeel(Globals::getCustomLookAndFeel())
{
    font = customLookAndFeel->getFontRobotoCondensedRegular().withHeight(14.0F);
    
    setupDate();

    setupSizeControlsCallback();
}

Footer::~Footer()
{
}

void Footer::paint(juce::Graphics& g)
{
    drawBackground(g);
    drawRecomendedSize(g);
    drawProjectSize(g);
    drawNotification(g);
    drawDate(g);
}

void Footer::resized()
{
    bounds = getLocalBounds();

    auto area = bounds;
    auto recomendedSizeArea = area.removeFromLeft(240);
    recomendedSizeArea.removeFromLeft(10);
    recomendedSize = recomendedSizeArea;

    auto projectSizeArea = area.removeFromLeft(300);
    projectSizeArea.removeFromLeft(10);
    projectSize = projectSizeArea;

    auto notificationArea = area.removeFromLeft(80);
    notificationArea.removeFromLeft(10);
    notification = notificationArea;

    auto dateArea = area;
    dateArea.removeFromRight(10);
    date = dateArea;
}

void Footer::setupDate()
{
    juce::Time currentTime = juce::Time::getCurrentTime();
    dateStr = currentTime.formatted("%A, %d/%m/%Y");
}


void Footer::drawBackground(juce::Graphics& g)
{
    g.setColour(customLookAndFeel->getCurrentTheme().ButtonsID_01_ON);
    g.fillRoundedRectangle(bounds.toFloat(), 1);

    //g.setColour(customLookAndFeel->getCurrentTheme().CustomDarkGrey);
    //g.drawRoundedRectangle(bounds.toFloat().reduced(0.3F), 1, 0.3F);
}

void Footer::drawRecomendedSize(juce::Graphics& g)
{
    text = recomendedSizeStr;
    auto area = recomendedSize;

    g.setFont(font);
    g.setColour(customLookAndFeel->getCurrentTheme().CustomGrey);
    g.drawText(text, area.toFloat(), juce::Justification::centredLeft);
}

void Footer::setupSizeControlsCallback()
{
    mainControls.onSizeChangeForFooter = [this]()
        {
            projectSizeStr = updateSizingText();
            notificationStr = updateNotificationText(totalPixel);
            repaint();
        };

    controlCanvas.onSizeChangeForFooter = [this]()
        {
            projectSizeStr = updateSizingText();
            notificationStr = updateNotificationText(totalPixel);
            repaint();
        };
}

juce::String Footer::formatWithDots(juce::String textSizeTotalPixel)
{
    std::string inputText{ textSizeTotalPixel.toStdString() };
    std::string outputText{};
    int countDigit{};

    for (size_t i = inputText.length(); i > 0; --i)
    {
        outputText.insert(outputText.begin(), inputText.at(i - 1));
        countDigit++;

        if (countDigit == 3 && i != 1)
        {
            outputText.insert(outputText.begin(), '.');
            countDigit = 0;
        }
    }

    return outputText;
}

juce::String Footer::updateSizingText()
{
    auto totalFrames = mainControls.getTotalFrames();
    auto canvasW = mainControls.getCanvas().getCanvasEdit().getRealCanvasWH().getX();
    auto canvasH = mainControls.getCanvas().getCanvasEdit().getRealCanvasWH().getY();
    auto sizeTotalPixel = totalFrames * canvasW * canvasH;
    auto sizeInMegaPixel = (double)sizeTotalPixel / 1000000;

    auto textTotalFrames = juce::String{ totalFrames };
    auto textCanvasW = juce::String{ canvasW };
    auto textCanvasH = juce::String{ canvasH };
    auto textSizeTotalPixel = juce::String{ sizeTotalPixel };
    auto textSizeInMegaPixel = juce::String{ sizeInMegaPixel, 1 };    // One digit

    textSizeTotalPixel = formatWithDots(textSizeTotalPixel);

    juce::String processedText = "Size : " + textCanvasW + " X " + textCanvasH + " X " + textTotalFrames +
        " = " + textSizeTotalPixel + " PX " + "= " + textSizeInMegaPixel + " MB";

    totalPixel = sizeTotalPixel;
    return processedText;
}

juce::String Footer::updateNotificationText(const int pixels)
{
    juce::String newText = {};
    if (pixels > 0 && pixels < 4000000)
    {
        newText = "Nice";
    }
    else if (pixels > 4000000 && pixels < 9000000)
    {
        newText = "Perfect";
    }
    else if (pixels > 9000000 && pixels < 14000000)
    {
        newText = "Still Okay";
    }
    else if (pixels > 16000000 && pixels < 20000000)
    {
        newText = "Quite Big";
    }
    else
    {
        newText = "Too Big";
    }

    return newText;
}

void Footer::drawProjectSize(juce::Graphics& g)
{
    text = projectSizeStr;

    auto area = projectSize;

    g.setFont(font);
    g.setColour(customLookAndFeel->getCurrentTheme().CustomGrey);
    g.drawText(text, area.toFloat(), juce::Justification::centredLeft);
}

void Footer::drawNotification(juce::Graphics& g)
{
    text = notificationStr;
    auto area = notification;

    g.setFont(font);
    g.setColour(customLookAndFeel->getCurrentTheme().CustomGrey);
    g.drawText(text, area.toFloat(), juce::Justification::centredLeft);
}

void Footer::drawDate(juce::Graphics& g)
{
    text = dateStr;
    auto area = date;

    g.setFont(font);
    g.setColour(customLookAndFeel->getCurrentTheme().CustomGrey);
    g.drawText(text, area.toFloat(), juce::Justification::centredRight);
}
