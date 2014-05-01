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


#define WINDOWS_RESOURCE_FILE( X ) File::getSpecialLocation(File::currentExecutableFile).getParentDirectory().getChildFile( X )
#define MAC_RESOURCE_FILE( X ) File::getSpecialLocation(File::currentExecutableFile).getParentDirectory().getParentDirectory().getChildFile( X )

#ifdef __APPLE__
	#define RESOURCE_FILE( X ) MAC_RESOURCE_FILE( X )
#else
	#define RESOURCE_FILE( X ) WINDOWS_RESOURCE_FILE( X )
#endif


class CustomMenuBarButton : public TextButton
{
public:
	enum ButtonType {AccountChartType, CompaniesType, CustomersType, EventsType, SuppliersType,
					BusinessModelType, BusinessPlanType, FinancialRatiosType, OpenSourceInnovationType, ReportGeneratorTytpe,
					LogoutType, AccountingTabType, ReportingTabType};

	CustomMenuBarButton(ButtonType btntype) {
		switch (btntype) {
		case AccountChartType:
			imageNormal = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/normal/AccountChart.png"));
			imageMouseOver = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/mouseOver/AccountChart.png"));
			imageMouseDown = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/mouseClicked/AccountChart.png"));
			break;
		case CompaniesType:
			imageNormal = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/normal/Companies.png"));
			imageMouseOver = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/mouseOver/Companies.png"));
			imageMouseDown = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/mouseClicked/Companies.png"));
			break;
		case CustomersType:
			imageNormal = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/normal/Customers.png"));
			imageMouseOver = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/mouseOver/Customers.png"));
			imageMouseDown = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/mouseClicked/Customers.png"));
			break;
		case EventsType:
			imageNormal = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/normal/Events.png"));
			imageMouseOver = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/mouseOver/Events.png"));
			imageMouseDown = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/mouseClicked/Events.png"));
			break;
		case SuppliersType:
			imageNormal = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/normal/Suppliers.png"));
			imageMouseOver = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/mouseOver/Suppliers.png"));
			imageMouseDown = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/mouseClicked/Suppliers.png"));
			break;
		case BusinessModelType:
			imageNormal = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/ReportingTab/normal/BusinessModelCanvas.png"));
			imageMouseOver = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/ReportingTab/mouseOver/BusinessModelCanvas.png"));
			imageMouseDown = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/ReportingTab/mouseClicked/BusinessModelCanvas.png"));
			break;
		case BusinessPlanType:
			imageNormal = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/ReportingTab/normal/BusinessPlan.png"));
			imageMouseOver = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/ReportingTab/mouseOver/BusinessPlan.png"));
			imageMouseDown = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/ReportingTab/mouseClicked/BusinessPlan.png"));
			break;
		case FinancialRatiosType:
			imageNormal = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/ReportingTab/normal/FinancialRatios.png"));
			imageMouseOver = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/ReportingTab/mouseOver/FinancialRatios.png"));
			imageMouseDown = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/ReportingTab/mouseClicked/FinancialRatios.png"));
			break;
		case OpenSourceInnovationType:
			imageNormal = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/ReportingTab/normal/OpenSourceInno.png"));
			imageMouseOver = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/ReportingTab/mouseOver/OpenSourceInno.png"));
			imageMouseDown = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/ReportingTab/mouseClicked/OpenSourceInno.png"));
			break;
		case ReportGeneratorTytpe:
			imageNormal = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/ReportingTab/normal/ReportGenerator.png"));
			imageMouseOver = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/ReportingTab/mouseOver/ReportGenerator.png"));
			imageMouseDown = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/ReportingTab/mouseClicked/ReportGenerator.png"));
			break;
		case LogoutType:
			imageNormal = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/Logout/LogoutNormal.png"));
			imageMouseOver = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/Logout/MouseOver.png"));
			imageMouseDown = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/Logout/MouseClick.png"));
			break;
		case AccountingTabType:
			imageNormal = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/Tabs/Accounting/AccountingTabNormal.png"));
			imageMouseOver = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/Tabs/Accounting/AccountingTabNormalMouseOver.png"));
			imageMouseDown = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/Tabs/Accounting/AccountingTabSelected.png"));
			break;
		case ReportingTabType:
			imageNormal = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/Tabs/Reporting/ReportingTabNormal.png"));
			imageMouseOver = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/Tabs/Reporting/ReportingTabNormalMouseOver.png"));
			imageMouseDown = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/Tabs/Reporting/ReportingTabSelected.png"));
			break;
		default:
			imageNormal = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/normal/Suppliers.png"));
			imageMouseOver = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/mouseOver/Suppliers.png"));
			imageMouseDown = ImageCache::getFromFile(RESOURCE_FILE("./Resources/sidebar/AccountingTab/mouseClicked/Suppliers.png"));
		}
	}

	void paint(Graphics &g) {

		if (isMouseButtonDown()) {
			g.drawImage(imageMouseDown, 0, 0, getWidth(), getHeight(), 0, 0, imageMouseDown.getWidth(), imageMouseDown.getHeight());
		}
		else if (isMouseOver()) {
			g.drawImage(imageMouseOver, 0, 0, getWidth(), getHeight(), 0, 0, imageMouseOver.getWidth(), imageMouseOver.getHeight());
		}
		else {
			g.drawImage(imageNormal, 0, 0, getWidth(), getHeight(), 0, 0, imageNormal.getWidth(), imageNormal.getHeight());
		}
	}

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
		comp->setBounds(4, 4, getWidth()-8, getHeight()-8);
	}

	Component *getEnclosedComp() {
		return comp;
	}

private:
	ScopedPointer<Component> comp;
};

//=======================================================================================================




//=======================================================================================================
class AccountChartsListBoxModel : public ListBoxModel
{
	int getNumRows() override
	{
		return 8;
	}

	void paintListBoxItem(int rowNumber, Graphics &g, int width, int height, bool rowIsSelected) override
	{
		/*g.fillAll(Colours::grey);
		g.setColour(Colours::black);
		g.drawRect(Rectangle<float>(0,0,width+1,height+1));
		g.setColour(Colours::azure);
		g.drawText(String(rowNumber), Rectangle<int>(0,0,width,height), Justification::centred, false);*/
	}

	Component* refreshComponentForRow(int rowNumber, bool isRowSelected, Component *existingComponentToUpdate) override
	{
		// create
		if (existingComponentToUpdate == nullptr) {
			Component *newComponent = (Component *) new CacheViewer();
			return newComponent;
		}
		// update
		else {
			return existingComponentToUpdate;
		}
	}
};

class AccountChartComponent : public Component
{
public:
	AccountChartComponent() {
		accountChartListBoxModel = new AccountChartsListBoxModel();
		accountChart = new ListBox(String::empty, accountChartListBoxModel);
		accountChart->setRowHeight(620);

		addAndMakeVisible(accountChart);
	}

	~AccountChartComponent() {
		accountChart = nullptr;
	}

	void resized() override {
		accountChart->setBoundsRelative(0.08f, 0.05f, 0.9f, 0.94f);
	}

private:
	ScopedPointer<ListBox> accountChart;
	ScopedPointer<AccountChartsListBoxModel> accountChartListBoxModel;
};

//=======================================================================================================
class AccountCellButtons : public Component
{
public:
	AccountCellButtons() {
		save = new TextButton(L"save");
		restore = new TextButton(L"restore");
		remove = new TextButton(L"remove");
		addAndMakeVisible(save);
		addAndMakeVisible(restore);
		addAndMakeVisible(remove);
	}

	~AccountCellButtons() {
		save = nullptr;
		restore = nullptr;
		remove = nullptr;
	}

	void resized() override {
		save->setBoundsRelative(0.0f, 0.1f, 0.33f, 0.9f);
		restore->setBoundsRelative(0.33f, 0.1f, 0.33f, 0.9f);
		remove->setBoundsRelative(0.66f, 0.1f, 0.33f, 0.9f);
	}

	int rowIndex;

private:

	ScopedPointer<TextButton> save;
	ScopedPointer<TextButton> restore;
	ScopedPointer<TextButton> remove;
};
//=======================================================================================================
class AccountsTableListBoxModel	:	public TableListBox,
									public TableListBoxModel,
									public ChangeListener

{
public:
	AccountsTableListBoxModel() : TableListBox(String::empty, this) {}

	int getNumRows() override
	{
		return 8;
	}

	void paintRowBackground(Graphics &g, int rowNumber, int width, int height, bool rowIsSelected) {
		if (rowIsSelected) {
			g.setColour(Colours::grey.brighter().brighter());
			g.fillAll();
		}
	}

	void paintCell(Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
	{
		if (columnId == 4) {
			g.setColour(Colours::black);
			g.drawText(L"133", 0, 0, width, height, Justification::centred, false);
		}
	}

	Component * refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate)
	{
		// create
		if (existingComponentToUpdate == nullptr) {
			if (columnId == 1) {
				TextEditFocusReport *payload = new TextEditFocusReport();
				payload->rowIndex = rowNumber;
				payload->setText(L"00.00.00.00");
				payload->addChangeListener(this);
				MarginComponent *newComponent = new MarginComponent(payload);
				return (Component *)newComponent;
			}
			else if (columnId == 2) {
				TextEditFocusReport *payload = new TextEditFocusReport();
				payload->rowIndex = rowNumber;
				payload->setText(L"Πολύ βασικός");
				payload->addChangeListener(this);
				MarginComponent *newComponent = new MarginComponent(payload);
				return (Component *)newComponent;
			}
			else if (columnId == 3) {
				ComboBoxFocusReport *payload = new ComboBoxFocusReport();
				payload->rowIndex = rowNumber;
				payload->addItem(L"Type I", 1);
				payload->addItem(L"Type II", 2);
				payload->addItem(L"Type III", 3);
				payload->addItem(L"Type IV", 4);
				payload->addItem(L"Type V", 5);
				payload->addChangeListener(this);
				MarginComponent *newComponent = new MarginComponent(payload);
				return (Component *)newComponent;
			}
			else if (columnId == 5 && isRowSelected) {
				AccountCellButtons *newComponent = new AccountCellButtons();
				newComponent->setVisible(isRowSelected);
				newComponent->rowIndex = rowNumber;
				return (Component *)newComponent;
			}

			return nullptr;
		}
		// update
		else {
			if (columnId == 1) {
				MarginComponent *newComponent = dynamic_cast<MarginComponent *>(existingComponentToUpdate);
				if (newComponent) {
					TextEditFocusReport *tefr = dynamic_cast<TextEditFocusReport *>(newComponent->getEnclosedComp());
					if (tefr) {
						tefr->rowIndex = rowNumber;
					}
				}
			}
			else if (columnId == 2) {
				MarginComponent *newComponent = dynamic_cast<MarginComponent *>(existingComponentToUpdate);
				if (newComponent) {
					TextEditFocusReport *tefr = dynamic_cast<TextEditFocusReport *>(newComponent->getEnclosedComp());
					if (tefr) {
						tefr->rowIndex = rowNumber;
					}
				}
			}
			else if (columnId == 3) {
				MarginComponent *newComponent = dynamic_cast<MarginComponent *>(existingComponentToUpdate);
				if (newComponent) {
					ComboBoxFocusReport *cbfr = dynamic_cast<ComboBoxFocusReport *>(newComponent->getEnclosedComp());
					if (cbfr) {
						cbfr->rowIndex = rowNumber;
					}
				}
			}
			else if (columnId == 5) {
				if (!isRowSelected) {
					delete existingComponentToUpdate;
					return nullptr;
				}

				AccountCellButtons *newComponent = dynamic_cast<AccountCellButtons *>(existingComponentToUpdate);
				if (newComponent) {
					newComponent->rowIndex = rowNumber;
				}
			}

			return existingComponentToUpdate;
		}
	}

	void changeListenerCallback(ChangeBroadcaster *source) {
		TextEditFocusReport *tefr = dynamic_cast<TextEditFocusReport *>(source);
		ComboBoxFocusReport *cbfr = dynamic_cast<ComboBoxFocusReport *>(source);

		if (tefr) {
			selectRow(tefr->rowIndex);
		}
		else if (cbfr) {
			selectRow(cbfr->rowIndex);
		}
	}
};

//=======================================================================================================
class AccountsComponent : public Component
{
public:
	AccountsComponent() {
		TableHeaderComponent *accountsHeaderComponent = new TableHeaderComponent();
		accountsHeaderComponent->addColumn(L"Κωδικός Λογαριασμού", 1, 250, 100, 250);
		accountsHeaderComponent->addColumn(L"Ονομασία Λογαριασμού", 2, 250, 100, 250);
		accountsHeaderComponent->addColumn(L"Είδος Λογαριασμού", 3, 150, 100, 250);
		accountsHeaderComponent->addColumn(L"Υπόλοιπο Λογαριασμού", 4, 250, 100, 250);
		accountsHeaderComponent->addColumn(String::empty, 5, 200, 100, 250);

		accounts = new AccountsTableListBoxModel();
		accounts->setRowHeight(40);
		accounts->setHeader(accountsHeaderComponent);
		accounts->setHeaderHeight(40);

		addAndMakeVisible(accounts);
	}

	~AccountsComponent() {
		accounts = nullptr;
	}

	void resized() override {
		accounts->setBoundsRelative(0.08f, 0.05f, 0.9f, 0.94f);
	}

private:
	ScopedPointer<AccountsTableListBoxModel> accounts;
};


//=======================================================================================================
//=======================================================================================================
class CustomersTableListBoxModel : public TableListBoxModel
{
	int getNumRows() override
	{
		return 8;
	}

	void paintRowBackground(Graphics &g, int rowNumber, int width, int height, bool rowIsSelected) {
		if (rowIsSelected) {
			g.setColour(Colours::grey.brighter().brighter());
			g.fillAll();
		}
	}

	void paintCell(Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
	{
		if (columnId == 4) {
			g.setColour(Colours::black);
			g.drawText(L"133", 0, 0, width, height, Justification::centred, false);
		}
	}

	Component * refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate)
	{
		// create
		if (existingComponentToUpdate == nullptr) {
			if (columnId == 1) {
				TextEditor *payload = new TextEditor();
				payload->setText(L"Παύλος Τσιμπούκης");
				MarginComponent *newComponent = new MarginComponent(payload);
				return (Component *)newComponent;
			}
			else if (columnId == 2) {
				TextEditor *payload = new TextEditor();
				payload->setText(L"Πούπουλα Ο.Ε.Ο.");
				MarginComponent *newComponent = new MarginComponent(payload);
				return (Component *)newComponent;
			}
			else if (columnId == 3) {
				TextEditor *payload = new TextEditor();
				payload->setText(L"6972009460");
				MarginComponent *newComponent = new MarginComponent(payload);
				return (Component *)newComponent;
			}
			else if (columnId == 5 && isRowSelected) {
				AccountCellButtons *newComponent = new AccountCellButtons();
				newComponent->setVisible(isRowSelected);
				return (Component *)newComponent;
			}

			return nullptr;
		}
		// update
		else {
			if (columnId == 1) {
				
			}
			else if (columnId == 2) {
				
			}
			else if (columnId == 3) {
				
			}
			else if (columnId == 5) {
				if (!isRowSelected) {
					delete existingComponentToUpdate;
					return nullptr;
				}
			}

			return existingComponentToUpdate;
		}
	}
};

//=======================================================================================================
class CustomersComponent : public Component
{
public:
	CustomersComponent() {
		TableHeaderComponent *accountsHeaderComponent = new TableHeaderComponent();
		accountsHeaderComponent->addColumn(L"Ονοματεπώνυμο πελάτη", 1, 250, 100, 250);
		accountsHeaderComponent->addColumn(L"Επωνυμία", 2, 250, 100, 250);
		accountsHeaderComponent->addColumn(L"Τηλέφωνο", 3, 150, 100, 250);
		accountsHeaderComponent->addColumn(L"Υπόλοιπο", 4, 250, 100, 250);
		accountsHeaderComponent->addColumn(String::empty, 5, 200, 100, 250);

		customersTableListBoxModel = new CustomersTableListBoxModel();
		customers = new TableListBox(String::empty, customersTableListBoxModel);
		customers->setRowHeight(40);
		customers->setHeader(accountsHeaderComponent);
		customers->setHeaderHeight(40);

		addAndMakeVisible(customers);
	}

	~CustomersComponent() {
		customers = nullptr;
	}

	void resized() override {
		customers->setBoundsRelative(0.08f, 0.05f, 0.9f, 0.94f);
	}

private:
	ScopedPointer<TableListBox> customers;
	ScopedPointer<CustomersTableListBoxModel> customersTableListBoxModel;
};

//=======================================================================================================
class SuppliersTableListBoxModel : public TableListBoxModel
{
	int getNumRows() override
	{
		return 8;
	}

	void paintRowBackground(Graphics &g, int rowNumber, int width, int height, bool rowIsSelected) {
		if (rowIsSelected) {
			g.setColour(Colours::grey.brighter().brighter());
			Rectangle<int> area();
			g.fillAll();
		}
	}

	void paintCell(Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
	{
		if (columnId == 4) {
			g.setColour(Colours::black);
			g.drawText(L"133", 0, 0, width, height, Justification::centred, false);
		}
	}

	Component * refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate)
	{
		// create
		if (existingComponentToUpdate == nullptr) {
			if (columnId == 1) {
				TextEditor *payload = new TextEditor();
				payload->setText(L"Σπύρος Τομπούλογλου");
				MarginComponent *newComponent = new MarginComponent(payload);
				return (Component *)newComponent;
			}
			else if (columnId == 2) {
				TextEditor *payload = new TextEditor();
				payload->setText(L"Μαξιλάρια Α.Ε.");
				MarginComponent *newComponent = new MarginComponent(payload);
				return (Component *)newComponent;
			}
			else if (columnId == 3) {
				TextEditor *payload = new TextEditor();
				payload->setText(L"6972009460");
				MarginComponent *newComponent = new MarginComponent(payload);
				return (Component *)newComponent;
			}
			else if (columnId == 5 && isRowSelected) {
				AccountCellButtons *newComponent = new AccountCellButtons();
				newComponent->setVisible(isRowSelected);
				return (Component *)newComponent;
			}

			return nullptr;
		}
		// update
		else {
			if (columnId == 1) {

			}
			else if (columnId == 2) {

			}
			else if (columnId == 3) {

			}
			else if (columnId == 5) {
				if (!isRowSelected) {
					delete existingComponentToUpdate;
					return nullptr;
				}
			}

			return existingComponentToUpdate;
		}
	}
};

//=======================================================================================================
class SuppliersComponent : public Component
{
public:
	SuppliersComponent() {
		TableHeaderComponent *accountsHeaderComponent = new TableHeaderComponent();
		accountsHeaderComponent->addColumn(L"Ονοματεπώνυμο προμηθευτή", 1, 250, 100, 250);
		accountsHeaderComponent->addColumn(L"Επωνυμία", 2, 250, 100, 250);
		accountsHeaderComponent->addColumn(L"Τηλέφωνο", 3, 150, 100, 250);
		accountsHeaderComponent->addColumn(L"Υπόλοιπο", 4, 250, 100, 250);
		accountsHeaderComponent->addColumn(String::empty, 5, 200, 100, 250);

		suppliersTableListBoxModel = new SuppliersTableListBoxModel();
		accounts = new TableListBox(String::empty, suppliersTableListBoxModel);
		accounts->setRowHeight(40);
		accounts->setHeader(accountsHeaderComponent);
		accounts->setHeaderHeight(40);

		addAndMakeVisible(accounts);
	}

	~SuppliersComponent() {
		accounts = nullptr;
	}

	void resized() override {
		accounts->setBoundsRelative(0.08f, 0.05f, 0.9f, 0.94f);
	}

private:
	ScopedPointer<TableListBox> accounts;
	ScopedPointer<SuppliersTableListBoxModel> suppliersTableListBoxModel;
};

//=======================================================================================================
class CustomTabbedButtonBar :	public Component,
								public ChangeBroadcaster,
								public ButtonListener
{
public:
	CustomTabbedButtonBar() : index(5) {
		customers = new CustomMenuBarButton(CustomMenuBarButton::CustomersType);
		suppliers = new CustomMenuBarButton(CustomMenuBarButton::SuppliersType);
		accountChart = new CustomMenuBarButton(CustomMenuBarButton::EventsType);
		accounts = new CustomMenuBarButton(CustomMenuBarButton::AccountChartType);
		companies = new CustomMenuBarButton(CustomMenuBarButton::CompaniesType);

		reporting = new CustomMenuBarButton(CustomMenuBarButton::ReportingTabType);
		accounting = new CustomMenuBarButton(CustomMenuBarButton::AccountingTabType);
		logout = new CustomMenuBarButton(CustomMenuBarButton::LogoutType);

		businessModel = new CustomMenuBarButton(CustomMenuBarButton::BusinessModelType);
		businessPlan = new CustomMenuBarButton(CustomMenuBarButton::BusinessPlanType);
		financialRatios = new CustomMenuBarButton(CustomMenuBarButton::FinancialRatiosType);
		openSourceInnovation = new CustomMenuBarButton(CustomMenuBarButton::OpenSourceInnovationType);
		reportGenerator = new CustomMenuBarButton(CustomMenuBarButton::ReportGeneratorTytpe);

		customers->addListener(this);
		suppliers->addListener(this);
		accountChart->addListener(this);
		accounts->addListener(this);
		companies->addListener(this);
		reporting->addListener(this);
		accounting->addListener(this);
		logout->addListener(this);
		businessModel->addListener(this);
		businessPlan->addListener(this);
		financialRatios->addListener(this);
		openSourceInnovation->addListener(this);
		reportGenerator->addListener(this);

		addAndMakeVisible(customers);
		addAndMakeVisible(suppliers);
		addAndMakeVisible(accountChart);
		addAndMakeVisible(accounts);
		addAndMakeVisible(companies);
		addAndMakeVisible(reporting);
		addAndMakeVisible(accounting);
		addAndMakeVisible(companies);
		addAndMakeVisible(logout);
		addChildComponent(businessModel);
		addChildComponent(businessPlan);
		addChildComponent(financialRatios);
		addChildComponent(openSourceInnovation);
		addChildComponent(reportGenerator);
	}

	~CustomTabbedButtonBar() {
		reporting = nullptr;
		accounting = nullptr;
		customers = nullptr;
		suppliers = nullptr;
		accountChart = nullptr;
		accounts = nullptr;
		companies = nullptr;
		logout = nullptr;
		businessModel = nullptr;
		businessPlan = nullptr;
		financialRatios = nullptr;
		openSourceInnovation = nullptr;
		reportGenerator = nullptr;
	}

	void paint(Graphics &g) override {
		Path rect = Theme::createRectPath(0, 0, getWidth(), getHeight(), 0, 0, 10);

		g.setColour(Colours::grey);
		g.fillPath(rect);
	}

	void resized() override {
		customers->setBounds(0, 67, getWidth(), 75);
		suppliers->setBounds(0, 167, getWidth(), 75);
		accountChart->setBounds(0, 267, getWidth(), 75);
		accounts->setBounds(0, 367, getWidth(), 75);
		companies->setBounds(0, 467, getWidth(), 75);

		businessModel->setBounds(0, 67, getWidth(), 75);
		businessPlan->setBounds(0, 167, getWidth(), 75);
		financialRatios->setBounds(0, 267, getWidth(), 75);
		openSourceInnovation->setBounds(0, 367, getWidth(), 75);
		reportGenerator->setBounds(0, 467, getWidth(), 75);

		reporting->setBounds(54, 0, 66, 28);
		accounting->setBounds(0, 0, 66, 28);

		logout->setBounds(0, getHeight()-34, 120, 34);
	}

	int getCurrentTabIndex() const {
		return index;
	}

	void buttonClicked(Button* buttonThatWasClicked) {
		if (buttonThatWasClicked == reporting) {
			customers->setVisible(false);
			suppliers->setVisible(false);
			accountChart->setVisible(false);
			accounts->setVisible(false);
			companies->setVisible(false);

			businessModel->setVisible(true);
			businessPlan->setVisible(true);
			financialRatios->setVisible(true);
			openSourceInnovation->setVisible(true);
			reportGenerator->setVisible(true);
		}
		else if (buttonThatWasClicked == accounting) {
			customers->setVisible(true);
			suppliers->setVisible(true);
			accountChart->setVisible(true);
			accounts->setVisible(true);
			companies->setVisible(true);

			businessModel->setVisible(false);
			businessPlan->setVisible(false);
			financialRatios->setVisible(false);
			openSourceInnovation->setVisible(false);
			reportGenerator->setVisible(false);
		}
		else if (buttonThatWasClicked == customers) {
			index = 1;
		}
		else if (buttonThatWasClicked == suppliers) {
			index = 2;
		}
		else if (buttonThatWasClicked == accountChart) {
			index = 3;
		}
		else if (buttonThatWasClicked == accounts) {
			index = 4;
		}
		else if (buttonThatWasClicked == companies) {
			index = 4;
		}
		else if (buttonThatWasClicked == businessModel) {
			index = 6;
		}
		else if (buttonThatWasClicked == businessPlan) {
			index = 7;
		}
		else if (buttonThatWasClicked == financialRatios) {
			index = 8;
		}
		else if (buttonThatWasClicked == openSourceInnovation) {
			index = 9;
		}
		else if (buttonThatWasClicked == reportGenerator) {
			index = 10;
		}
		else if (buttonThatWasClicked == logout) {
			index = 6;
		}
		else {
			index = 5;
		}
		sendChangeMessage();
	}

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

class CustomTabComponent :	public Component,
							public ChangeListener,
							public Timer
{
public:
	CustomTabComponent() {
		setWantsKeyboardFocus(false);
		search = new TextEditor();
		search->setFont(Font(22));
		search->setTextToShowWhenEmpty(L"Enter Search Keyword", Colours::black.withAlpha(0.5f));

		accountChartComponent = new AccountChartComponent();
		accountsComponent = new AccountsComponent();
		suppliersComponent = new SuppliersComponent();
		customersComponent = new CustomersComponent();

		tabButtons = new CustomTabbedButtonBar();
		tabButtons->addChangeListener(this);
		tabButtons->sendChangeMessage();

		addChildComponent(accountChartComponent);
		addChildComponent(accountsComponent);
		addChildComponent(suppliersComponent);
		addChildComponent(customersComponent);

		addAndMakeVisible(search);
		addAndMakeVisible(tabButtons);

		startTimer(100);
	}

	~CustomTabComponent() {
		search = nullptr;
		accountChartComponent = nullptr;
		accountsComponent = nullptr;
		suppliersComponent = nullptr;
		customersComponent = nullptr;
	}

	void resized() override {
		const float width = getWidth();
		const float height = getHeight();
		search->setBoundsRelative(0.5f - 0.125f, 0.01, 0.25f, 0.05f);
		accountChartComponent->setBoundsRelative(0.05f, 0.05f, 0.9f, 0.94f);
		accountsComponent->setBoundsRelative(0.05f, 0.05f, 0.9f, 0.94f);
		suppliersComponent->setBoundsRelative(0.05f, 0.05f, 0.9f, 0.94f);
		customersComponent->setBoundsRelative(0.05f, 0.05f, 0.9f, 0.94f);
		tabButtons->setBounds(0, 0.12f*getHeight(), 120, 575);
	}

	void timerCallback() override {
		ComponentAnimator &an = Desktop::getInstance().getAnimator();
		Rectangle<int> finalBoundsVisible = Rectangle<int>(0, tabButtons->getY(), tabButtons->getWidth(), tabButtons->getHeight());
		Rectangle<int> finalBoundsHidden = Rectangle<int>(-tabButtons->getWidth(), tabButtons->getY(), tabButtons->getWidth(), tabButtons->getHeight());

		if (getMouseXYRelative().getY() > 0 && getMouseXYRelative().getX() > 0 && getMouseXYRelative().getX() < tabButtons->getWidth()*0.8f && tabButtons->getX() < 0 && an.getComponentDestination(tabButtons) == finalBoundsHidden) {
			an.cancelAnimation(tabButtons, false);
			an.animateComponent(tabButtons, finalBoundsVisible, 1.0f, 400, false, 0.0f, 1.0f);
		}
		else if ((getMouseXYRelative().getY() < 0 || ( getMouseXYRelative().getX() > 0 && getMouseXYRelative().getX() > tabButtons->getWidth() )) && tabButtons->getX() == 0) {
			an.cancelAnimation(tabButtons, false);
			an.animateComponent(tabButtons, finalBoundsHidden, 1.0f, 400, false, 0.0f, 1.0f);
		}
	}

	void changeListenerCallback(ChangeBroadcaster *source)
	{
		if (source == tabButtons) {
			switch (tabButtons->getCurrentTabIndex()) {
			case 0:
				accountChartComponent->setVisible(false);
				accountsComponent->setVisible(false);
				suppliersComponent->setVisible(false);
				customersComponent->setVisible(false);
				break;
			case 1:
				accountChartComponent->setVisible(false);
				accountsComponent->setVisible(false);
				suppliersComponent->setVisible(false);
				customersComponent->setVisible(false);
				break;
			case 2:
				accountChartComponent->setVisible(false);
				accountsComponent->setVisible(false);
				suppliersComponent->setVisible(false);
				customersComponent->setVisible(true);
				break;
			case 3:
				accountChartComponent->setVisible(false);
				accountsComponent->setVisible(false);
				suppliersComponent->setVisible(true);
				customersComponent->setVisible(false);
				break;
			case 4:
				accountChartComponent->setVisible(true);
				accountsComponent->setVisible(false);
				suppliersComponent->setVisible(false);
				customersComponent->setVisible(false);
				break;
			case 5:
				accountChartComponent->setVisible(false);
				accountsComponent->setVisible(true);
				suppliersComponent->setVisible(false);
				customersComponent->setVisible(false);
				break;

			default:
				break;
			}
		}
	}

private:
	ScopedPointer<TextEditor> search;
	ScopedPointer<AccountChartComponent> accountChartComponent;
	ScopedPointer<AccountsComponent> accountsComponent;
	ScopedPointer<SuppliersComponent> suppliersComponent;
	ScopedPointer<CustomersComponent> customersComponent;

	ScopedPointer<CustomTabbedButtonBar> tabButtons;
};

//==============================================================================
MainComponent::MainComponent ()
{
	setWantsKeyboardFocus(true);
	LookAndFeel::setDefaultLookAndFeel(&theme);

	addAndMakeVisible (tabs = new CoeusTabbedComponent());
	tabs->setTabBarDepth(50);
 
	tc = new ThemeComponent(*this);
	tc->setOpaque(true);
	tc->addToDesktop(ComponentPeer::StyleFlags::windowHasCloseButton | ComponentPeer::StyleFlags::windowIsResizable | ComponentPeer::StyleFlags::windowHasTitleBar);
	tc->centreWithSize(800, 600);
	tc->setVisible(false);

	//[UserPreSize]
    //[/UserPreSize]

	commandManager.registerAllCommandsForTarget(this);
	commandManager.getKeyMappings()->addKeyPress(CoeusCommandIDs::NewTab, KeyPress('t', ModifierKeys::commandModifier, juce_wchar('t')));
	commandManager.getKeyMappings()->addKeyPress(CoeusCommandIDs::CloseTab, KeyPress('w', ModifierKeys::commandModifier, juce_wchar('w')));
	commandManager.getKeyMappings()->addKeyPress(CoeusCommandIDs::OpenThemeSettingsDialog, KeyPress('e', ModifierKeys::commandModifier, juce_wchar('e')));
	addKeyListener(commandManager.getKeyMappings());
	
	commandManager.setFirstCommandTarget(this);

	commandManager.invokeDirectly(CoeusCommandIDs::NewTab, true);

	this->setBoundsRelative(0.0f, 0.0f, 1.0f, 1.0f);

    //[Constructor] You can add your own custom stuff here..


    //[/Constructor]
}

MainComponent::~MainComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

	tabs = nullptr;

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
	tabs->setBoundsRelative(0.0f, 0.0f, 1.0f, 1.0f);

	//[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]


    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]

ApplicationCommandTarget * MainComponent::getNextCommandTarget()
{
	return findFirstTargetParentComponent();
}

void MainComponent::getAllCommands(Array< CommandID > &commands)
{
	// this returns the set of all commands that this target can perform.. 
	const CommandID ids[] = { CoeusCommandIDs::ConnectToServerDialog,
		CoeusCommandIDs::SelectCompanyDialog,
		CoeusCommandIDs::SyncWithServer,
		CoeusCommandIDs::NewTab,
		CoeusCommandIDs::CloseTab,
		CoeusCommandIDs::QuitProgram,
		CoeusCommandIDs::OpenThemeSettingsDialog
	};
	commands.addArray(ids, numElementsInArray(ids));
}

void MainComponent::getCommandInfo(CommandID commandID, ApplicationCommandInfo &result)
{
	const String generalCategory("General");
	switch (commandID)
	{
	case CoeusCommandIDs::ConnectToServerDialog :
		result.setInfo("Connet to server", "Connet to server", generalCategory, 0);
//		result.addDefaultKeypress('C', ModifierKeys::commandModifier);
		break;
	case CoeusCommandIDs::SelectCompanyDialog:
		result.setInfo("Select Company", "Select Company", generalCategory, 0);
		result.addDefaultKeypress('o', ModifierKeys::commandModifier);
		break;
	case CoeusCommandIDs::SyncWithServer:
		result.setInfo("Sync with server", "Sync with server", generalCategory, 0);
		result.addDefaultKeypress('s', ModifierKeys::commandModifier);
		break;
	case CoeusCommandIDs::NewTab:
		result.setInfo("Open a new Tab", "Open a new Tab", generalCategory, 0);
		result.addDefaultKeypress('t', ModifierKeys::commandModifier);
		break;
	case CoeusCommandIDs::CloseTab:
		result.setInfo("Close Current Tab", "Close Current Tab", generalCategory, 0);
		result.addDefaultKeypress('w', ModifierKeys::commandModifier);
		break;
	case CoeusCommandIDs::QuitProgram:
		result.setInfo("Quit App", "Quit App", generalCategory, 0);
//		result.addDefaultKeypress('q', ModifierKeys::commandModifier);
		break;
	case CoeusCommandIDs::OpenThemeSettingsDialog:
		result.setInfo("Theme settings", "Theme settings", generalCategory, 0);
		//		result.addDefaultKeypress('q', ModifierKeys::commandModifier);
		break;
	default:
		break;
	};
}

bool MainComponent::perform(const InvocationInfo &info)
{

	switch (info.commandID)
	{
	case CoeusCommandIDs::ConnectToServerDialog: {
		break;
	}
	case CoeusCommandIDs::SelectCompanyDialog: {
		break;
	}
	case CoeusCommandIDs::SyncWithServer: {
		break;
	}
	case CoeusCommandIDs::NewTab: {
		Component *comp = new CustomTabComponent();
		tabs->addTab(String("Main"), Colours::beige, comp, true);
		break;
	}
	case CoeusCommandIDs::CloseTab: {
		tabs->removeTab(tabs->getCurrentTabIndex());
		break;
	}
	case CoeusCommandIDs::QuitProgram: {
		 break;
	}
	case CoeusCommandIDs::OpenThemeSettingsDialog: {
		tc->setVisible(true);
		tc->toFront(true);
		tc->grabKeyboardFocus();
		break;
	}
	default:
		break;
	};

	return true;
}


//==============================================================================



//[EndFile] You can add extra defines here...Transform
//[/EndFile]
