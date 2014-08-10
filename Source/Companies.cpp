#include "Companies.h"
#include "CustomComponents.h"
#include "Accounts.h"

CompaniesTableListBoxModel::CompaniesTableListBoxModel() : qe(nullptr), rowUnderMouse(-1) {}

int CompaniesTableListBoxModel::getNumRows()
{
	if (qe != nullptr) {
		return qe->num_rows;
	}
	else {
		return 0;
	}
}

void CompaniesTableListBoxModel::paintRowBackground(Graphics &g, int rowNumber, int width, int height, bool rowIsSelected)
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

void CompaniesTableListBoxModel::paintRow(Graphics &g, int rowNumber, int width, int height, bool rowIsSelected)
{
}

Component * CompaniesTableListBoxModel::refreshComponentForRow(int rowNumber, bool isRowSelected, Component *existingComponentToUpdate)
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

void CompaniesTableListBoxModel::setQueryEntry(QueryEntry *qe_)
{
	qe = qe_;
}

void CompaniesTableListBoxModel::changeListenerCallback(ChangeBroadcaster *source)
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

void CompaniesTableListBoxModel::mouseMove(const MouseEvent &event)
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

void CompaniesTableListBoxModel::mouseExit(const MouseEvent &event)
{
	const int prevR = rowUnderMouse;
	rowUnderMouse = -1;
	repaintRow(rowUnderMouse);
	repaintRow(prevR);
}

//================================================================================

CompaniesComponent::CompaniesComponent()
{
	title->setText("Suppliers", dontSendNotification);

	TableHeaderComponent *accountsHeaderComponent = new TableHeaderComponent();
	accountsHeaderComponent->addColumn(L"Companies1", 1, 250, 100, 250);
	accountsHeaderComponent->addColumn(L"Companies1", 2, 250, 100, 250);
	accountsHeaderComponent->addColumn(L"Companies1", 3, 150, 100, 250);
	accountsHeaderComponent->addColumn(L"Companies1", 4, 250, 100, 250);
	accountsHeaderComponent->addColumn(String::empty, 5, 200, 100, 250);

	companiesTableListBoxModel = new CompaniesTableListBoxModel();
	companiesTableListBoxModel->setRowHeight(40);
	companiesTableListBoxModel->setHeader(accountsHeaderComponent);
	companiesTableListBoxModel->setHeaderHeight(40);

	addAndMakeVisible(companiesTableListBoxModel);

	//searchButtonPressed();
}

CompaniesComponent::~CompaniesComponent()
{
	companiesTableListBoxModel = nullptr;
}

void CompaniesComponent::resized()
{
	CustomTabContent::resized();
	companiesTableListBoxModel->setBounds(getComponentArea());
}

void CompaniesComponent::receivedResults(QueryEntry *qe_)
{
	qe = qe_;
	companiesTableListBoxModel->setQueryEntry(qe);
	companiesTableListBoxModel->updateContent();
}

void CompaniesComponent::mouseExit(const MouseEvent &event)
{
	companiesTableListBoxModel->mouseExit(event);
}

void CompaniesComponent::searchButtonPressed()
{
	String andOr = (searchFilter->getSelectedId() == 2) ? " AND " : " OR ";
	String orStr = " OR ";
	StringArray terms;
	terms.addTokens(search->getText(), true);

	String queryStr = "SELECT CompanyName, LegalInc, Telephone, Activity FROM companies WHERE ";

	for (int i = 0; i < terms.size(); i++) {
		queryStr += "VAT like '%" + terms[i] + "%' " + orStr;
		queryStr += "IRS like '%" + terms[i] + "%' " + orStr;
		queryStr += "CompanyName like '%" + terms[i] + "%' " + orStr;
		queryStr += "LegalInc like '%" + terms[i] + "%' " + orStr;
		queryStr += "Address like '%" + terms[i] + "%' " + orStr;
		queryStr += "DateOfBirth like '%" + terms[i] + "%' " + orStr;
		queryStr += "AddressNumber like '%" + terms[i] + "%' " + orStr;
		queryStr += "PersonInCharge like '%" + terms[i] + "%' " + orStr;

		queryStr += "Telephone like '%" + terms[i] + "%' " + orStr;
		queryStr += "Activity like '%" + terms[i] + "%' " + orStr;
		queryStr += "StartDate like '%" + terms[i] + "%' " + orStr;
		queryStr += "Faxnumber like '%" + terms[i] + "%' " + orStr;
		queryStr += "Email like '%" + terms[i] + "%' " + orStr;

		queryStr += "Comments like '%" + terms[i] + "%' " + andOr;
	}

	queryStr += (searchFilter->getSelectedId() == 2 || terms.size() == 0) ? " 1 = 1" : " 1 = 0";

	//		CompanyVAT varchar(10) NOT NULL,

	CacheSystem *cs = CacheSystem::getInstance();
	cs->getResultsFor(queryStr, this);

	std::cout << queryStr << std::endl;
}