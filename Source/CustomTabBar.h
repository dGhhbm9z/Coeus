#ifndef CustomTabBarGuard
#define CustomTabBarGuard

#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomComponents.h"
#include "Theme.h"
#include "Accounts.h"
#include "AccountChart.h"
#include "Customers.h"
#include "Suppliers.h"
#include "Companies.h"

//=======================================================================================================
class CustomTabbedButtonBar : public Component,
	public ChangeBroadcaster,
	public ButtonListener
{
public:
	CustomTabbedButtonBar();
	~CustomTabbedButtonBar();
	void paint(Graphics &g) override;
	void resized() override;
	int getCurrentTabIndex() const;
	void buttonClicked(Button* buttonThatWasClicked) override;

private:
	int index;

	ScopedPointer<CustomMenuBarButton> reporting;
	ScopedPointer<CustomMenuBarButton> accounting;
	ScopedPointer<CustomMenuBarButton> logout;

	ScopedPointer<CustomMenuBarButton> customers;
	ScopedPointer<CustomMenuBarButton> suppliers;
	ScopedPointer<CustomMenuBarButton> accountChart;
	ScopedPointer<CustomMenuBarButton> accounts;
	ScopedPointer<CustomMenuBarButton> companies;

	ScopedPointer<CustomMenuBarButton> businessModel;
	ScopedPointer<CustomMenuBarButton> businessPlan;
	ScopedPointer<CustomMenuBarButton> financialRatios;
	ScopedPointer<CustomMenuBarButton> openSourceInnovation;
	ScopedPointer<CustomMenuBarButton> reportGenerator;

	ThemeAlt themeAlt;
};

class CustomTabComponent : public Component,
	public ChangeListener,
	public Timer
{
public:
	CustomTabComponent();
	~CustomTabComponent();
	void resized() override;
	void timerCallback() override;
	void changeListenerCallback(ChangeBroadcaster *source) override;
    void resizeStart();
    void resizeEnd();

private:
	ScopedPointer<AccountChartComponent> accountChartComponent;
	ScopedPointer<AccountsComponent> accountsComponent;
	ScopedPointer<SuppliersComponent> suppliersComponent;
	ScopedPointer<CustomersComponent> customersComponent;
	ScopedPointer<CompaniesComponent> companiesComponent;

	ScopedPointer<CustomTabbedButtonBar> tabButtons;
    bool isBeingResized;
};

#endif
