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
	void focusGained(FocusChangeType cause) {
		sendChangeMessage();
	}

	int rowIndex;
};

//=======================================================================================================

class TextEditFocusReport : public TextEditor,
	public ChangeBroadcaster
{
public:
	void focusGained(FocusChangeType cause) {
		sendChangeMessage();
	}

	int rowIndex;
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

#endif