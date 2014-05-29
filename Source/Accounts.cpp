#include "Accounts.h"

AccountCellButtons::AccountCellButtons()
{
	save = new TextButton(L"save");
	restore = new TextButton(L"restore");
	remove = new TextButton(L"remove");
	addAndMakeVisible(save);
	addAndMakeVisible(restore);
	addAndMakeVisible(remove);
}

AccountCellButtons::~AccountCellButtons()
{
	save = nullptr;
	restore = nullptr;
	remove = nullptr;
}

void AccountCellButtons::resized()
{
	save->setBoundsRelative(0.0f, 0.1f, 0.33f, 0.9f);
	restore->setBoundsRelative(0.33f, 0.1f, 0.33f, 0.9f);
	remove->setBoundsRelative(0.66f, 0.1f, 0.33f, 0.9f);
}

//=======================================================================================================


AccountsTableListBoxModel::AccountsTableListBoxModel() : TableListBox(String::empty, this) {}

int AccountsTableListBoxModel::getNumRows()
{
	return 8;
}

void AccountsTableListBoxModel::paintRowBackground(Graphics &g, int rowNumber, int width, int height, bool rowIsSelected)
{
	if (rowIsSelected) {
		g.setColour(Colours::grey.brighter().brighter());
		g.fillAll();
	}
}

void AccountsTableListBoxModel::paintCell(Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
	if (columnId == 4) {
		g.setColour(Colours::black);
		g.drawText(L"133", 0, 0, width, height, Justification::centred, false);
	}
}

Component * AccountsTableListBoxModel::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate)
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
		if (columnId >= 1 && columnId <= 4) {
			MarginComponent *newComponent = dynamic_cast<MarginComponent *>(existingComponentToUpdate);
			if (newComponent) {
				TextEditFocusReport *tefr = dynamic_cast<TextEditFocusReport *>(newComponent->getEnclosedComp());
				if (tefr) {
					tefr->rowIndex = rowNumber;
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

void AccountsTableListBoxModel::changeListenerCallback(ChangeBroadcaster *source)
{
	TextEditFocusReport *tefr = dynamic_cast<TextEditFocusReport *>(source);
	ComboBoxFocusReport *cbfr = dynamic_cast<ComboBoxFocusReport *>(source);

	if (tefr) {
		selectRow(tefr->rowIndex);
	}
	else if (cbfr) {
		selectRow(cbfr->rowIndex);
	}
}

//=======================================================================================================

AccountsComponent::AccountsComponent() {
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

AccountsComponent::~AccountsComponent() 
{
	accounts = nullptr;
}

void AccountsComponent::resized() 
{
	CustomTabContent::resized();
	accounts->setBounds(getComponentArea());
}