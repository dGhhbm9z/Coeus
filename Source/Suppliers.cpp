#include "Suppliers.h"
#include "CustomComponents.h"
#include "Accounts.h"

SuppliersTableListBoxModel::SuppliersTableListBoxModel() : qe(nullptr) {}

int SuppliersTableListBoxModel::getNumRows()
{
	if (qe != nullptr) {
		return qe->num_rows;
	}
	else {
		return 0;
	}
}

void SuppliersTableListBoxModel::paintRowBackground(Graphics &g, int rowNumber, int width, int height, bool rowIsSelected) 
{
	if (rowIsSelected) {
		g.setColour(Colours::grey.brighter().brighter());
		Rectangle<int> area();
		g.fillAll();
	}
}

void SuppliersTableListBoxModel::paintCell(Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
	if (columnId == 4) {
		g.setColour(Colours::black);

		String msg;
		if (qe != nullptr) {
			msg = qe->getFieldFromRow(rowNumber, columnId - 1);
		}

		g.drawText(msg, 0, 0, width, height, Justification::centred, false);
	}
}

Component * SuppliersTableListBoxModel::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate)
{
	// create
	if (existingComponentToUpdate == nullptr) {
		if (columnId >= 1 && columnId <= 4) {
			TextEditor *payload = new TextEditor();
			payload->setMultiLine(true);
			if (qe != nullptr) {
				payload->setText(qe->getFieldFromRow(rowNumber, columnId - 1));
			}
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
		if (columnId >= 1 && columnId <= 4) {
			MarginComponent *margin = dynamic_cast<MarginComponent *> (existingComponentToUpdate);
			if (margin != nullptr) {
				TextEditor *payload = dynamic_cast<TextEditor *> (margin->getEnclosedComp());
					
				if (qe != nullptr && payload != nullptr) {
					payload->setText(qe->getFieldFromRow(rowNumber, columnId - 1));
				}
			}
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

void SuppliersTableListBoxModel::setQueryEntry(QueryEntry *qe_) 
{
	qe = qe_;
}

//================================================================================

SuppliersComponent::SuppliersComponent()
{
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

	CacheSystem *cs = CacheSystem::getInstance();
	cs->getResultsFor(String(L"SELECT SupplierCode, Name, PhoneNumber, SupplierTransactions FROM suppliers"), this);
}

SuppliersComponent::~SuppliersComponent()
{
	accounts = nullptr;
}

void SuppliersComponent::resized() 
{
	CustomTabContent::resized();
	accounts->setBounds(getComponentArea());
}

void SuppliersComponent::receivedResults(QueryEntry *qe_) 
{
	qe = qe_;
	suppliersTableListBoxModel->setQueryEntry(qe);
	accounts->updateContent();
}