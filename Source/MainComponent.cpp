#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize(820, 540);   // This is mandatory to not trigger error in debug mode

    setupLayoutUI();
    setupButtons(ptr_Global_CustomLookAndFeel);
    setupPageInfo();

    newFilmstripProjects.reserve(10);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)

    updatePageContent(g);

}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

    setupLayoutUI();
}

void MainComponent::updatePageContent(juce::Graphics& g)
{
    g.fillAll(ptr_Global_CustomLookAndFeel->getBackgroundColour());

    if (currentSlideWorksPage == PageState::PAGE1_GREETINGS)
    {
        g.setColour(ptr_Global_CustomLookAndFeel->getCurrentTheme().Page_1);
        g.fillRoundedRectangle(base_Workspace.toFloat(), 1);

        g.setFont(ptr_Global_CustomLookAndFeel->getFontRobotoCondensedBold().withHeight(ptr_Global_CustomLookAndFeel->getFontSizeTitle()));
        g.setColour(ptr_Global_CustomLookAndFeel->getColorCustomDarkGrey());
        g.drawText("Filmstrip Knob & Slider Generator", base_Workspace, juce::Justification::centred, true);
    }

    if (currentSlideWorksPage == PageState::PAGE2_WORKSPACE)
    {
        g.setColour(ptr_Global_CustomLookAndFeel->getCurrentTheme().ButtonsID_01_ON);
        g.fillRoundedRectangle(area_Layer1_MainWorkspace.toFloat(), 1);

        g.setColour(ptr_Global_CustomLookAndFeel->getCurrentTheme().SlideworksBaseColour);
        g.fillRoundedRectangle(area_Layer2_MainWorkspace.toFloat(), 1);
        g.setColour(ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomDarkest);
        g.drawRoundedRectangle(area_Layer2_MainWorkspace.toFloat(), 1, 0.2F);

        //g.setColour(ptr_Global_CustomLookAndFeel->getCurrentTheme().SlideworksBaseColour);
        //g.fillRoundedRectangle(area_Layer3_MainWorkspace.toFloat(), 1);
    }
}

void MainComponent::NewUpdateVisibilityPAGE_2(bool visible)
{
    if (newFilmstripProjects.size() > 0)
    {
        for (auto& project : newFilmstripProjects)
        {
            project->getTabButton().setEnabled(visible);
            project->getTabButton().setVisible(visible);

            project->getMainControls().setEnabled(visible);
            project->getMainControls().setVisible(visible);

            project->getNameAndModeControl().setEnabled(visible);
            project->getNameAndModeControl().setVisible(visible);

            project->getCanvas().setEnabled(visible);
            project->getCanvas().setVisible(visible);

            project->getSubControls().setEnabled(visible);
            project->getSubControls().setVisible(visible);

            project->getFooter().setEnabled(visible);
            project->getFooter().setVisible(visible);
        }
    }
}

void MainComponent::updatePage3InfoVisibility(bool visible)
{
    pageInfo.setEnabled(visible);
    pageInfo.setVisible(visible);
}

/////////////////////////////////////////////////////////////////////
void MainComponent::setupLayoutUI()
{
    ///////////////// NEW PLAN PAGE 1 COMPONENT /////////////////
    base_SlideWorks = getLocalBounds().reduced(5);
    int componentSpace = 2;

    juce::Rectangle<int> area_NewProjectButton{ base_SlideWorks.getX(), base_SlideWorks.getY(), MenuButtonWidth, MenuButtonHeight };
    juce::Rectangle<int> area_ThemeButton{ area_NewProjectButton.getRight() + componentSpace, area_NewProjectButton.getY(), area_NewProjectButton.getWidth(), area_NewProjectButton.getHeight() };
    juce::Rectangle<int> area_InfoButton{ area_ThemeButton.getRight() + componentSpace, area_NewProjectButton.getY(), area_NewProjectButton.getWidth(), area_NewProjectButton.getHeight() };

    SW_NewProjectButton.setBounds(area_NewProjectButton);
    SW_ThemeButton.setBounds(area_ThemeButton);
    SW_InfoButton.setBounds(area_InfoButton);

    base_Workspace = base_SlideWorks;
    base_Workspace.removeFromTop(SW_NewProjectButton.getHeight() + componentSpace);

    //////// ==== PAGE 2 WORKSPACE ==== ////////

    ///== Area Footer ==///
    auto copy_base_Workspace = base_Workspace;
    area_Footer = copy_base_Workspace.removeFromBottom(FooterHeight);
    copy_base_Workspace.removeFromBottom(1);
    area_MainControl = copy_base_Workspace.removeFromLeft(MainControlWidth);
    copy_base_Workspace.removeFromLeft(1);
    area_Layer1_MainWorkspace = copy_base_Workspace;

    area_FilmstripProjects = copy_base_Workspace.removeFromTop(FooterHeight);
    area_Layer2_MainWorkspace = copy_base_Workspace;
    area_Layer2_MainWorkspace = area_Layer2_MainWorkspace.reduced(1);

    auto copy_area_Layer2_MainWorkspace = area_Layer2_MainWorkspace;
    area_ModeButtons = copy_area_Layer2_MainWorkspace.removeFromTop(FooterHeight);
    copy_area_Layer2_MainWorkspace.removeFromLeft(1);
    copy_area_Layer2_MainWorkspace.removeFromRight(1);
    copy_area_Layer2_MainWorkspace.removeFromBottom(1);
    area_Layer3_MainWorkspace = copy_area_Layer2_MainWorkspace;

    auto copy_area_Layer3_MainWorkspace = area_Layer3_MainWorkspace;

    if (newFilmstripProjects.size() > 0)
    {
        // PLAN:
        // ONLY TAB BUTTON WILL DEFINES HERE, BECAUSE THIS BUTTONS IS MOVABLE, 
        // THE REST IS DEFINES IN ITS OWN CLASS CONSTRUCTORS.

        // TAB BUTTON VIEWPORT
        auto copy_area_FilmstripProjects = area_FilmstripProjects;

        juce::Rectangle<int> tabButtonArea{ copy_area_FilmstripProjects.getX(),copy_area_FilmstripProjects.getY(), FPButtonWidth, copy_area_FilmstripProjects.getHeight() + 1 };

        for (auto& project : newFilmstripProjects)
        {
            if (project != nullptr)
            {
                addAndMakeVisible(project->getTabButton());
                project->getTabButton().setBounds(tabButtonArea.reduced(1));
                tabButtonArea.translate(FPButtonWidth - 1, 0);

                // Resize all Project component
                project->setupLayout(base_Workspace);
            }
        }
    }


    //////////------------ INFO CARD GROUP ------------////////
    pageInfo.setBounds(base_Workspace);
}

void MainComponent::setupButtons(CustomLookAndFeel* customLookAndFeel)
{
    setupProjectButtons(customLookAndFeel);
}

void MainComponent::setupPageInfo()
{
    pageInfo.setBounds(base_Workspace);
    pageInfo.getCloseButton().onClick = [this]() 
        {
            currentSlideWorksPage = previousSlideWorksPage;

            if (currentSlideWorksPage == PageState::PAGE2_WORKSPACE)
                NewUpdateVisibilityPAGE_2(true);

            updatePage3InfoVisibility(false);
            repaint();
        };
    addAndMakeVisible(pageInfo);

    pageInfo.setEnabled(false);
    pageInfo.setVisible(false);

    //updatePage3InfoVisibility(false);
}

void MainComponent::setupProjectButtons(CustomLookAndFeel* customLookAndFeel)
{
    SW_NewProjectButton.setButtonText("New");
    SW_NewProjectButton.setComponentID("Buttons_ID_01_SW");
    SW_NewProjectButton.setLookAndFeel(customLookAndFeel);
    SW_NewProjectButton.onClick = [&, customLookAndFeel, this]()
        {
            bool buttonMenuEnable{ false };
            if (newFilmstripProjects.size() < 5)
            {
                buttonMenuEnable = true;
            }

            juce::PopupMenu menu;
            menu.addSectionHeader("New Filmstrip Project");
            menu.addSeparator();
            menu.addItem(1, "Knob Filmstrip", buttonMenuEnable, false);
            menu.addItem(2, "Slider Filmstrip", buttonMenuEnable, false);
            menu.setLookAndFeel(customLookAndFeel);


            menu.showMenuAsync(juce::PopupMenu::Options{}.withTargetComponent(SW_NewProjectButton), [this](int result)
                {
                    if (result == 1)
                    {
                        auto project = std::make_unique<New_FilmstripProject>(FilmstripType::KNOB, base_Workspace);

                        auto* ptr = project.get();
                        project->getTabButton().getMainButton().onClick = [this, ptr]()
                            {
                                for (auto& proj : newFilmstripProjects)
                                {
                                    bool isSelected = (proj.get() == ptr);

                                    proj->getTabButton().getMainButton().setToggleState(isSelected, juce::dontSendNotification);

                                    proj->getMainControls().setEnabled(isSelected);
                                    proj->getMainControls().setVisible(isSelected);

                                    proj->getNameAndModeControl().setEnabled(isSelected);
                                    proj->getNameAndModeControl().setVisible(isSelected);

                                    proj->getCanvas().setEnabled(isSelected);
                                    proj->getCanvas().setVisible(isSelected);

                                    proj->getSubControls().setEnabled(isSelected);
                                    proj->getSubControls().setVisible(isSelected);

                                    proj->getFooter().setEnabled(isSelected);
                                    proj->getFooter().setVisible(isSelected);
                                }
                            };

                        project->getTabButton().getCloseButton().onClick = [safeThis = juce::Component::SafePointer<MainComponent>(this), ptr]()
                            {
                                if (auto* mainComp = safeThis.getComponent())
                                {
                                    size_t deletedIndex{};
                                    bool wasActive{};
                                    for (size_t i = 0; i < mainComp->newFilmstripProjects.size(); i++)
                                    {
                                        if (mainComp->newFilmstripProjects.at(i).get() == ptr)
                                        {
                                            deletedIndex = i;
                                            wasActive = mainComp->newFilmstripProjects.at(i)->getTabButton().getMainButton().getToggleState();
                                        }

                                    }
                                    mainComp->newFilmstripProjects.erase(mainComp->newFilmstripProjects.begin() + deletedIndex);

                                    if (mainComp->newFilmstripProjects.size() > 0)
                                    {
                                        if (wasActive)
                                        {
                                            if (deletedIndex == mainComp->newFilmstripProjects.size())
                                                mainComp->newFilmstripProjects.at(deletedIndex - 1)->getTabButton().getMainButton().setToggleState(true, juce::dontSendNotification);
                                            else 
                                                mainComp->newFilmstripProjects.at(deletedIndex)->getTabButton().getMainButton().setToggleState(true, juce::dontSendNotification);
                                            
                                            // Reload the project based on tabButton toggle state
                                            for (auto& proj : mainComp->newFilmstripProjects)
                                            {
                                                bool visible = (proj->getTabButton().getMainButton().getToggleState());

                                                proj->getMainControls().setEnabled(visible);
                                                proj->getMainControls().setVisible(visible);

                                                proj->getNameAndModeControl().setEnabled(visible);
                                                proj->getNameAndModeControl().setVisible(visible);

                                                proj->getCanvas().setEnabled(visible);
                                                proj->getCanvas().setVisible(visible);

                                                proj->getSubControls().setEnabled(visible);
                                                proj->getSubControls().setVisible(visible);

                                                proj->getFooter().setEnabled(visible);
                                                proj->getFooter().setVisible(visible);
                                            }
                                        }
                                        else
                                        {
                                            // Nothing need to reload
                                        }
                                    }
                                    else
                                    {
                                        mainComp->currentSlideWorksPage = PageState::PAGE1_GREETINGS;
                                        mainComp->repaint();
                                    }

                                    mainComp->setupLayoutUI();     // This is the one that make this system use safePointer.
                                }
                            };

                        addChildComponent(project->getNameAndModeControl());
                        addChildComponent(project->getMainControls());
                        addChildComponent(project->getCanvas());
                        addChildComponent(project->getSubControls());
                        addChildComponent(project->getFooter());

                        newFilmstripProjects.push_back(std::move(project));
                        
                    }
                    else if (result == 2)
                    {

                        auto project = std::make_unique<New_FilmstripProject>(FilmstripType::SLIDER, base_Workspace);

                        auto* ptr = project.get();
                        project->getTabButton().getMainButton().onClick = [this, ptr]()
                            {
                                for (auto& proj : newFilmstripProjects)
                                {
                                    bool isSelected = (proj.get() == ptr);

                                    proj->getTabButton().getMainButton().setToggleState(isSelected, juce::dontSendNotification);

                                    proj->getMainControls().setEnabled(isSelected);
                                    proj->getMainControls().setVisible(isSelected);

                                    proj->getNameAndModeControl().setEnabled(isSelected);
                                    proj->getNameAndModeControl().setVisible(isSelected);

                                    proj->getCanvas().setEnabled(isSelected);
                                    proj->getCanvas().setVisible(isSelected);

                                    proj->getSubControls().setEnabled(isSelected);
                                    proj->getSubControls().setVisible(isSelected);

                                    proj->getFooter().setEnabled(isSelected);
                                    proj->getFooter().setVisible(isSelected);
                                }
                            };

                        project->getTabButton().getCloseButton().onClick = [safeThis = juce::Component::SafePointer<MainComponent>(this), ptr]()
                            {
                                if (auto* mainComp = safeThis.getComponent())
                                {
                                    size_t deletedIndex{};
                                    bool wasActive{};
                                    for (size_t i = 0; i < mainComp->newFilmstripProjects.size(); i++)
                                    {
                                        if (mainComp->newFilmstripProjects.at(i).get() == ptr)
                                        {
                                            deletedIndex = i;
                                            wasActive = mainComp->newFilmstripProjects.at(i)->getTabButton().getMainButton().getToggleState();
                                        }

                                    }
                                    mainComp->newFilmstripProjects.erase(mainComp->newFilmstripProjects.begin() + deletedIndex);

                                    if (mainComp->newFilmstripProjects.size() > 0)
                                    {
                                        if (wasActive)
                                        {
                                            if (deletedIndex == mainComp->newFilmstripProjects.size())
                                                mainComp->newFilmstripProjects.at(deletedIndex - 1)->getTabButton().getMainButton().setToggleState(true, juce::dontSendNotification);
                                            else
                                                mainComp->newFilmstripProjects.at(deletedIndex)->getTabButton().getMainButton().setToggleState(true, juce::dontSendNotification);

                                            // Reload the project based on tabButton toggle state
                                            for (auto& proj : mainComp->newFilmstripProjects)
                                            {
                                                bool visible = (proj->getTabButton().getMainButton().getToggleState());

                                                proj->getMainControls().setEnabled(visible);
                                                proj->getMainControls().setVisible(visible);

                                                proj->getNameAndModeControl().setEnabled(visible);
                                                proj->getNameAndModeControl().setVisible(visible);

                                                proj->getCanvas().setEnabled(visible);
                                                proj->getCanvas().setVisible(visible);

                                                proj->getSubControls().setEnabled(visible);
                                                proj->getSubControls().setVisible(visible);

                                                proj->getFooter().setEnabled(visible);
                                                proj->getFooter().setVisible(visible);
                                            }
                                        }
                                        else
                                        {
                                            // Nothing need to reload
                                        }
                                    }
                                    else
                                    {
                                        mainComp->currentSlideWorksPage = PageState::PAGE1_GREETINGS;
                                        mainComp->repaint();
                                    }

                                    mainComp->setupLayoutUI();
                                }
                            };


                        addChildComponent(project->getNameAndModeControl());
                        addChildComponent(project->getMainControls());
                        addChildComponent(project->getCanvas());
                        addChildComponent(project->getSubControls());
                        addChildComponent(project->getFooter());

                        newFilmstripProjects.push_back(std::move(project));

                    }


                    // SET NEW PROJECT TO VISIBLE
                    if (newFilmstripProjects.size() > 0)
                    {
                        currentSlideWorksPage = PageState::PAGE2_WORKSPACE;

                        NewUpdateVisibilityPAGE_2(true);
                        updatePage3InfoVisibility(false);


                        for (auto& proj : newFilmstripProjects)
                        {
                            bool isSelected = (proj.get() == newFilmstripProjects.back().get());

                            proj->getTabButton().getMainButton().setToggleState(isSelected, juce::dontSendNotification);

                            proj->getMainControls().setEnabled(isSelected);
                            proj->getMainControls().setVisible(isSelected);

                            proj->getNameAndModeControl().setEnabled(isSelected);
                            proj->getNameAndModeControl().setVisible(isSelected);

                            proj->getCanvas().setEnabled(isSelected);
                            proj->getCanvas().setVisible(isSelected);

                            proj->getSubControls().setEnabled(isSelected);
                            proj->getSubControls().setVisible(isSelected);

                            proj->getFooter().setEnabled(isSelected);
                            proj->getFooter().setVisible(isSelected);
                        }
                    }

                    setupLayoutUI();
                    repaint();
                }
            );
        };
    addAndMakeVisible(SW_NewProjectButton);

    SW_ThemeButton.setButtonText("Theme");
    SW_ThemeButton.setComponentID("Buttons_ID_01_SW");
    SW_ThemeButton.setLookAndFeel(customLookAndFeel);
    SW_ThemeButton.onClick = [&, customLookAndFeel, this] ()
        {
            ThemeType currentTheme = customLookAndFeel->getCurrentThemeType();

            juce::PopupMenu menu;
            menu.setLookAndFeel(customLookAndFeel);
            menu.addSectionHeader("Theme");
            menu.addSeparator();
            menu.addItem(1, "Office Light", true, currentTheme == ThemeType::OfficeLight);
            menu.addItem(2, "Dark Night", true, currentTheme == ThemeType::DarkNight);

            menu.showMenuAsync(juce::PopupMenu::Options{}.withTargetComponent(SW_ThemeButton), [this, customLookAndFeel](int result)
                {
                    if (result == 1)
                    {
                        customLookAndFeel->setTheme(ThemeType::OfficeLight);
                    }
                    else if (result == 2)
                    {
                        customLookAndFeel->setTheme(ThemeType::DarkNight);
                    }
                    repaint();

                    Globals::repaintTitleBar = true;

                }
            );
        };
    addAndMakeVisible(SW_ThemeButton);

    SW_InfoButton.setButtonText("Info");
    SW_InfoButton.setComponentID("Buttons_ID_01_SW");
    SW_InfoButton.setLookAndFeel(customLookAndFeel);
    SW_InfoButton.onClick = [this]()
        {
            if (currentSlideWorksPage != PageState::PAGE3_INFO)
            {
                previousSlideWorksPage = currentSlideWorksPage;
                currentSlideWorksPage = PageState::PAGE3_INFO;

                NewUpdateVisibilityPAGE_2(false);

                updatePage3InfoVisibility(true);
                repaint();
            }
        };
    addAndMakeVisible(SW_InfoButton);
}

void MainComponent::setupSimulationKnob(CustomLookAndFeel* customLookAndFeel)
{
    simulationKnob.setName("simulationKnob");
    simulationKnob.setRange(0, 100, 1);
    simulationKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    simulationKnob.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    simulationKnob.setLookAndFeel(customLookAndFeel);
    simulationKnob.onValueChange = [this]() {};
    addAndMakeVisible(simulationKnob);
}
