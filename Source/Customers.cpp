#include "Customers.h"
#include "CustomComponents.h"
#include "Accounts.h"

int CustomersTableListBoxModel::getNumRows()
{
	return 8;
}

void CustomersTableListBoxModel::paintRowBackground(Graphics &g, int rowNumber, int width, int height, bool rowIsSelected) 
{
	if (rowIsSelected) {
		g.setColour(Colours::grey.brighter().brighter());
		g.fillAll();
	}
}

void CustomersTableListBoxModel::paintCell(Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
	if (columnId == 4) {
		g.setColour(Colours::black);
		g.drawText(L"133", 0, 0, width, height, Justification::centred, false);
	}
}

Component * CustomersTableListBoxModel::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate)
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


//================================================================

CustomersComponent::CustomersComponent()
{
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

CustomersComponent::~CustomersComponent() 
{
	customers = nullptr;
}

void CustomersComponent::resized() 
{
	CustomTabContent::resized();
	customers->setBounds(getComponentArea());
}