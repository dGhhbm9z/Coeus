#ifndef __ThemeHeader__
#define __ThemeHeader__

#include "../JuceLibraryCode/JuceHeader.h"

class ThemeButton : public ToggleButton
{
public:
	ThemeButton(Colour &info, String txt) : infoColour(info) {
		text = String(txt);
	};

	void paintButton(Graphics &g, bool isMouseOverButton, bool isButtonDown) override {

		g.setColour(infoColour);
		g.fillAll();

		if (isButtonDown || getToggleState()) {
			g.setColour(infoColour.contrasting());
			g.drawRect(0, 0, getWidth(), getHeight(), 2);
		}
		else if (isMouseOverButton) {
			g.setColour(infoColour.contrasting(0.4));
			g.drawRect(0, 0, getWidth(), getHeight(), 2);
		}

		g.setColour(infoColour.contrasting());
		g.drawText(text, 0, 0, getWidth(), getHeight(), Justification::centred, true);
	};

	void setInfoColour(Colour colour) {
		infoColour = colour;
	};

private:
	Colour &infoColour;
	String text;
};

class ThemeComponent	:	public Component,
							public ButtonListener,
							public ChangeListener
{
public:
	ThemeComponent(Component &compToRefresh_);
	~ThemeComponent();

	void resized() override;

	void buttonClicked(Button *buttonThatWasClicked) override;

	void paint(Graphics &g) override;

	void userTriedToCloseWindow() override;

	void changeListenerCallback(ChangeBroadcaster *broadcaster);

	void saveData(OutputStream *os);

	void loadData(InputStream *is);

private:
	Component &compToRefresh;

	ScopedPointer<ThemeButton> buttonGr1Button;
	ScopedPointer<ThemeButton> buttonGr2Button;
	ScopedPointer<ThemeButton> buttonGr3Button;
	ScopedPointer<ThemeButton> buttonOutlineHoverButton;
	ScopedPointer<ThemeButton> buttonOutlineButton;
	ScopedPointer<ThemeButton> buttonTextDownButton;
	ScopedPointer<ThemeButton> buttonTextOverButton;
	ScopedPointer<ThemeButton> buttonTextButton;
	ScopedPointer<ThemeButton> tabButtonBarGr1Button;
	ScopedPointer<ThemeButton> tabButtonBarGr2Button;
	ScopedPointer<ThemeButton> tabButtonBarOutlineButton;
	ScopedPointer<ThemeButton> tabButtonFrontTabButton;
	ScopedPointer<ThemeButton> tabButtonFrontTabOutlineButton;
	ScopedPointer<ThemeButton> tabButtonBG1Button;
	ScopedPointer<ThemeButton> tabButtonBG2Button;
	ScopedPointer<ThemeButton> tabButtonOutlineButton;

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

	ScopedPointer<ColourSelector> cs;

	ScopedPointer<TextButton> saveButton;
	ScopedPointer<TextButton> loadButton;

	ThemeButton *lastButtonThatWasClicked;
};

class Theme	:	public LookAndFeel_V2
{
public:
	// Button stuff
	void drawButtonBackground (Graphics &, Button &button, const Colour &backgroundColour, bool isMouseOverButton, bool isButtonDown) override; 
    Font getTextButtonFont (TextButton&, int) override;
	void drawButtonText (Graphics &, TextButton &, bool isMouseOverButton, bool isButtonDown) override;
	void drawToggleButton (Graphics &, ToggleButton &, bool isMouseOverButton, bool isButtonDown) override;
	void changeToggleButtonWidthToFitText (ToggleButton &) override;
	void drawTickBox (Graphics &, Component &, float x, float y, float w, float h, bool ticked, bool isEnabled, bool isMouseOverButton, bool isButtonDown) override;
	void drawDrawableButton (Graphics &, DrawableButton &, bool isMouseOverButton, bool isButtonDown) override;

	// tabs stuff

	int getTabButtonSpaceAroundImage () override;
	int getTabButtonOverlap (int tabDepth) override;
	int getTabButtonBestWidth (TabBarButton &, int tabDepth) override;
	void drawTabButton (TabBarButton &, Graphics &, bool isMouseOver, bool isMouseDown) override;
	void drawTabButtonText (TabBarButton &, Graphics &, bool isMouseOver, bool isMouseDown) override;
	void drawTabbedButtonBarBackground (TabbedButtonBar &, Graphics &) override;
	void drawTabAreaBehindFrontButton (TabbedButtonBar &, Graphics &, int w, int h) override;

	static Path createRectPath(int x, int y, int w, int h, int pad, int padB, int cDist);

	// scrollbars
	bool areScrollbarButtonsVisible() override;

	// table header
	void drawTableHeaderBackground(Graphics &, TableHeaderComponent &) override;
	void drawTableHeaderColumn(Graphics &, const String &columnName, int columnId, int width, int height, bool isMouseOver, bool isMouseDown, int columnFlags) override;

	void drawDocumentWindowTitleBar(DocumentWindow &, Graphics &, int w, int h, int titleSpaceX, int titleSpaceW, const Image *icon, bool drawTitleTextOnLeft) override;

	// combobox stuff
	void drawComboBox(Graphics &, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, ComboBox &) override;
	juce::Font getComboBoxFont(ComboBox &) override;
	Label * createComboBoxTextBox(ComboBox &) override;
	void positionComboBoxText(ComboBox &, Label &) override;
    
    // pop up menus
    void drawPopupMenuBackground (Graphics &, int width, int height) override;
    
//    void drawPopupMenuItem (Graphics &, const Rectangle< int > &area, bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu, const String &text, const String &shortcutKeyText, const Drawable *icon, const Colour *textColour) override
//    
//    void drawPopupMenuSectionHeader (Graphics &, const Rectangle< int > &area, const String &sectionName) override
//    Font getPopupMenuFont () override
//    
//    void drawPopupMenuUpDownArrow (Graphics &, int width, int height, bool isScrollUpArrow) override
//    void getIdealPopupMenuItemSize (const String &text, bool isSeparator, int standardMenuItemHeight, int &idealWidth, int &idealHeight) override
};


class ThemeAlt : public Theme
{
public:
	// Button stuff
	void drawButtonBackground(Graphics &, Button &button, const Colour &backgroundColour, bool isMouseOverButton, bool isButtonDown) override;
    Font getTextButtonFont (TextButton&, int) override;
	void drawButtonText(Graphics &, TextButton &, bool isMouseOverButton, bool isButtonDown) override;

	// tabs stuff
	int getTabButtonSpaceAroundImage() override;
	int getTabButtonOverlap(int tabDepth) override;
	int getTabButtonBestWidth(TabBarButton &, int tabDepth) override;
	void drawTabButton(TabBarButton &, Graphics &, bool isMouseOver, bool isMouseDown) override;
	void drawTabButtonText(TabBarButton &, Graphics &, bool isMouseOver, bool isMouseDown) override;
	void drawTabbedButtonBarBackground(TabbedButtonBar &, Graphics &) override;
	void drawTabAreaBehindFrontButton(TabbedButtonBar &, Graphics &, int w, int h) override;
};

class CoeusTabbedComponent :   public TabbedComponent
{
public:
    CoeusTabbedComponent();
    void paint (Graphics& g) override;
};

#endif
