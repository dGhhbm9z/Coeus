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

class CustomTabComponent :	public Component,
							public ListBoxModel
{
public:
	CustomTabComponent() {
		title = new Label(String::empty, L"Λογιστικά Άρθρα");
		title->setFont(Font(22));
		title->setJustificationType(Justification::centred);
		listBox = new ListBox(String::empty, this);
		listBox->setRowHeight(620);
		
		addAndMakeVisible(listBox);
		addAndMakeVisible(title);
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
	}

	int CustomTabComponent::getNumRows() override
	{
		return 800;
	}

	void CustomTabComponent::paintListBoxItem(int rowNumber, Graphics &g, int width, int height, bool rowIsSelected) override
	{
		/*g.fillAll(Colours::grey);
		g.setColour(Colours::black);
		g.drawRect(Rectangle<float>(0,0,width+1,height+1));
		g.setColour(Colours::azure);
		g.drawText(String(rowNumber), Rectangle<int>(0,0,width,height), Justification::centred, false);*/
	}

	Component* CustomTabComponent::refreshComponentForRow(int rowNumber, bool isRowSelected, Component *existingComponentToUpdate) override
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

private:
	ScopedPointer<Label> title;
	ScopedPointer<ListBox> listBox;
};

//==============================================================================
MainComponent::MainComponent ()
{
	Component *comp = new CustomTabComponent();
	LookAndFeel::setDefaultLookAndFeel(&theme);

	addAndMakeVisible (tabs = new CoeusTabbedComponent());
	tabs->setTabBarDepth(50);
	tabs->addTab(String("Tab One"), Colours::beige, comp, true);
	tabs->addTab(String("Tab Two"), Colours::cornsilk, nullptr, false);
	tabs->addTab(String("Tab Three"), Colours::orange, nullptr, false);
    
    comp->setBoundsRelative(0.0f, 0.0f, 1.0f, 1.0f);
    
	//[UserPreSize]
    //[/UserPreSize]

	setSize(getParentWidth(), getParentHeight());

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
		CoeusCommandIDs::QuitProgram
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
		result.addDefaultKeypress('n', ModifierKeys::commandModifier);
		break;
	case CoeusCommandIDs::SelectCompanyDialog:
		result.setInfo("Select Company", "Select Company", generalCategory, 0);
		result.addDefaultKeypress('n', ModifierKeys::commandModifier);
		break;
	case CoeusCommandIDs::SyncWithServer:
		result.setInfo("Sync with server", "Sync with server", generalCategory, 0);
		result.addDefaultKeypress('n', ModifierKeys::commandModifier);
		break;
	case CoeusCommandIDs::NewTab:
		result.setInfo("Open a new Tab", "Open a new Tab", generalCategory, 0);
		result.addDefaultKeypress('n', ModifierKeys::commandModifier);
		break;
	case CoeusCommandIDs::CloseTab:
		result.setInfo("Close Current Tab", "Close Current Tab", generalCategory, 0);
		result.addDefaultKeypress('n', ModifierKeys::commandModifier);
		break;
	case CoeusCommandIDs::QuitProgram:
		result.setInfo("Quit App", "Quit App", generalCategory, 0);
		result.addDefaultKeypress('n', ModifierKeys::commandModifier);
		break;
	default:
		break;
	};
}

bool MainComponent::perform(const InvocationInfo &info)
{
	if (info.commandID != CoeusCommandIDs::QuitProgram) {
		return true;
	}

	switch (info.commandID)
	{
	case CoeusCommandIDs::ConnectToServerDialog:
		break;
	case CoeusCommandIDs::SelectCompanyDialog :
		break;
	case CoeusCommandIDs::SyncWithServer :
		break;
	case CoeusCommandIDs::NewTab :
		break;
	case CoeusCommandIDs::CloseTab :
		break;
	case CoeusCommandIDs::QuitProgram :
		break;
	default:
		break;
	};

	return true;
}


//==============================================================================



//[EndFile] You can add extra defines here...
//[/EndFile]
