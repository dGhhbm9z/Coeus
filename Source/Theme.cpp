#include "Theme.h"

Colour tabButtonBackgroundWhenSelected = Colour(0xffffffff);
//Gradient from 0xffd3d3d3 to 0xffd7d7d7
Colour tabButtonBackground = Colour(0xffd3d3d3);
Colour tabButtonTextWhenSelected = Colour(0xffd3d3d3);
Colour tabButtonTextMouseOver = Colour(0xff000000);
Colour tabButtonTextOnClick = Colour(0xff486c7b);
//Gradient from 0xff3c3c37 to 0xff486c7b
Colour tabLineFill = Colour(0xff3c3c37);
Colour aboveTabBarFill = Colour(0xff486c7b);
Colour sideBarLeftFill = Colour(0xff3c3c37);
Colour sideBarRightFill = Colour(0xff3c3c37);
Colour workSpaceFill = Colour(0xffffffff);

Colour buttonGr1 = Colour(0xffdddddd);
Colour buttonGr2 = Colour(0xffdddddd);
Colour buttonGr3 = Colour(0xffffffff);
Colour buttonOutlineHover = Colour(0xff545454);
Colour buttonOutline = Colour(0xffd3d3d3);
Colour buttonTextDown = Colour(0xb2002828);
Colour buttonTextOver = Colour(0xff000000);
Colour buttonText = Colour(0xff808080);
Colour tabButtonBarGr1 = Colour(0xff002020);
Colour tabButtonBarGr2 = Colour(0xff008080);
Colour tabButtonBarOutline = Colour(0xff545454);
Colour tabButtonFrontTab = Colour(0xfffefefe);
Colour tabButtonFrontTabOutline = Colour(0xffaaaaaa);
Colour tabButtonBG1 = Colour(0xfff5f5f5);
Colour tabButtonBG2 = Colour(0xffe6e6e6);
Colour tabButtonOutline = Colour(0xff5c5c5c);

//---------------------------------------------------------------------
// 

ThemeComponent::ThemeComponent(Component &compToRefresh_)
: compToRefresh(compToRefresh_)
{
	buttonGr1Button = new ThemeButton(buttonGr1, L"buttonGr1");
	lastButtonThatWasClicked = buttonGr1Button;
	buttonGr2Button = new ThemeButton(buttonGr2, L"buttonGr2");
	buttonGr3Button = new ThemeButton(buttonGr3, L"buttonGr3");
	buttonOutlineHoverButton = new ThemeButton(buttonOutlineHover, L"buttonOutlineHover");
	buttonOutlineButton = new ThemeButton(buttonOutline, L"buttonOutline");
	buttonTextDownButton = new ThemeButton(buttonTextDown, L"buttonTextDown");
	buttonTextOverButton = new ThemeButton(buttonTextOver, L"buttonTextOver");
	buttonTextButton = new ThemeButton(buttonText, L"buttonText");
	tabButtonBarGr1Button = new ThemeButton(tabButtonBarGr1, L"tabButtonBarGr1");
	tabButtonBarGr2Button = new ThemeButton(tabButtonBarGr2, L"tabButtonBarGr2");
	tabButtonBarOutlineButton = new ThemeButton(tabButtonBarOutline, L"tabButtonBarOutline");
	tabButtonFrontTabButton = new ThemeButton(tabButtonFrontTab, L"tabButtonFrontTab");
	tabButtonFrontTabOutlineButton = new ThemeButton(tabButtonFrontTabOutline, L"tabButtonFrontTabOutline");
	tabButtonBG1Button = new ThemeButton(tabButtonBG1, L"tabButtonBG1");
	tabButtonBG2Button = new ThemeButton(tabButtonBG2, L"tabButtonBG2");
	tabButtonOutlineButton = new ThemeButton(tabButtonOutline, L"tabButtonOutline");

	tabButtonBackgroundWhenSelectedButton = new ThemeButton(tabButtonBackgroundWhenSelected, L"tabButtonBackgroundWhenSelected");
	tabButtonBackgroundButton = new ThemeButton(tabButtonBackground, L"tabButtonBackground");
	tabButtonTextWhenSelectedButton = new ThemeButton(tabButtonTextWhenSelected, L"tabButtonTextMouseOver");
	tabButtonTextMouseOverButton = new ThemeButton(tabButtonTextMouseOver, L"tabButtonTextOnClick");
	tabButtonTextOnClickButton = new ThemeButton(tabButtonTextOnClick, L"tabLineFill");
	tabLineFillButton = new ThemeButton(tabLineFill, L"aboveTabBarFill");
	aboveTabBarFillButton = new ThemeButton(aboveTabBarFill, L"aboveTabBarFill");
	sideBarLeftFillButton = new ThemeButton(sideBarLeftFill, L"sideBarLeftFill");
	sideBarRightFillButton = new ThemeButton(sideBarRightFill, L"sideBarRightFill");
	workSpaceFillButton = new ThemeButton(workSpaceFill, L"workSpaceFill");

	saveButton = new TextButton(L"save");
	loadButton = new TextButton(L"load");

	cs = new ColourSelector();
	cs->addChangeListener(this);

	buttonGr1Button->addListener(this);
	buttonGr2Button->addListener(this);
	buttonGr3Button->addListener(this);
	buttonOutlineHoverButton->addListener(this);
	buttonOutlineButton->addListener(this);
	buttonTextDownButton->addListener(this);
	buttonTextOverButton->addListener(this);
	buttonTextButton->addListener(this);
	tabButtonBarGr1Button->addListener(this);
	tabButtonBarGr2Button->addListener(this);
	tabButtonBarOutlineButton->addListener(this);
	tabButtonFrontTabButton->addListener(this);
	tabButtonFrontTabOutlineButton->addListener(this);
	tabButtonBG1Button->addListener(this);
	tabButtonBG2Button->addListener(this);
	tabButtonOutlineButton->addListener(this);

	buttonGr1Button->setRadioGroupId(1);
	buttonGr2Button->setRadioGroupId(1);
	buttonGr3Button->setRadioGroupId(1);
	buttonOutlineHoverButton->setRadioGroupId(1);
	buttonOutlineButton->setRadioGroupId(1);
	buttonTextDownButton->setRadioGroupId(1);
	buttonTextOverButton->setRadioGroupId(1);
	buttonTextButton->setRadioGroupId(1);
	tabButtonBarGr1Button->setRadioGroupId(1);
	tabButtonBarGr2Button->setRadioGroupId(1);
	tabButtonBarOutlineButton->setRadioGroupId(1);
	tabButtonFrontTabButton->setRadioGroupId(1);
	tabButtonFrontTabOutlineButton->setRadioGroupId(1);
	tabButtonBG1Button->setRadioGroupId(1);
	tabButtonBG2Button->setRadioGroupId(1);
	tabButtonOutlineButton->setRadioGroupId(1);

	addAndMakeVisible(buttonGr1Button);
	addAndMakeVisible(buttonGr2Button);
	addAndMakeVisible(buttonGr3Button);
	addAndMakeVisible(buttonOutlineHoverButton);
	addAndMakeVisible(buttonOutlineButton);
	addAndMakeVisible(buttonTextDownButton);
	addAndMakeVisible(buttonTextOverButton);
	addAndMakeVisible(buttonTextButton);
	addAndMakeVisible(tabButtonBarGr1Button);
	addAndMakeVisible(tabButtonBarGr2Button);
	addAndMakeVisible(tabButtonBarOutlineButton);
	addAndMakeVisible(tabButtonFrontTabButton);
	addAndMakeVisible(tabButtonFrontTabOutlineButton);
	addAndMakeVisible(tabButtonBG1Button);
	addAndMakeVisible(tabButtonBG2Button);
	addAndMakeVisible(tabButtonOutlineButton);


	tabButtonBackgroundWhenSelectedButton->addListener(this);
	tabButtonBackgroundButton->addListener(this);
	tabButtonTextWhenSelectedButton->addListener(this);
	tabButtonTextMouseOverButton->addListener(this);
	tabButtonTextOnClickButton->addListener(this);
	tabLineFillButton->addListener(this);
	aboveTabBarFillButton->addListener(this);
	sideBarLeftFillButton->addListener(this);
	sideBarRightFillButton->addListener(this);
	workSpaceFillButton->addListener(this);

	tabButtonBackgroundWhenSelectedButton->setRadioGroupId(1);
	tabButtonBackgroundButton->setRadioGroupId(1);
	tabButtonTextWhenSelectedButton->setRadioGroupId(1);
	tabButtonTextMouseOverButton->setRadioGroupId(1);
	tabButtonTextOnClickButton->setRadioGroupId(1);
	tabLineFillButton->setRadioGroupId(1);
	aboveTabBarFillButton->setRadioGroupId(1);
	sideBarLeftFillButton->setRadioGroupId(1);
	sideBarRightFillButton->setRadioGroupId(1);
	workSpaceFillButton->setRadioGroupId(1);

	addAndMakeVisible(tabButtonBackgroundWhenSelectedButton);
	addAndMakeVisible(tabButtonBackgroundButton);
	addAndMakeVisible(tabButtonTextWhenSelectedButton);
	addAndMakeVisible(tabButtonTextMouseOverButton);
	addAndMakeVisible(tabButtonTextOnClickButton);
	addAndMakeVisible(tabLineFillButton);
	addAndMakeVisible(aboveTabBarFillButton);
	addAndMakeVisible(sideBarLeftFillButton);
	addAndMakeVisible(sideBarRightFillButton);
	addAndMakeVisible(workSpaceFillButton);


	saveButton->addListener(this);
	loadButton->addListener(this);

	addAndMakeVisible(saveButton);
	addAndMakeVisible(loadButton);

	addAndMakeVisible(cs);
}

ThemeComponent::~ThemeComponent()
{

}

void ThemeComponent::resized()
{
	float vsz = (1 - 0.1f) / 18.0f;
	float vs = 0.05f;
	float hs = 0.05f;
	float hsz = 0.3f;

	buttonGr1Button->setBoundsRelative(hs, vs, hsz, vsz);	vs += vsz;
	buttonGr2Button->setBoundsRelative(hs, vs, hsz, vsz);	vs += vsz;
	buttonGr3Button->setBoundsRelative(hs, vs, hsz, vsz);	vs += vsz;
	buttonOutlineHoverButton->setBoundsRelative(hs, vs, hsz, vsz);	vs += vsz;
	buttonOutlineButton->setBoundsRelative(hs, vs, hsz, vsz);	vs += vsz;
	buttonTextDownButton->setBoundsRelative(hs, vs, hsz, vsz);	vs += vsz;
	buttonTextOverButton->setBoundsRelative(hs, vs, hsz, vsz);	vs += vsz;
	buttonTextButton->setBoundsRelative(hs, vs, hsz, vsz);	vs += vsz;
	tabButtonBarGr1Button->setBoundsRelative(hs, vs, hsz, vsz);	vs += vsz;
	tabButtonBarGr2Button->setBoundsRelative(hs, vs, hsz, vsz);	vs += vsz;
	tabButtonBarOutlineButton->setBoundsRelative(hs, vs, hsz, vsz);	vs += vsz;
	tabButtonFrontTabButton->setBoundsRelative(hs, vs, hsz, vsz);	vs += vsz;
	tabButtonFrontTabOutlineButton->setBoundsRelative(hs, vs, hsz, vsz);	vs += vsz;
	tabButtonBG1Button->setBoundsRelative(hs, vs, hsz, vsz);	vs += vsz;
	tabButtonBG2Button->setBoundsRelative(hs, vs, hsz, vsz);	vs += vsz;
	tabButtonOutlineButton->setBoundsRelative(hs, vs, hsz, vsz);	vs += vsz;

	hs = 0.35f;
	vs = 0.05f;
	tabButtonBackgroundWhenSelectedButton->setBoundsRelative(hs, vs, hsz, vsz);
	vs += vsz;
	tabButtonBackgroundButton->setBoundsRelative(hs, vs, hsz, vsz);
	vs += vsz;
	tabButtonTextWhenSelectedButton->setBoundsRelative(hs, vs, hsz, vsz);
	vs += vsz;
	tabButtonTextMouseOverButton->setBoundsRelative(hs, vs, hsz, vsz);
	vs += vsz;
	tabButtonTextOnClickButton->setBoundsRelative(hs, vs, hsz, vsz);
	vs += vsz;
	tabLineFillButton->setBoundsRelative(hs, vs, hsz, vsz);
	vs += vsz;
	aboveTabBarFillButton->setBoundsRelative(hs, vs, hsz, vsz);
	vs += vsz;
	sideBarLeftFillButton->setBoundsRelative(hs, vs, hsz, vsz);
	vs += vsz;
	sideBarRightFillButton->setBoundsRelative(hs, vs, hsz, vsz);
	vs += vsz;
	workSpaceFillButton->setBoundsRelative(hs, vs, hsz, vsz);

	vsz = vs + vsz;
	hs = 0.65f;
	vs = 0.05f;
	hsz = 0.3f;
	cs->setBoundsRelative(hs, vs, hsz, vsz);
	vs += vsz;
	vsz = (1 - 0.1f) / 18.0f;
	vs += vsz;
	loadButton->setBoundsRelative(hs, vs, hsz, vsz);
	vs += vsz;
	saveButton->setBoundsRelative(hs, vs, hsz, vsz);
}


void ThemeComponent::buttonClicked(Button *buttonThatWasClicked)
{
	lastButtonThatWasClicked = (ThemeButton *) buttonThatWasClicked;

	if (buttonThatWasClicked == tabButtonBackgroundWhenSelectedButton) {
		cs->setCurrentColour(tabButtonBackgroundWhenSelected);
	}
	else if (buttonThatWasClicked == tabButtonBackgroundButton) {
		cs->setCurrentColour(tabButtonBackground);
	}
	else if (buttonThatWasClicked == tabButtonTextWhenSelectedButton) {
		cs->setCurrentColour(tabButtonTextWhenSelected);
	}
	else if (buttonThatWasClicked == tabButtonTextMouseOverButton) {
		cs->setCurrentColour(tabButtonTextMouseOver);
	}
	else if (buttonThatWasClicked == tabButtonTextOnClickButton) {
		cs->setCurrentColour(tabButtonTextOnClick);
	}
	else if (buttonThatWasClicked == tabLineFillButton) {
		cs->setCurrentColour(tabLineFill);
	}
	else if (buttonThatWasClicked == aboveTabBarFillButton) {
		cs->setCurrentColour(aboveTabBarFill);
	}
	else if (buttonThatWasClicked == sideBarLeftFillButton) {
		cs->setCurrentColour(sideBarLeftFill);
	}
	else if (buttonThatWasClicked == sideBarRightFillButton) {
		cs->setCurrentColour(sideBarRightFill);
	}
	else if (buttonThatWasClicked == workSpaceFillButton) {
		cs->setCurrentColour(workSpaceFill);
	}
	else if (buttonThatWasClicked == buttonGr1Button) {
		cs->setCurrentColour(buttonGr1);
	}
	else if (buttonThatWasClicked == buttonGr2Button) {
		cs->setCurrentColour(buttonGr2);
	}
	else if (buttonThatWasClicked == buttonGr3Button) {
		cs->setCurrentColour(buttonGr3);
	}
	else if (buttonThatWasClicked == buttonOutlineHoverButton) {
		cs->setCurrentColour(buttonOutlineHover);
	}
	else if (buttonThatWasClicked == buttonOutlineButton) {
		cs->setCurrentColour(buttonOutline);
	}
	else if (buttonThatWasClicked == buttonTextDownButton) {
		cs->setCurrentColour(buttonTextDown);
	}
	else if (buttonThatWasClicked == buttonTextOverButton) {
		cs->setCurrentColour(buttonTextOver);
	}
	else if (buttonThatWasClicked == buttonTextButton) {
		cs->setCurrentColour(buttonText);
	}
	else if (buttonThatWasClicked == tabButtonBarGr1Button) {
		cs->setCurrentColour(tabButtonBarGr1);
	}
	else if (buttonThatWasClicked == tabButtonBarGr2Button) {
		cs->setCurrentColour(tabButtonBarGr2);
	}
	else if (buttonThatWasClicked == tabButtonBarOutlineButton) {
		cs->setCurrentColour(tabButtonBarOutline);
	}
	else if (buttonThatWasClicked == tabButtonFrontTabButton) {
		cs->setCurrentColour(tabButtonFrontTab);
	}
	else if (buttonThatWasClicked == tabButtonFrontTabOutlineButton) {
		cs->setCurrentColour(tabButtonFrontTabOutline);
	}
	else if (buttonThatWasClicked == tabButtonBG1Button) {
		cs->setCurrentColour(tabButtonBG1);
	}
	else if (buttonThatWasClicked == tabButtonBG2Button) {
		cs->setCurrentColour(tabButtonBG2);
	}
	else if (buttonThatWasClicked == tabButtonOutlineButton) {
		cs->setCurrentColour(tabButtonOutline);
	}
	else if (buttonThatWasClicked == saveButton) {
		// open dialog - get file name
		FileChooser fc("Choose a file to open...",
			File::getSpecialLocation(File::SpecialLocationType::userDocumentsDirectory),
			"*.theme",
			true);
		if (fc.browseForFileToOpen())
		{
			// recreate file
			String fname = String(fc.getResult().getFullPathName());
			if (!fname.endsWith(String(L".theme"))) {
				fname.append(L".theme", 6);
			}
			File themeFile = File(fname);
			if (themeFile.existsAsFile()) {
				themeFile.deleteFile();
				themeFile.create();
			}
			else {
				themeFile.create();
			}

			// write data
			saveData(themeFile.createOutputStream());
		}
	}
	else if (buttonThatWasClicked == loadButton) {
		// open dialog - get file name
		FileChooser fc("Choose a file to open...",
			File::getSpecialLocation(File::SpecialLocationType::userDocumentsDirectory),
			"*.theme",
			true);
		if (fc.browseForFileToOpen())
		{
			// recreate file
			File themeFile = fc.getResult();
			
			if (themeFile.existsAsFile()) {
				// read data
				loadData(themeFile.createInputStream());
				repaint();
				compToRefresh.repaint();
			}
		}
	}
	
	repaint();
}

void ThemeComponent::saveData(OutputStream *os)
{
	uint32 buffer;

	buffer = tabButtonBackgroundWhenSelected.getARGB();
	os->write(&buffer, sizeof(uint32));
	buffer = tabButtonBackground.getARGB();
	os->write(&buffer, sizeof(uint32));
	buffer = tabButtonTextWhenSelected.getARGB();
	os->write(&buffer, sizeof(uint32));
	buffer = tabButtonTextMouseOver.getARGB();
	os->write(&buffer, sizeof(uint32));
	buffer = tabButtonTextOnClick.getARGB();
	os->write(&buffer, sizeof(uint32));
	buffer = tabLineFill.getARGB();
	os->write(&buffer, sizeof(uint32));
	buffer = aboveTabBarFill.getARGB();
	os->write(&buffer, sizeof(uint32));
	buffer = sideBarLeftFill.getARGB();
	os->write(&buffer, sizeof(uint32));
	buffer = sideBarRightFill.getARGB();
	os->write(&buffer, sizeof(uint32));
	buffer = workSpaceFill.getARGB();
	os->write(&buffer, sizeof(uint32));
	buffer = buttonGr1.getARGB();
	os->write(&buffer, sizeof(uint32));
	buffer = buttonGr2.getARGB();
	os->write(&buffer, sizeof(uint32));
	buffer = buttonGr3.getARGB();
	os->write(&buffer, sizeof(uint32));
	buffer = buttonOutlineHover.getARGB();
	os->write(&buffer, sizeof(uint32));
	buffer = buttonOutline.getARGB();
	os->write(&buffer, sizeof(uint32));
	buffer = buttonTextDown.getARGB();
	os->write(&buffer, sizeof(uint32));
	buffer = buttonTextOver.getARGB();
	os->write(&buffer, sizeof(uint32));
	buffer = buttonText.getARGB();
	os->write(&buffer, sizeof(uint32));
	buffer = tabButtonBarGr1.getARGB();
	os->write(&buffer, sizeof(uint32));
	buffer = tabButtonBarGr2.getARGB();
	os->write(&buffer, sizeof(uint32));
	buffer = tabButtonBarOutline.getARGB();
	os->write(&buffer, sizeof(uint32));
	buffer = tabButtonFrontTab.getARGB();
	os->write(&buffer, sizeof(uint32));
	buffer = tabButtonFrontTabOutline.getARGB();
	os->write(&buffer, sizeof(uint32));
	buffer = tabButtonBG1.getARGB();
	os->write(&buffer, sizeof(uint32));
	buffer = tabButtonBG2.getARGB();
	os->write(&buffer, sizeof(uint32));
	buffer = tabButtonOutline.getARGB();
	os->write(&buffer, sizeof(uint32));

	deleteAndZero(os);
}

void ThemeComponent::loadData(InputStream *is)
{
	uint32 buffer;

	is->read(&buffer, sizeof(uint32));
	tabButtonBackgroundWhenSelected = Colour(buffer);
	is->read(&buffer, sizeof(uint32));
	tabButtonBackground = Colour(buffer);
	is->read(&buffer, sizeof(uint32));
	tabButtonTextWhenSelected = Colour(buffer);
	is->read(&buffer, sizeof(uint32));
	tabButtonTextMouseOver = Colour(buffer);
	is->read(&buffer, sizeof(uint32));
	tabButtonTextOnClick = Colour(buffer);
	is->read(&buffer, sizeof(uint32));
	tabLineFill = Colour(buffer);
	is->read(&buffer, sizeof(uint32));
	aboveTabBarFill = Colour(buffer);
	is->read(&buffer, sizeof(uint32));
	sideBarLeftFill = Colour(buffer);
	is->read(&buffer, sizeof(uint32));
	sideBarRightFill = Colour(buffer);
	is->read(&buffer, sizeof(uint32));
	workSpaceFill = Colour(buffer);
	is->read(&buffer, sizeof(uint32));
	buttonGr1 = Colour(buffer);
	is->read(&buffer, sizeof(uint32));
	buttonGr2 = Colour(buffer);
	is->read(&buffer, sizeof(uint32));
	buttonGr3 = Colour(buffer);
	is->read(&buffer, sizeof(uint32));
	buttonOutlineHover = Colour(buffer);
	is->read(&buffer, sizeof(uint32));
	buttonOutline = Colour(buffer);
	is->read(&buffer, sizeof(uint32));
	buttonTextDown = Colour(buffer);
	is->read(&buffer, sizeof(uint32));
	buttonTextOver = Colour(buffer);
	is->read(&buffer, sizeof(uint32));
	buttonText = Colour(buffer);
	is->read(&buffer, sizeof(uint32));
	tabButtonBarGr1 = Colour(buffer);
	is->read(&buffer, sizeof(uint32));
	tabButtonBarGr2 = Colour(buffer);
	is->read(&buffer, sizeof(uint32));
	tabButtonBarOutline = Colour(buffer);
	is->read(&buffer, sizeof(uint32));
	tabButtonFrontTab = Colour(buffer);
	is->read(&buffer, sizeof(uint32));
	tabButtonFrontTabOutline = Colour(buffer);
	is->read(&buffer, sizeof(uint32));
	tabButtonBG1 = Colour(buffer);
	is->read(&buffer, sizeof(uint32));
	tabButtonBG2 = Colour(buffer);
	is->read(&buffer, sizeof(uint32));
	tabButtonOutline = Colour(buffer);

	deleteAndZero(is);
}

void ThemeComponent::paint(Graphics &g)
{
	g.fillAll(workSpaceFill);
}

void ThemeComponent::userTriedToCloseWindow()
{
	this->setVisible(false);
}

void ThemeComponent::changeListenerCallback(ChangeBroadcaster *broadcaster)
{
	if (broadcaster != cs) {
		return;
	}
	((ThemeButton *)lastButtonThatWasClicked)->setInfoColour(cs->getCurrentColour());

	if (lastButtonThatWasClicked == tabButtonBackgroundWhenSelectedButton) {
		tabButtonBackgroundWhenSelected = cs->getCurrentColour();
	}
	else if (lastButtonThatWasClicked == tabButtonBackgroundButton) {
		tabButtonBackground = cs->getCurrentColour();
	}
	else if (lastButtonThatWasClicked == tabButtonTextWhenSelectedButton) {
		tabButtonTextWhenSelected = cs->getCurrentColour();
	}
	else if (lastButtonThatWasClicked == tabButtonTextMouseOverButton) {
		tabButtonTextMouseOver = cs->getCurrentColour();
	}
	else if (lastButtonThatWasClicked == tabButtonTextOnClickButton) {
		tabButtonTextOnClick = cs->getCurrentColour();
	}
	else if (lastButtonThatWasClicked == tabLineFillButton) {
		tabLineFill = cs->getCurrentColour();
	}
	else if (lastButtonThatWasClicked == aboveTabBarFillButton) {
		aboveTabBarFill = cs->getCurrentColour();
	}
	else if (lastButtonThatWasClicked == sideBarLeftFillButton) {
		sideBarLeftFill = cs->getCurrentColour();
	}
	else if (lastButtonThatWasClicked == sideBarRightFillButton) {
		sideBarRightFill = cs->getCurrentColour();
	}
	else if (lastButtonThatWasClicked == workSpaceFillButton) {
		workSpaceFill = cs->getCurrentColour();
	}

	repaint();
	compToRefresh.repaint();
}

//---------------------------------------------------------------------
// buttons
Path Theme::createRectPath(int x, int y, int w, int h, int pad, int padB, int cDist)
{
	const float width = w;
	const float height = h;

	Path rect;
	rect.startNewSubPath(pad, height - cDist - padB);
	rect.lineTo(pad, cDist + pad);
	rect.quadraticTo(pad, pad, cDist + pad, pad);
	rect.lineTo(width - cDist - pad, pad);
	rect.quadraticTo(width - pad, pad, width - pad, cDist + pad);
	rect.lineTo(width - pad, height - cDist - padB);
	rect.quadraticTo(width - pad, height - padB, width - cDist - pad, height - padB);
	rect.lineTo(cDist + pad, height - padB);
	rect.quadraticTo(pad, height - padB, pad, height - cDist - padB);

	return rect;
}

//---------------------------------------------------------------------
// Button stuff
void Theme::drawButtonBackground (Graphics &g, Button &button, const Colour &backgroundColour, bool isMouseOverButton, bool isButtonDown)
{
	Path rect = createRectPath(2, 2, button.getWidth()-4, button.getHeight()-4, 1, 1, 5);

	ColourGradient cG = ColourGradient(buttonGr1, 0, 0, buttonGr2, 0, button.getHeight(), false);
	cG.addColour(0.3f, buttonGr3);
	g.setGradientFill(cG);
	if (!isButtonDown) {
        g.fillPath(rect);
    }

	g.setColour(isMouseOverButton ? buttonOutlineHover : buttonOutline);
	g.strokePath(rect, PathStrokeType(1.5f));
}

Font Theme::getTextButtonFont (TextButton&, int)
{
	return Font();
}

void Theme::drawButtonText (Graphics &g, TextButton &button, bool isMouseOverButton, bool isButtonDown)
{
	Colour c;

	if (isButtonDown) {
		c = buttonTextDown;
	}
	else if (isMouseOverButton) {
		c = buttonTextOver;
	}
	else {
		c = buttonText;
	}

	g.setColour(c);
	g.drawText(button.getButtonText(), 0, 0, button.getWidth(), button.getHeight()-4, Justification::centred, true);
}

void Theme::drawToggleButton (Graphics &, ToggleButton &, bool isMouseOverButton, bool isButtonDown)
{
}

void Theme::changeToggleButtonWidthToFitText (ToggleButton &)
{
}

void Theme::drawTickBox (Graphics &, Component &, float x, float y, float w, float h, bool ticked, bool isEnabled, bool isMouseOverButton, bool isButtonDown)
{
}

void Theme::drawDrawableButton (Graphics &, DrawableButton &, bool isMouseOverButton, bool isButtonDown)
{
}

//---------------------------------------------------------------------
// tabs

int Theme::getTabButtonSpaceAroundImage ()
{
	return 0;
}

int Theme::getTabButtonOverlap (int tabDepth)
{
	return -1;
}

int Theme::getTabButtonBestWidth (TabBarButton &tabButton, int tabDepth)
{
	Font f(12);
	return f.getStringWidth(tabButton.getButtonText()) + 26;
}

void Theme::drawTabButton(TabBarButton &tabButton, Graphics &g, bool isMouseOver, bool isMouseDown)
{
	Colour c;

	if (isMouseDown) {
		c = (Colours::aqua).darker().darker().withAlpha(0.7f);
	}
	else if (isMouseOver) {
		c = Colours::black;
	}
	else {
		c = Colours::grey.darker();
	}

	const float leftX1 = 2, rightX1 = tabButton.getWidth() - 2, topY1 = tabButton.getHeight() / 3, bottomY1 = tabButton.getHeight();
	const float leftX2 = 7, rightX2 = tabButton.getWidth() - 7, topY2 = tabButton.getHeight() / 3 + 5;

	Path rect;
	rect.startNewSubPath(leftX1, bottomY1);
	rect.lineTo(leftX1, topY2);
	rect.quadraticTo(leftX1, topY1, leftX2, topY1);
	rect.lineTo(rightX2, topY1);
	rect.quadraticTo(rightX1, topY1, rightX1, topY2);
	rect.lineTo(rightX1, bottomY1);

	if (tabButton.isFrontTab()) {
		g.setColour(tabButtonFrontTab);
		g.fillPath(rect);

		g.setColour(tabButtonFrontTabOutline);
		g.strokePath(rect, PathStrokeType(0.5));
	}
	else {
		g.setColour(tabButtonBG1);
		g.fillPath(rect);

		g.setColour(tabButtonBG2);
		g.fillRect(leftX1, topY1+(bottomY1 - topY1) / 2, rightX1 - leftX1, (bottomY1 - topY1) / 2 - 1);

		g.setColour(tabButtonOutline);
		g.strokePath(rect, PathStrokeType(0.5));

		g.setColour(tabButtonBarOutline);
		g.drawLine(2, tabButton.getHeight(), tabButton.getWidth()-2, tabButton.getHeight(), 0.4f);
	}

	g.setFont(Font(12));
	g.setColour(c);
	g.drawText(tabButton.getButtonText(), 0, topY1, tabButton.getWidth(), tabButton.getHeight() * 3 / 4, Justification::centred, true);
}

void Theme::drawTabButtonText (TabBarButton &tabButton, Graphics &g, bool isMouseOver, bool isMouseDown)
{

}

void Theme::drawTabbedButtonBarBackground (TabbedButtonBar &tabButton, Graphics &g)
{
	Path rect;
	rect = createRectPath(0, 0, tabButton.getWidth(), tabButton.getHeight(), 5, 0, 5);
	ColourGradient cG = ColourGradient(tabButtonBarGr1, 0, 0, tabButtonBarGr2, 0, tabButton.getHeight(), false);
	g.setGradientFill(cG);
	g.fillPath(rect);
	g.setColour(tabButtonBarOutline);
	g.strokePath(rect, PathStrokeType(0.4f));
}

void Theme::drawTabAreaBehindFrontButton (TabbedButtonBar &tabBar, Graphics &g, int w, int h)
{
}

void Theme::drawTableHeaderBackground(Graphics &g, TableHeaderComponent &th)
{
	g.fillAll(Colours::white);

	for (int i = 0; i <= th.getNumColumns(true); i++) {
		if (i <= 3) {
			Rectangle<int> area(th.getColumnPosition(i));

			area.removeFromTop(area.getHeight() / 2);

			g.setGradientFill(ColourGradient(Colour(0xffe8ebf9), 0.0f, (float)area.getY(),
				Colour(0xfff6f8f9), 0.0f, (float)area.getBottom(),
				false));
			g.fillRect(area);

			g.setColour(Colour(0x33000000));
			g.fillRect(area.removeFromBottom(1));

			g.fillRect(th.getColumnPosition(i).removeFromRight(1));
		}
	}
}

void Theme::drawTableHeaderColumn(Graphics &g, const String &columnName, int columnId, int width, int height, bool isMouseOver, bool isMouseDown, int columnFlags)
{
	if (columnName.isNotEmpty()) {
		LookAndFeel_V2::drawTableHeaderColumn(g, columnName, columnId, width, height, isMouseOver, isMouseDown, columnFlags);
	}
}

void Theme::drawDocumentWindowTitleBar(DocumentWindow &, Graphics &g, int w, int h, int titleSpaceX, int titleSpaceW, const Image *icon, bool drawTitleTextOnLeft)
{
	g.fillAll(Colour(0xff3a3a3a));
	g.setColour(Colour(0xffffffff));
	g.setFont(Font(16));
	g.drawText("Coeus Finance", 0, 0, w, h, Justification::centred, false);
}

void Theme::drawComboBox(Graphics &g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, ComboBox &box)
{
	ColourGradient gc(Colour(0xff3a3a3a), 0, 0, Colour(0xffd1cfcf), width*0.2, height * 3, false);
	g.setGradientFill(gc);
	g.fillRoundedRectangle(0, 0, width, height, 5);

	float wf = 1 - 0.68;
	float sz = height / 3.0f;
	float startx = width*0.68 + (wf*width - sz) / 2.0f;
	if (isButtonDown) {
		g.setColour(Colour(0xff2cc2cd));
	}
	else if (box.isMouseOver()) {
		g.setColour(Colour(0xff1a7b82));
	}
	else {
		g.setColour(Colours::white);
	}
	g.fillEllipse(startx, sz, sz, sz);

	g.setColour(Colour(0xff3a3a3a));
	float vX1 = startx + sz/4.0f;
	float vX2 = startx + sz/2.0f;
	float vY1 = sz + sz/4.0f;
	float vY2 = 2.0f*sz - sz/4.0f;
	float vX3 = startx + sz - sz / 4.0f;
	float vY3 = sz + sz/4.0f;
	g.drawLine(vX1, vY1, vX2, vY2, 2.0f);
	g.drawLine(vX3, vY3, vX2, vY2, 2.0f);
}

juce::Font Theme::getComboBoxFont(ComboBox &)
{
	return Font();
}

Label * Theme::createComboBoxTextBox(ComboBox &box)
{
	String comboText = box.getItemText(box.getSelectedId());
	Label *lbl = new Label(comboText, comboText);
	lbl->setColour(Label::textColourId, Colours::white);
	return lbl;
}

void Theme::positionComboBoxText(ComboBox &box, Label &lbl)
{
	Rectangle<int> rect(0, 0, box.getWidth()*0.68, box.getHeight());
	lbl.setBounds(rect);
	lbl.setJustificationType(Justification::centred);
	// TODO: wtf/remove next line
	lbl.setColour(Label::textColourId, Colours::white);
}

//---------------------------------------------------------------------
// Button stuff
void ThemeAlt::drawButtonBackground(Graphics &g, Button &button, const Colour &backgroundColour, bool isMouseOverButton, bool isButtonDown)
{
	g.setColour(Colour(0xff3b393a));
	g.fillAll();
	g.setColour(Colour(0xff148373));
	g.fillRect(0, 0, 7, button.getHeight());
}

Font ThemeAlt::getTextButtonFont (TextButton&, int)
{
	return Font();
}

void ThemeAlt::drawButtonText(Graphics &g, TextButton &button, bool isMouseOverButton, bool isButtonDown)
{
	Colour c;

	if (isButtonDown) {
		c = buttonTextDown;
	}
	else if (isMouseOverButton) {
		c = buttonTextOver;
	}
	else {
		c = Colour(0xff148373);
	}

	g.setColour(c);
	g.drawText(button.getButtonText(), 0, 0, button.getWidth(), button.getHeight() - 4, Justification::centred, true);
}

//---------------------------------------------------------------------
// theme alt
int ThemeAlt::getTabButtonSpaceAroundImage()
{
	return 0;
}

int ThemeAlt::getTabButtonOverlap(int tabDepth)
{
	return -5;
}

int ThemeAlt::getTabButtonBestWidth(TabBarButton &tabButton, int tabDepth)
{
	return tabDepth+8;
}

void ThemeAlt::drawTabButton(TabBarButton &tabButton, Graphics &g, bool isMouseOver, bool isMouseDown)
{
	if (tabButton.isFrontTab()) {
		if (isMouseOver) {
			g.setColour(tabButtonBG2.withAlpha(0.8f));
		}
		else {
			g.setColour(tabButtonBG2);
		}
	}
	else {
		if (isMouseOver) {
			g.setColour(tabButtonBG2.darker().withAlpha(0.8f));
		}
		else {
			g.setColour(tabButtonBG2.darker());
		}
	}
	g.fillAll();

	Colour c;
	if (isMouseDown) {
		c = (Colours::aqua).darker().darker().withAlpha(0.7f);
	}
	else if (isMouseOver) {
		c = Colours::black;
	}
	else {
		c = Colours::grey.darker();
	}

	g.setFont(Font(12));
	g.setColour(c);
	g.drawText(tabButton.getButtonText(), 0, 0, tabButton.getWidth(), tabButton.getHeight(), Justification::centred, true);
}

void ThemeAlt::drawTabButtonText(TabBarButton &tabButton, Graphics &g, bool isMouseOver, bool isMouseDown)
{

}

void ThemeAlt::drawTabbedButtonBarBackground(TabbedButtonBar &tabButton, Graphics &g)
{
	
}

void ThemeAlt::drawTabAreaBehindFrontButton(TabbedButtonBar &tabBar, Graphics &g, int w, int h)
{
}


//-----------------------------------------------------------------------
bool Theme::areScrollbarButtonsVisible()
{
	return false;
}

CoeusTabbedComponent::CoeusTabbedComponent()
: TabbedComponent (TabbedButtonBar::Orientation::TabsAtTop)
{
    
}

void CoeusTabbedComponent::paint (Graphics& g)
{
}


