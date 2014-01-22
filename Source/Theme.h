#ifndef __ThemeHeader__
#define __ThemeHeader__

#include "../JuceLibraryCode/JuceHeader.h"

class ThemeButton : public TextButton
{
public:
	void paint(Graphics &g) override {

		if (isMouseButtonDown()) {
			g.setColour(infoColour);
		}
		else {
			g.setColour(infoColour.darker());
		}
		g.fillAll();

		if (isMouseOver()) {
			g.setColour(infoColour.brighter().brighter());
			g.drawRect(0, 0, getWidth(), getHeight(), 2);
		}
	};

	void setInfoColour(Colour &colour) {
		infoColour = colour;
	};

private:
	Colour infoColour;
};

class ThemeComponent	:	public Component,
							public ButtonListener
{
public:
	ThemeComponent();
	~ThemeComponent();

	void resized() override;

	void buttonClicked(Button *buttonThatWasClicked) override;

	void paint(Graphics &g) override;

private:
	ScopedPointer<Label> tabButtonBackgroundWhenSelectedLabel;
	ScopedPointer<Label> tabButtonBackgroundLabel;
	ScopedPointer<Label> tabButtonTextWhenSelectedLabel;
	ScopedPointer<Label> tabButtonTextMouseOverLabel;
	ScopedPointer<Label> tabButtonTextOnClickLabel;
	ScopedPointer<Label> tabLineFillLabel;
	ScopedPointer<Label> aboveTabBarFillLabel;
	ScopedPointer<Label> sideBarLeftFillLabel;
	ScopedPointer<Label> sideBarRightFillLabel;
	ScopedPointer<Label> workSpaceFillLabel;

	ScopedPointer<ThemeButton> tabButtonBackgroundWhenSelectedButton;
	ScopedPointer<ThemeButton> tabButtonBackgroundButton;
	ScopedPointer<ThemeButton> tabButtonTextWhenSelectedButton;
	ScopedPointer<ThemeButton> tabButtonTextMouseOverButton;
	ScopedPointer<ThemeButton> tabButtonTextOnClickButton;
	ScopedPointer<ThemeButton> tabLineFillButton;
	ScopedPointer<ThemeButton> aboveTabBarFillButton;
	ScopedPointer<ThemeButton> sideBarLeftFillButton;
	ScopedPointer<ThemeButton> sideBarRightFillButton;
	ScopedPointer<ThemeButton> workSpaceFillButton;

};

class Theme	:	public LookAndFeel_V2
{
public:
	// Button stuff
	void drawButtonBackground (Graphics &, Button &button, const Colour &backgroundColour, bool isMouseOverButton, bool isButtonDown); 
	Font getTextButtonFont (TextButton &button);
	void drawButtonText (Graphics &, TextButton &, bool isMouseOverButton, bool isButtonDown);
	void drawToggleButton (Graphics &, ToggleButton &, bool isMouseOverButton, bool isButtonDown);
	void changeToggleButtonWidthToFitText (ToggleButton &);
	void drawTickBox (Graphics &, Component &, float x, float y, float w, float h, bool ticked, bool isEnabled, bool isMouseOverButton, bool isButtonDown);
	void drawDrawableButton (Graphics &, DrawableButton &, bool isMouseOverButton, bool isButtonDown);

	// tabs stuff

	int getTabButtonSpaceAroundImage ();
	int getTabButtonOverlap (int tabDepth);
	int getTabButtonBestWidth (TabBarButton &, int tabDepth);
	void drawTabButton (TabBarButton &, Graphics &, bool isMouseOver, bool isMouseDown);
	void drawTabButtonText (TabBarButton &, Graphics &, bool isMouseOver, bool isMouseDown);
	void drawTabbedButtonBarBackground (TabbedButtonBar &, Graphics &);
	void drawTabAreaBehindFrontButton (TabbedButtonBar &, Graphics &, int w, int h);

	static Path createRectPath(int x, int y, int w, int h, int pad, int padB, int cDist);

	// scrollbars
	bool areScrollbarButtonsVisible() override;
};


class CoeusTabbedComponent :   public TabbedComponent
{
public:
    CoeusTabbedComponent();
    void paint (Graphics& g) override;
};

#endif