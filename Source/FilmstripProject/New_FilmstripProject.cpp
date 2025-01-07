/*
  ==============================================================================

    New_FilmstripProject.cpp
    Created: 10 Dec 2024 2:19:53pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "New_FilmstripProject.h"

New_FilmstripProject::New_FilmstripProject(const FilmstripType& filmstripType, juce::Rectangle<int> baseWorkspace)
    : filmstripType(filmstripType)
    , boundary(baseWorkspace)
    , mainControls(filmstripType, assets, assetsButtons, canvas, subControls)
    , canvas(filmstripType, assets, assetsButtons, subControls)
    //, canvas(filmstripType, assets, assetsButtons)
    //, subControls(filmstripType, canvas)
    , subControls(filmstripType)
{
    setupLayout(baseWorkspace);
    setupTabButtonAndEditorCallback();
}

New_FilmstripProject::~New_FilmstripProject()
{
}

void New_FilmstripProject::setupLayout(juce::Rectangle<int> baseWorkspace)
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

void New_FilmstripProject::setupModeChanged(const juce::Rectangle<int> baseWorkspace)
{
    nameAndMode.onModeChange = [this, baseWorkspace]()
        {
            setupLayout(baseWorkspace);
        };

    WorkingMode mode = nameAndMode.getMode();

    canvas.setMode(mode);
}

juce::Rectangle<int> New_FilmstripProject::getBaseWorkspace() const
{
    return boundary;
}

void New_FilmstripProject::setupTabButtonAndEditorCallback()
{
    nameAndMode.onTextChangedCallback = [this](const juce::String& newText)
        {
            tabButton.getMainButton().setButtonText(newText);
        };
}

void New_FilmstripProject::setProjectName(juce::String& name)
{
    this->projectName = name;
    tabButton.setMainButtonText(name);
}

const juce::String& New_FilmstripProject::getProjectName() const
{
    return projectName;
}

const FilmstripType& New_FilmstripProject::getFilmstripType() const
{
    return filmstripType;
}

std::vector<std::unique_ptr<New_Asset>>& New_FilmstripProject::getAssets()
{
    return assets;
}

void New_FilmstripProject::AddAsset(const AssetType& type)
{
    assets.emplace_back(std::make_unique<New_Asset>(type));
    mainControls.getAssetsManager().addAssetButton(assets.back()->getAssetTypeStr());
}

New_TabButton& New_FilmstripProject::getTabButton()
{
    return tabButton;
}

New_NameAndMode& New_FilmstripProject::getNameAndModeControl()
{
    return nameAndMode;
}

New_MainControls& New_FilmstripProject::getMainControls()
{
    return mainControls;
}

New_Canvas& New_FilmstripProject::getCanvas()
{
    return canvas;
}

New_SubControls& New_FilmstripProject::getSubControls()
{
    return subControls;
}

Footer& New_FilmstripProject::getFooter()
{
    return footer;
}

void New_FilmstripProject::resetCurrentTheme()
{
    //tabButton.resetCurrentTheme(); 
    //nameAndMode.resetCurrentTheme(); 
    mainControls.resetCurrentTheme();
    //canvas.resetCurrentTheme(); 
    //subControls.resetCurrentTheme(); 
    //footer.resetCurrentTheme(); 
}
