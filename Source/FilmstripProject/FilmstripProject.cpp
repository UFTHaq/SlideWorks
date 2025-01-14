/*
  ==============================================================================

    FilmstripProject.cpp
    Created: 10 Dec 2024 2:19:53pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "FilmstripProject.h"

FilmstripProject::FilmstripProject
(
    const FilmstripType& type
    , juce::Rectangle<int> baseWorkspace
)
    : filmstripType(type)
    , boundary(baseWorkspace)
    , tabButton(type)
    , nameAndMode(type)
    , mainControls(type, assets, assetsButtons, canvas, subControls)
    , canvas(type, assets, assetsButtons, subControls)
    , controlSliderStyle(type)
    , controlLighting(type)
    , controlCanvas(type, canvas)
    , subControls(type, controlSliderStyle, controlLighting, controlCanvas)
    , footer(type, mainControls, controlCanvas)
{

    setupLayout(baseWorkspace);
    setupTabButtonAndEditorCallback();
}

FilmstripProject::~FilmstripProject()
{
}

void FilmstripProject::setupLayout(juce::Rectangle<int> baseWorkspace)
{
    auto area = baseWorkspace;

    setupModeChanged(area);

    auto footerArea = area.removeFromBottom(FOOTER_HEIGHT);
    footer.setBounds(footerArea);

    area.removeFromBottom(1);

    auto mainControlArea = area.removeFromLeft(MAIN_CONTROL_W);
    mainControls.setBounds(mainControlArea);
    area.removeFromLeft(1);

    auto layer1Area = area;
    auto tabArea = area.removeFromTop(FOOTER_HEIGHT);
    auto layer2Area = area;
    layer2Area = layer2Area.reduced(1);

    auto layerNameAndMode = layer2Area.removeFromTop(FOOTER_HEIGHT);
    nameAndMode.setBounds(layerNameAndMode);

    layer2Area.removeFromLeft(1);
    layer2Area.removeFromRight(1);
    layer2Area.removeFromBottom(1);

    auto layer3Area = layer2Area;

    if (nameAndMode.getMode() == WorkingMode::EDIT_MODE)
    {
        auto subControlArea = layer3Area.removeFromRight(SUB_CONTROL_W);
        subControls.setBounds(subControlArea);

        layer3Area.removeFromRight(1);
        auto canvasArea = layer3Area;
        canvas.setBounds(canvasArea);
    }
    else 
    {
        auto canvasArea = layer3Area;
        canvas.setBounds(canvasArea);

        auto subControlArea = juce::Rectangle<int>{ 0,0,0,0 };
        subControls.setBounds(subControlArea);
    }
}

void FilmstripProject::setupModeChanged(const juce::Rectangle<int> baseWorkspace)
{
    nameAndMode.onModeChange = [this, baseWorkspace]()
        {
            setupLayout(baseWorkspace);
        };

    WorkingMode mode = nameAndMode.getMode();

    canvas.setMode(mode);
}

juce::Rectangle<int> FilmstripProject::getBaseWorkspace() const
{
    return boundary;
}

void FilmstripProject::setupTabButtonAndEditorCallback()
{
    nameAndMode.onTextChangedCallback = [this](const juce::String& newText)
        {
            tabButton.getMainButton().setButtonText(newText);
        };
}

void FilmstripProject::setProjectName(juce::String& name)
{
    this->projectName = name;
    tabButton.setMainButtonText(name);
}

const juce::String& FilmstripProject::getProjectName() const
{
    return projectName;
}

const FilmstripType& FilmstripProject::getFilmstripType() const
{
    return filmstripType;
}

std::vector<std::unique_ptr<Asset>>& FilmstripProject::getAssets()
{
    return assets;
}

void FilmstripProject::AddAsset(const AssetType& type)
{
    assets.emplace_back(std::make_unique<Asset>(type));
    mainControls.getAssetsManager().addAssetButton(assets.back()->getAssetTypeStr());
}

TabButton& FilmstripProject::getTabButton()
{
    return tabButton;
}

NameAndMode& FilmstripProject::getNameAndModeControl()
{
    return nameAndMode;
}

MainControls& FilmstripProject::getMainControls()
{
    return mainControls;
}

Canvas& FilmstripProject::getCanvas()
{
    return canvas;
}

SubControls& FilmstripProject::getSubControls()
{
    return subControls;
}

Footer& FilmstripProject::getFooter()
{
    return footer;
}

void FilmstripProject::resetCurrentTheme()
{
    //tabButton.resetCurrentTheme(); 
    //nameAndMode.resetCurrentTheme(); 
    mainControls.resetCurrentTheme();
    //canvas.resetCurrentTheme(); 
    //subControls.resetCurrentTheme(); 
    //footer.resetCurrentTheme(); 
}
