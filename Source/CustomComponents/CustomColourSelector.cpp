/*
  ==============================================================================

    CustomColourSelector.cpp
    Created: 13 Jan 2025 8:57:11am
    Author:  UFTHaq
    Copy and modified from juce_ColourSelector.cpp

  ==============================================================================
*/

#include "CustomColourSelector.h"

struct ColourComponentSlider final 
    : public juce::Slider
{
    ColourComponentSlider(const juce::String& name) : juce::Slider(name)
    {
        setRange(0.0, 255.0, 1.0);
    }

    juce::String getTextFromValue(double value) override
    {
        return juce::String::toHexString((int)value).toUpperCase().paddedLeft('0', 2);
    }

    double getValueFromText(const juce::String& text) override
    {
        return (double)text.getHexValue32();
    }
};

//==============================================================================
class CustomColourSelector::ColourSpaceView final 
    : public juce::Component
{
public:
    ColourSpaceView(CustomColourSelector& cs, float& hue, float& sat, float& val, int edgeSize)
        : owner(cs), h(hue), s(sat), v(val), edge(edgeSize)
    {
        addAndMakeVisible(marker);
        setMouseCursor(juce::MouseCursor::CrosshairCursor);
    }

    void paint(juce::Graphics& g) override
    {
        if (colours.isNull())
        {
            auto width = getWidth() / 2;
            auto height = getHeight() / 2;
            colours = juce::Image(juce::Image::RGB, width, height, false);

            juce::Image::BitmapData pixels(colours, juce::Image::BitmapData::writeOnly);

            for (int y = 0; y < height; ++y)
            {
                auto val = 1.0f - (float)y / (float)height;

                for (int x = 0; x < width; ++x)
                {
                    auto sat = (float)x / (float)width;
                    pixels.setPixelColour(x, y, juce::Colour(h, sat, val, 1.0f));
                }
            }
        }

        g.setOpacity(1.0f);
        g.drawImageTransformed(colours,
            juce::RectanglePlacement(juce::RectanglePlacement::stretchToFit)
            .getTransformToFit(colours.getBounds().toFloat(),
                getLocalBounds().reduced(edge).toFloat()),
            false);
    }

    void mouseDown(const juce::MouseEvent& e) override
    {
        mouseDrag(e);
    }

    void mouseDrag(const juce::MouseEvent& e) override
    {
        auto sat = (float)(e.x - edge) / (float)(getWidth() - edge * 2);
        auto val = 1.0f - (float)(e.y - edge) / (float)(getHeight() - edge * 2);

        owner.setSV(sat, val);
    }

    void updateIfNeeded()
    {
        if (!juce::approximatelyEqual(lastHue, h))
        {
            lastHue = h;
            colours = {};
            repaint();
        }

        updateMarker();
    }

    void resized() override
    {
        colours = {};
        updateMarker();
    }

private:
    CustomColourSelector& owner;
    float& h;
    float& s;
    float& v;
    float lastHue = 0;
    const int edge;
    juce::Image colours;

    struct ColourSpaceMarker final : public Component
    {
        ColourSpaceMarker()
        {
            setInterceptsMouseClicks(false, false);
        }

        void paint(juce::Graphics& g) override
        {
            g.setColour(juce::Colour::greyLevel(0.1f));
            g.drawEllipse(1.0f, 1.0f, (float)getWidth() - 2.0f, (float)getHeight() - 2.0f, 1.0f);
            g.setColour(juce::Colour::greyLevel(0.9f));
            g.drawEllipse(2.0f, 2.0f, (float)getWidth() - 4.0f, (float)getHeight() - 4.0f, 1.0f);
        }
    };

    ColourSpaceMarker marker;

    void updateMarker()
    {
        auto markerSize = juce::jmax(14, edge * 2);
        auto area = getLocalBounds().reduced(edge);

        marker.setBounds(juce::Rectangle<int>(markerSize, markerSize)
            .withCentre(area.getRelativePoint(s, 1.0f - v)));
    }

    JUCE_DECLARE_NON_COPYABLE(ColourSpaceView)
};

//==============================================================================
class CustomColourSelector::HueSelectorComp final 
    : public juce::Component
{
public:
    HueSelectorComp(CustomColourSelector& cs, float& hue, int edgeSize)
        : owner(cs), h(hue), edge(edgeSize)
    {
        addAndMakeVisible(marker);
    }

    void paint(juce::Graphics& g) override
    {
        float edgeF = float(edge);

        juce::ColourGradient cg;
        cg.isRadial = false;
        cg.point1.setXY(0.0f, (float)edgeF);
        cg.point2.setXY(0.0f, (float)getHeight());

        for (float i = 0.0f; i <= 1.0f; i += 0.02f)
            cg.addColour(i, juce::Colour(i, 1.0f, 1.0f, 1.0f));

        g.setGradientFill(cg);
        //g.fillRect(getLocalBounds().reduced(edge));
        g.fillRoundedRectangle(getLocalBounds().toFloat().reduced(edgeF), 2.0F);

        g.setColour(juce::Colours::whitesmoke);
        g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(float(edgeF) - 0.5F), 3.0F, 0.5F);
    }

    void resized() override
    {
        auto markerSize = juce::jmax(14, edge * 2);
        auto area = getLocalBounds().reduced(edge);

        marker.setBounds(juce::Rectangle<int>(getWidth(), markerSize)
            .withCentre(area.getRelativePoint(0.5f, h)));
    }

    void mouseDown(const juce::MouseEvent& e) override
    {
        mouseDrag(e);
    }

    void mouseDrag(const juce::MouseEvent& e) override
    {
        owner.setHue((float)(e.y - edge) / (float)(getHeight() - edge * 2));
    }

    void updateIfNeeded()
    {
        resized();
    }

private:
    CustomColourSelector& owner;
    float& h;
    const int edge;

    struct HueSelectorMarker final : public Component
    {
        HueSelectorMarker()
        {
            setInterceptsMouseClicks(false, false);
        }

        void paint(juce::Graphics& g) override
        {
            auto cw = (float)getWidth();
            auto ch = (float)getHeight();

            juce::Path p;
            p.addTriangle(1.0f, 1.0f,
                cw * 0.3f, ch * 0.5f,
                1.0f, ch - 1.0f);

            p.addTriangle(cw - 1.0f, 1.0f,
                cw * 0.7f, ch * 0.5f,
                cw - 1.0f, ch - 1.0f);

            g.setColour(juce::Colours::white.withAlpha(0.75f));
            g.fillPath(p);

            g.setColour(juce::Colours::black.withAlpha(0.75f));
            g.strokePath(p, juce::PathStrokeType(1.2f));
        }
    };

    HueSelectorMarker marker;

    JUCE_DECLARE_NON_COPYABLE(HueSelectorComp)
};

//==============================================================================
class CustomColourSelector::SwatchComponent final 
    : public juce::Component
{
public:
    SwatchComponent(CustomColourSelector& cs, int itemIndex)
        : owner(cs), index(itemIndex)
    {
    }

    void paint(juce::Graphics& g) override
    {
        (void)g;

        //auto col = owner.getSwatchColour(index);

        //g.fillCheckerBoard(getLocalBounds().toFloat(), 6.0f, 6.0f,
        //    juce::Colour(0xffdddddd).overlaidWith(col),
        //    juce::Colour(0xffffffff).overlaidWith(col));
    }

    void mouseDown(const juce::MouseEvent&) override
    {
        juce::PopupMenu m;
        m.addItem(1, TRANS("Use this swatch as the current colour"));
        m.addSeparator();
        m.addItem(2, TRANS("Set this swatch to the current colour"));

        m.showMenuAsync(juce::PopupMenu::Options().withTargetComponent(this),
            juce::ModalCallbackFunction::forComponent(menuStaticCallback, this));
    }

private:
    CustomColourSelector& owner;
    const int index;

    static void menuStaticCallback(int result, SwatchComponent* comp)
    {
        if (comp != nullptr)
        {
            if (result == 1)  comp->setColourFromSwatch();
            if (result == 2)  comp->setSwatchFromColour();
        }
    }

    void setColourFromSwatch()
    {
        owner.setCurrentColour(owner.getSwatchColour(index));
    }

    void setSwatchFromColour()
    {
        if (owner.getSwatchColour(index) != owner.getCurrentColour())
        {
            owner.setSwatchColour(index, owner.getCurrentColour());
            repaint();
        }
    }

    JUCE_DECLARE_NON_COPYABLE(SwatchComponent)
};

//==============================================================================
class CustomColourSelector::ColourPreviewComp final 
    : public juce::Component
{
public:
    ColourPreviewComp(CustomColourSelector& cs, bool isEditable)
        : owner(cs)
    {
        colourLabel.setFont(labelFont);
        colourLabel.setJustificationType(juce::Justification::centred);

        if (isEditable)
        {
            colourLabel.setEditable(true);

            colourLabel.onEditorShow = [this]
                {
                    if (auto* ed = colourLabel.getCurrentTextEditor())
                        ed->setInputRestrictions((owner.flags & showAlphaChannel) ? 8 : 6, "1234567890ABCDEFabcdef");
                };

            colourLabel.onEditorHide = [this]
                {
                    updateColourIfNecessary(colourLabel.getText());
                };
        }

        addAndMakeVisible(colourLabel);
    }

    void updateIfNeeded()
    {
        auto newColour = owner.getCurrentColour();

        if (currentColour != newColour)
        {
            currentColour = newColour;
            auto textColour = (juce::Colours::white.overlaidWith(currentColour).contrasting());

            colourLabel.setColour(juce::Label::textColourId, textColour);
            colourLabel.setColour(juce::Label::textWhenEditingColourId, textColour);
            colourLabel.setText(currentColour.toDisplayString((owner.flags & showAlphaChannel) != 0), juce::dontSendNotification);

            labelWidth = juce::GlyphArrangement::getStringWidthInt(labelFont, colourLabel.getText());

            repaint();
        }
    }

    void paint(juce::Graphics& g) override
    {
        (void)g;

        //g.fillCheckerBoard(getLocalBounds().toFloat(), 10.0f, 10.0f,
        //    juce::Colour(0xffdddddd).overlaidWith(currentColour),
        //    juce::Colour(0xffffffff).overlaidWith(currentColour));
    }

    void resized() override
    {
        colourLabel.centreWithSize(labelWidth + 10, (int)labelFont.getHeight() + 10);
    }

    void setFontMainPreview(const juce::Font font)
    {
        labelFont = font;
        colourLabel.setFont(labelFont);
    }

private:
    void updateColourIfNecessary(const juce::String& newColourString)
    {
        auto newColour = juce::Colour::fromString(newColourString);

        if (newColour != currentColour)
            owner.setCurrentColour(newColour);
    }

    CustomColourSelector& owner;

    juce::Colour currentColour;
    //juce::Font labelFont{ withDefaultMetrics(juce::FontOptions { 18.0f, juce::Font::italic }) };
    juce::Font labelFont{ juce::FontOptions{} };
    int labelWidth = 0;
    juce::Label colourLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ColourPreviewComp)
};

//==============================================================================
CustomColourSelector::CustomColourSelector(int sectionsToShow, int edge, int gapAroundColourSpaceComponent)
    : colour(juce::Colours::white)
    , flags(sectionsToShow)
    , edgeGap(edge)
{
    // not much point having a selector with no components in it!
    jassert((flags & (showColourAtTop | showSliders | showColourspace)) != 0);

    updateHSV();

    if ((flags & showColourAtTop) != 0)
    {
        previewComponent.reset(new ColourPreviewComp(*this, (flags & editableColour) != 0));
        addAndMakeVisible(previewComponent.get());
    }

    if ((flags & showSliders) != 0)
    {
        labelsRGBA.emplace_back(std::make_unique<juce::Label>("R"));
        labelsRGBA.emplace_back(std::make_unique<juce::Label>("G"));
        labelsRGBA.emplace_back(std::make_unique<juce::Label>("B"));

        labelsEdit.emplace_back(std::make_unique<juce::Label>("R"));
        labelsEdit.emplace_back(std::make_unique<juce::Label>("G"));
        labelsEdit.emplace_back(std::make_unique<juce::Label>("B"));

        sliders.emplace_back(std::make_unique<juce::Slider>("R"));
        sliders.emplace_back(std::make_unique<juce::Slider>("G"));
        sliders.emplace_back(std::make_unique<juce::Slider>("B"));

        sliders.at(0)->setComponentID("Slider_ID_04_COLOUR_SELECTOR_SLIDERS_R");
        sliders.at(1)->setComponentID("Slider_ID_04_COLOUR_SELECTOR_SLIDERS_G");
        sliders.at(2)->setComponentID("Slider_ID_04_COLOUR_SELECTOR_SLIDERS_B");

        for (size_t i = 0; i < sliders.size(); i++)
        {
            labelsRGBA.at(i)->setComponentID("Label_ID_07_RGBA");
            labelsRGBA.at(i)->setText(labelsRGBA.at(i)->getName() + "  : ", juce::dontSendNotification);

            labelsEdit.at(i)->setComponentID("Label_ID_07_RGBA_EDIT");
            labelsEdit.at(i)->setJustificationType(juce::Justification::centred);
            labelsEdit.at(i)->setColour(juce::Label::backgroundColourId, juce::Colours::transparentBlack);
            labelsEdit.at(i)->setColour(juce::Label::backgroundWhenEditingColourId, juce::Colours::black);
            labelsEdit.at(i)->setColour(juce::Label::textWhenEditingColourId, juce::Colours::white);
            labelsEdit.at(i)->setColour(juce::TextEditor::outlineColourId, juce::Colours::transparentBlack);
            labelsEdit.at(i)->setColour(juce::TextEditor::highlightColourId, juce::Colours::royalblue);
            labelsEdit.at(i)->setEditable(false, true);
            labelsEdit.at(i)->onTextChange = [this, i]()
                {
                    juce::String text = labelsEdit.at(i)->getText();

                    auto value = text.getHexValue32();

                    sliders.at(i)->setValue(value);
                };

            sliders.at(i)->setRange(0, 255, 1);
            sliders.at(i)->setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
            sliders.at(i)->setTextBoxIsEditable(false);
            sliders.at(i)->onValueChange = [this, i]()
                {
                    changeColour();
                    
                    for (size_t j = 0; j < sliders.size(); j++)
                    {
                        auto backgroundColor = getCurrentColour();
                        labelsRGBA.at(j)->setColour(juce::Label::textColourId, backgroundColor.contrasting());

                        labelsEdit.at(j)->setColour(juce::Label::textColourId, backgroundColor.contrasting());
                        labelsEdit.at(j)->setColour(juce::Label::outlineColourId, backgroundColor.contrasting());
                    }

                    int value = int(sliders.at(i)->getValue());
                    labelsEdit.at(i)->setText(juce::String::toHexString(value).toUpperCase().paddedLeft('0', 2), juce::sendNotification);
                };



            addAndMakeVisible(labelsRGBA.at(i).get());
            addAndMakeVisible(labelsEdit.at(i).get());
            addAndMakeVisible(sliders.at(i).get());
        }

        //sliders[0].reset(new ColourComponentSlider(TRANS("R")));
        //sliders[1].reset(new ColourComponentSlider(TRANS("G")));
        //sliders[2].reset(new ColourComponentSlider(TRANS("B")));
        //sliders[3].reset(new ColourComponentSlider(TRANS("A")));

        //addAndMakeVisible(sliders[0].get());
        //addAndMakeVisible(sliders[1].get());
        //addAndMakeVisible(sliders[2].get());
        //addChildComponent(sliders[3].get());

        //sliders[3]->setVisible((flags & showAlphaChannel) != 0);

        //for (auto& slider : sliders)
        //{
        //    slider->onValueChange = [this] { changeColour(); };
        //}
    }

    if ((flags & showColourspace) != 0)
    {
        colourSpace.reset(new ColourSpaceView(*this, h, s, v, gapAroundColourSpaceComponent));
        hueSelector.reset(new HueSelectorComp(*this, h, gapAroundColourSpaceComponent));

        addAndMakeVisible(colourSpace.get());
        addAndMakeVisible(hueSelector.get());
    }

    update(juce::dontSendNotification);
}

CustomColourSelector::~CustomColourSelector()
{
    dispatchPendingMessages();
    swatchComponents.clear();
}

//==============================================================================
juce::Colour CustomColourSelector::getCurrentColour() const
{
    return ((flags & showAlphaChannel) != 0) ? colour : colour.withAlpha((juce::uint8)0xff);
}

void CustomColourSelector::setCurrentColour(juce::Colour c, juce::NotificationType notification)
{
    if (c != colour)
    {
        colour = ((flags & showAlphaChannel) != 0) ? c : c.withAlpha((juce::uint8)0xff);

        updateHSV();
        update(notification);
    }
}

void CustomColourSelector::setHue(float newH)
{
    newH = juce::jlimit(0.0f, 1.0f, newH);

    if (!juce::approximatelyEqual(h, newH))
    {
        h = newH;
        colour = juce::Colour(h, s, v, colour.getFloatAlpha());
        update(juce::sendNotification);
    }
}

void CustomColourSelector::setSV(float newS, float newV)
{
    newS = juce::jlimit(0.0f, 1.0f, newS);
    newV = juce::jlimit(0.0f, 1.0f, newV);

    if (!juce::approximatelyEqual(s, newS) || !juce::approximatelyEqual(v, newV))
    {
        s = newS;
        v = newV;
        colour = juce::Colour(h, s, v, colour.getFloatAlpha());
        update(juce::sendNotification);
    }
}

//==============================================================================
void CustomColourSelector::updateHSV()
{
    colour.getHSB(h, s, v);
}

void CustomColourSelector::update(juce::NotificationType notification)
{
    if (sliders[0] != nullptr)
    {
        sliders[0]->setValue((int)colour.getRed(), notification);
        sliders[1]->setValue((int)colour.getGreen(), notification);
        sliders[2]->setValue((int)colour.getBlue(), notification);
        //sliders[3]->setValue((int)colour.getAlpha(), notification);
    }

    if (colourSpace != nullptr)
    {
        colourSpace->updateIfNeeded();
        hueSelector->updateIfNeeded();
    }

    if (previewComponent != nullptr)
        previewComponent->updateIfNeeded();

    if (notification != juce::dontSendNotification)
        sendChangeMessage();

    if (notification == juce::sendNotificationSync)
        dispatchPendingMessages();
}

//==============================================================================
void CustomColourSelector::paint(juce::Graphics& g)
{
    auto backgroundColor = findColour(backgroundColourId);

    g.fillAll(backgroundColor);

    //if ((flags & showSliders) != 0)
    //{
    //    auto textColor = backgroundColor.contrasting();

    //    g.setColour(textColor);
    //    g.setFont(fontRGB);
    //}
}

void CustomColourSelector::resized()
{
    const int swatchesPerRow = 8;
    const int swatchHeight = 22;

    const int numSliders = ((flags & showAlphaChannel) != 0) ? 4 : 3;
    const int numSwatches = getNumSwatches();

    const int swatchSpace = numSwatches > 0 ? edgeGap + swatchHeight * ((numSwatches + 7) / swatchesPerRow) : 0;
    const int sliderSpace = ((flags & showSliders) != 0) ? juce::jmin(22 * numSliders + edgeGap, proportionOfHeight(0.3f)) : 0;
    const int topSpace = ((flags & showColourAtTop) != 0) ? juce::jmin(30 + edgeGap * 2, proportionOfHeight(0.2f)) : edgeGap;

    if (previewComponent != nullptr)
        previewComponent->setBounds(edgeGap, edgeGap * 2, getWidth() - edgeGap * 2, topSpace - edgeGap * 2);

    int y = topSpace;

    if ((flags & showColourspace) != 0)
    {
        const int hueWidth = juce::jmin(50, proportionOfWidth(0.15f));

        colourSpace->setBounds(edgeGap, y,
            getWidth() - hueWidth - edgeGap - 4,
            getHeight() - topSpace - sliderSpace - swatchSpace - edgeGap);

        hueSelector->setBounds(colourSpace->getRight() + 4, y,
            getWidth() - edgeGap - (colourSpace->getRight() + 4),
            colourSpace->getHeight());

        y = getHeight() - sliderSpace - swatchSpace - edgeGap;
    }

    if ((flags & showSliders) != 0)
    {
        auto sliderHeight = juce::jmax(4, sliderSpace / numSliders);

        for (int i = 0; i < numSliders; ++i)
        {
            //auto gap = 0.065F;
            //auto sliderBounds = juce::Rectangle<int>{ proportionOfWidth(gap), y, proportionOfWidth(1 - (gap * 2)), sliderHeight - 2 };
            //auto sliderBounds = juce::Rectangle<int>{ colourSpace->getX(), y, colourSpace->getWidth(), sliderHeight - 2};
            auto sliderBounds = juce::Rectangle<int>{ (edgeGap * 3), y, (getWidth() - (edgeGap * 2 * 3)), sliderHeight - 2 };
            sliderBounds = sliderBounds.withSizeKeepingCentre(sliderBounds.getWidth(), sliderBounds.getHeight() - 2);

            if (i < 3)
            {
                auto copySliderBounds = sliderBounds;

                auto labelRBGABounds = sliderBounds.removeFromLeft(int(copySliderBounds.getWidth() * 0.110F));
                sliderBounds.removeFromLeft(5);

                auto labelEditBounds = sliderBounds.removeFromLeft(int(copySliderBounds.getWidth() * 0.275F));
                sliderBounds.removeFromLeft(5);

                labelsRGBA.at(i)->setBounds(labelRBGABounds);
                labelsEdit.at(i)->setBounds(labelEditBounds);
                sliders.at(i)->setBounds(sliderBounds);
            }

            y += sliderHeight;
        }
    }

    if (numSwatches > 0)
    {
        const int startX = 8;
        const int xGap = 4;
        const int yGap = 4;
        const int swatchWidth = (getWidth() - startX * 2) / swatchesPerRow;
        y += edgeGap;

        if (swatchComponents.size() != numSwatches)
        {
            swatchComponents.clear();

            for (int i = 0; i < numSwatches; ++i)
            {
                auto* sc = new SwatchComponent(*this, i);
                swatchComponents.add(sc);
                addAndMakeVisible(sc);
            }
        }

        int x = startX;

        for (int i = 0; i < swatchComponents.size(); ++i)
        {
            auto* sc = swatchComponents.getUnchecked(i);

            sc->setBounds(x + xGap / 2,
                y + yGap / 2,
                swatchWidth - xGap,
                swatchHeight - yGap);

            if (((i + 1) % swatchesPerRow) == 0)
            {
                x = startX;
                y += swatchHeight;
            }
            else
            {
                x += swatchWidth;
            }
        }
    }
}

void CustomColourSelector::changeColour()
{
    if (sliders[0] != nullptr)
        setCurrentColour(juce::Colour(
            (juce::uint8)sliders[0]->getValue(),
            (juce::uint8)sliders[1]->getValue(),
            (juce::uint8)sliders[2]->getValue()
            //(juce::uint8)sliders[3]->getValue()
        ));
}

//==============================================================================
int CustomColourSelector::getNumSwatches() const
{
    return 0;
}

juce::Colour CustomColourSelector::getSwatchColour(int) const
{
    jassertfalse; // if you've overridden getNumSwatches(), you also need to implement this method
    return juce::Colours::black;
}

void CustomColourSelector::setSwatchColour(int, const juce::Colour&)
{
    jassertfalse; // if you've overridden getNumSwatches(), you also need to implement this method
}

void CustomColourSelector::setMainHEXFont(const juce::Font font)
{
    this->fontMainHex = font;

    previewComponent->setFontMainPreview(font);
}

void CustomColourSelector::setRGBFont(const juce::Font font)
{
    this->fontRGB = font;

    for (size_t i = 0; i < sliders.size(); i++)
    {
        labelsRGBA.at(i)->setFont(fontRGB);
        labelsEdit.at(i)->setFont(fontRGB);
    }
}