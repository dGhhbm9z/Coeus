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

//==============================================================================
MainComponent::MainComponent ()
{
    Component *comp = new Component();
	LookAndFeel::setDefaultLookAndFeel(&theme);

	addAndMakeVisible (tabs = new CoeusTabbedComponent());
	tabs->setTabBarDepth(50);
	tabs->addTab(String("Tab One"), Colours::beige, comp, true);
	tabs->addTab(String("Tab Two"), Colours::cornsilk, nullptr, false);
	tabs->addTab(String("Tab Three"), Colours::orange, nullptr, false);
    
    comp->setBoundsRelative(0.0f, 0.0f, 1.0f, 1.0f);
    
    comp->addAndMakeVisible (helloWorldLabel = new Label (String::empty,
                                                    "Theme test"));
    helloWorldLabel->setFont (Font (40.00f, Font::bold));
    helloWorldLabel->setJustificationType (Justification::centred);
    helloWorldLabel->setEditable (false, false, false);
    helloWorldLabel->setColour (Label::textColourId, Colours::black);
    helloWorldLabel->setColour (TextEditor::textColourId, Colours::black);
    helloWorldLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    comp->addAndMakeVisible (quitButton = new TextButton (String::empty));
    quitButton->setButtonText ("Quit");
    quitButton->addListener (this);
    
	addAndMakeVisible (toggleButton = new ToggleButton (String::empty));
    toggleButton->setButtonText ("ToggleButton");
    toggleButton->addListener (this);
    
	comp->addAndMakeVisible (comboBox = new ComboBox());
    
	comp->addAndMakeVisible (listBox = new ListBox (String::empty, this));
	//listBox->setColour (ListBox::backgroundColourId, Colours::black);
    
	comp->addAndMakeVisible (te = new TextEditor ());

    //[UserPreSize]
    //[/UserPreSize]

    setSize (800, 600);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

MainComponent::~MainComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    helloWorldLabel = nullptr;
    quitButton = nullptr;
	listBox = nullptr;
	tabs = nullptr;
	te = nullptr;
	toggleButton = nullptr;
	comboBox = nullptr;


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
    helloWorldLabel->setBounds (250, 100, 296, 48);
    quitButton->setBounds (100, 100, 150, 42);
	toggleButton->setBounds(100, 50, 120, 32);
	comboBox->setBounds(250, 50, 100, 30);
	listBox->setBounds(100, 170, 300, 400);
	listBox->updateContent();
	tabs->setBounds(0, 0, getWidth(), getHeight());
	te->setBounds(500, 10, 250, 150);
	

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == quitButton)
    {
        //[UserButtonCode_quitButton] -- add your button handler code here..

        JUCEApplication::quit();

        //[/UserButtonCode_quitButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

int MainComponent::getNumRows ()
{
	return 45;
}

void MainComponent::paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected)
{
	g.fillAll(Colours::grey);
	g.setColour(Colours::black);
	g.drawRect(Rectangle<float>(0,0,width+1,height+1));
	g.setColour(Colours::azure);
	g.drawText(String(rowNumber), Rectangle<int>(0,0,width,height), Justification::centred, false);
}

//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================



//[EndFile] You can add extra defines here...
//[/EndFile]
