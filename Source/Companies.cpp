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
        showControls = false;

        // add fields
        // summary
        addAndMakeVisible(companyNameTE = new CoeusListTextEditor("CompanyName"));
        addAndMakeVisible(legalIncTE = new CoeusListTextEditor("LegalInc"));
        addAndMakeVisible(telephoneTE = new CoeusListTextEditor("Telephone"));
        addAndMakeVisible(activityTE = new CoeusListTextEditor("Activity"));
        companyNameTE->addListener(&owner);
        legalIncTE->addListener(&owner);
        telephoneTE->addListener(&owner);
        activityTE->addListener(&owner);
        
        // summary labels
        addAndMakeVisible(companyName = new CoeusListLabel("Company Name", "Company Name"));
        addAndMakeVisible(legalInc = new CoeusListLabel("Inc", "Inc"));
        addAndMakeVisible(telephone = new CoeusListLabel("Telephone", "Telephone"));
        addAndMakeVisible(activity = new CoeusListLabel("Activity", "Activity"));

        // detailed view
        addAndMakeVisible(VATTE = new CoeusListTextEditor("VAT"));
        addAndMakeVisible(IRSTE = new CoeusListTextEditor("IRS"));
        addAndMakeVisible(AddressTE = new CoeusListTextEditor("Address"));
        addAndMakeVisible(AddressNumberTE = new CoeusListTextEditor("AddressNumber"));
        addAndMakeVisible(PersonInChargeTE = new CoeusListTextEditor("PersonInCharge"));
        addAndMakeVisible(StartDateTE = new CoeusListTextEditor("StartDate"));
        addAndMakeVisible(CommentsTE = new CoeusListTextEditor("Comments"));
        VATTE->addListener(&owner);
        IRSTE->addListener(&owner);
        AddressTE->addListener(&owner);
        AddressNumberTE->addListener(&owner);
        PersonInChargeTE->addListener(&owner);
        StartDateTE->addListener(&owner);
        CommentsTE->addListener(&owner);

        // detailed view labels
        addAndMakeVisible(VAT = new CoeusListLabel("VAT", "VAT"));
        addAndMakeVisible(IRS = new CoeusListLabel("IRS", "IRS"));
        addAndMakeVisible(Address = new CoeusListLabel("Address", "Address"));
        addAndMakeVisible(AddressNumber = new CoeusListLabel("Address Number", "Address Number"));
        addAndMakeVisible(PersonInCharge = new CoeusListLabel("Owner/CEO", "Owner/CEO"));
        addAndMakeVisible(StartDate = new CoeusListLabel("Start date", "Start date"));
        addAndMakeVisible(Comments = new CoeusListLabel("Comments", "Comments"));

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

CompaniesTableListBoxModel::CompaniesTableListBoxModel(CacheSystemClient *ccc_)
: CoeusList(ccc_)
{
    update();
    rowSizes.calloc(1); //hack +1
    
    fieldNames.add("VAT");
    fieldNames.add("IRS");
    fieldNames.add("CompanyName");
    fieldNames.add("LegalInc");
    fieldNames.add("Address");
    fieldNames.add("AddressNumber");
    fieldNames.add("PersonInCharge");
    fieldNames.add("Telephone");
    fieldNames.add("Activity");
    fieldNames.add("StartDate");
    fieldNames.add("Comments");
    
    tableName = "companies";

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
        g.setColour(Colour(0xff9d9d9d));
        g.fillRect(x, y, width, height);
    }
    else if (rowNumber == rowUnderMouse && (rowSizes[rowNumber] != CompaniesRowComponent::maxRowSize)) {
        g.setColour(Colours::lightgrey.brighter().brighter());
        g.fillRect(x, y, width, height);
    }
    else if (getNumRows() && (rowSizes[rowNumber] == CompaniesRowComponent::maxRowSize)) {
        g.setColour(Colour(Colour(0xffbebebe)));
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
            newComp->updateFromMapForRow(qe, rowsToUpdate[keys], rowNumber, dView, editedRows.contains(rowNumber));
        }
        else {
            newComp->updateFromQueryForRow(qe, rowNumber,  dView, editedRows.contains(rowNumber));
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
                cmp->updateFromMapForRow(qe, rowsToUpdate[keys], rowNumber, dView, editedRows.contains(rowNumber));
            }
            else {
                cmp->updateFromQueryForRow(qe, rowNumber,  dView, editedRows.contains(rowNumber));
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
	companiesTableListBoxModel = new CompaniesTableListBoxModel(this);
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
	Rectangle<int> compBounds = getComponentArea();
	compBounds.setHeight(compBounds.getHeight() - bottomDemoImage.getHeight());
	compBounds.setWidth(compBounds.getWidth()*0.8);
	companiesTableListBoxModel->setBounds(compBounds);
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

void CompaniesComponent::saveButtonPressed()
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

CoeusListRowComponent * CompaniesComponent::getAddComponent()
{
    return new CompaniesRowComponent(*companiesTableListBoxModel);
}
