#include "Companies.h"
#include "CustomComponents.h"
#include "Accounts.h"

CompaniesTableListBoxModel::CompaniesTableListBoxModel() : qe(nullptr), rowUnderMouse(-1)
{
    update();
}

void CompaniesTableListBoxModel::paint(Graphics &g)
{
//    g.fillAll(Colours::aquamarine);
}

int CompaniesTableListBoxModel::getNumRows()
{
    // TODO: remove
    return 20;
    
	if (qe != nullptr) {
		return qe->num_rows;
	}
	else {
		return 0;
	}
}

int CompaniesTableListBoxModel::getMinRowSize()
{
    return 20;
}

int CompaniesTableListBoxModel::getMaxRowSize()
{
    return 100;
}

int CompaniesTableListBoxModel::getRowSize(int rowNumber)
{
    return rowNumber < 5 ? 20 : 100;
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
        Label *newComp = new Label(String(rowNumber), String(rowNumber));
        if (rowNumber % 2) {
            newComp->setColour(Label::backgroundColourId, Colours::rosybrown);
        }
        else {
            newComp->setColour(Label::backgroundColourId, Colours::royalblue);
        }
		return newComp;
	}
	// update
	else {
        Label * lbl = dynamic_cast<Label *>(existingComponentToUpdate);
        lbl ? lbl->setText(String(rowNumber), dontSendNotification) ,0:0;
        if (rowNumber % 2) {
            lbl->setColour(Label::backgroundColourId, Colours::rosybrown);
        }
        else {
            lbl->setColour(Label::backgroundColourId, Colours::royalblue);
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
// TODO : remove line below if not used
//	const int x = event.getPosition().getX();
	const int y = event.getPosition().getY();
	const int r = getRowIndexAt(y);
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

//	TableHeaderComponent *accountsHeaderComponent = new TableHeaderComponent();
//	accountsHeaderComponent->addColumn(L"Companies1", 1, 250, 100, 250);
//	accountsHeaderComponent->addColumn(L"Companies1", 2, 250, 100, 250);
//	accountsHeaderComponent->addColumn(L"Companies1", 3, 150, 100, 250);
//	accountsHeaderComponent->addColumn(L"Companies1", 4, 250, 100, 250);
//	accountsHeaderComponent->addColumn(String::empty, 5, 200, 100, 250);

	companiesTableListBoxModel = new CompaniesTableListBoxModel();

// TODO: what to do with the header?
//	companiesTableListBoxModel->setHeader(accountsHeaderComponent);
//	companiesTableListBoxModel->setHeaderHeight(40);

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
	companiesTableListBoxModel->update();
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