#ifndef __ThemeHeader__
#define __ThemeHeader__

#include "../JuceLibraryCode/JuceHeader.h"


class Theme	:	public LookAndFeel_V2
{
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
};


class CoeusTabbedComponent :   public TabbedComponent
{
public:
    CoeusTabbedComponent();
    void paint (Graphics& g) override;
};

#endif