#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize(820, 540);   // This is mandatory to not trigger error in debug mode

    setupLayoutUI();
    setupButtons(ptr_Global_CustomLookAndFeel);
    setupCustomGroupComponents();

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

    if (currentSlideWorksPage == PageState::PAGE3_INFO)
    {
        g.setColour(ptr_Global_CustomLookAndFeel->getCurrentTheme().Page_1);
        g.fillRoundedRectangle(base_Workspace.toFloat(), 1);
        
        groupDialog_2_Info.paint(g);
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
    closeDialog_2_Info.setEnabled(visible);
    closeDialog_2_Info.setVisible(visible);

    author_param.setVisible(visible);
    author_arg.setVisible(visible);

    version_param.setVisible(visible);
    version_arg.setVisible(visible);

    release_param.setVisible(visible);
    release_arg.setVisible(visible);

    license_param.setVisible(visible);
    license_arg.setVisible(visible);

    juceVersion_arg.setVisible(visible);
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

    //if (SlideWorksMode == ModeState::EDIT)

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

    ////////------------ INFO CARD GROUP ------------////////
    auto base_groupDialog_2_Info{ base_Workspace.withSizeKeepingCentre(275, 240) };
    auto groupDialog_2_Info_Area = base_groupDialog_2_Info.reduced(10);
    groupDialog_2_Info_Area.removeFromBottom(40);
    groupDialog_2_Info.setBounds(groupDialog_2_Info_Area);

    auto infoArea = groupDialog_2_Info_Area;
    infoArea.removeFromTop(8);
    infoArea = infoArea.reduced(20);
    infoArea = infoArea.withSizeKeepingCentre(150, infoArea.getHeight());

    auto contentHeight = infoArea.getHeight() / 5;
    auto author = infoArea.removeFromTop(contentHeight);
    auto version = infoArea.removeFromTop(contentHeight);
    auto release = infoArea.removeFromTop(contentHeight);
    auto license = infoArea.removeFromTop(contentHeight);
    auto juceVer = infoArea.removeFromTop(contentHeight);

    auto paramWidht = static_cast<int>(infoArea.getWidth() * 0.4F);
    author_param.setBounds(author.removeFromLeft(paramWidht));
    author_arg.setBounds(author);
    version_param.setBounds(version.removeFromLeft(paramWidht));
    version_arg.setBounds(version);
    release_param.setBounds(release.removeFromLeft(paramWidht));
    release_arg.setBounds(release);
    license_param.setBounds(license.removeFromLeft(paramWidht));
    license_arg.setBounds(license);
    juceVersion_arg.setBounds(juceVer);

    // CLOSE BUTTON
    {
        auto w = 100;
        auto h = 30;
        juce::Rectangle dialog2_Close{
            base_groupDialog_2_Info.getX() + (base_groupDialog_2_Info.getWidth() - w) / 2,
            base_groupDialog_2_Info.getBottom() - h - 10,
            w,
            h
        };
        closeDialog_2_Info.setBounds(dialog2_Close);
    }    
}

void MainComponent::setupButtons(CustomLookAndFeel* customLookAndFeel)
{
    setupProjectButtons(customLookAndFeel);
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

void MainComponent::setupCustomGroupComponents()
{
    auto indentation = 5.0F;
    auto gap = 6.0F;
    auto cornerSize = 5.0F;
    auto lineThick = 1.0F;
    auto fontSize = 16.0F;
    auto font = ptr_Global_CustomLookAndFeel->getFontRobotoCondensedRegular().withHeight(fontSize);
    auto fontColor = ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomDarkGrey;
    auto outlineColor = ptr_Global_CustomLookAndFeel->getCurrentTheme().OutlineControl;

    groupDialog_2_Info.setName("DIALOG 2 INFO");
    groupDialog_2_Info.setText("SLIDEWORKS");
    groupDialog_2_Info.setTextLabelPosition(juce::Justification::centred);
    groupDialog_2_Info.setFont(ptr_Global_CustomLookAndFeel->getFontRobotoCondensedBold().withHeight(18.0F));
    groupDialog_2_Info.setFontColour(ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomGroupComponent);
    groupDialog_2_Info.setOutlineColour(ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomGroupComponent);
    groupDialog_2_Info.setCornerSize(10.0F);
    groupDialog_2_Info.setIndentation(3.0F);
    groupDialog_2_Info.setTextLineGap(8.0F);
    groupDialog_2_Info.setLineThickness(1.5F);
    addAndMakeVisible(groupDialog_2_Info);

    author_param.setText("Author", juce::dontSendNotification);
    author_param.setJustificationType(juce::Justification::centredLeft);
    author_param.setFont(ptr_Global_CustomLookAndFeel->getFontRobotoCondensedBold().withHeight(17.0F));
    author_param.setColour(juce::Label::backgroundColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomTransparent);
    author_param.setColour(juce::Label::textColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomGroupComponent);
    author_param.setLookAndFeel(ptr_Global_CustomLookAndFeel);
    addAndMakeVisible(author_param);
    author_arg.setText(":  UFTHaq", juce::dontSendNotification);
    author_arg.setJustificationType(juce::Justification::centredLeft);
    author_arg.setFont(ptr_Global_CustomLookAndFeel->getFontRobotoCondensedBold().withHeight(17.0F));
    author_arg.setColour(juce::Label::backgroundColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomTransparent);
    author_arg.setColour(juce::Label::textColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomGroupComponent);
    author_arg.setLookAndFeel(ptr_Global_CustomLookAndFeel);
    addAndMakeVisible(author_arg);

    version_param.setText("Version", juce::dontSendNotification);
    version_param.setJustificationType(juce::Justification::centredLeft);
    version_param.setFont(ptr_Global_CustomLookAndFeel->getFontRobotoCondensedBold().withHeight(17.0F));
    version_param.setColour(juce::Label::backgroundColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomTransparent);
    version_param.setColour(juce::Label::textColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomGroupComponent);
    version_param.setLookAndFeel(ptr_Global_CustomLookAndFeel);
    addAndMakeVisible(version_param);
    version_arg.setText(":  1.0", juce::dontSendNotification);
    version_arg.setJustificationType(juce::Justification::centredLeft);
    version_arg.setFont(ptr_Global_CustomLookAndFeel->getFontRobotoCondensedBold().withHeight(17.0F));
    version_arg.setColour(juce::Label::backgroundColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomTransparent);
    version_arg.setColour(juce::Label::textColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomGroupComponent);
    version_arg.setLookAndFeel(ptr_Global_CustomLookAndFeel);
    addAndMakeVisible(version_arg);

    release_param.setText("Release", juce::dontSendNotification);
    release_param.setJustificationType(juce::Justification::centredLeft);
    release_param.setFont(ptr_Global_CustomLookAndFeel->getFontRobotoCondensedBold().withHeight(17.0F));
    release_param.setColour(juce::Label::backgroundColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomTransparent);
    release_param.setColour(juce::Label::textColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomGroupComponent);
    release_param.setLookAndFeel(ptr_Global_CustomLookAndFeel);
    addAndMakeVisible(release_param);
    release_arg.setText(":  15/12/2024", juce::dontSendNotification);
    release_arg.setJustificationType(juce::Justification::centredLeft);
    release_arg.setFont(ptr_Global_CustomLookAndFeel->getFontRobotoCondensedBold().withHeight(17.0F));
    release_arg.setColour(juce::Label::backgroundColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomTransparent);
    release_arg.setColour(juce::Label::textColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomGroupComponent);
    release_arg.setLookAndFeel(ptr_Global_CustomLookAndFeel);
    addAndMakeVisible(release_arg);

    license_param.setText("License", juce::dontSendNotification);
    license_param.setJustificationType(juce::Justification::centredLeft);
    license_param.setFont(ptr_Global_CustomLookAndFeel->getFontRobotoCondensedBold().withHeight(17.0F));
    license_param.setColour(juce::Label::backgroundColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomTransparent);
    license_param.setColour(juce::Label::textColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomGroupComponent);
    license_param.setLookAndFeel(ptr_Global_CustomLookAndFeel);
    addAndMakeVisible(license_param);
    license_arg.setText(":  APGLv3", juce::dontSendNotification);
    license_arg.setJustificationType(juce::Justification::centredLeft);
    license_arg.setFont(ptr_Global_CustomLookAndFeel->getFontRobotoCondensedBold().withHeight(17.0F));
    license_arg.setColour(juce::Label::backgroundColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomTransparent);
    license_arg.setColour(juce::Label::textColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomGroupComponent);
    license_arg.setLookAndFeel(ptr_Global_CustomLookAndFeel);
    addAndMakeVisible(license_arg);

    juceVersion_arg.setText("Created with JUCE 8.0.3", juce::dontSendNotification);
    juceVersion_arg.setJustificationType(juce::Justification::centredBottom);
    juceVersion_arg.setFont(ptr_Global_CustomLookAndFeel->getFontRobotoCondensedBold().withHeight(17.0F));
    juceVersion_arg.setColour(juce::Label::backgroundColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomTransparent);
    juceVersion_arg.setColour(juce::Label::textColourId, ptr_Global_CustomLookAndFeel->getCurrentTheme().CustomGroupComponent);
    juceVersion_arg.setLookAndFeel(ptr_Global_CustomLookAndFeel);
    addAndMakeVisible(juceVersion_arg);

    closeDialog_2_Info.setButtonText("CLOSE");
    closeDialog_2_Info.setComponentID("Buttons_ID_02_Close_Group");
    closeDialog_2_Info.onClick = [this]()
        {
            currentSlideWorksPage = previousSlideWorksPage;

            if (currentSlideWorksPage == PageState::PAGE2_WORKSPACE)
                NewUpdateVisibilityPAGE_2(true);

            updatePage3InfoVisibility(false);
            repaint();
        };
    addAndMakeVisible(closeDialog_2_Info);

    updatePage3InfoVisibility(false);
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
