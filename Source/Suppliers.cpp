#include "Suppliers.h"
#include "CustomComponents.h"
#include "Accounts.h"

SuppliersTableListBoxModel::SuppliersTableListBoxModel() : TableListBox(String::empty, this), qe(nullptr), rowUnderMouse(-1) {}

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
		g.fillAll();
	}
	else if (rowNumber == rowUnderMouse) {
		g.setColour(Colours::lightgrey.brighter().brighter());
		g.fillAll();
	}
}

void SuppliersTableListBoxModel::paintCell(Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
}

Component * SuppliersTableListBoxModel::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate)
{
	// create
	if (existingComponentToUpdate == nullptr) {
		if (columnId >= 1 && columnId <= 4) {
			TextEditFocusReport *payload = new TextEditFocusReport();
			payload->setMultiLine(true);
			payload->rowIndex = rowNumber;
			payload->addChangeListener(this);

			if (qe != nullptr) {
				payload->setText(qe->getFieldFromRow(rowNumber, columnId - 1));
			}

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
			MarginComponent *margin = dynamic_cast<MarginComponent *> (existingComponentToUpdate);
			if (margin != nullptr) {
				TextEditFocusReport *payload = dynamic_cast<TextEditFocusReport *> (margin->getEnclosedComp());

				if (qe != nullptr && payload != nullptr) {
					payload->setText(qe->getFieldFromRow(rowNumber, columnId - 1));
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

void SuppliersTableListBoxModel::setQueryEntry(QueryEntry *qe_) 
{
	qe = qe_;
}

void SuppliersTableListBoxModel::changeListenerCallback(ChangeBroadcaster *source)
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

void SuppliersTableListBoxModel::mouseMove(const MouseEvent &event)
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

void SuppliersTableListBoxModel::mouseExit(const MouseEvent &event)
{
	const int prevR = rowUnderMouse;
	rowUnderMouse = -1;
	repaintRow(rowUnderMouse);
	repaintRow(prevR);
}

//================================================================================

SuppliersComponent::SuppliersComponent()
{
	title->setText("Suppliers", dontSendNotification);

	TableHeaderComponent *accountsHeaderComponent = new TableHeaderComponent();
	accountsHeaderComponent->addColumn(L"Ονοματεπώνυμο προμηθευτή", 1, 250, 100, 250);
	accountsHeaderComponent->addColumn(L"Επωνυμία", 2, 250, 100, 250);
	accountsHeaderComponent->addColumn(L"Τηλέφωνο", 3, 150, 100, 250);
	accountsHeaderComponent->addColumn(L"Υπόλοιπο", 4, 250, 100, 250);
	accountsHeaderComponent->addColumn(String::empty, 5, 200, 100, 250);

	suppliersTableListBoxModel = new SuppliersTableListBoxModel();
	suppliersTableListBoxModel->setRowHeight(40);
	suppliersTableListBoxModel->setHeader(accountsHeaderComponent);
	suppliersTableListBoxModel->setHeaderHeight(40);

	addAndMakeVisible(suppliersTableListBoxModel);

	CacheSystem *cs = CacheSystem::getInstance();
	cs->getResultsFor(String(L"SELECT SupplierCode, Name, PhoneNumber, SupplierTransactions FROM suppliers"), this);
}

SuppliersComponent::~SuppliersComponent()
{
	suppliersTableListBoxModel = nullptr;
}

void SuppliersComponent::resized() 
{
	CustomTabContent::resized();
	suppliersTableListBoxModel->setBounds(getComponentArea());
}

void SuppliersComponent::receivedResults(QueryEntry *qe_) 
{
	qe = qe_;
	suppliersTableListBoxModel->setQueryEntry(qe);
	suppliersTableListBoxModel->updateContent();
}

void SuppliersComponent::mouseExit(const MouseEvent &event)
{
	suppliersTableListBoxModel->mouseExit(event);
}