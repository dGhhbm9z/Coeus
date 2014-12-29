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

#include "MainComponent.h"
#include "CustomTabBar.h"


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

	commandManager.registerAllCommandsForTarget(this);
	commandManager.getKeyMappings()->addKeyPress(CoeusCommandIDs::NewTab, KeyPress('t', ModifierKeys::commandModifier, juce_wchar('t')));
	commandManager.getKeyMappings()->addKeyPress(CoeusCommandIDs::CloseTab, KeyPress('w', ModifierKeys::commandModifier, juce_wchar('w')));
	commandManager.getKeyMappings()->addKeyPress(CoeusCommandIDs::OpenThemeSettingsDialog, KeyPress('e', ModifierKeys::commandModifier, juce_wchar('e')));
	addKeyListener(commandManager.getKeyMappings());
	
	commandManager.setFirstCommandTarget(this);

	commandManager.invokeDirectly(CoeusCommandIDs::NewTab, true);
}

MainComponent::~MainComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    tabs->clearTabs();
	tabs = nullptr;

	delete CacheSystem::getInstance();

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
	tabs->setBounds(0, 0, getWidth(), getHeight());

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
		Component *comp = new CustomTabComponent(*tabs);
		tabs->addTab(String("CST"), Colours::beige, comp, true);
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
