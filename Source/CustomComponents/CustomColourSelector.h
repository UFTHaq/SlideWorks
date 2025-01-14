/*
  ==============================================================================

    CustomColourSelector.h
    Created: 13 Jan 2025 8:57:11am
    Author:  UFTHaq
    Copy and modified from juce_ColourSelector.h

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class CustomColourSelector
    : public juce::Component
    , public juce::ChangeBroadcaster
{
public:
    //==============================================================================
    /** Options for the type of selector to show. These are passed into the constructor. */
    enum ColourSelectorOptions
    {
        showAlphaChannel = 1 << 0,   /**< if set, the colour's alpha channel can be changed as well as its RGB. */

        showColourAtTop = 1 << 1,   /**< if set, a swatch of the colour is shown at the top of the component. */
        editableColour = 1 << 2,   /**< if set, the colour shows at the top of the component is editable. */
        showSliders = 1 << 3,   /**< if set, RGB sliders are shown at the bottom of the component. */
        showColourspace = 1 << 4    /**< if set, a big HSV selector is shown. */
    };

    //==============================================================================
    /** Creates a ColourSelector object.

        The flags are a combination of values from the ColourSelectorOptions enum, specifying
        which of the selector's features should be visible.

        The edgeGap value specifies the amount of space to leave around the edge.

        gapAroundColourSpaceComponent indicates how much of a gap to put around the
        colourspace and hue selector components.
    */
    CustomColourSelector(int flags = (showAlphaChannel | showColourAtTop | showSliders | showColourspace),
        int edgeGap = 4,
        int gapAroundColourSpaceComponent = 7);

    /** Destructor. */
    ~CustomColourSelector() override;

    //==============================================================================
    /** Returns the colour that the user has currently selected.

        The ColourSelector class is also a ChangeBroadcaster, so listeners can
        register to be told when the colour changes.

        @see setCurrentColour
    */
    juce::Colour getCurrentColour() const;

    /** Changes the colour that is currently being shown.

        @param newColour           the new colour to show
        @param notificationType    whether to send a notification of the change to listeners.
                                   A notification will only be sent if the colour has changed.
    */
    void setCurrentColour(juce::Colour newColour, juce::NotificationType notificationType = juce::sendNotification);

    //==============================================================================
    /** Tells the selector how many preset colour swatches you want to have on the component.

        To enable swatches, you'll need to override getNumSwatches(), getSwatchColour(), and
        setSwatchColour(), to return the number of colours you want, and to set and retrieve
        their values.
    */
    virtual int getNumSwatches() const;

    /** Called by the selector to find out the colour of one of the swatches.

        Your subclass should return the colour of the swatch with the given index.

        To enable swatches, you'll need to override getNumSwatches(), getSwatchColour(), and
        setSwatchColour(), to return the number of colours you want, and to set and retrieve
        their values.
    */
    virtual juce::Colour getSwatchColour(int index) const;

    /** Called by the selector when the user puts a new colour into one of the swatches.

        Your subclass should change the colour of the swatch with the given index.

        To enable swatches, you'll need to override getNumSwatches(), getSwatchColour(), and
        setSwatchColour(), to return the number of colours you want, and to set and retrieve
        their values.
    */
    virtual void setSwatchColour(int index, const juce::Colour& newColour);


    //==============================================================================
    /** A set of colour IDs to use to change the colour of various aspects of the keyboard.

        These constants can be used either via the Component::setColour(), or LookAndFeel::setColour()
        methods.

        @see Component::setColour, Component::findColour, LookAndFeel::setColour, LookAndFeel::findColour
    */
    enum ColourIds
    {
        backgroundColourId = 0x1007000,    /**< the colour used to fill the component's background. */
        labelTextColourId = 0x1007001     /**< the colour used for the labels next to the sliders. */
    };

    void setMainHEXFont(const juce::Font font);
    void setRGBFont(const juce::Font font);

private:
    //==============================================================================
    class SwatchComponent;
    class ColourSpaceView;
    class HueSelectorComp;
    class ColourPreviewComp;

    juce::Colour colour;
    float h, s, v;
    std::vector<std::unique_ptr<juce::Label>> labelsRGBA{};
    std::vector<std::unique_ptr<juce::Label>> labelsEdit{};
    std::vector<std::unique_ptr<juce::Slider>> sliders{};

    //std::unique_ptr<juce::Slider> sliders[4];

    std::unique_ptr<ColourSpaceView> colourSpace;
    std::unique_ptr<HueSelectorComp> hueSelector;
    std::unique_ptr<ColourPreviewComp> previewComponent;
    juce::OwnedArray<SwatchComponent> swatchComponents;
    const int flags;
    int edgeGap;

    juce::Font fontMainHex{ juce::FontOptions{} };
    juce::Font fontRGB{ juce::FontOptions{} };

    void setHue(float newH);
    void setSV(float newS, float newV);
    void updateHSV();
    void update(juce::NotificationType);
    void changeColour();
    void paint(juce::Graphics&) override;
    void resized() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomColourSelector)


    // IN HERE, WE DONT DO SWATCHES (COLOR PALETTE).
};
