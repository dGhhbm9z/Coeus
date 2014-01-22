#include "Theme.h"

const Colour tabButtonBackgroundWhenSelected = Colour(0xffffffff);
//Gradient from 0xffd3d3d3 to 0xffd7d7d7
const Colour tabButtonBackground = Colour(0xffd3d3d3);
const Colour tabButtonTextWhenSelected = Colour(0xffd3d3d3);
const Colour tabButtonTextMouseOver = Colour(0xff000000);
const Colour tabButtonTextOnClick = Colour(0xff486c7b);
//Gradient from 0xff3c3c37 to 0xff486c7b
const Colour tabLineFill = Colour(0xff3c3c37);
const Colour aboveTabBarFill = Colour(0xff486c7b);
const Colour sideBarLeftFill = Colour(0xff3c3c37);
const Colour sideBarRightFill = Colour(0xff3c3c37);
const Colour workSpaceFill = Colour(0xffffffff);

ThemeComponent::ThemeComponent()
{
	tabButtonBackgroundWhenSelectedLabel = new Label(String::empty, L"tabButtonBackgroundWhenSelected");
	tabButtonBackgroundLabel = new Label(String::empty, L"tabButtonBackground");
	tabButtonTextWhenSelectedLabel = new Label(String::empty, L"tabButtonTextWhenSelected");
	tabButtonTextMouseOverLabel = new Label(String::empty, L"tabButtonTextMouseOver");
	tabButtonTextOnClickLabel = new Label(String::empty, L"tabButtonTextOnClick");
	tabLineFillLabel = new Label(String::empty, L"tabLineFill");
	aboveTabBarFillLabel = new Label(String::empty, L"aboveTabBarFill");
	sideBarLeftFillLabel = new Label(String::empty, L"sideBarLeftFill");
	sideBarRightFillLabel = new Label(String::empty, L"sideBarRightFill");
	workSpaceFillLabel = new Label(String::empty, L"workSpaceFill");

	tabButtonBackgroundWhenSelectedButton = new ThemeButton();
	tabButtonBackgroundButton = new ThemeButton();
	tabButtonTextWhenSelectedButton = new ThemeButton();
	tabButtonTextMouseOverButton = new ThemeButton();
	tabButtonTextOnClickButton = new ThemeButton();
	tabLineFillButton = new ThemeButton();
	aboveTabBarFillButton = new ThemeButton();
	sideBarLeftFillButton = new ThemeButton();
	sideBarRightFillButton = new ThemeButton();
	workSpaceFillButton = new ThemeButton();

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

	addAndMakeVisible(tabButtonBackgroundWhenSelectedLabel);
	addAndMakeVisible(tabButtonBackgroundLabel);
	addAndMakeVisible(tabButtonTextWhenSelectedLabel);
	addAndMakeVisible(tabButtonTextMouseOverLabel);
	addAndMakeVisible(tabButtonTextOnClickLabel);
	addAndMakeVisible(tabLineFillLabel);
	addAndMakeVisible(aboveTabBarFillLabel);
	addAndMakeVisible(sideBarLeftFillLabel);
	addAndMakeVisible(sideBarRightFillLabel);
	addAndMakeVisible(workSpaceFillLabel);

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

}

ThemeComponent::~ThemeComponent()
{

}

void ThemeComponent::resized()
{
	const float vsz = 1 / 12;
	float vs = 0.05f;
	float hs = 0.05f;
	float hsz = 0.4f;

	tabButtonBackgroundWhenSelectedLabel->setBounds(hs, vs, hsz, vsz);
	vs += vsz;
	tabButtonBackgroundLabel->setBounds(hs, vs, hsz, vsz);
	vs += vsz;
	tabButtonTextWhenSelectedLabel->setBounds(hs, vs, hsz, vsz);
	vs += vsz;
	tabButtonTextMouseOverLabel->setBounds(hs, vs, hsz, vsz);
	vs += vsz;
	tabButtonTextOnClickLabel->setBounds(hs, vs, hsz, vsz);
	vs += vsz;
	tabLineFillLabel->setBounds(hs, vs, hsz, vsz);
	vs += vsz;
	aboveTabBarFillLabel->setBounds(hs, vs, hsz, vsz);
	vs += vsz;
	sideBarLeftFillLabel->setBounds(hs, vs, hsz, vsz);
	vs += vsz;
	sideBarRightFillLabel->setBounds(hs, vs, hsz, vsz);
	vs += vsz;
	workSpaceFillLabel->setBounds(hs, vs, hsz, vsz);

	hs = 0.55f;
	vs = 0.05f;
	tabButtonBackgroundWhenSelectedButton->setBounds(hs, vs, hsz, vsz);
	vs += vsz;
	tabButtonBackgroundButton->setBounds(hs, vs, hsz, vsz);
	vs += vsz;
	tabButtonTextWhenSelectedButton->setBounds(hs, vs, hsz, vsz);
	vs += vsz;
	tabButtonTextMouseOverButton->setBounds(hs, vs, hsz, vsz);
	vs += vsz;
	tabButtonTextOnClickButton->setBounds(hs, vs, hsz, vsz);
	vs += vsz;
	tabLineFillButton->setBounds(hs, vs, hsz, vsz);
	vs += vsz;
	aboveTabBarFillButton->setBounds(hs, vs, hsz, vsz);
	vs += vsz;
	sideBarLeftFillButton->setBounds(hs, vs, hsz, vsz);
	vs += vsz;
	sideBarRightFillButton->setBounds(hs, vs, hsz, vsz);
	vs += vsz;
	workSpaceFillButton->setBounds(hs, vs, hsz, vsz);
}

void ThemeComponent::buttonClicked(Button *buttonThatWasClicked)
{

	//((ThemeButton *)buttonThatWasClicked)->setInfoColour();
}

void ThemeComponent::paint(Graphics &g)
{
	g.fillAll(workSpaceFill);
}

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

// Button stuff
void Theme::drawButtonBackground (Graphics &g, Button &button, const Colour &backgroundColour, bool isMouseOverButton, bool isButtonDown)
{
	Path rect = createRectPath(2, 2, button.getWidth()-4, button.getHeight()-4, 1, 1, 5);

	ColourGradient cG = ColourGradient(Colour(0xffdddddd), 0, 0, Colour(0xffdddddd), 0, button.getHeight(), false);
	cG.addColour(0.3f, Colour(0xffffffff));
	g.setGradientFill(cG);
	if (!isButtonDown) {
        g.fillPath(rect);
    }

	g.setColour(isMouseOverButton ?  Colour(0xffd3d3d3).darker() : Colour(0xffd3d3d3));
	g.strokePath(rect, PathStrokeType(1.5f));
}

Font Theme::getTextButtonFont (TextButton &button)
{
	return Font();
}

void Theme::drawButtonText (Graphics &g, TextButton &button, bool isMouseOverButton, bool isButtonDown)
{
	Colour c;

	if (isButtonDown) {
		c = (Colours::aqua).darker().darker().withAlpha(0.7f);
	}
	else if (isMouseOverButton) {
		c = Colours::black;
	}
	else {
		c = Colours::grey.darker();
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
		g.setColour(Colour(0xfffefefe));
		g.fillPath(rect);

		g.setColour(Colour(0xffaaaaaa));
		g.strokePath(rect, PathStrokeType(0.5));
	}
	else {
		g.setColour(Colour(0xffe6e6e6).brighter().brighter());
		g.fillPath(rect);

		g.setColour(Colour(0xffe6e6e6));
		g.fillRect(leftX1, topY1+(bottomY1 - topY1) / 2, rightX1 - leftX1, (bottomY1 - topY1) / 2 - 1);

		g.setColour(Colour(0xffe6e6e6).darker());
		g.strokePath(rect, PathStrokeType(0.5));

		g.setColour(Colour(0xffd3d3d3).darker());
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
	const float pad = 1;
//	const float cDist = 5+pad;
//	const float width = tabButton.getWidth()-2*pad;
//	const float height = tabButton.getHeight();

	Path rect;
//	rect.startNewSubPath(pad, height);
//	rect.lineTo(pad, cDist);
//	rect.quadraticTo(pad, pad, cDist, pad);
//	rect.lineTo(width-cDist, pad);
//	rect.quadraticTo(width, pad, width, cDist);
//	rect.lineTo(width, height);
//
//	g.setColour(Colour(0xffaaaaaa));
//	g.strokePath(rect, PathStrokeType(2.0f));

	rect = createRectPath(0, 0, tabButton.getWidth(), tabButton.getHeight(), 5, 0, 5);
	ColourGradient cG = ColourGradient(Colour(0xffe3e3e3), 0, 0, Colour(0xffcccccc), 0, tabButton.getHeight(), false);
	g.setGradientFill(cG);
	g.fillPath(rect);
	g.setColour(Colour(0xffd3d3d3).darker());
	g.strokePath(rect, PathStrokeType(0.4f));
}

void Theme::drawTabAreaBehindFrontButton (TabbedButtonBar &tabBar, Graphics &g, int w, int h)
{
}

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
    const float pad = 1;
	const float cDist = 5;
	const float width = getWidth();
	const float height = getHeight();
    
	Path rect;
	rect.startNewSubPath(pad, height-cDist-pad);
	rect.lineTo(pad, cDist+pad);
	rect.quadraticTo(pad, pad, cDist+pad, pad);
	rect.lineTo(width-cDist-pad, pad);
	rect.quadraticTo(width-pad, pad, width-pad, cDist+pad);
	rect.lineTo(width-pad, height-cDist-pad);
	rect.quadraticTo(width-pad, height-pad, width-cDist-pad, height-pad);
	rect.lineTo(cDist+pad, height-pad);
	rect.quadraticTo(pad, height-pad, pad, height-cDist-pad);
    
	g.setColour(Colour(0xffaaaaaa));
	g.strokePath(rect, PathStrokeType(1.0f));
}


