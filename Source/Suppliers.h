#ifndef SuppliersGuard
#define SuppliersGuard

#include "../JuceLibraryCode/JuceHeader.h"
#include "CacheSystem.h"

//=======================================================================================================
class SuppliersTableListBoxModel : public TableListBoxModel
{
public:
	SuppliersTableListBoxModel();

	int getNumRows() override;
	void paintRowBackground(Graphics &g, int rowNumber, int width, int height, bool rowIsSelected) override;
	void paintCell(Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
	Component * refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate) override;
	void setQueryEntry(QueryEntry *qe_);

private:
	QueryEntry *qe;
};

//=======================================================================================================
class SuppliersComponent : public Component,
	public CacheSystemClient
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

		CacheSystem *cs = CacheSystem::getInstance();
		cs->getResultsFor(String(L"SELECT SupplierCode, Name, PhoneNumber, SupplierTransactions FROM suppliers"), this);
	}

	~SuppliersComponent() {
		accounts = nullptr;
	}

	void resized() override {
		accounts->setBounds(0.01f*getWidth(), 0.01f*getHeight(), getWidth() - 0.01f*getWidth(), getHeight() - 0.01f*getHeight());
	}

	void receivedResults(QueryEntry *qe_) override {
		qe = qe_;
		suppliersTableListBoxModel->setQueryEntry(qe);
		accounts->updateContent();
	}

private:
	ScopedPointer<TableListBox> accounts;
	ScopedPointer<SuppliersTableListBoxModel> suppliersTableListBoxModel;
	QueryEntry *qe;
};

#endif