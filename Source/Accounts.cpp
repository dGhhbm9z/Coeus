#include "Accounts.h"
#include "CustomComponents.h"

class AccountsRowComponent :   public CoeusListRowComponent
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
    
    AccountsRowComponent(CoeusList &owner_) : CoeusListRowComponent(owner_) {
        detailedView = false;
        showControls = false;
        
        // add fields
        // summary
        addAndMakeVisible(InvoiceTE = new CoeusListTextEditor("Invoice"));
        addAndMakeVisible(RecordDateTE = new CoeusListTextEditor("RecordDate"));
        addAndMakeVisible(RecordTypeTE = new CoeusListTextEditor("RecordType"));
        addAndMakeVisible(ReasoningTE = new CoeusListTextEditor("Reasoning"));
        InvoiceTE->addListener(&owner);
        RecordDateTE->addListener(&owner);
        RecordTypeTE->addListener(&owner);
        ReasoningTE->addListener(&owner);
        
        // summary labels
        addAndMakeVisible(Invoice = new CoeusListLabel("Invoice", "Invoice"));
        addAndMakeVisible(RecordDate = new CoeusListLabel("RecordDate", "Record Date"));
        addAndMakeVisible(RecordType = new CoeusListLabel("RecordType", "Record Type"));
        addAndMakeVisible(Reasoning = new CoeusListLabel("Reasoning", "Reasoning"));
        
        // detailed view
        addAndMakeVisible(CommentsTE = new CoeusListTextEditor("Comments"));
        addAndMakeVisible(anrticlenumbertextTE = new CoeusListTextEditor("anrticlenumbertextTE"));
        CommentsTE->addListener(&owner);
        anrticlenumbertextTE->addListener(&owner);
        
        // detailed view labels
        addAndMakeVisible(Comments = new CoeusListLabel("Comments", "Comments"));
        addAndMakeVisible(anrticlenumbertext = new CoeusListLabel("anrticlenumbertext", "anrticlenumbertext"));
        
        resized();
    }
    
    ~AccountsRowComponent() {
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
        InvoiceTE->setBounds(lm, tm, teWS, teHS);
        RecordDateTE->setBounds(lm+teWS+pad, tm, teWS, teHS);
        RecordTypeTE->setBounds(lm+2*(teWS+pad), tm, 150, teHS);
        ReasoningTE->setBounds(lm+2*(teWS+pad)+pad+150, tm, teWS, teHS);
    }
    
    void resizeForDetailed() override {
        // detailed
        InvoiceTE->setBounds(lm+teWS+pad, tm+teHS, teWS, teHS);
        RecordDateTE->setBounds(lm+teWS+pad, tm+2*teHS, teWS, teHS);
        RecordTypeTE->setBounds(lm+teWS+pad, tm+3*teHS, teWS, teHS);
        // summary labels
        Invoice->setBounds(lm, tm+teHS, teWS, teHS);
        RecordDate->setBounds(lm, tm+2*teHS, teWS, teHS);
        RecordType->setBounds(lm, tm+3*teHS, teWS, teHS);

        // detailed view
        ReasoningTE->setBounds(lm+3*(teWS+pad), tm+teHS, teWS, teHS);
        CommentsTE->setBounds(lm+3*(teWS+pad), tm+2*teHS, teWS, teHS);
        anrticlenumbertextTE->setBounds(lm+3*(teWS+pad), tm+3*teHS, teWS, teHS);
        
        // detailed view labels
        Reasoning->setBounds(lm+2*(teWS+pad), tm+teHS, teWS, teHS);
        Comments->setBounds(lm+2*(teWS+pad), tm+2*teHS, teWS, teHS);
        anrticlenumbertext->setBounds(lm+2*(teWS+pad), tm+3*teHS, teWS, teHS);
    }
    
    void updateRow() {
        
    }
    
    void insertRow() {
        
    }
    //TODO
    void updateFromTransactionsQueryForRow(QueryEntry *qe, int row, bool dView, bool edit)
    {
        setDetailedView(dView);
        setEdit(edit);
        resized();
        this->row = row;
        if(qe) {
            // summary
            for (int i=0; i<getNumChildComponents(); i++) {
                TextEditor *te = dynamic_cast<TextEditor*>(getChildComponent(i));
                if (te) {
                    te->setText(qe->getFieldFromRow(row, owner.fieldNames.indexOf(te->getName())));
                    te->setEnabled(edit);
                }
            }
        }
    }
    //TODO
    void updateFromTransactionsMapForRow(QueryEntry *qe, std::map<String, String> rowUpdates, int row, bool dView, bool edit)
    {
        setDetailedView(dView);
        resized();
        this->row = row;
        
        for (int i=0; i<getNumChildComponents(); i++) {
            TextEditor *te = dynamic_cast<TextEditor*>(getChildComponent(i));
            if (te) {
                const StringArray key = (qe != nullptr) ? qe->getFieldFromRow(row, owner.getKeyField()) : StringArray();
                if (key.size() && (rowUpdates.find(te->getName()) != rowUpdates.end())) {
                    te->setText(rowUpdates[te->getName()]);
                }
                else {
                    te->setText(qe->getFieldFromRow(row, owner.fieldNames.indexOf(te->getName())));
                }
                te->setEnabled(edit);
            }
        }
    }
    //TODO: add function to addRemove transactions
    
private:
    // summary
    ScopedPointer<TextEditor> RecordDateTE, anrticlenumbertextTE, InvoiceTE, CommentsTE, RecordTypeTE, ReasoningTE;
    ScopedPointer<Label> RecordDate, anrticlenumbertext, Invoice, Comments, RecordType, Reasoning;
    
    // detailed
    OwnedArray<TextEditor> transactions;

};

//================================================================================

AccountsTableListBoxModel::AccountsTableListBoxModel(CacheSystemClient *ccc_)
: CoeusList(ccc_)
{
    update();
    rowSizes.calloc(1); //hack +1

/* TODO
    ScopedPointer<Label> accountLabel;
    ScopedPointer<Label> accountNameLabel;
    ScopedPointer<Label> creditLabel;
    ScopedPointer<Label> debtLabel;
 */
 
    fieldNames.add("RecordDate");
// TODO
//    fieldNames.add("anrticlenumbertext");
    
    fieldNames.add("Invoice");
    fieldNames.add("Comments");
    fieldNames.add("RecordType");
    fieldNames.add("Reasoning");
    
    tableName = "events";
}

Array<int> AccountsTableListBoxModel::getKeyField()
{
    Array<int> kf;
    kf.add(0);
    kf.add(1);
    return kf;
}

int AccountsTableListBoxModel::getNumRows()
{
    if (qe != nullptr) {
        return qe->num_rows;
    }
    else {
        return 0;
    }
}

int AccountsTableListBoxModel::getRowSize(int rowNumber)
{
    return (rowNumber >= 0 && rowNumber < getNumRows()) ? rowSizes[rowNumber] : 0;
}

void AccountsTableListBoxModel::paintRowBackground(Graphics &g, int rowNumber, int x, int y, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected) {
        g.setColour(Colour(0xff9d9d9d));
        g.fillRect(x, y, width, height);
    }
    else if (rowNumber == rowUnderMouse && (rowSizes[rowNumber] != AccountsRowComponent::maxRowSize)) {
        g.setColour(Colours::lightgrey.brighter().brighter());
        g.fillRect(x, y, width, height);
    }
    else if (getNumRows() && (rowSizes[rowNumber] == AccountsRowComponent::maxRowSize)) {
        g.setColour(Colour(Colour(0xffbebebe)));
        g.fillRect(x, y, width, height);
    }
}

CoeusListRowComponent * AccountsTableListBoxModel::refreshComponentForRow(int rowNumber, bool isRowSelected, CoeusListRowComponent *existingComponentToUpdate)
{
    // create
    if (existingComponentToUpdate == nullptr) {
        AccountsRowComponent *newComp = new AccountsRowComponent(*this);
        newComp->addMouseListener(this, true);
        newComp->addChangeListener(this);
        newComp->setRow(rowNumber);
        
        const bool dView = (rowNumber < getNumRows()) ? rowSizes[rowNumber] == AccountsRowComponent::maxRowSize : false;
        const StringArray keys = (qe != nullptr) ? qe->getFieldFromRow(rowNumber, getKeyField()) : StringArray();
        if (keys.size() && (rowsToUpdate.find(keys) != rowsToUpdate.end())) {
            newComp->updateFromMapForRow(qe, rowsToUpdate[keys], rowNumber, dView, editedRows.contains(rowNumber));
            newComp->updateFromTransactionsMapForRow(qe, rowsToUpdate[keys], rowNumber, dView, editedRows.contains(rowNumber));
        }
        else {
            newComp->updateFromQueryForRow(qe, rowNumber,  dView, editedRows.contains(rowNumber));
            newComp->updateFromTransactionsQueryForRow(qe, rowNumber,  dView, editedRows.contains(rowNumber));
        }
        newComp->shouldShowControls(isRowSelected || rowUnderMouse == rowNumber);
        
        return newComp;
    }
    // update
    else {
        AccountsRowComponent * cmp = dynamic_cast<AccountsRowComponent *>(existingComponentToUpdate);
        
        if(cmp) {
            const bool dView = (rowNumber < getNumRows()) ? rowSizes[rowNumber] == AccountsRowComponent::maxRowSize : false;
            const StringArray keys = (qe != nullptr) ? qe->getFieldFromRow(rowNumber, getKeyField()) : StringArray();
            if (keys.size() && (rowsToUpdate.find(keys) != rowsToUpdate.end())) {
                cmp->updateFromMapForRow(qe, rowsToUpdate[keys], rowNumber, dView, editedRows.contains(rowNumber));
                cmp->updateFromTransactionsMapForRow(qe, rowsToUpdate[keys], rowNumber, dView, editedRows.contains(rowNumber));
            }
            else {
                cmp->updateFromQueryForRow(qe, rowNumber,  dView, editedRows.contains(rowNumber));
                cmp->updateFromTransactionsQueryForRow(qeTransactions, rowNumber,  dView, editedRows.contains(rowNumber));
            }
            cmp->shouldShowControls(isRowSelected || rowUnderMouse == rowNumber);
        }
        
        return existingComponentToUpdate;
    }
}

void AccountsTableListBoxModel::setQueryEntryForTransactions(QueryEntry *qe_)
{
    if(qe_) {
        qeTransactions = qe_;
        rowSizes.realloc(qe->num_rows);
        // fill in row sizes
        for(int i=0; i<qe->num_rows; i++) {
            rowSizes[i] = getMinRowSize();
        }
        
        //TODO : add components for each row | consider using "pages"
        
        update();
        repaint();
    }
}

int AccountsTableListBoxModel::getMinRowSize()
{
    return AccountsRowComponent::minRowSize;
}

int AccountsTableListBoxModel::getMaxRowSize()
{
    return AccountsRowComponent::maxRowSize;
}

//================================================================

AccountsComponent::AccountsComponent()
{
    title->setText("Events", dontSendNotification);
    AccountsTableListBoxModel = new class AccountsTableListBoxModel(this);
    addAndMakeVisible(AccountsTableListBoxModel);
    AccountsTableListBoxModel->addChangeListener(this);
    
    tableHeader1->setText("Invoice", dontSendNotification);
    tableHeader2->setText("Date", dontSendNotification);
    tableHeader3->setText("Comments", dontSendNotification);
    tableHeader4->setText("Reasoning", dontSendNotification);
    
    //searchButtonPressed();
}

AccountsComponent::~AccountsComponent()
{
    AccountsTableListBoxModel = nullptr;
}

void AccountsComponent::resized()
{
    CustomTabContent::resized();
    Rectangle<int> compBounds = getComponentArea();
    compBounds.setY(compBounds.getY());
    AccountsTableListBoxModel->setBounds(compBounds);
}

void AccountsComponent::receivedResults(QueryEntry *qe_)
{
    if (qe_->num_fields > 1) {
        if (qe_->request.startsWith("SELECT * FROM events WHERE ")) {
            qe = qe_;
            AccountsTableListBoxModel->setQueryEntry(qe);
//            AccountsTableListBoxModel->update();
        }
        else {
            qeTransactions = qe_;
            AccountsTableListBoxModel->setQueryEntryForTransactions(qeTransactions);
            AccountsTableListBoxModel->update();
        }
    }
    else {
        // if update
        if (AccountsTableListBoxModel->savedpks.size()) {
            // fix this v
            StringArray pk = AccountsTableListBoxModel->savedpks[0];
            AccountsTableListBoxModel->wasSaved(pk);
        }
        // if delete
    }
}

void AccountsComponent::mouseExit(const MouseEvent &event)
{
    AccountsTableListBoxModel->mouseExit(event);
}

void AccountsComponent::searchButtonPressed()
{
    { // Common info
        String andOr = (searchFilter->getSelectedId() == 2) ? " AND " : " OR ";
        String orStr = " OR ";
        StringArray terms;
        terms.addTokens(search->getText(), true);
        
        String queryStr = "SELECT * FROM events WHERE ";
        
        for (int i = 0; i < terms.size(); i++) {
            queryStr += "Invoice like '%" + terms[i] + "%' " + orStr;
            queryStr += "RecordDate like '%" + terms[i] + "%' " + orStr;
            queryStr += "RecordType like '%" + terms[i] + "%' " + orStr;
            queryStr += "Comments like '%" + terms[i] + "%' " + orStr;
            queryStr += "Reasoning like '%" + terms[i] + "%' " + andOr;
        }
        
        queryStr += (searchFilter->getSelectedId() == 2 || terms.size() == 0) ? " 1 = 1" : " 1 = 0";
        
        std::cout << queryStr << std::endl;
        
        CacheSystem *cs = CacheSystem::getInstance();
        cs->getResultsFor(queryStr, QueryEntry::Accounts, this);
    }
    { // Event transactions
        String andOr = (searchFilter->getSelectedId() == 2) ? " AND " : " OR ";
        String orStr = " OR ";
        StringArray terms;
        terms.addTokens(search->getText(), true);
        
        String queryStr = "SELECT events2accounts.* FROM events RIGHT JOIN events2accounts ON events.invoice=events2accounts.invoice AND events.VAT=events2accounts.VAT WHERE ";
        
        for (int i = 0; i < terms.size(); i++) {
            queryStr += "events.Invoice like '%" + terms[i] + "%' " + orStr;
            queryStr += "events.RecordDate like '%" + terms[i] + "%' " + orStr;
            queryStr += "events.RecordType like '%" + terms[i] + "%' " + orStr;
            queryStr += "events.Comments like '%" + terms[i] + "%' " + orStr;
            queryStr += "events.Reasoning like '%" + terms[i] + "%' " + andOr;
            // TODO : add events2accounts field search
        }
        
        queryStr += (searchFilter->getSelectedId() == 2 || terms.size() == 0) ? " 1 = 1" : " 1 = 0";
        std::cout << queryStr << std::endl;
        
        CacheSystem *cs = CacheSystem::getInstance();
        cs->getResultsFor(queryStr, QueryEntry::Accounts, this);

    }
}

void AccountsComponent::addButtonPressed()
{
    
}

void AccountsComponent::saveButtonPressed()
{
    //    if (!editButton->getToggleState()) {
    //        //
    //        StringArray pkNames;
    //        pkNames.add("CustomerCode");
    //        pkNames.add("CustomerVAT");
    //
    //        AccountsTableListBoxModel->updateDatabaseTable("Accounts", pkNames, this);
    //
    //    }
    //
    //    AccountsTableListBoxModel->update();
}

void AccountsComponent::changeListenerCallback(ChangeBroadcaster *source)
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

CoeusListRowComponent * AccountsComponent::getAddComponent()
{
    return new AccountsRowComponent(*AccountsTableListBoxModel);
}
