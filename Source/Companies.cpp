#include "Companies.h"
#include "CustomComponents.h"
#include "Accounts.h"

CompaniesTableListBoxModel::CompaniesTableListBoxModel() : qe(nullptr), rowUnderMouse(-1)
{
    update();
}

void CompaniesTableListBoxModel::paint(Graphics &g)
{
}

int CompaniesTableListBoxModel::getNumRows()
{
	if (qe != nullptr) {
		return qe->num_rows;
	}
	else {
		return 0;
	}
}

int CompaniesTableListBoxModel::getMinRowSize()
{
    //TODO: impl
    return 20;
}

int CompaniesTableListBoxModel::getMaxRowSize()
{
    //TODO: impl
    return 100;
}

int CompaniesTableListBoxModel::getRowSize(int rowNumber)
{
    //TODO: impl
    if(clickedRows.contains(rowNumber)) {
        return 120;
    }

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
    //TODO: impl
	// create
	if (existingComponentToUpdate == nullptr) {
        Label *newComp = new Label(String(rowNumber), String(rowNumber));
        newComp->addMouseListener(this, true);
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
}

void CompaniesTableListBoxModel::mouseDown (const MouseEvent &event)
{
    Label *lbl = dynamic_cast<Label*>(event.eventComponent);
    if(lbl) {
        int row = lbl->getText().getIntValue();
        if (row >= 0 && row < getNumRows()) {
            if(clickedRows.contains(row)) {
                clickedRows.removeAllInstancesOf(row);
            }
            else {
                clickedRows.add(row);
            }
            rowChangedSize(row, getRowSize(row));
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
	companiesTableListBoxModel = new CompaniesTableListBoxModel();
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
		queryStr += "AddressNumber like '%" + terms[i] + "%' " + orStr;
		queryStr += "PersonInCharge like '%" + terms[i] + "%' " + orStr;

		queryStr += "Telephone like '%" + terms[i] + "%' " + orStr;
		queryStr += "Activity like '%" + terms[i] + "%' " + orStr;
		queryStr += "StartDate like '%" + terms[i] + "%' " + orStr;

		queryStr += "Comments like '%" + terms[i] + "%' " + andOr;
	}

	queryStr += (searchFilter->getSelectedId() == 2 || terms.size() == 0) ? " 1 = 1" : " 1 = 0";



	CacheSystem *cs = CacheSystem::getInstance();
    cs->getResultsFor(queryStr, QueryEntry::Companies, this);
    
	std::cout << queryStr << std::endl;
}
