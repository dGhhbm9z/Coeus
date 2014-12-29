#include "Suppliers.h"
#include "CustomComponents.h"

class SuppliersRowComponent :   public CoeusListRowComponent
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
    
    SuppliersRowComponent(CoeusList &owner_) : CoeusListRowComponent(owner_) {
        detailedView = false;
        showControls = false;
        
        // add fields
        // summary
        addAndMakeVisible(SupplierCodeTE = new CoeusListTextEditor("SupplierCode"));
        addAndMakeVisible(NameTE = new CoeusListTextEditor("Name"));
        addAndMakeVisible(FathersNameTE = new CoeusListTextEditor("FathersName"));
        addAndMakeVisible(PhonenumberTE = new CoeusListTextEditor("Phonenumber"));
        SupplierCodeTE->addListener(&owner);
        NameTE->addListener(&owner);
        FathersNameTE->addListener(&owner);
        PhonenumberTE->addListener(&owner);

        // summary labels
        addAndMakeVisible(SupplierCode = new CoeusListLabel("Supplier Code", "Supplier Code"));
        addAndMakeVisible(Name = new CoeusListLabel("Name", "Name"));
        addAndMakeVisible(FathersName = new CoeusListLabel("FathersName", "FathersName"));
        addAndMakeVisible(Phonenumber = new CoeusListLabel("Phonenumber", "Phonenumber"));
        
        // detailed view
        addAndMakeVisible(TrademarkTE = new CoeusListTextEditor("Trademark"));
        addAndMakeVisible(SupplierVATTE = new CoeusListTextEditor("SupplierVAT"));
        addAndMakeVisible(DateOfBirthTE = new CoeusListTextEditor("DateOfBirth"));
        addAndMakeVisible(AddressTE = new CoeusListTextEditor("Address"));
        addAndMakeVisible(CityTE = new CoeusListTextEditor("City"));
        addAndMakeVisible(CountryTE = new CoeusListTextEditor("Country"));
        addAndMakeVisible(FaxnumberTE = new CoeusListTextEditor("FaxNumber"));
        addAndMakeVisible(EmailTE = new CoeusListTextEditor("Email"));
        addAndMakeVisible(IDcardNumberTE = new CoeusListTextEditor("IDcardNumber"));
        addAndMakeVisible(SupplierTransactionsTE = new CoeusListTextEditor("SupplierTransactions"));
        addAndMakeVisible(PublicRevenueServiceTE = new CoeusListTextEditor("PublicRevenueService"));
        addAndMakeVisible(CommercialActivityTE = new CoeusListTextEditor("CommercialActivity"));
        TrademarkTE->addListener(&owner);
        SupplierVATTE->addListener(&owner);
        DateOfBirthTE->addListener(&owner);
        AddressTE->addListener(&owner);
        CityTE->addListener(&owner);
        CountryTE->addListener(&owner);
        FaxnumberTE->addListener(&owner);
        EmailTE->addListener(&owner);
        IDcardNumberTE->addListener(&owner);
        SupplierTransactionsTE->addListener(&owner);
        PublicRevenueServiceTE->addListener(&owner);
        CommercialActivityTE->addListener(&owner);

        
        // detailed view labels
        addAndMakeVisible(Trademark = new CoeusListLabel("Trademark", "Trademark"));
        addAndMakeVisible(SupplierVAT = new CoeusListLabel("VAT", "VAT"));
        addAndMakeVisible(DateOfBirth = new CoeusListLabel("Date Of Birth", "Date Of Birth"));
        addAndMakeVisible(Address = new CoeusListLabel("Address", "Address"));
        addAndMakeVisible(City = new CoeusListLabel("City", "City"));
        addAndMakeVisible(Country = new CoeusListLabel("Country", "Country"));
        addAndMakeVisible(Faxnumber = new CoeusListLabel("Fax number", "Fax number"));
        addAndMakeVisible(Email = new CoeusListLabel("Email", "Email"));
        addAndMakeVisible(IDcardNumber = new CoeusListLabel("IDcardNumber", "IDcardNumber"));
        addAndMakeVisible(SupplierTransactions = new CoeusListLabel("SupplierTransactions", "Supplier Transactions"));
        addAndMakeVisible(PublicRevenueService = new CoeusListLabel("PublicRevenueService", "PublicRevenueService"));
        addAndMakeVisible(CommercialActivity = new CoeusListLabel("CommercialActivity", "CommercialActivity"));
        
        resized();
    }
    
    ~SuppliersRowComponent() {
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
        SupplierCodeTE->setBounds(lm, tm, teWS, teHS);
        NameTE->setBounds(lm+teWS+pad, tm, teWS, teHS);
        FathersNameTE->setBounds(lm+2*(teWS+pad), tm, 150, teHS);
        PhonenumberTE->setBounds(lm+2*(teWS+pad)+pad+150, tm, teWS, teHS);
    }
    
    void resizeForDetailed() override {
        // detailed
        SupplierCodeTE->setBounds(lm+teWS+pad, tm+teHS, teWS, teHS);
        NameTE->setBounds(lm+teWS+pad, tm+2*teHS, teWS, teHS);
        FathersNameTE->setBounds(lm+teWS+pad, tm+3*teHS, 150, teHS);
        PhonenumberTE->setBounds(lm+teWS+pad, tm+4*teHS, teWS, teHS);
        // summary labels
        SupplierCode->setBounds(lm, tm+teHS, teWS, teHS);
        Name->setBounds(lm, tm+2*teHS, teWS, teHS);
        FathersName->setBounds(lm, tm+3*teHS, teWS, teHS);
        Phonenumber->setBounds(lm, tm+4*teHS, teWS, teHS);
        // detailed view
        TrademarkTE->setBounds(lm+teWS+pad, tm+5*teHS, teWS, teHS);
        SupplierVATTE->setBounds(lm+teWS+pad, tm+6*teHS, teWS, teHS);
        DateOfBirthTE->setBounds(lm+teWS+pad, tm+7*teHS, teWS, teHS);
        AddressTE->setBounds(lm+teWS+pad, tm+8*teHS, teWS, teHS);
        CityTE->setBounds(lm+teWS+pad, tm+9*teHS, teWS, teHS);
        CountryTE->setBounds(lm+teWS+pad, tm+10*teHS, teWS, teHS);
        
        FaxnumberTE->setBounds(lm+3*(teWS+pad), tm+6*teHS, teWS, teHS);
        EmailTE->setBounds(lm+3*(teWS+pad), tm+7*teHS, teWS, teHS);
        IDcardNumberTE->setBounds(lm+3*(teWS+pad), tm+8*teHS, teWS, teHS);
        SupplierTransactionsTE->setBounds(lm+3*(teWS+pad), tm+9*teHS, teWS, teHS);
        PublicRevenueServiceTE->setBounds(lm+3*(teWS+pad), tm+10*teHS, teWS, teHS);
        CommercialActivityTE->setBounds(lm+3*(teWS+pad), tm+11*teHS, teWS, teHS);
        
        // detailed view labels
        Trademark->setBounds(lm, tm+5*teHS, teWS, teHS);
        SupplierVAT->setBounds(lm, tm+6*teHS, teWS, teHS);
        DateOfBirth->setBounds(lm, tm+7*teHS, teWS, teHS);
        Address->setBounds(lm, tm+8*teHS, teWS, teHS);
        City->setBounds(lm, tm+9*teHS, teWS, teHS);
        Country->setBounds(lm, tm+10*teHS, teWS, teHS);
        
        Faxnumber->setBounds(lm+2*(teWS+pad), tm+6*teHS, teWS, teHS);
        Email->setBounds(lm+2*(teWS+pad), tm+7*teHS, teWS, teHS);
        IDcardNumber->setBounds(lm+2*(teWS+pad), tm+8*teHS, teWS, teHS);
        SupplierTransactions->setBounds(lm+2*(teWS+pad), tm+9*teHS, teWS, teHS);
        PublicRevenueService->setBounds(lm+2*(teWS+pad), tm+10*teHS, teWS, teHS);
        CommercialActivity->setBounds(lm+2*(teWS+pad), tm+11*teHS, teWS, teHS);
    }
    
    void updateRow() {
    }
    
    void insertRow() {
    }
    
private:
    // summary
    ScopedPointer<TextEditor> SupplierCodeTE, SupplierVATTE, TrademarkTE, NameTE;
    ScopedPointer<Label> SupplierCode, SupplierVAT, Trademark, Name;
    
    // detailed
    ScopedPointer<TextEditor> FathersNameTE, DateOfBirthTE, AddressTE, CityTE;
    ScopedPointer<Label> FathersName, DateOfBirth, Address, City;
    
    ScopedPointer<TextEditor> CountryTE, PhonenumberTE, FaxnumberTE, EmailTE, IDcardNumberTE, SupplierTransactionsTE, PublicRevenueServiceTE, CommercialActivityTE;
    ScopedPointer<Label> Country, Phonenumber, Faxnumber, Email, IDcardNumber, SupplierTransactions, PublicRevenueService, CommercialActivity;
};

//================================================================================

SuppliersTableListBoxModel::SuppliersTableListBoxModel(CacheSystemClient *ccc_)
: CoeusList(ccc_)
{
    update();
    rowSizes.calloc(1); //hack +1
    
    fieldNames.add("SupplierCode");
    fieldNames.add("CompanyVAT");
    fieldNames.add("SupplierVAT");
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
    fieldNames.add("SupplierTransactions");
    
    fieldNames.add("PublicRevenueService");
    fieldNames.add("CommercialActivity");
    
    tableName = "suppliers";
}

Array<int> SuppliersTableListBoxModel::getKeyField()
{
    Array<int> kf;
    kf.add(0);
    return kf;
}

int SuppliersTableListBoxModel::getNumRows()
{
    if (qe != nullptr) {
        return qe->num_rows;
    }
    else {
        return 0;
    }
}

int SuppliersTableListBoxModel::getRowSize(int rowNumber)
{
    return (rowNumber >= 0 && rowNumber < getNumRows()) ? rowSizes[rowNumber] : 0;
}

void SuppliersTableListBoxModel::paintRowBackground(Graphics &g, int rowNumber, int x, int y, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected) {
        g.setColour(Colour(0xff9d9d9d));
        g.fillRect(x, y, width, height);
    }
    else if (rowNumber == rowUnderMouse && (rowSizes[rowNumber] != SuppliersRowComponent::maxRowSize)) {
        g.setColour(Colours::lightgrey.brighter().brighter());
        g.fillRect(x, y, width, height);
    }
    else if (getNumRows() && (rowSizes[rowNumber] == SuppliersRowComponent::maxRowSize)) {
        g.setColour(Colour(Colour(0xffbebebe)));
        g.fillRect(x, y, width, height);
    }
}

CoeusListRowComponent * SuppliersTableListBoxModel::refreshComponentForRow(int rowNumber, bool isRowSelected, CoeusListRowComponent *existingComponentToUpdate)
{
    // create
    if (existingComponentToUpdate == nullptr) {
        SuppliersRowComponent *newComp = new SuppliersRowComponent(*this);
        newComp->addMouseListener(this, true);
        newComp->addChangeListener(this);
        newComp->setRow(rowNumber);
        
        // TODO
        const bool dView = (rowNumber < getNumRows()) ? rowSizes[rowNumber] == SuppliersRowComponent::maxRowSize : false;
        newComp->updateFromQueryForRow(qe, rowNumber, dView, editedRows.contains(rowNumber));
        newComp->shouldShowControls(isRowSelected);
        
        return newComp;
    }
    // update
    else {
        SuppliersRowComponent * cmp = dynamic_cast<SuppliersRowComponent *>(existingComponentToUpdate);
        
        if(cmp) {
            const bool dView = (rowNumber < getNumRows()) ? rowSizes[rowNumber] == SuppliersRowComponent::maxRowSize : false;
            cmp->updateFromQueryForRow(qe, rowNumber, dView, editedRows.contains(rowNumber));
            cmp->shouldShowControls(isRowSelected);
        }
        
        return existingComponentToUpdate;
    }
}

int SuppliersTableListBoxModel::getMinRowSize()
{
    return SuppliersRowComponent::minRowSize;
}

int SuppliersTableListBoxModel::getMaxRowSize()
{
    return SuppliersRowComponent::maxRowSize;
}

//================================================================

SuppliersComponent::SuppliersComponent()
{
    title->setText("Suppliers", dontSendNotification);
    suppliersTableListBoxModel = new SuppliersTableListBoxModel(this);
    addAndMakeVisible(suppliersTableListBoxModel);
    suppliersTableListBoxModel->addChangeListener(this);
    
    tableHeader1->setText("Supplier Code", dontSendNotification);
    tableHeader2->setText("Name", dontSendNotification);
    tableHeader3->setText("Fathers Name", dontSendNotification);
    tableHeader4->setText("Phone Number", dontSendNotification);
    
    //searchButtonPressed();
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
    if (qe_->num_fields > 1) {
        qe = qe_;
        suppliersTableListBoxModel->setQueryEntry(qe);
        suppliersTableListBoxModel->update();
    }
}

void SuppliersComponent::mouseExit(const MouseEvent &event)
{
    suppliersTableListBoxModel->mouseExit(event);
}

void SuppliersComponent::searchButtonPressed()
{
    String andOr = (searchFilter->getSelectedId() == 2) ? " AND " : " OR ";
    String orStr = " OR ";
    StringArray terms;
    terms.addTokens(search->getText(), true);
    
    String queryStr = "SELECT * FROM suppliers WHERE ";
    
    for (int i = 0; i < terms.size(); i++) {
        queryStr += "SupplierCode like '%" + terms[i] + "%' " + orStr;
        queryStr += "SupplierVAT like '%" + terms[i] + "%' " + orStr;
        queryStr += "Trademark like '%" + terms[i] + "%' " + orStr;
        queryStr += "Name like '%" + terms[i] + "%' " + orStr;
        queryStr += "FathersName like '%" + terms[i] + "%' " + orStr;
        queryStr += "DateOfBirth like '%" + terms[i] + "%' " + orStr;
        queryStr += "Address like '%" + terms[i] + "%' " + orStr;
        queryStr += "City like '%" + terms[i] + "%' " + orStr;
        
        queryStr += "Country like '%" + terms[i] + "%' " + orStr;
        queryStr += "Phonenumber like '%" + terms[i] + "%' " + orStr;
        queryStr += "Faxnumber like '%" + terms[i] + "%' " + orStr;
        queryStr += "Email like '%" + terms[i] + "%' " + orStr;
        queryStr += "IDcardNumber like '%" + terms[i] + "%' " + orStr;
        queryStr += "SupplierTransactions like '%" + terms[i] + "%' " + orStr;
        
        queryStr += "PublicRevenueService like '%" + terms[i] + "%' " + orStr;
        queryStr += "CommercialActivity like '%" + terms[i] + "%' " + andOr;
    }
    
    queryStr += (searchFilter->getSelectedId() == 2 || terms.size() == 0) ? " 1 = 1" : " 1 = 0";
    
    //		CompanyVAT varchar(10) NOT NULL,
    
    CacheSystem *cs = CacheSystem::getInstance();
    cs->getResultsFor(queryStr, QueryEntry::Suppliers, this);
    
    std::cout << queryStr << std::endl;
}

void SuppliersComponent::addButtonPressed()
{
    // show add overlay
}

void SuppliersComponent::saveButtonPressed()
{
//    if (!editButton->getToggleState()) {
//        //
//        StringArray pkNames;
//        pkNames.add("SupplierCode");
//        pkNames.add("SupplierVAT");
//
//        suppliersTableListBoxModel->updateDatabaseTable("suppliers", pkNames, this);
//
//    }
//
//    suppliersTableListBoxModel->update();
}

void SuppliersComponent::changeListenerCallback(ChangeBroadcaster *source)
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

CoeusListRowComponent * SuppliersComponent::getAddComponent()
{
    return new SuppliersRowComponent(*suppliersTableListBoxModel);
}
