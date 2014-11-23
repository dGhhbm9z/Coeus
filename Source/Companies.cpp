#include "Companies.h"
#include "CustomComponents.h"

class CompaniesRowComponent :   public CoeusListRowComponent
{
public:
    static const int minRowSize = 40;
    static const int maxRowSize = 480;
    const int lm = 4;
    const int tm = 2;
    const int bm = 2;
    const int pad = 4;
    const int teHS = getMinRowSize() - tm - bm;
    const int teWS = 250;
    
    CompaniesRowComponent(CoeusList &owner_) : CoeusListRowComponent(owner_) {
        detailedView = false;
        editView = false;
        showControls = false;

        // add fields
        // summary
        addAndMakeVisible(companyNameTE = new TextEditor("CompanyName"));
        addAndMakeVisible(legalIncTE = new TextEditor("LegalInc"));
        addAndMakeVisible(telephoneTE = new TextEditor("Telephone"));
        addAndMakeVisible(activityTE = new TextEditor("Activity"));
        companyNameTE->addListener(&owner);
        legalIncTE->addListener(&owner);
        telephoneTE->addListener(&owner);
        activityTE->addListener(&owner);
        
        // summary labels
        addAndMakeVisible(companyName = new Label("Company Name", "Company Name"));
        addAndMakeVisible(legalInc = new Label("Inc", "Inc"));
        addAndMakeVisible(telephone = new Label("Telephone", "Telephone"));
        addAndMakeVisible(activity = new Label("Activity", "Activity"));

        // detailed view
        addAndMakeVisible(VATTE = new TextEditor("VAT"));
        addAndMakeVisible(IRSTE = new TextEditor("IRS"));
        addAndMakeVisible(AddressTE = new TextEditor("Address"));
        addAndMakeVisible(AddressNumberTE = new TextEditor("AddressNumber"));
        addAndMakeVisible(PersonInChargeTE = new TextEditor("PersonInCharge"));
        addAndMakeVisible(StartDateTE = new TextEditor("StartDate"));
        addAndMakeVisible(CommentsTE = new TextEditor("Comments"));
        VATTE->addListener(&owner);
        IRSTE->addListener(&owner);
        AddressTE->addListener(&owner);
        AddressNumberTE->addListener(&owner);
        PersonInChargeTE->addListener(&owner);
        StartDateTE->addListener(&owner);
        CommentsTE->addListener(&owner);

        // detailed view labels
        addAndMakeVisible(VAT = new Label("VAT", "VAT"));
        addAndMakeVisible(IRS = new Label("IRS", "IRS"));
        addAndMakeVisible(Address = new Label("Address", "Address"));
        addAndMakeVisible(AddressNumber = new Label("Address Number", "Address Number"));
        addAndMakeVisible(PersonInCharge = new Label("Owner/CEO", "Owner/CEO"));
        addAndMakeVisible(StartDate = new Label("Start date", "Start date"));
        addAndMakeVisible(Comments = new Label("Comments", "Comments"));

        resized();
    }

    ~CompaniesRowComponent() {
    }

    void setEdit(bool ed) {
        companyNameTE->setEnabled(ed);
        legalIncTE->setEnabled(ed);
        telephoneTE->setEnabled(ed);
        activityTE->setEnabled(ed);
        
        VATTE->setEnabled(ed);
        IRSTE->setEnabled(ed);
        AddressTE->setEnabled(ed);
        AddressNumberTE->setEnabled(ed);
        PersonInChargeTE->setEnabled(ed);
        StartDateTE->setEnabled(ed);
        CommentsTE->setEnabled(ed);
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
        companyNameTE->setBounds(lm+teWS+pad, tm+teHS, teWS, teHS);
        legalIncTE->setBounds(lm+teWS+pad, tm+2*teHS, teWS, teHS);
        telephoneTE->setBounds(lm+teWS+pad, tm+3*teHS, 150, teHS);
        activityTE->setBounds(lm+teWS+pad, tm+4*teHS, teWS, teHS);
        // summary labels
        companyName->setBounds(lm, tm+teHS, teWS, teHS);
        legalInc->setBounds(lm, tm+2*teHS, teWS, teHS);
        telephone->setBounds(lm, tm+3*teHS, teWS, teHS);
        activity->setBounds(lm, tm+4*teHS, teWS, teHS);
        // detailed view
        VATTE->setBounds(lm+teWS+pad, tm+5*teHS, teWS, teHS);
        IRSTE->setBounds(lm+teWS+pad, tm+6*teHS, teWS, teHS);
        AddressTE->setBounds(lm+teWS+pad, tm+7*teHS, teWS, teHS);
        AddressNumberTE->setBounds(lm+teWS+pad, tm+8*teHS, teWS, teHS);
        PersonInChargeTE->setBounds(lm+teWS+pad, tm+9*teHS, teWS, teHS);
        StartDateTE->setBounds(lm+teWS+pad, tm+10*teHS, teWS, teHS);
        CommentsTE->setBounds(lm+teWS+pad, tm+11*teHS, teWS, teHS);
        // detailed view labels
        VAT->setBounds(lm, tm+5*teHS, teWS, teHS);
        IRS->setBounds(lm, tm+6*teHS, teWS, teHS);
        Address->setBounds(lm, tm+7*teHS, teWS, teHS);
        AddressNumber->setBounds(lm, tm+8*teHS, teWS, teHS);
        PersonInCharge->setBounds(lm, tm+9*teHS, teWS, teHS);
        StartDate->setBounds(lm, tm+10*teHS, teWS, teHS);
        Comments->setBounds(lm, tm+11*teHS, teWS, teHS);
    }
    
    int fieldNameToIndex(String fname) const override {
        if (fname.equalsIgnoreCase("CompanyName")) {
            return 0;
        }
        else if (fname.equalsIgnoreCase("LegalInc")) {
            return 1;
        }
        else if (fname.equalsIgnoreCase("Telephone")) {
            return 2;
        }
        else if (fname.equalsIgnoreCase("Activity")) {
            return 3;
        }
        else if (fname.equalsIgnoreCase("VAT")) {
            return 4;
        }
        else if (fname.equalsIgnoreCase("IRS")) {
            return 5;
        }
        else if (fname.equalsIgnoreCase("Address")) {
            return 6;
        }
        else if (fname.equalsIgnoreCase("AddressNumber")) {
            return 7;
        }
        else if (fname.equalsIgnoreCase("PersonInCharge")) {
            return 8;
        }
        else if (fname.equalsIgnoreCase("StartDate")) {
            return 9;
        }
        else if (fname.equalsIgnoreCase("Comments")) {
            return 10;
        }
        
        return 0;
    }
    
    void updateRow() {
        
    }
    
    void insertRow() {
        
    }
    
private:
    // summary
    ScopedPointer<TextEditor> companyNameTE, legalIncTE, telephoneTE, activityTE;
    ScopedPointer<Label> companyName, legalInc, telephone, activity;

    // detailed
    ScopedPointer<TextEditor> VATTE, IRSTE, AddressTE, AddressNumberTE, PersonInChargeTE, StartDateTE, CommentsTE;
    ScopedPointer<Label> VAT, IRS, Address, AddressNumber, PersonInCharge, StartDate, Comments;
};

//================================================================================

CompaniesTableListBoxModel::CompaniesTableListBoxModel()
{
    update();
    rowSizes.calloc(1); //hack +1
}

Array<int> CompaniesTableListBoxModel::getKeyField()
{
    Array<int> kf;
    kf.add(0);
    return kf;
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
    else if (getNumRows() && (rowSizes[rowNumber] == CompaniesRowComponent::maxRowSize)) {
        g.setColour(Colours::lightgrey.brighter().brighter().brighter());
        g.fillRect(x, y, width, height);
    }
}

CoeusListRowComponent * CompaniesTableListBoxModel::refreshComponentForRow(int rowNumber, bool isRowSelected, CoeusListRowComponent *existingComponentToUpdate)
{
	// create
	if (existingComponentToUpdate == nullptr) {
        CompaniesRowComponent *newComp = new CompaniesRowComponent(*this);
        newComp->addMouseListener(this, true);
        newComp->addChangeListener(this);
        newComp->setRow(rowNumber);

        const bool dView = (rowNumber < getNumRows()) ? rowSizes[rowNumber] == CompaniesRowComponent::maxRowSize : false;
        const StringArray keys = (qe != nullptr) ? qe->getFieldFromRow(rowNumber, getKeyField()) : StringArray();
        if (keys.size() && (rowsToUpdate.find(keys) != rowsToUpdate.end())) {
            newComp->updateFromMapForRow(qe, rowsToUpdate[keys], rowNumber, dView, edit);
        }
        else {
            newComp->updateFromQueryForRow(qe, rowNumber,  dView, edit);
        }
        newComp->shouldShowControls(isRowSelected || rowUnderMouse == rowNumber);

        return newComp;
	}
	// update
	else {
        CompaniesRowComponent * cmp = dynamic_cast<CompaniesRowComponent *>(existingComponentToUpdate);

        if(cmp) {
            const bool dView = (rowNumber < getNumRows()) ? rowSizes[rowNumber] == CompaniesRowComponent::maxRowSize : false;
            const StringArray keys = (qe != nullptr) ? qe->getFieldFromRow(rowNumber, getKeyField()) : StringArray();
            if (keys.size() && (rowsToUpdate.find(keys) != rowsToUpdate.end())) {
                cmp->updateFromMapForRow(qe, rowsToUpdate[keys], rowNumber, dView, edit);
            }
            else {
                cmp->updateFromQueryForRow(qe, rowNumber,  dView, edit);
            }
            cmp->shouldShowControls(isRowSelected || rowUnderMouse == rowNumber);
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
    companiesTableListBoxModel->addChangeListener(this);

    tableHeader1->setText("Company Name", dontSendNotification);
    tableHeader2->setText("Legan Inc.", dontSendNotification);
    tableHeader3->setText("Contact", dontSendNotification);
    tableHeader4->setText("Activity", dontSendNotification);
    
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
    if (qe_->num_fields > 1) {
        qe = qe_;
        companiesTableListBoxModel->setQueryEntry(qe);
        companiesTableListBoxModel->update();
    }
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

	String queryStr = "SELECT * FROM companies WHERE ";

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

void CompaniesComponent::addButtonPressed()
{
    // show add overlay
}

void CompaniesComponent::editButtonPressed()
{
//    if (!editButton->getToggleState()) {
//        //
//        StringArray pkNames;
//        pkNames.add("VAT");
//
//        companiesTableListBoxModel->updateDatabaseTable("companies", pkNames, this);
//
//    }
//
//    companiesTableListBoxModel->update();
}

void CompaniesComponent::changeListenerCallback(ChangeBroadcaster *source)
{
    CoeusList *src = dynamic_cast<CoeusList*>(source);
    if(src && !src->getWantsHeader()) {
        tableHeader1->setVisible(false);
        tableHeader2->setVisible(false);
        tableHeader3->setVisible(false);
        tableHeader4->setVisible(false);
    }
    else {
        tableHeader1->setVisible(true);
        tableHeader2->setVisible(true);
        tableHeader3->setVisible(true);
        tableHeader4->setVisible(true);
    }
}
