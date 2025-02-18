/*
  ==============================================================================

    AssetsViewport.cpp
    Created: 10 Dec 2024 2:44:48pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "AssetsManager.h"

AssetsManager::AssetsManager
(
    const FilmstripType& type
    , std::vector<std::unique_ptr<Asset>>& assets
    , std::vector<std::unique_ptr<AssetButtons>>& assetsButtons
    , Canvas& canvas
    , SubControls& subControls
)
    : filmstripType(type)
    , assets(assets)
    , assetsButtons(assetsButtons)
    , canvas(canvas)
    , subControls(subControls)
    , customLookAndFeel(Globals::getCustomLookAndFeel())
{
    setupAddNewAssetButton();
    setupAssetsViewport();
    setupDefaultAssets();
}

AssetsManager::~AssetsManager()
{
}

void AssetsManager::paint(juce::Graphics& g)
{
    g.setColour(customLookAndFeel->getCurrentTheme().SlideworksBaseColour);
    g.fillRoundedRectangle(viewportRect.toFloat(), 1);

    g.setColour(customLookAndFeel->getCurrentTheme().CustomDarkGrey);
    g.drawRoundedRectangle(viewportRect.toFloat().reduced(0.5F), 1, 0.5F);
}

void AssetsManager::resized()
{
    auto bounds = getLocalBounds();

    // Area Add New Asset
    auto addButtonArea = bounds.removeFromTop(20).removeFromLeft(35);
    addNewAssetButton.setBounds(addButtonArea);

    // Area Assets Viewport
    resizeViewport(bounds);

    resizeContainer();
}

void AssetsManager::setupAddNewAssetButton()
{
    addNewAssetButton.setComponentID("Buttons_ID_07_NEW_ASSET");
    addNewAssetButton.onClick = [this]()
        {
            addAssetsSystem();
        };
    addAndMakeVisible(addNewAssetButton);
}

void AssetsManager::setupAssetsViewport()
{
    assetsViewport.setComponentID("Viewport_O1_Main");
    assetsViewport.setViewedComponent(&assetsContainer, false);
    assetsViewport.setScrollBarsShown(true, false);
    addAndMakeVisible(assetsViewport);
}

void AssetsManager::setupDefaultAssets()
{
    switch (filmstripType)
    {
    case FilmstripType::KNOB:

        assets.emplace_back(std::make_unique<Asset>(AssetType::KNOB));
        addAssetButton("Knob");

        assets.emplace_back(std::make_unique<Asset>(AssetType::KNOB_SCALE));
        addAssetButton("Scale");

        break;

    case FilmstripType::SLIDER:

        assets.emplace_back(std::make_unique<Asset>(AssetType::THUMB));
        addAssetButton("Thumb");

        assets.emplace_back(std::make_unique<Asset>(AssetType::TRACK));
        addAssetButton("Track");

        assets.emplace_back(std::make_unique<Asset>(AssetType::TRACK_SCALE));
        addAssetButton("Scale");

        break;
    default:
        break;
    }
}

void AssetsManager::addAssetsSystem()
{
    bool buttonMenuEnable{ false };
    if (assetsButtons.size() < 7)
    {
        buttonMenuEnable = true;
    }

    if (filmstripType == FilmstripType::KNOB)
    {
        juce::PopupMenu menu;
        menu.addSectionHeader("Assets Manager");
        menu.addSeparator();
        menu.addItem(1, "Add Knob", buttonMenuEnable, false);
        menu.addItem(2, "Add Scale", buttonMenuEnable, false);
        menu.addItem(3, "Generate Scale", buttonMenuEnable, false);

        menu.showMenuAsync(juce::PopupMenu::Options{}.withTargetComponent(addNewAssetButton), [this](int result)
            {
                if (result == 1)
                {
                    assets.emplace_back(std::make_unique<Asset>(AssetType::KNOB));
                    addAssetButton("Knob");
                }
                else if (result == 2)
                {
                    assets.emplace_back(std::make_unique<Asset>(AssetType::KNOB_SCALE));
                    addAssetButton("Scale");
                }
                else if (result == 3)
                {
                    assets.emplace_back(std::make_unique<Asset>(AssetType::KNOB_SCALE_GENERATED));
                    addAssetButton("Scale");
                }

                resizeContainer();
                canvas.resized();
                canvas.getCanvasEdit().setupNewAsset();
            }
        );
    }

    if (filmstripType == FilmstripType::SLIDER)
    {
        juce::PopupMenu menu;
        menu.addSectionHeader("Assets Manager");
        menu.addSeparator();
        menu.addItem(1, "Add Thumb", buttonMenuEnable, false);
        menu.addItem(2, "Add Track", buttonMenuEnable, false);
        menu.addItem(3, "Add Scale", buttonMenuEnable, false);
        menu.addItem(4, "Generate Scale", buttonMenuEnable, false);

        menu.showMenuAsync(juce::PopupMenu::Options{}.withTargetComponent(addNewAssetButton), [this](int result)
            {
                if (result == 1)
                {
                    assets.emplace_back(std::make_unique<Asset>(AssetType::THUMB));
                    addAssetButton("Thumb");
                }
                else if (result == 2)
                {
                    assets.emplace_back(std::make_unique<Asset>(AssetType::TRACK));
                    addAssetButton("Track");
                }
                else if (result == 3)
                {
                    assets.emplace_back(std::make_unique<Asset>(AssetType::TRACK_SCALE));
                    addAssetButton("Scale");
                }
                else if (result == 4)
                {
                    assets.emplace_back(std::make_unique<Asset>(AssetType::TRACK_SCALE_GENERATED));
                    addAssetButton("Scale");
                }

                resizeContainer();
                canvas.resized();
                canvas.getCanvasEdit().setupNewAsset();
            }
        );
    }
}

void AssetsManager::resizeViewport(juce::Rectangle<int>& bounds)
{
    auto viewportArea = bounds;
    viewportArea.removeFromTop(3);
    viewportRect = viewportArea;
    assetsViewport.setBounds(viewportArea.reduced(1));
}

void AssetsManager::resizeContainer()
{
    auto bounds = assetsViewport.getLocalBounds();

    int buttonHeight{ 24 };
    int spaceH{ 1 };
    int spaceW{ 1 };
    int totalHeight{};
    int thickness{};
    int buttonWidth{};
    int y{};

    for (size_t i = 0; i < assetsButtons.size(); i++)
    {
        y = (int)i * (buttonHeight + spaceH);
    }
    totalHeight = y + buttonHeight + (spaceH * 2);

    if (totalHeight < assetsViewport.getHeight())
    {
        thickness = 0;
        buttonWidth = bounds.getWidth() - (spaceW * 2);
    }
    else
    {
        thickness = 8;
        buttonWidth = bounds.getWidth() - spaceW - thickness;
    }

    for (size_t i = 0; i < assetsButtons.size(); i++)
    {
        y = (int)i * (buttonHeight + spaceH);

        auto buttonBounds = juce::Rectangle{ spaceW, 1 + y, buttonWidth, buttonHeight };

        auto button = assetsButtons.at(i).get();
        auto& asset = assets.at(i);
        auto controlAsset = asset->getControlAsset().get();

        auto area = subControls.getLocalBounds().reduced(5);
        //asset->getControlAsset()->setBounds(area.removeFromTop(200));          // setBounds for ControlAssets and their inheritances.
        int areaHeight{ 0 };

        if (auto assetSubControlBounds = dynamic_cast<ControlAssetKnob*>(controlAsset))
        {
            areaHeight = assetSubControlBounds->getAreaHeight();
            assetSubControlBounds->setBounds(area.removeFromTop(areaHeight));
        }
        else if (auto assetSubControlBounds = dynamic_cast<ControlAssetKnobScale*>(controlAsset))
        {
            areaHeight = assetSubControlBounds->getAreaHeight();
            assetSubControlBounds->setBounds(area.removeFromTop(areaHeight));
        }
        else if (auto assetSubControlBounds = dynamic_cast<ControlAssetThumb*>(controlAsset))
        {
            areaHeight = assetSubControlBounds->getAreaHeight();
            assetSubControlBounds->setBounds(area.removeFromTop(areaHeight));
        }
        else if (auto assetSubControlBounds = dynamic_cast<ControlAssetTrack*>(controlAsset))
        {
            areaHeight = assetSubControlBounds->getAreaHeight();
            assetSubControlBounds->setBounds(area.removeFromTop(areaHeight));
        }
        else if (auto assetSubControlBounds = dynamic_cast<ControlAssetTrackScale*>(controlAsset))
        {
            areaHeight = assetSubControlBounds->getAreaHeight();
            assetSubControlBounds->setBounds(area.removeFromTop(areaHeight));
        }


        button->setIndex(i);
        button->setBounds(buttonBounds);
        button->clickThis = [this, &asset](AssetButtons* btn)
            {
                if (btn->isThisSelected())
                {
                    btn->selectThis(false);

                    subControls.removeFromSubControl(asset->getControlAsset());
                }
                else
                {
                    for (size_t j = 0; j < assetsButtons.size(); j++)
                    {
                        assetsButtons.at(j)->selectThis(false);
                    }

                    btn->selectThis(true);

                    resizeContainer();

                    subControls.displayToSubControl(asset->getControlAsset());  // addAndMakeVisible
                }

                subControls.repaint();
            };

        button->getLoadImageButton().onClick = [this, button, &asset]()
            {
                // FileChooser
                fileChooserFunction([this, button, &asset](juce::String chooserPath)
                    {
                        if (chooserPath.isEmpty())
                        {
                            DBG("No valid file selected");
                            return;
                        }

                        juce::File path = chooserPath;
                        asset->setAssetFilePathAndLoadImage(path);

                        juce::String name = path.getFileName();
                        asset->setAssetName(name);
                        button->setNameDisplay(name);
                        button->repaint();

                        // ENABLE AND SET TOGGLE TRUE
                        button->getVisibleButton().setEnabled(true);
                        button->getVisibleButton().setToggleState(true, juce::dontSendNotification);
                        asset->makeVisible(true);

                        // REPAINT CANVAS
                        canvas.repaint();

                        // SET IMAGE RATIO TO CONTROL ASSET
                        int w = asset->getAssetImage().getWidth();
                        int h = asset->getAssetImage().getHeight();

                        DBG("IMAGE W : " << w);
                        DBG("IMAGE H : " << h);

                        asset->getControlAsset()->setOriginalAssetRatio(w, h);

                        // MAKE IT USED THE NEWEST BOUNDS
                        asset->getControlAsset()->calculateAssetRealAndVirtualBounds();

                        //resizeContainer();
                    }
                );
            };

        button->getVisibleButton().onClick = [this, button, &asset]()
            {
                // Visible (Eye) Button
                if (button->getVisibleButton().getToggleState())
                {
                    button->getVisibleButton().setToggleState(false, juce::dontSendNotification);
                    asset->makeVisible(false);
                }

                else
                {
                    button->getVisibleButton().setToggleState(true, juce::dontSendNotification);
                    asset->makeVisible(true);
                }

                // REPAINT CANVAS
                canvas.repaint();
            };

        button->getDeleteButton().onClick = [safeThis = juce::Component::SafePointer<AssetsManager>(this), button]()
            {
                // No need to remove from assetsContainer, just erase the component.

                size_t deleteIndex = button->getIndex();

                if (auto* assetsManager = safeThis.getComponent())
                {
                    assetsManager->getAssets().erase(assetsManager->getAssets().begin() + deleteIndex);
                    assetsManager->getAssetButtons().erase(assetsManager->getAssetButtons().begin() + deleteIndex);

                    if (assetsManager->getAssets().size() == 0) 
                        assetsManager->getSubControls().displayDefaultSubControl();
                    
                    assetsManager->resizeContainer();
                    assetsManager->getSubControls().resizeContainer();

                    // REPAINT CANVAS
                    assetsManager->canvas.repaint();
                }

            };

        assetsContainer.addAndMakeVisible(button);

        button->onDragCallback = [this](AssetButtons* draggedButton, juce::Point<int> dragPoint)
            {
                handleDrag(draggedButton, dragPoint);
            };

    }

    assetsContainer.setSize(bounds.getWidth(), totalHeight);

    assetsViewport.setScrollBarThickness(thickness);
}

void AssetsManager::handleDrag(AssetButtons* draggedButton, juce::Point<int> dragPoint)
{
    size_t draggedIndex = std::distance(assetsButtons.begin(), std::find_if(assetsButtons.begin(), assetsButtons.end(),
        [draggedButton](const auto& btn)
        {
            return btn.get() == draggedButton;
        }));

    int buttonHeight = assetsButtons.back()->getHeight();

    size_t targetIndex = std::clamp(static_cast<size_t>(dragPoint.y / (buttonHeight + 1)),
                                    size_t(0),
                                    assetsButtons.size() - 1);

    if (draggedIndex != targetIndex)
    {
        // Rearrange the assetsButtons vector
        auto draggedElement = std::move(assetsButtons.at(draggedIndex));
        assetsButtons.erase(assetsButtons.begin() + draggedIndex);
        assetsButtons.insert(assetsButtons.begin() + targetIndex, std::move(draggedElement));

        // Rearrange the assets vector
        auto asset = std::move(assets.at(draggedIndex));
        assets.erase(assets.begin() + draggedIndex);
        assets.insert(assets.begin() + targetIndex, std::move(asset));

        resizeContainer();

        subControls.resized();

        // need to calll repaint the canvas
        canvas.repaint();
    }
}


juce::TextButton& AssetsManager::getAddNewAssetButton()
{
    return addNewAssetButton;
}

std::vector<std::unique_ptr<AssetButtons>>& AssetsManager::getAssetButtons()
{
    return assetsButtons;
}

std::vector<std::unique_ptr<Asset>>& AssetsManager::getAssets()
{
    return assets;
}

SubControls& AssetsManager::getSubControls() const
{
    return subControls;
}


void AssetsManager::addAssetButton(const juce::String& type)
{
    assetsButtons.emplace_back(std::make_unique<AssetButtons>(type));
    addAndMakeVisible(assetsButtons.back().get());
}

void AssetsManager::fileChooserFunction(std::function<void(juce::String)> onFileSelected)
{
    fileChooser.reset(new juce::FileChooser("Select a file", juce::File(), "*.png"));

    auto fileChooserFlags = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles;

    fileChooser->launchAsync(fileChooserFlags, [onFileSelected](const juce::FileChooser& chooser)
        {
            juce::File selectedFile = chooser.getResult();
            juce::String inputPath{};

            if (selectedFile.existsAsFile())
            {
                inputPath = selectedFile.getFullPathName();

                if (selectedFile.hasFileExtension(".png"))
                {
                    DBG("Selected file is a valid PNG: " << inputPath);
                }
                else
                {
                    DBG("Selected file is NOT a PNG: " << inputPath);
                }
            }
            else
            {
                DBG("No file is selected");
                inputPath.clear();
            }

            onFileSelected(inputPath);
        }
    );
}
