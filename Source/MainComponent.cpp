/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "MainComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

class CustomTabbedButtonBar : public TabbedButtonBar
{
public:
	CustomTabbedButtonBar() : TabbedButtonBar(TabbedButtonBar::Orientation::TabsAtLeft) {}

};

class CustomTabComponent :	public Component,
							public ListBoxModel,
							public Timer
{
public:
	CustomTabComponent() {
		setWantsKeyboardFocus(false);
		title = new Label(String::empty, L"Λογιστικά Άρθρα");
		title->setFont(Font(22));
		title->setJustificationType(Justification::centred);
		listBox = new ListBox(String::empty, this);
		listBox->setRowHeight(620);
		tabButtons = new CustomTabbedButtonBar();
		tabButtons->setLookAndFeel(&themeAlt);
		tabButtons->addTab(L"Reporting", Colours::white, 0);
		tabButtons->addTab(L"Business Plan", Colours::white, 1);
		tabButtons->addTab(L"Customers", Colours::white, 2);
		tabButtons->addTab(L"Suppliers", Colours::white, 3);
		tabButtons->addTab(L"Account Chart", Colours::white, 4);
		tabButtons->addTab(L"Accounts", Colours::white, 5);

		addAndMakeVisible(listBox);
		addAndMakeVisible(title);
		addAndMakeVisible(tabButtons);

		startTimer(100);
	}

	~CustomTabComponent() {
		title = nullptr;
		listBox = nullptr;
	}

	void resized() override {
		const float width = getWidth();
		const float height = getHeight();
		title->setBoundsRelative(0.5f - 0.125f , 0, 0.25f, 0.05f);
		listBox->setBoundsRelative(0.05f, 0.05f, 0.9f, 0.94f);
		tabButtons->setBoundsRelative(0.0f, 0.05f, 0.05f, 0.54f);
	}

	int getNumRows() override
	{
		return 8;
	}

	void paintListBoxItem(int rowNumber, Graphics &g, int width, int height, bool rowIsSelected) override
	{
		/*g.fillAll(Colours::grey);
		g.setColour(Colours::black);
		g.drawRect(Rectangle<float>(0,0,width+1,height+1));
		g.setColour(Colours::azure);
		g.drawText(String(rowNumber), Rectangle<int>(0,0,width,height), Justification::centred, false);*/
	}

	Component* refreshComponentForRow(int rowNumber, bool isRowSelected, Component *existingComponentToUpdate) override
	{
		// create
		if (existingComponentToUpdate == nullptr) {
			Component *newComponent = (Component *) new CacheViewer();
			return newComponent;
		}
		// update
		else {
			return existingComponentToUpdate;
		}
	}

	void timerCallback() override {
		ComponentAnimator &an = Desktop::getInstance().getAnimator();
		Rectangle<int> finalBoundsVisible = Rectangle<int>(0, tabButtons->getY(), tabButtons->getWidth(), tabButtons->getHeight());
		Rectangle<int> finalBoundsHidden = Rectangle<int>(-tabButtons->getWidth(), tabButtons->getY(), tabButtons->getWidth(), tabButtons->getHeight());

		if (getMouseXYRelative().getY() > 0 && getMouseXYRelative().getX() > 0 && getMouseXYRelative().getX() < tabButtons->getWidth()*0.8f && tabButtons->getX() < 0 && an.getComponentDestination(tabButtons) == finalBoundsHidden) {
			an.cancelAnimation(tabButtons, false);
			an.animateComponent(tabButtons, finalBoundsVisible, 1.0f, 400, false, 0.0f, 1.0f);
		}
		else if ((getMouseXYRelative().getY() < 0 || ( getMouseXYRelative().getX() > 0 && getMouseXYRelative().getX() > tabButtons->getWidth() )) && tabButtons->getX() == 0) {
			an.cancelAnimation(tabButtons, false);
			an.animateComponent(tabButtons, finalBoundsHidden, 1.0f, 400, false, 0.0f, 1.0f);
		}
	}

private:
	ScopedPointer<Label> title;
	ScopedPointer<ListBox> listBox;
	ScopedPointer<CustomTabbedButtonBar> tabButtons;
	ThemeAlt themeAlt;
};

//==============================================================================
MainComponent::MainComponent ()
{
	setWantsKeyboardFocus(true);
	LookAndFeel::setDefaultLookAndFeel(&theme);

	addAndMakeVisible (tabs = new CoeusTabbedComponent());
	tabs->setTabBarDepth(50);
 
	tc = new ThemeComponent(*this);
	tc->setOpaque(true);
	tc->addToDesktop(ComponentPeer::StyleFlags::windowHasCloseButton | ComponentPeer::StyleFlags::windowIsResizable | ComponentPeer::StyleFlags::windowHasTitleBar);
	tc->centreWithSize(800, 600);
	tc->setVisible(false);

	//[UserPreSize]
    //[/UserPreSize]

	commandManager.registerAllCommandsForTarget(this);
	commandManager.getKeyMappings()->addKeyPress(CoeusCommandIDs::NewTab, KeyPress('t', ModifierKeys::commandModifier, juce_wchar('t')));
	commandManager.getKeyMappings()->addKeyPress(CoeusCommandIDs::CloseTab, KeyPress('w', ModifierKeys::commandModifier, juce_wchar('w')));
	commandManager.getKeyMappings()->addKeyPress(CoeusCommandIDs::OpenThemeSettingsDialog, KeyPress('e', ModifierKeys::commandModifier, juce_wchar('e')));
	addKeyListener(commandManager.getKeyMappings());
	
	commandManager.setFirstCommandTarget(this);

	commandManager.invokeDirectly(CoeusCommandIDs::NewTab, true);

	this->setBoundsRelative(0.0f, 0.0f, 1.0f, 1.0f);

    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

MainComponent::~MainComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

	tabs = nullptr;

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffffffff));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainComponent::resized()
{
	tabs->setBoundsRelative(0.0f, 0.0f, 1.0f, 1.0f);

	//[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]


    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]

ApplicationCommandTarget * MainComponent::getNextCommandTarget()
{
	return findFirstTargetParentComponent();
}

void MainComponent::getAllCommands(Array< CommandID > &commands)
{
	// this returns the set of all commands that this target can perform.. 
	const CommandID ids[] = { CoeusCommandIDs::ConnectToServerDialog,
		CoeusCommandIDs::SelectCompanyDialog,
		CoeusCommandIDs::SyncWithServer,
		CoeusCommandIDs::NewTab,
		CoeusCommandIDs::CloseTab,
		CoeusCommandIDs::QuitProgram,
		CoeusCommandIDs::OpenThemeSettingsDialog
	};
	commands.addArray(ids, numElementsInArray(ids));
}

void MainComponent::getCommandInfo(CommandID commandID, ApplicationCommandInfo &result)
{
	const String generalCategory("General");
	switch (commandID)
	{
	case CoeusCommandIDs::ConnectToServerDialog :
		result.setInfo("Connet to server", "Connet to server", generalCategory, 0);
//		result.addDefaultKeypress('C', ModifierKeys::commandModifier);
		break;
	case CoeusCommandIDs::SelectCompanyDialog:
		result.setInfo("Select Company", "Select Company", generalCategory, 0);
		result.addDefaultKeypress('o', ModifierKeys::commandModifier);
		break;
	case CoeusCommandIDs::SyncWithServer:
		result.setInfo("Sync with server", "Sync with server", generalCategory, 0);
		result.addDefaultKeypress('s', ModifierKeys::commandModifier);
		break;
	case CoeusCommandIDs::NewTab:
		result.setInfo("Open a new Tab", "Open a new Tab", generalCategory, 0);
		result.addDefaultKeypress('t', ModifierKeys::commandModifier);
		break;
	case CoeusCommandIDs::CloseTab:
		result.setInfo("Close Current Tab", "Close Current Tab", generalCategory, 0);
		result.addDefaultKeypress('w', ModifierKeys::commandModifier);
		break;
	case CoeusCommandIDs::QuitProgram:
		result.setInfo("Quit App", "Quit App", generalCategory, 0);
//		result.addDefaultKeypress('q', ModifierKeys::commandModifier);
		break;
	case CoeusCommandIDs::OpenThemeSettingsDialog:
		result.setInfo("Theme settings", "Theme settings", generalCategory, 0);
		//		result.addDefaultKeypress('q', ModifierKeys::commandModifier);
		break;
	default:
		break;
	};
}

bool MainComponent::perform(const InvocationInfo &info)
{

	switch (info.commandID)
	{
	case CoeusCommandIDs::ConnectToServerDialog: {
		break;
	}
	case CoeusCommandIDs::SelectCompanyDialog: {
		break;
	}
	case CoeusCommandIDs::SyncWithServer: {
		break;
	}
	case CoeusCommandIDs::NewTab: {
		Component *comp = new CustomTabComponent();
		tabs->addTab(String("Main"), Colours::beige, comp, true);
		break;
	}
	case CoeusCommandIDs::CloseTab: {
		tabs->removeTab(tabs->getCurrentTabIndex());
		break;
	}
	case CoeusCommandIDs::QuitProgram: {
		 break;
	}
	case CoeusCommandIDs::OpenThemeSettingsDialog: {
		tc->setVisible(true);
		tc->toFront(true);
		tc->grabKeyboardFocus();
		break;
	}
	default:
		break;
	};

	return true;
}


//==============================================================================



//[EndFile] You can add extra defines here...Transform
//[/EndFile]
