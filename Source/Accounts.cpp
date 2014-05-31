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


AccountsTableListBoxModel::AccountsTableListBoxModel() : TableListBox(String::empty, this), qe(nullptr), rowUnderMouse(-1) {}

int AccountsTableListBoxModel::getNumRows()
{
	if (qe != nullptr) {
		return qe->num_rows;
	}
	else {
		return 0;
	}
}

void AccountsTableListBoxModel::paintRowBackground(Graphics &g, int rowNumber, int width, int height, bool rowIsSelected)
{
	if (rowIsSelected) {
		g.setColour(Colours::grey.brighter().brighter());
		g.fillAll();
	}
	else if (rowNumber == rowUnderMouse) {
		g.setColour(Colours::lightgrey.brighter().brighter());
		g.fillAll();
	}
}

void AccountsTableListBoxModel::paintCell(Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{

}

Component * AccountsTableListBoxModel::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate)
{
	// create
	if (existingComponentToUpdate == nullptr) {
		if (columnId == 1) {
			TextEditFocusReport *payload = new TextEditFocusReport();
			payload->rowIndex = rowNumber;
			
			if (qe != nullptr && payload != nullptr) {
				payload->setText(qe->getFieldFromRow(rowNumber, columnId - 1));
			}

			payload->addChangeListener(this);
			MarginComponent *newComponent = new MarginComponent(payload);
			return (Component *)newComponent;
		}
		else if (columnId == 2) {
			TextEditFocusReport *payload = new TextEditFocusReport();
			payload->rowIndex = rowNumber;
			
			if (qe != nullptr && payload != nullptr) {
				payload->setText(qe->getFieldFromRow(rowNumber, columnId - 1));
			}

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
		else if (columnId == 4) {
			LabelFocusReport *payload = new LabelFocusReport();
			payload->rowIndex = rowNumber;

			if (qe != nullptr && payload != nullptr) {
				payload->setText(qe->getFieldFromRow(rowNumber, columnId - 1), dontSendNotification);
			}

			payload->setEditable(false);
			payload->addChangeListener(this);
			payload->setJustificationType(Justification::centred);
			MarginComponent *newComponent = new MarginComponent(payload);
			return (Component *)newComponent;
		}
		else if (columnId == 5 && isRowSelected) {
			AccountCellButtons *newComponent = new AccountCellButtons();
			newComponent->setVisible(true);
			newComponent->rowIndex = rowNumber;
			return (Component *)newComponent;
		}
		else if (columnId == 5 && !isRowSelected) {
			LabelFocusReport *payload = new LabelFocusReport();
			payload->rowIndex = rowNumber;
			payload->setText(String::empty, dontSendNotification);
			payload->setEditable(false);
			payload->addChangeListener(this);
			payload->setJustificationType(Justification::centred);
			MarginComponent *newComponent = new MarginComponent(payload);
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
				ComboBoxFocusReport *cbfr = dynamic_cast<ComboBoxFocusReport *>(newComponent->getEnclosedComp());
				LabelFocusReport *lbfr = dynamic_cast<LabelFocusReport *>(newComponent->getEnclosedComp());
				if (tefr) {
					tefr->rowIndex = rowNumber;
				}
				else if (cbfr) {
					cbfr->rowIndex = rowNumber;
				}
				else if (lbfr) {
					lbfr->rowIndex = rowNumber;
				}
			}
		}
		else if (columnId == 5) {
			AccountCellButtons *acb = dynamic_cast<AccountCellButtons *>(existingComponentToUpdate);
			MarginComponent *newComponent = dynamic_cast<MarginComponent *>(existingComponentToUpdate);
			LabelFocusReport *lbfr = nullptr;
			if (newComponent) {
				lbfr = dynamic_cast<LabelFocusReport *>(newComponent->getEnclosedComp());
			}

			if (acb && isRowSelected) {
				acb->rowIndex = rowNumber;
			}
			else if (lbfr && !isRowSelected) {
				lbfr->rowIndex = rowNumber;
			}
			else if (acb && !isRowSelected) {
				delete existingComponentToUpdate;

				LabelFocusReport *payload = new LabelFocusReport();
				payload->rowIndex = rowNumber;
				payload->setText(String::empty, dontSendNotification);
				payload->setEditable(false);
				payload->addChangeListener(this);
				payload->setJustificationType(Justification::centred);
				MarginComponent *newComponent = new MarginComponent(payload);
				return (Component *)newComponent;
			}
			else if (lbfr && isRowSelected) {
				delete existingComponentToUpdate;

				AccountCellButtons *newComponent = new AccountCellButtons();
				newComponent->rowIndex = rowNumber;
				newComponent->setVisible(true);
				return (Component *)newComponent;
			}
		}

		return existingComponentToUpdate;
	}
}

void AccountsTableListBoxModel::setQueryEntry(QueryEntry *qe_)
{
	qe = qe_;
}

void AccountsTableListBoxModel::changeListenerCallback(ChangeBroadcaster *source)
{
	TextEditFocusReport *tefr = dynamic_cast<TextEditFocusReport *>(source);
	ComboBoxFocusReport *cbfr = dynamic_cast<ComboBoxFocusReport *>(source);
	LabelFocusReport *lbfr = dynamic_cast<LabelFocusReport *>(source);

	if (tefr) {
		if (tefr->focus) {
			selectRow(tefr->rowIndex);
		}
		else {
			const int prevR = rowUnderMouse;
			rowUnderMouse = tefr->rowIndex;
			repaintRow(rowUnderMouse);
			repaintRow(prevR);
		}
	}
	else if (cbfr) {
		if (cbfr->focus) {
			selectRow(cbfr->rowIndex);
		}
		else {
			const int prevR = rowUnderMouse;
			rowUnderMouse = cbfr->rowIndex;
			repaintRow(rowUnderMouse);
			repaintRow(prevR);
		}
	}
	else if (lbfr) {
		if (lbfr->focus) {
			selectRow(lbfr->rowIndex);
		}
		else {
			const int prevR = rowUnderMouse;
			rowUnderMouse = lbfr->rowIndex;
			repaintRow(rowUnderMouse);
			repaintRow(prevR);
		}
	}
}

void AccountsTableListBoxModel::mouseMove(const MouseEvent &event)
{
	const int x = event.getPosition().getX();
	const int y = event.getPosition().getY();
	const int r = getRowContainingPosition(x, y);
	if (r != rowUnderMouse) {
		const int prevR = rowUnderMouse;
		rowUnderMouse = r;
		repaintRow(rowUnderMouse);
		repaintRow(prevR);
	}
}

void AccountsTableListBoxModel::mouseExit(const MouseEvent &event)
{
	const int prevR = rowUnderMouse;
	rowUnderMouse = -1;
	repaintRow(rowUnderMouse);
	repaintRow(prevR);
}

//=======================================================================================================

AccountsComponent::AccountsComponent() {
	title->setText("Accounts", dontSendNotification);

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

	CacheSystem *cs = CacheSystem::getInstance();
	cs->getResultsFor(String(L"SELECT Code, Name, AccountType, XreosPist FROM accounts"), this);
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

void AccountsComponent::mouseExit(const MouseEvent &event)
{
	accounts->mouseExit(event);
}

void AccountsComponent::receivedResults(QueryEntry *qe_)
{
	qe = qe_;
	accounts->setQueryEntry(qe);
	accounts->updateContent();
}