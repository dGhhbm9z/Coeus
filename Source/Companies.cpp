#include "Companies.h"
#include "CustomComponents.h"
#include "Accounts.h"

class CompaniesRowComponent :   public CoeusListRowComponent
{
public:
    static const int minRowSize = 40;
    static const int maxRowSize = 200;
    const int lm = 4;
    const int tm = 2;
    const int bm = 2;
    const int pad = 4;
    const int teHS = getMinRowSize() - tm - bm;
    const int teWS = 250;
    
    CompaniesRowComponent() {
        detailedView = false;
        editView = false;
        showControls = false;

        // add fields
        addAndMakeVisible(companyNameTE = new TextEditor());
        addAndMakeVisible(legalIncTE = new TextEditor());
        addAndMakeVisible(telephoneTE = new TextEditor());
        addAndMakeVisible(activityTE = new TextEditor());
        
        resized();
    }

    ~CompaniesRowComponent() {
    }

    int getCoeusListHeight() override {
        if (detailedView) {
            return maxRowSize;
        }

        return minRowSize;
    }
    
    int getMinRowSize() override {
        return minRowSize;
    }
    
    int getMaxRowSize() override {
        return maxRowSize;
    }
    
    void resizeForSummary() override {
        // summary
        companyNameTE->setBounds(lm, tm, teWS, teHS);
        legalIncTE->setBounds(lm+teWS+pad, tm, teWS, teHS);
        telephoneTE->setBounds(lm+2*(teWS+pad), tm, 150, teHS);
        activityTE->setBounds(lm+2*(teWS+pad)+pad+150, tm, teWS, teHS);
    }
    
    void resizeForDetailed() override {
        // detailed
        companyNameTE->setBounds(lm, tm, teWS, teHS);
        legalIncTE->setBounds(lm+teWS+pad, tm+teHS, teWS, teHS);
        telephoneTE->setBounds(lm+2*(teWS+pad), tm+2*teHS, 150, teHS);
        activityTE->setBounds(lm+2*(teWS+pad)+pad+150, tm+3*teHS, teWS, teHS);
    }

    void updateFromQueryForRow(QueryEntry *qe, int row, bool dView) override {
        setDetailedView(dView);
        resized();
        this->row = row;
        if(qe) {
            // summary
            companyNameTE->setText(qe->getFieldFromRow(row, 0));
            legalIncTE->setText(qe->getFieldFromRow(row, 1));
            telephoneTE->setText(qe->getFieldFromRow(row, 2));
            activityTE->setText(qe->getFieldFromRow(row, 3));
        }
    }
    
    void updateRow() {
        
    }
    
    void insertRow() {
        
    }
    
private:
    // summary
    ScopedPointer<TextEditor> companyNameTE, legalIncTE, telephoneTE, activityTE;

    // detailed
    ScopedPointer<TextEditor> VAT, IRS, Address, AddressNumber, PersonInCharge, StartDate, Comments;
};

//================================================================================

CompaniesTableListBoxModel::CompaniesTableListBoxModel()
{
    update();
    rowSizes.calloc(1); //hack +1
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

int CompaniesTableListBoxModel::getRowSize(int rowNumber)
{
    return (rowNumber >= 0 && rowNumber < getNumRows()) ? rowSizes[rowNumber] : 0;
}

void CompaniesTableListBoxModel::paintRowBackground(Graphics &g, int rowNumber, int x, int y, int width, int height, bool rowIsSelected)
{
	if (rowIsSelected) {
		g.setColour(Colours::grey.brighter().brighter());
        g.fillRect(x, y, width, height);
	}
	else if (rowNumber == rowUnderMouse) {
		g.setColour(Colours::lightgrey.brighter().brighter());
        g.fillRect(x, y, width, height);
	}
}

CoeusListRowComponent * CompaniesTableListBoxModel::refreshComponentForRow(int rowNumber, bool isRowSelected, CoeusListRowComponent *existingComponentToUpdate)
{
	// create
	if (existingComponentToUpdate == nullptr) {
        CompaniesRowComponent *newComp = new CompaniesRowComponent();
        newComp->addMouseListener(this, true);
        newComp->addChangeListener(this);
        newComp->setRow(rowNumber);

        // TODO
        const bool dView = (rowNumber < getNumRows()) ? rowSizes[rowNumber] == CompaniesRowComponent::maxRowSize : false;
        newComp->updateFromQueryForRow(qe, rowNumber,  dView);
        newComp->shouldShowControls(isRowSelected);

		return newComp;
	}
	// update
	else {
        CompaniesRowComponent * cmp = dynamic_cast<CompaniesRowComponent *>(existingComponentToUpdate);

        if(cmp) {
            const bool dView = (rowNumber < getNumRows()) ? rowSizes[rowNumber] == CompaniesRowComponent::maxRowSize : false;
            cmp->updateFromQueryForRow(qe, rowNumber, dView);
            cmp->shouldShowControls(isRowSelected);
        }

		return existingComponentToUpdate;
	}
}

int CompaniesTableListBoxModel::getMinRowSize()
{
    return CompaniesRowComponent::minRowSize;
}

int CompaniesTableListBoxModel::getMaxRowSize()
{
    return CompaniesRowComponent::maxRowSize;
}

//================================================================================

CompaniesComponent::CompaniesComponent()
{
    title->setText("Companies", dontSendNotification);
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

    queryStr += " ORDER BY LegalInc";


	CacheSystem *cs = CacheSystem::getInstance();
    cs->getResultsFor(queryStr, QueryEntry::Companies, this);
    
	std::cout << queryStr << std::endl;
}
