#ifndef CustomComponentsGuard
#define CustomComponentsGuard

#include "../JuceLibraryCode/JuceHeader.h"
#include "CoeusList.h"

class CustomMenuBarButton : public TextButton
{
public:
	enum ButtonType {
		AccountChartType, CompaniesType, CustomersType, EventsType, SuppliersType,
		BusinessModelType, BusinessPlanType, FinancialRatiosType, OpenSourceInnovationType, ReportGeneratorTytpe,
		LogoutType, AccountingTabType, ReportingTabType
	};

	CustomMenuBarButton(ButtonType btntype);
	void paint(Graphics &g) override;

private:
	Image imageNormal;
	Image imageMouseOver;
	Image imageMouseDown;
};

//=======================================================================================================

class ComboBoxFocusReport : public ComboBox,
	public ChangeBroadcaster
{
public:
	void focusGained(FocusChangeType cause) override {
		focus = true;
		sendChangeMessage();
	}

	void mouseEnter(const MouseEvent &event) override {
		focus = false;
		sendChangeMessage();
	}

	int rowIndex;
	bool focus;
};

//=======================================================================================================

class TextEditFocusReport : public TextEditor,
	public ChangeBroadcaster
{
public:
	void focusGained(FocusChangeType cause) override {
		focus = true;
		sendChangeMessage();
	}

	void mouseEnter(const MouseEvent &event) override {
		focus = false;
		sendChangeMessage();
	}

	int rowIndex;
	bool focus;
};

//=======================================================================================================

class LabelFocusReport : public Label,
	public ChangeBroadcaster
{
public:
	void focusGained(FocusChangeType cause) override {
		focus = true;
		sendChangeMessage();
	}

	void mouseEnter(const MouseEvent &event) override {
		focus = false;
		sendChangeMessage();
	}

	int rowIndex;
	bool focus;
};

//=======================================================================================================
class MarginComponent : public Component
{
public:
	MarginComponent(Component *comp_) : comp(comp_) {
		if (comp) {
			addAndMakeVisible(comp);
		}
	}

	~MarginComponent() {
		comp = nullptr;
	}

	void resized() override {
		comp->setBounds(4, 4, getWidth() - 8, getHeight() - 8);
	}

	Component *getEnclosedComp() {
		return comp;
	}

private:
	ScopedPointer<Component> comp;
};

//=======================================================================================================
class OverlayComp   :   public Component
{
public:
    void paint(Graphics &g) override {
        g.fillAll(Colours::grey.withAlpha(0.8f));
    }
};

//=======================================================================================================

class CustomTabContent :	public Component,
							public ComboBox::Listener,
                            public Button::Listener,
                            public ChangeListener
{
public:
	CustomTabContent();
	~CustomTabContent();

	void resized() override;
	juce::Rectangle<int> getComponentArea();

	void comboBoxChanged(ComboBox *comboBoxThatHasChanged) override;

	virtual void searchButtonPressed() = 0;
	virtual void addButtonPressed() = 0;
    virtual void saveButtonPressed() {}
    virtual void removeButtonPressed() = 0;
    virtual void duplicateButtonPressed() {}

    void changeListenerCallback(ChangeBroadcaster *source) override = 0;
    
	void buttonClicked(Button *) override;
    
    virtual CoeusListRowComponent *getAddComponent() = 0;

    ScopedPointer<ImageComponent> bottomDemo;
    
protected:
	ScopedPointer<Label> title;
	ScopedPointer<TextEditor> search;
	ScopedPointer<ComboBox> searchFilter;
	ScopedPointer<ImageButton> searchButton;    
    ScopedPointer<Label> tableHeader1, tableHeader2, tableHeader3, tableHeader4;
    ScopedPointer<ImageButton> addButton, duplicateButton, removeButton;
    ScopedPointer<OverlayComp> addOverlayComp;
    ScopedPointer<CoeusListRowComponent> addComp;

	ScopedPointer<ImageComponent> rightDemo;
	Image rightDemoImage, bottomDemoImage;

	Image imageNormal;
	Image imageMouseOver;
	Image imageMouseDown;

private:

};

#endif
