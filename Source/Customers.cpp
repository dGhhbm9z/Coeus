#include "Customers.h"
#include "CustomComponents.h"

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

    CustomersRowComponent(CoeusList &owner_) : CoeusListRowComponent(owner_) {
        detailedView = false;
        showControls = false;

        // add fields
        // summary
        addAndMakeVisible(CustomerCodeTE = new TextEditor("CustomerCode"));
        addAndMakeVisible(NameTE = new TextEditor("Name"));
        addAndMakeVisible(FathersNameTE = new TextEditor("FathersName"));
        addAndMakeVisible(PhonenumberTE = new TextEditor("Phonenumber"));
        CustomerCodeTE->addListener(&owner);
        NameTE->addListener(&owner);
        FathersNameTE->addListener(&owner);
        PhonenumberTE->addListener(&owner);

        // summary labels
        addAndMakeVisible(CustomerCode = new Label("Customer Code", "Customer Code"));
        addAndMakeVisible(Name = new Label("Name", "Name"));
        addAndMakeVisible(FathersName = new Label("FathersName", "FathersName"));
        addAndMakeVisible(Phonenumber = new Label("Phonenumber", "Phonenumber"));

        // detailed view
        addAndMakeVisible(TrademarkTE = new TextEditor("Trademark"));
        addAndMakeVisible(CustomerVATTE = new TextEditor("CustomerVAT"));
        addAndMakeVisible(DateOfBirthTE = new TextEditor("DateOfBirth"));
        addAndMakeVisible(AddressTE = new TextEditor("Address"));
        addAndMakeVisible(CityTE = new TextEditor("City"));
        addAndMakeVisible(CountryTE = new TextEditor("Country"));
        addAndMakeVisible(ShippingAdressTE = new TextEditor("ShippingAddress"));
        addAndMakeVisible(FaxnumberTE = new TextEditor("FaxNumber"));
        addAndMakeVisible(EmailTE = new TextEditor("Email"));
        addAndMakeVisible(IDcardNumberTE = new TextEditor("IDcardNumber"));
        addAndMakeVisible(CustomerTransactionsTE = new TextEditor("CustomerTransactions"));
        addAndMakeVisible(PublicRevenueServiceTE = new TextEditor("PublicRevenueService"));
        addAndMakeVisible(CommercialActivityTE = new TextEditor("CommercialActivity"));
        TrademarkTE->addListener(&owner);
        CustomerVATTE->addListener(&owner);
        DateOfBirthTE->addListener(&owner);
        CityTE->addListener(&owner);
        CountryTE->addListener(&owner);
        ShippingAdressTE->addListener(&owner);
        FaxnumberTE->addListener(&owner);
        EmailTE->addListener(&owner);
        IDcardNumberTE->addListener(&owner);
        CustomerTransactionsTE->addListener(&owner);
        PublicRevenueServiceTE->addListener(&owner);
        CommercialActivityTE->addListener(&owner);

        // detailed view labels
        addAndMakeVisible(Trademark = new Label("Trademark", "Trademark"));
        addAndMakeVisible(CustomerVAT = new Label("VAT", "VAT"));
        addAndMakeVisible(DateOfBirth = new Label("Date Of Birth", "Date Of Birth"));
        addAndMakeVisible(Address = new Label("Address", "Address"));
        addAndMakeVisible(City = new Label("City", "City"));
        addAndMakeVisible(Country = new Label("Country", "Country"));
        addAndMakeVisible(ShippingAdress = new Label("Shipping Adress", "Shipping Adress"));
        addAndMakeVisible(Faxnumber = new Label("Fax number", "Fax number"));
        addAndMakeVisible(Email = new Label("Email", "Email"));
        addAndMakeVisible(IDcardNumber = new Label("IDcardNumber", "IDcardNumber"));
        addAndMakeVisible(CustomerTransactions = new Label("CustomerTransactions", "CustomerTransactions"));
        addAndMakeVisible(PublicRevenueService = new Label("PublicRevenueService", "PublicRevenueService"));
        addAndMakeVisible(CommercialActivity = new Label("CommercialActivity", "CommercialActivity"));

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
        CustomerCodeTE->setBounds(lm, tm, teWS, teHS);
        NameTE->setBounds(lm+teWS+pad, tm, teWS, teHS);
        FathersNameTE->setBounds(lm+2*(teWS+pad), tm, 150, teHS);
        PhonenumberTE->setBounds(lm+2*(teWS+pad)+pad+150, tm, teWS, teHS);
    }

    void resizeForDetailed() override {
        // detailed
        CustomerCodeTE->setBounds(lm+teWS+pad, tm+teHS, teWS, teHS);
        NameTE->setBounds(lm+teWS+pad, tm+2*teHS, teWS, teHS);
        FathersNameTE->setBounds(lm+teWS+pad, tm+3*teHS, 150, teHS);
        PhonenumberTE->setBounds(lm+teWS+pad, tm+4*teHS, teWS, teHS);
        // summary labels
        CustomerCode->setBounds(lm, tm+teHS, teWS, teHS);
        Name->setBounds(lm, tm+2*teHS, teWS, teHS);
        FathersName->setBounds(lm, tm+3*teHS, teWS, teHS);
        Phonenumber->setBounds(lm, tm+4*teHS, teWS, teHS);
        // detailed view
        TrademarkTE->setBounds(lm+teWS+pad, tm+5*teHS, teWS, teHS);
        CustomerVATTE->setBounds(lm+teWS+pad, tm+6*teHS, teWS, teHS);
        DateOfBirthTE->setBounds(lm+teWS+pad, tm+7*teHS, teWS, teHS);
        AddressTE->setBounds(lm+teWS+pad, tm+8*teHS, teWS, teHS);
        CityTE->setBounds(lm+teWS+pad, tm+9*teHS, teWS, teHS);
        CountryTE->setBounds(lm+teWS+pad, tm+10*teHS, teWS, teHS);
        ShippingAdressTE->setBounds(lm+teWS+pad, tm+11*teHS, teWS, teHS);

        FaxnumberTE->setBounds(lm+3*(teWS+pad), tm+6*teHS, teWS, teHS);
        EmailTE->setBounds(lm+3*(teWS+pad), tm+7*teHS, teWS, teHS);
        IDcardNumberTE->setBounds(lm+3*(teWS+pad), tm+8*teHS, teWS, teHS);
        CustomerTransactionsTE->setBounds(lm+3*(teWS+pad), tm+9*teHS, teWS, teHS);
        PublicRevenueServiceTE->setBounds(lm+3*(teWS+pad), tm+10*teHS, teWS, teHS);
        CommercialActivityTE->setBounds(lm+3*(teWS+pad), tm+11*teHS, teWS, teHS);

        // detailed view labels
        Trademark->setBounds(lm, tm+5*teHS, teWS, teHS);
        CustomerVAT->setBounds(lm, tm+6*teHS, teWS, teHS);
        DateOfBirth->setBounds(lm, tm+7*teHS, teWS, teHS);
        Address->setBounds(lm, tm+8*teHS, teWS, teHS);
        City->setBounds(lm, tm+9*teHS, teWS, teHS);
        Country->setBounds(lm, tm+10*teHS, teWS, teHS);
        ShippingAdress->setBounds(lm, tm+11*teHS, teWS, teHS);

        Faxnumber->setBounds(lm+2*(teWS+pad), tm+6*teHS, teWS, teHS);
        Email->setBounds(lm+2*(teWS+pad), tm+7*teHS, teWS, teHS);
        IDcardNumber->setBounds(lm+2*(teWS+pad), tm+8*teHS, teWS, teHS);
        CustomerTransactions->setBounds(lm+2*(teWS+pad), tm+9*teHS, teWS, teHS);
        PublicRevenueService->setBounds(lm+2*(teWS+pad), tm+10*teHS, teWS, teHS);
        CommercialActivity->setBounds(lm+2*(teWS+pad), tm+11*teHS, teWS, teHS);
    }
    
    void updateRow() {

    }

    void insertRow() {

    }

private:
    // summary
    ScopedPointer<TextEditor> CustomerCodeTE, NameTE, FathersNameTE, PhonenumberTE;
    ScopedPointer<Label> CustomerCode, Name, FathersName, Phonenumber;

    // detailed
    ScopedPointer<TextEditor> TrademarkTE, CustomerVATTE, DateOfBirthTE, AddressTE, CityTE, CountryTE, ShippingAdressTE, FaxnumberTE;
    ScopedPointer<Label> Trademark, CustomerVAT, DateOfBirth, Address, City, Country, ShippingAdress, Faxnumber;
    ScopedPointer<TextEditor> EmailTE, IDcardNumberTE, CustomerTransactionsTE, PublicRevenueServiceTE, CommercialActivityTE;
    ScopedPointer<Label> Email, IDcardNumber, CustomerTransactions, PublicRevenueService, CommercialActivity;
};

//================================================================================

CustomersTableListBoxModel::CustomersTableListBoxModel(CacheSystemClient *ccc_)
: CoeusList(ccc_)
{
    update();
    rowSizes.calloc(1); //hack +1
    
    fieldNames.add("CustomerCode");
    fieldNames.add("CompanyVAT");
    fieldNames.add("CustomerVAT");
    fieldNames.add("Trademark");
    fieldNames.add("Name");
    fieldNames.add("FathersName");
    
    fieldNames.add("DateOfBirth");
    fieldNames.add("Address");
    
    fieldNames.add("City");
    fieldNames.add("Country");
    fieldNames.add("ShippingAdress");
    fieldNames.add("Phonenumber");
    
    fieldNames.add("Faxnumber");
    fieldNames.add("Email");
    fieldNames.add("IDcardNumber");
    fieldNames.add("CustomerTransactions");

    fieldNames.add("PublicRevenueService");
    fieldNames.add("CommercialActivity");
    
    tableName = "customers";
}

Array<int> CustomersTableListBoxModel::getKeyField()
{
    Array<int> kf;
    kf.add(0);
    kf.add(2);
    return kf;
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
        g.setColour(Colour(0xff9d9d9d));
        g.fillRect(x, y, width, height);
    }
    else if (rowNumber == rowUnderMouse && (rowSizes[rowNumber] != CustomersRowComponent::maxRowSize)) {
        g.setColour(Colours::lightgrey.brighter().brighter());
        g.fillRect(x, y, width, height);
    }
    else if (getNumRows() && (rowSizes[rowNumber] == CustomersRowComponent::maxRowSize)) {
        g.setColour(Colour(Colour(0xffbebebe)));
        g.fillRect(x, y, width, height);
    }
}

CoeusListRowComponent * CustomersTableListBoxModel::refreshComponentForRow(int rowNumber, bool isRowSelected, CoeusListRowComponent *existingComponentToUpdate)
{
    // create
    if (existingComponentToUpdate == nullptr) {
        CustomersRowComponent *newComp = new CustomersRowComponent(*this);
        newComp->addMouseListener(this, true);
        newComp->addChangeListener(this);
        newComp->setRow(rowNumber);

        const bool dView = (rowNumber < getNumRows()) ? rowSizes[rowNumber] == CustomersRowComponent::maxRowSize : false;
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
        CustomersRowComponent * cmp = dynamic_cast<CustomersRowComponent *>(existingComponentToUpdate);

        if(cmp) {
            const bool dView = (rowNumber < getNumRows()) ? rowSizes[rowNumber] == CustomersRowComponent::maxRowSize : false;
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
    customersTableListBoxModel = new CustomersTableListBoxModel(this);
	addAndMakeVisible(customersTableListBoxModel);
    customersTableListBoxModel->addChangeListener(this);

    tableHeader1->setText("Customer Code", dontSendNotification);
    tableHeader2->setText("Name", dontSendNotification);
    tableHeader3->setText("Fathers Name", dontSendNotification);
    tableHeader4->setText("Phone Number", dontSendNotification);
    
	//searchButtonPressed();
}

CustomersComponent::~CustomersComponent() 
{
	customersTableListBoxModel = nullptr;
}

void CustomersComponent::resized() 
{
	CustomTabContent::resized();
    Rectangle<int> compBounds = getComponentArea();
    compBounds.setY(compBounds.getY());
    customersTableListBoxModel->setBounds(compBounds);
}

void CustomersComponent::receivedResults(QueryEntry *qe_)
{
    if (qe_->num_fields > 1) {
        qe = qe_;
        customersTableListBoxModel->setQueryEntry(qe);
        customersTableListBoxModel->update();
    }
    else {
        // if update
        if (customersTableListBoxModel->savedpks.size()) {
            // fix this v
            StringArray pk = customersTableListBoxModel->savedpks[0];
            customersTableListBoxModel->wasSaved(pk);
        }
        // if delete
    }
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

    String queryStr = "SELECT * FROM customers WHERE ";

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

void CustomersComponent::addButtonPressed()
{

}

void CustomersComponent::saveButtonPressed()
{
//    if (!editButton->getToggleState()) {
//        //
//        StringArray pkNames;
//        pkNames.add("CustomerCode");
//        pkNames.add("CustomerVAT");
//
//        customersTableListBoxModel->updateDatabaseTable("customers", pkNames, this);
//
//    }
//
//    customersTableListBoxModel->update();
}

void CustomersComponent::changeListenerCallback(ChangeBroadcaster *source)
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

CoeusListRowComponent * CustomersComponent::getAddComponent()
{
    return new CustomersRowComponent(*customersTableListBoxModel);
}
