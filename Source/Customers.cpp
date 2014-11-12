#include "Customers.h"
#include "CustomComponents.h"
#include "Accounts.h"


class CustomersRowComponent :   public CoeusListRowComponent
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

    CustomersRowComponent() {
        detailedView = false;
        editView = false;
        showControls = false;

        // add fields
        // summary
        addAndMakeVisible(companyNameTE = new TextEditor());
        addAndMakeVisible(legalIncTE = new TextEditor());
        addAndMakeVisible(telephoneTE = new TextEditor());
        addAndMakeVisible(activityTE = new TextEditor());

        // summary labels
        addAndMakeVisible(companyName = new Label("Company Name", "Company Name"));
        addAndMakeVisible(legalInc = new Label("Inc", "Inc"));
        addAndMakeVisible(telephone = new Label("Telephone", "Telephone"));
        addAndMakeVisible(activity = new Label("Activity", "Activity"));

        // detailed view
        addAndMakeVisible(VATTE = new TextEditor());
        addAndMakeVisible(IRSTE = new TextEditor());
        addAndMakeVisible(AddressTE = new TextEditor());
        addAndMakeVisible(AddressNumberTE = new TextEditor());
        addAndMakeVisible(PersonInChargeTE = new TextEditor());
        addAndMakeVisible(StartDateTE = new TextEditor());
        addAndMakeVisible(CommentsTE = new TextEditor());

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

    ~CustomersRowComponent() {
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
            // detailed view
            VATTE->setText(qe->getFieldFromRow(row, 4));
            IRSTE->setText(qe->getFieldFromRow(row, 5));
            AddressTE->setText(qe->getFieldFromRow(row, 6));
            AddressNumberTE->setText(qe->getFieldFromRow(row, 7));
            PersonInChargeTE->setText(qe->getFieldFromRow(row, 8));
            StartDateTE->setText(qe->getFieldFromRow(row, 9));
            CommentsTE->setText(qe->getFieldFromRow(row, 10));
        }
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

CustomersTableListBoxModel::CustomersTableListBoxModel()
{
    update();
    rowSizes.calloc(1); //hack +1
}

int CustomersTableListBoxModel::getNumRows()
{
    if (qe != nullptr) {
        return qe->num_rows;
    }
    else {
        return 0;
    }
}

int CustomersTableListBoxModel::getRowSize(int rowNumber)
{
    return (rowNumber >= 0 && rowNumber < getNumRows()) ? rowSizes[rowNumber] : 0;
}

void CustomersTableListBoxModel::paintRowBackground(Graphics &g, int rowNumber, int x, int y, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected) {
        g.setColour(Colours::grey.brighter().brighter());
        g.fillRect(x, y, width, height);
    }
    else if (rowNumber == rowUnderMouse) {
        g.setColour(Colours::lightgrey.brighter().brighter());
        g.fillRect(x, y, width, height);
    }
    else if (getNumRows() && (rowSizes[rowNumber] == CustomersRowComponent::maxRowSize)) {
        g.setColour(Colours::lightgrey.brighter().brighter().brighter());
        g.fillRect(x, y, width, height);
    }
}

CoeusListRowComponent * CustomersTableListBoxModel::refreshComponentForRow(int rowNumber, bool isRowSelected, CoeusListRowComponent *existingComponentToUpdate)
{
    // create
    if (existingComponentToUpdate == nullptr) {
        CustomersRowComponent *newComp = new CustomersRowComponent();
        newComp->addMouseListener(this, true);
        newComp->addChangeListener(this);
        newComp->setRow(rowNumber);

        // TODO
        const bool dView = (rowNumber < getNumRows()) ? rowSizes[rowNumber] == CustomersRowComponent::maxRowSize : false;
        newComp->updateFromQueryForRow(qe, rowNumber,  dView);
        newComp->shouldShowControls(isRowSelected);

        return newComp;
    }
    // update
    else {
        CustomersRowComponent * cmp = dynamic_cast<CustomersRowComponent *>(existingComponentToUpdate);

        if(cmp) {
            const bool dView = (rowNumber < getNumRows()) ? rowSizes[rowNumber] == CustomersRowComponent::maxRowSize : false;
            cmp->updateFromQueryForRow(qe, rowNumber, dView);
            cmp->shouldShowControls(isRowSelected);
        }

        return existingComponentToUpdate;
    }
}

int CustomersTableListBoxModel::getMinRowSize()
{
    return CustomersRowComponent::minRowSize;
}

int CustomersTableListBoxModel::getMaxRowSize()
{
    return CustomersRowComponent::maxRowSize;
}

//================================================================

CustomersComponent::CustomersComponent()
{
	title->setText("Customers", dontSendNotification);
    customersTableListBoxModel = new CustomersTableListBoxModel();
	addAndMakeVisible(customersTableListBoxModel);

	//searchButtonPressed();
}

CustomersComponent::~CustomersComponent() 
{
	customersTableListBoxModel = nullptr;
}

void CustomersComponent::resized() 
{
	CustomTabContent::resized();
	customersTableListBoxModel->setBounds(getComponentArea());
}

void CustomersComponent::receivedResults(QueryEntry *qe_)
{
	qe = qe_;
	customersTableListBoxModel->setQueryEntry(qe);
    customersTableListBoxModel->update();
}

void CustomersComponent::mouseExit(const MouseEvent &event)
{
	customersTableListBoxModel->mouseExit(event);
}

void CustomersComponent::searchButtonPressed()
{
	String andOr = (searchFilter->getSelectedId() == 2) ? " AND " : " OR ";
	String orStr = " OR ";
	StringArray terms;
	terms.addTokens(search->getText(), true);

	String queryStr = "SELECT Name, Trademark, PhoneNumber, CustomerTransactions FROM customers WHERE ";

	for (int i = 0; i < terms.size(); i++) {
		queryStr += "CustomerCode like '%" + terms[i] + "%' " + orStr;
		queryStr += "CustomerVat like '%" + terms[i] + "%' " + orStr;
		queryStr += "Trademark like '%" + terms[i] + "%' " + orStr;
		queryStr += "Name like '%" + terms[i] + "%' " + orStr;
		queryStr += "FathersName like '%" + terms[i] + "%' " + orStr;
		queryStr += "DateOfBirth like '%" + terms[i] + "%' " + orStr;
		queryStr += "Address like '%" + terms[i] + "%' " + orStr;
		queryStr += "City like '%" + terms[i] + "%' " + orStr;

		queryStr += "Country like '%" + terms[i] + "%' " + orStr;
		queryStr += "ShippingAdress like '%" + terms[i] + "%' " + orStr;
		queryStr += "Phonenumber like '%" + terms[i] + "%' " + orStr;
		queryStr += "Faxnumber like '%" + terms[i] + "%' " + orStr;
		queryStr += "Email like '%" + terms[i] + "%' " + orStr;
		queryStr += "DateOfBirth like '%" + terms[i] + "%' " + orStr;
		queryStr += "IDcardNumber like '%" + terms[i] + "%' " + orStr;
		queryStr += "CustomerTransactions like '%" + terms[i] + "%' " + orStr;

		queryStr += "PublicRevenueService like '%" + terms[i] + "%' " + orStr;
		queryStr += "CommercialActivity like '%" + terms[i] + "%' " + andOr;
	}

	queryStr += (searchFilter->getSelectedId() == 2 || terms.size() == 0) ? " 1 = 1" : " 1 = 0";

//		CompanyVAT varchar(10) NOT NULL,
	
	CacheSystem *cs = CacheSystem::getInstance();
    cs->getResultsFor(queryStr, QueryEntry::Customers, this);

	std::cout << queryStr << std::endl;
}
