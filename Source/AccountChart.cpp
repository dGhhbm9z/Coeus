#include "AccountChart.h"
#include "CustomComponents.h"

class AccountChartRowComponent :   public CoeusListRowComponent
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
    
    AccountChartRowComponent(CoeusList &owner_) : CoeusListRowComponent(owner_) {
        detailedView = false;
        editView = false;
        showControls = false;
        
        // add fields
        // summary
        addAndMakeVisible(CodeTE = new TextEditor("Code"));
        addAndMakeVisible(NameTE = new TextEditor("Name"));
        addAndMakeVisible(AccountTypeTE = new TextEditor("AccountType"));
        addAndMakeVisible(XreosPistTE = new TextEditor("XreosPist"));

        CodeTE->addListener(&owner);
        NameTE->addListener(&owner);
        AccountTypeTE->addListener(&owner);
        XreosPistTE->addListener(&owner);
        
        resized();
    }
    
    ~AccountChartRowComponent() {
    }
    
    int getCoeusListHeight() override {
//        if (detailedView) {
//            return maxRowSize;
//        }
        
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
        CodeTE->setBounds(lm, tm, teWS, teHS);
        NameTE->setBounds(lm+teWS+pad, tm, teWS, teHS);
        AccountTypeTE->setBounds(lm+2*(teWS+pad), tm, 150, teHS);
        XreosPistTE->setBounds(lm+2*(teWS+pad)+pad+150, tm, teWS, teHS);
    }
    
    void resizeForDetailed() override {
        CodeTE->setBounds(lm+teWS+pad, tm+teHS, teWS, teHS);
        NameTE->setBounds(lm+teWS+pad, tm+2*teHS, teWS, teHS);
        AccountTypeTE->setBounds(lm+teWS+pad, tm+3*teHS, 150, teHS);
        XreosPistTE->setBounds(lm+teWS+pad, tm+4*teHS, teWS, teHS);

    }
    
    int fieldNameToIndex(String fname) const override {
        if (fname.equalsIgnoreCase("Code")) {
            return 1;
        }
        else if (fname.equalsIgnoreCase("Name")) {
            return 2;
        }
        else if (fname.equalsIgnoreCase("AccountType")) {
            return 3;
        }
        else if (fname.equalsIgnoreCase("XreosPist")) {
            return 4;
        }
        
        return 1;
    }
    
    void updateRow() {
        
    }
    
    void insertRow() {
        
    }
    
    void shouldShowControls(bool show) override {
        showControls = false;
        details->setVisible(false);
    }
    
private:
    // summary
    ScopedPointer<TextEditor> CodeTE, NameTE, AccountTypeTE, XreosPistTE;
};

//================================================================================

AccountChartTableListBoxModel::AccountChartTableListBoxModel()
{
    update();
    rowSizes.calloc(1); //hack +1
}

Array<int> AccountChartTableListBoxModel::getKeyField()
{
    Array<int> kf;
    kf.add(0);
    return kf;
}

int AccountChartTableListBoxModel::getNumRows()
{
    if (qe != nullptr) {
        return qe->num_rows;
    }
    else {
        return 0;
    }
}

int AccountChartTableListBoxModel::getRowSize(int rowNumber)
{
    return (rowNumber >= 0 && rowNumber < getNumRows()) ? rowSizes[rowNumber] : 0;
}

void AccountChartTableListBoxModel::paintRowBackground(Graphics &g, int rowNumber, int x, int y, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected) {
        g.setColour(Colours::grey.brighter().brighter());
        g.fillRect(x, y, width, height);
    }
    else if (rowNumber == rowUnderMouse) {
        g.setColour(Colours::lightgrey.brighter().brighter());
        g.fillRect(x, y, width, height);
    }
    else if (getNumRows() && (rowSizes[rowNumber] == AccountChartRowComponent::maxRowSize)) {
        g.setColour(Colours::lightgrey.brighter().brighter().brighter());
        g.fillRect(x, y, width, height);
    }
}

CoeusListRowComponent * AccountChartTableListBoxModel::refreshComponentForRow(int rowNumber, bool isRowSelected, CoeusListRowComponent *existingComponentToUpdate)
{
    // create
    if (existingComponentToUpdate == nullptr) {
        AccountChartRowComponent *newComp = new AccountChartRowComponent(*this);
        newComp->addMouseListener(this, true);
        newComp->addChangeListener(this);
        newComp->setRow(rowNumber);
        
        const bool dView = (rowNumber < getNumRows()) ? rowSizes[rowNumber] == AccountChartRowComponent::maxRowSize : false;
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
        AccountChartRowComponent * cmp = dynamic_cast<AccountChartRowComponent *>(existingComponentToUpdate);
        
        if(cmp) {
            const bool dView = (rowNumber < getNumRows()) ? rowSizes[rowNumber] == AccountChartRowComponent::maxRowSize : false;
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

int AccountChartTableListBoxModel::getMinRowSize()
{
    return AccountChartRowComponent::minRowSize;
}

int AccountChartTableListBoxModel::getMaxRowSize()
{
    return AccountChartRowComponent::maxRowSize;
}

//================================================================

AccountChartComponent::AccountChartComponent()
{
    title->setText("AccountChart", dontSendNotification);
    accountChartTableListBoxModel = new AccountChartTableListBoxModel();
    addAndMakeVisible(accountChartTableListBoxModel);
    accountChartTableListBoxModel->addChangeListener(this);
    
    tableHeader1->setText("Code", dontSendNotification);
    tableHeader2->setText("Name", dontSendNotification);
    tableHeader3->setText("Type", dontSendNotification);
    tableHeader4->setText("XreosPist", dontSendNotification);
    
    //searchButtonPressed();
}

AccountChartComponent::~AccountChartComponent()
{
    accountChartTableListBoxModel = nullptr;
}

void AccountChartComponent::resized()
{
    CustomTabContent::resized();
    Rectangle<int> compBounds = getComponentArea();
    accountChartTableListBoxModel->setBounds(compBounds);
}

void AccountChartComponent::receivedResults(QueryEntry *qe_)
{
    qe = qe_;
    accountChartTableListBoxModel->setQueryEntry(qe);
    accountChartTableListBoxModel->update();
}

void AccountChartComponent::mouseExit(const MouseEvent &event)
{
    accountChartTableListBoxModel->mouseExit(event);
}

void AccountChartComponent::searchButtonPressed()
{
    String andOr = (searchFilter->getSelectedId() == 2) ? " AND " : " OR ";
    String orStr = " OR ";
    StringArray terms;
    terms.addTokens(search->getText(), true);
    
    String queryStr = "SELECT * FROM accounts WHERE ";
    
    for (int i = 0; i < terms.size(); i++) {
        queryStr += "Code like '%" + terms[i] + "%' " + orStr;
        queryStr += "Name like '%" + terms[i] + "%' " + orStr;
        queryStr += "AccountType like '%" + terms[i] + "%' " + orStr;
        queryStr += "XreosPist like '%" + terms[i] + "%' " + andOr;
    }
    queryStr += (searchFilter->getSelectedId() == 2 || terms.size() == 0) ? " 1 = 1" : " 1 = 0";
    
    CacheSystem *cs = CacheSystem::getInstance();
    cs->getResultsFor(queryStr, QueryEntry::Accounts, this);
    
    std::cout << queryStr << std::endl;
}

void AccountChartComponent::addButtonPressed()
{
    // show add overlay
}

void AccountChartComponent::editButtonPressed()
{
    accountChartTableListBoxModel->setEdit(editButton->getToggleState());

    if (!editButton->getToggleState()) {
        //
        StringArray pkNames;
        pkNames.add("VAT");

        accountChartTableListBoxModel->updateDatabaseTable("accounts", pkNames, this);

    }

    accountChartTableListBoxModel->update();
}

void AccountChartComponent::changeListenerCallback(ChangeBroadcaster *source)
{
    CoeusListRowComponent *src = dynamic_cast<CoeusListRowComponent*>(source);
    if(src && src->isDetailed()) {
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
