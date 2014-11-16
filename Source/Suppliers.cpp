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
        editView = false;
        showControls = false;
        
        // add fields
        // summary
        addAndMakeVisible(SupplierCodeTE = new TextEditor("SupplierCode"));
        addAndMakeVisible(NameTE = new TextEditor("Name"));
        addAndMakeVisible(FathersNameTE = new TextEditor("FathersName"));
        addAndMakeVisible(PhonenumberTE = new TextEditor("Phonenumber"));
        
        // summary labels
        addAndMakeVisible(SupplierCode = new Label("Supplier Code", "Supplier Code"));
        addAndMakeVisible(Name = new Label("Name", "Name"));
        addAndMakeVisible(FathersName = new Label("FathersName", "FathersName"));
        addAndMakeVisible(Phonenumber = new Label("Phonenumber", "Phonenumber"));
        
        // detailed view
        addAndMakeVisible(TrademarkTE = new TextEditor("Trademark"));
        addAndMakeVisible(SupplierVATTE = new TextEditor("SupplierVAT"));
        addAndMakeVisible(DateOfBirthTE = new TextEditor("DateOfBirth"));
        addAndMakeVisible(AddressTE = new TextEditor("Address"));
        addAndMakeVisible(CityTE = new TextEditor("City"));
        addAndMakeVisible(CountryTE = new TextEditor("Country"));
        addAndMakeVisible(FaxnumberTE = new TextEditor("FaxNumber"));
        addAndMakeVisible(EmailTE = new TextEditor("Email"));
        addAndMakeVisible(IDcardNumberTE = new TextEditor("IDcardNumber"));
        addAndMakeVisible(SupplierTransactionsTE = new TextEditor("SupplierTransactions"));
        addAndMakeVisible(PublicRevenueServiceTE = new TextEditor("PublicRevenueService"));
        addAndMakeVisible(CommercialActivityTE = new TextEditor("CommercialActivity"));
        
        
        // detailed view labels
        addAndMakeVisible(Trademark = new Label("Trademark", "Trademark"));
        addAndMakeVisible(SupplierVAT = new Label("VAT", "VAT"));
        addAndMakeVisible(DateOfBirth = new Label("Date Of Birth", "Date Of Birth"));
        addAndMakeVisible(Address = new Label("Address", "Address"));
        addAndMakeVisible(City = new Label("City", "City"));
        addAndMakeVisible(Country = new Label("Country", "Country"));
        addAndMakeVisible(Faxnumber = new Label("Fax number", "Fax number"));
        addAndMakeVisible(Email = new Label("Email", "Email"));
        addAndMakeVisible(IDcardNumber = new Label("IDcardNumber", "IDcardNumber"));
        addAndMakeVisible(SupplierTransactions = new Label("SupplierTransactions", "Supplier Transactions"));
        addAndMakeVisible(PublicRevenueService = new Label("PublicRevenueService", "PublicRevenueService"));
        addAndMakeVisible(CommercialActivity = new Label("CommercialActivity", "CommercialActivity"));
        
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
    
    void updateFromQueryForRow(QueryEntry *qe, int row, bool dView, bool edit) override {
        setDetailedView(dView);
        resized();
        this->row = row;
        if(qe) {
            // summary
            SupplierCodeTE->setText(qe->getFieldFromRow(row, 1));
            SupplierVATTE->setText(qe->getFieldFromRow(row, 2));
            TrademarkTE->setText(qe->getFieldFromRow(row, 3));
            NameTE->setText(qe->getFieldFromRow(row, 4));
            // detailed view
            FathersNameTE->setText(qe->getFieldFromRow(row, 5));
            DateOfBirthTE->setText(qe->getFieldFromRow(row, 6));
            AddressTE->setText(qe->getFieldFromRow(row, 7));
            CityTE->setText(qe->getFieldFromRow(row, 8));
            CountryTE->setText(qe->getFieldFromRow(row, 9));
            PhonenumberTE->setText(qe->getFieldFromRow(row, 10));
            FaxnumberTE->setText(qe->getFieldFromRow(row, 11));
            EmailTE->setText(qe->getFieldFromRow(row, 12));
            IDcardNumberTE->setText(qe->getFieldFromRow(row, 13));
            SupplierTransactionsTE->setText(qe->getFieldFromRow(row, 14));
            PublicRevenueServiceTE->setText(qe->getFieldFromRow(row, 15));
            CommercialActivityTE->setText(qe->getFieldFromRow(row, 16));
            
            SupplierCodeTE->setEnabled(edit);
            SupplierVATTE->setEnabled(edit);
            TrademarkTE->setEnabled(edit);
            NameTE->setEnabled(edit);
            // detailed view
            FathersNameTE->setEnabled(edit);
            DateOfBirthTE->setEnabled(edit);
            AddressTE->setEnabled(edit);
            CityTE->setEnabled(edit);
            CountryTE->setEnabled(edit);
            PhonenumberTE->setEnabled(edit);
            FaxnumberTE->setEnabled(edit);
            EmailTE->setEnabled(edit);
            IDcardNumberTE->setEnabled(edit);
            SupplierTransactionsTE->setEnabled(edit);
            PublicRevenueServiceTE->setEnabled(edit);
            CommercialActivityTE->setEnabled(edit);
        }
    }
    
    void updateFromMapForRow(std::map<String, String>, int row, bool dView, bool edit) override {
        
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
    ScopedPointer<TextEditor> SupplierCodeTE, SupplierVATTE, TrademarkTE, NameTE;
    ScopedPointer<Label> SupplierCode, SupplierVAT, Trademark, Name;
    
    // detailed
    ScopedPointer<TextEditor> FathersNameTE, DateOfBirthTE, AddressTE, CityTE;
    ScopedPointer<Label> FathersName, DateOfBirth, Address, City;
    
    ScopedPointer<TextEditor> CountryTE, PhonenumberTE, FaxnumberTE, EmailTE, IDcardNumberTE, SupplierTransactionsTE, PublicRevenueServiceTE, CommercialActivityTE;
    ScopedPointer<Label> Country, Phonenumber, Faxnumber, Email, IDcardNumber, SupplierTransactions, PublicRevenueService, CommercialActivity;
};

//================================================================================

SuppliersTableListBoxModel::SuppliersTableListBoxModel()
{
    update();
    rowSizes.calloc(1); //hack +1
}

int SuppliersTableListBoxModel::getKeyField()
{
    return 0;
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
        g.setColour(Colours::grey.brighter().brighter());
        g.fillRect(x, y, width, height);
    }
    else if (rowNumber == rowUnderMouse) {
        g.setColour(Colours::lightgrey.brighter().brighter());
        g.fillRect(x, y, width, height);
    }
    else if (getNumRows() && (rowSizes[rowNumber] == SuppliersRowComponent::maxRowSize)) {
        g.setColour(Colours::lightgrey.brighter().brighter().brighter());
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
        newComp->updateFromQueryForRow(qe, rowNumber, dView, edit);
        newComp->shouldShowControls(isRowSelected);
        
        return newComp;
    }
    // update
    else {
        SuppliersRowComponent * cmp = dynamic_cast<SuppliersRowComponent *>(existingComponentToUpdate);
        
        if(cmp) {
            const bool dView = (rowNumber < getNumRows()) ? rowSizes[rowNumber] == SuppliersRowComponent::maxRowSize : false;
            cmp->updateFromQueryForRow(qe, rowNumber, dView, edit);
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
    suppliersTableListBoxModel = new SuppliersTableListBoxModel();
    addAndMakeVisible(suppliersTableListBoxModel);
    
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
    qe = qe_;
    suppliersTableListBoxModel->setQueryEntry(qe);
    suppliersTableListBoxModel->update();
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

void SuppliersComponent::editButtonPressed()
{
    suppliersTableListBoxModel->setEdit(editButton->getToggleState());
}