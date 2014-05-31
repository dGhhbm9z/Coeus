#ifndef CustomComponentsGuard
#define CustomComponentsGuard

#include "../JuceLibraryCode/JuceHeader.h"

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

class CustomTabContent : public Component
{
public:
	CustomTabContent();
	~CustomTabContent();

	void resized() override;
	Rectangle<int> getComponentArea();

protected:
	ScopedPointer<Label> title;
	ScopedPointer<TextEditor> search;

private:

};

#endif