/*
  ==============================================================================

    New_AssetsViewport.cpp
    Created: 10 Dec 2024 2:44:48pm
    Author:  UFTHaq

  ==============================================================================
*/

#include "New_AssetsManager.h"

New_AssetsManager::New_AssetsManager(const FilmstripType& type, std::vector<std::unique_ptr<New_Asset>>& assets, New_Canvas& canvas)
    : filmstripType(type), assets(assets), canvas(canvas), customLookAndFeel(Globals::getCustomLookAndFeel())
{
    setupAddNewAssetButton();
    setupAssetsViewport();

    switch (filmstripType)
    {
    case FilmstripType::KNOB:

        assets.emplace_back(std::make_unique<New_Asset>(AssetType::KNOB));
        addAssetButton("Knob");

        assets.emplace_back(std::make_unique<New_Asset>(AssetType::KNOB_SCALE));
        addAssetButton("Scale");

        break;

    case FilmstripType::SLIDER:

        assets.emplace_back(std::make_unique<New_Asset>(AssetType::THUMB));
        addAssetButton("Thumb");

        assets.emplace_back(std::make_unique<New_Asset>(AssetType::TRACK));
        addAssetButton("Track");
        
        assets.emplace_back(std::make_unique<New_Asset>(AssetType::TRACK_SCALE));
        addAssetButton("Scale");

        break;
    default:
        break;
    }
}

New_AssetsManager::~New_AssetsManager()
{
}

void New_AssetsManager::paint(juce::Graphics& g)
{
    g.setColour(customLookAndFeel->getCurrentTheme().SlideworksBaseColour);
    g.fillRoundedRectangle(viewportRect.toFloat(), 1);

    g.setColour(customLookAndFeel->getCurrentTheme().CustomDarkGrey);
    g.drawRoundedRectangle(viewportRect.toFloat().reduced(0.5F), 1, 0.5F);
}

void New_AssetsManager::resized()
{
    auto bounds = getLocalBounds();

    // Area Add New Asset
    auto addButtonArea = bounds.removeFromTop(20).removeFromLeft(35);
    addNewAssetButton.setBounds(addButtonArea);

    // Area Assets Viewport
    auto viewportArea = bounds;
    viewportArea.removeFromTop(3);
    viewportRect = viewportArea;
    assetsViewport.setBounds(viewportArea.reduced(1));

    resizeViewport();
}

void New_AssetsManager::resizeViewport()
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

        button->setIndex(i);
        button->setBounds(buttonBounds);
        button->getMainButton().onClick = [this, button]() 
            {
                if (button->getMainButton().getToggleState())
                {
                    button->getMainButton().setToggleState(false, juce::dontSendNotification);
                }
                else
                {
                    for (auto& mainButton : assetsButtons)
                    {
                        mainButton->getMainButton().setToggleState(false, juce::dontSendNotification);
                    }
                    button->getMainButton().setToggleState(true, juce::dontSendNotification);
                }
            };

        auto& asset = assets.at(i);
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

                        // ENABLE AND SET TOGGLE TRUE
                        button->getVisibleButton().setEnabled(true);
                        button->getVisibleButton().setToggleState(true, juce::dontSendNotification);
                        asset->makeVisible(true);

                        // REPAINT CANVAS
                        canvas.repaint();
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

        button->getDeleteButton().onClick = [safeThis = juce::Component::SafePointer<New_AssetsManager>(this), button]()
            {
                size_t deleteIndex = button->getIndex();

                if (auto* assetsManager = safeThis.getComponent())
                {
                    assetsManager->getAssets().erase(assetsManager->getAssets().begin() + deleteIndex);
                    assetsManager->getAssetButtons().erase(assetsManager->getAssetButtons().begin() + deleteIndex);
                    
                    assetsManager->resizeViewport();

                    // REPAINT CANVAS
                    assetsManager->canvas.repaint();
                }
            };

        assetsContainer.addAndMakeVisible(button);
    }

    assetsContainer.setSize(bounds.getWidth(), totalHeight);

    assetsViewport.setScrollBarThickness(thickness);
}

void New_AssetsManager::setupAddNewAssetButton()
{
    addNewAssetButton.setComponentID("Buttons_ID_07_NEW_ASSET");
    addNewAssetButton.onClick = [this]()
        {
            addAssetsSystem();
        };
    addAndMakeVisible(addNewAssetButton);
}

void New_AssetsManager::addAssetsSystem()
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
                    assets.emplace_back(std::make_unique<New_Asset>(AssetType::KNOB));
                    addAssetButton("Knob");
                }
                else if (result == 2)
                {
                    assets.emplace_back(std::make_unique<New_Asset>(AssetType::KNOB_SCALE));
                    addAssetButton("Scale");
                }
                else if (result == 3)
                {
                    assets.emplace_back(std::make_unique<New_Asset>(AssetType::KNOB_SCALE_GENERATED));
                    addAssetButton("Scale");
                }

                resizeViewport();
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
                    assets.emplace_back(std::make_unique<New_Asset>(AssetType::THUMB));
                    addAssetButton("Thumb");
                }
                else if (result == 2)
                {
                    assets.emplace_back(std::make_unique<New_Asset>(AssetType::TRACK));
                    addAssetButton("Track");
                }
                else if (result == 3)
                {
                    assets.emplace_back(std::make_unique<New_Asset>(AssetType::TRACK_SCALE));
                    addAssetButton("Scale");
                }
                else if (result == 4)
                {
                    assets.emplace_back(std::make_unique<New_Asset>(AssetType::TRACK_SCALE_GENERATED));
                    addAssetButton("Scale");
                }

                resizeViewport();
            }
        );
    }
}

void New_AssetsManager::setupAssetsViewport()
{
    assetsViewport.setComponentID("Viewport_O1_Main");
    assetsViewport.setViewedComponent(&assetsContainer, false);
    assetsViewport.setScrollBarsShown(true, false);
    addAndMakeVisible(assetsViewport);
}

juce::TextButton& New_AssetsManager::getAddNewAssetButton()
{
    return addNewAssetButton;
}

std::vector<std::unique_ptr<New_AssetButtons>>& New_AssetsManager::getAssetButtons()
{
    return assetsButtons;
}

std::vector<std::unique_ptr<New_Asset>>& New_AssetsManager::getAssets()
{
    return assets;
}

void New_AssetsManager::addAssetButton(const juce::String& type)
{
    assetsButtons.emplace_back(std::make_unique<New_AssetButtons>(type));
    addAndMakeVisible(assetsButtons.back().get());
}

void New_AssetsManager::fileChooserFunction(std::function<void(juce::String)> onFileSelected)
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
