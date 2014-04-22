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


class CustomMenuBarButton : public TextButton
{
public:
	CustomMenuBarButton(String name) : TextButton(name) {}

	void paint(Graphics &g) {
		Path rect = Theme::createRectPath(0, 0, getWidth(), getHeight(), 0, 0, 10);

		if (isMouseButtonDown()) {
			g.setColour(Colour(0xff434343));
		}
		else {
			g.setColour(Colour(0xff2b2b2b));
		}

		g.fillPath(rect);

		LookAndFeel &lnf = getLookAndFeel();
		lnf.drawButtonText(g, *this, this->isMouseOver(), this->isMouseButtonDown());
	}
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
		customers = new TextButton(L"Customers");
		suppliers = new TextButton(L"Suppliers");
		accountChart = new TextButton(L"Account Chart");
		accounts = new TextButton(L"Accounts");
		reporting = new CustomMenuBarButton(L"Reporting");
		accounting = new CustomMenuBarButton(L"Accounting");
		logout = new CustomMenuBarButton(L"Logout");

		customers->addListener(this);
		suppliers->addListener(this);
		accountChart->addListener(this);
		accounts->addListener(this);
		reporting->addListener(this);
		accounting->addListener(this);
		logout->addListener(this);

		customers->setLookAndFeel(&themeAlt);
		suppliers->setLookAndFeel(&themeAlt);
		accountChart->setLookAndFeel(&themeAlt);
		accounts->setLookAndFeel(&themeAlt);


		addAndMakeVisible(customers);
		addAndMakeVisible(suppliers);
		addAndMakeVisible(accountChart);
		addAndMakeVisible(accounts);
		addAndMakeVisible(reporting);
		addAndMakeVisible(accounting);
		addAndMakeVisible(logout);
	}

	~CustomTabbedButtonBar() {
		reporting = nullptr;
		accounting = nullptr;
		customers = nullptr;
		suppliers = nullptr;
		accountChart = nullptr;
		accounts = nullptr;
		logout = nullptr;
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
		reporting->setBounds(54, 0, 66, 28);
		accounting->setBounds(0, 0, 66, 28);
		logout->setBounds(0, getHeight()-34, 120, 34);
	}

	int getCurrentTabIndex() const {
		return index;
	}

	void buttonClicked(Button* buttonThatWasClicked) {
		if (buttonThatWasClicked == reporting) {
			index = 0;
		}
		else if (buttonThatWasClicked == accounting) {
			index = 1;
		}
		else if (buttonThatWasClicked == customers) {
			index = 2;
		}
		else if (buttonThatWasClicked == suppliers) {
			index = 3;
		}
		else if (buttonThatWasClicked == accountChart) {
			index = 4;
		}
		else if (buttonThatWasClicked == accounts) {
			index = 5;
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
	ScopedPointer<TextButton> customers;
	ScopedPointer<TextButton> suppliers;
	ScopedPointer<TextButton> accountChart;
	ScopedPointer<TextButton> accounts;
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
