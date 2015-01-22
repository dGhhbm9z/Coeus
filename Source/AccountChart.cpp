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
    
    AccountChartRowComponent(CoeusList &owner_, bool addComp_) : CoeusListRowComponent(owner_, addComp_) {
        detailedView = false;
        showControls = false;
        
        // add fields
        // summary
        addAndMakeVisible(CodeTE = new CoeusListTextEditor("Code"));
        addAndMakeVisible(NameTE = new CoeusListTextEditor("Name"));
        addAndMakeVisible(AccountTypeTE = new CoeusListTextEditor("AccountType"));
        addAndMakeVisible(XreosPistTE = new CoeusListTextEditor("XreosPist"));

		if (!addComp) {
			CodeTE->addListener(&owner);
			NameTE->addListener(&owner);
			AccountTypeTE->addListener(&owner);
			XreosPistTE->addListener(&owner);
		}

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
        CodeTE->setBounds(lm, tm, teWS/2, teHS);
        NameTE->setBounds(lm+teWS/2+pad, tm, 2*teWS, teHS);
        AccountTypeTE->setBounds(lm+2*(teWS+pad)+teWS/2, tm, 150, teHS);
        XreosPistTE->setBounds(lm+2*(teWS+pad)+pad+150+teWS/2, tm, teWS/2, teHS);
    }
    
    void resizeForDetailed() override {
		// summary
		CodeTE->setBounds(lm, tm, teWS / 2, teHS);
		NameTE->setBounds(lm + teWS / 2 + pad, tm, 2 * teWS, teHS);
		AccountTypeTE->setBounds(lm + 2 * (teWS + pad) + teWS / 2, tm, 150, teHS);
		XreosPistTE->setBounds(lm + 2 * (teWS + pad) + pad + 150 + teWS / 2, tm, teWS / 2, teHS);

    }
    
    void updateRow() {
        
    }
    
    void insertRow() {
        
    }
    
    void shouldShowControls(bool show) override {
		showControls = show;
		details->setVisible(false);
		editButton->setVisible(show && !addComp);
		saveButton->setVisible(show);
		setDetailedView(detailedView, true);
    }
    
private:
    // summary
    ScopedPointer<TextEditor> CodeTE, NameTE, AccountTypeTE, XreosPistTE;
};

//================================================================================

AccountChartTableListBoxModel::AccountChartTableListBoxModel(CacheSystemClient *ccc_)
: CoeusList(ccc_)
{
    update();
    rowSizes.calloc(1); //hack +1

    fieldNames.add("VAT");
    fieldNames.add("Code");
    fieldNames.add("Name");
    fieldNames.add("AccountType");
    fieldNames.add("XreosPist");
    
    tableName = "accounts";
}

Array<int> AccountChartTableListBoxModel::getKeyField()
{
    Array<int> kf;
    kf.add(0);
    kf.add(1);
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
        g.setColour(Colour(0xff9d9d9d));
        g.fillRect(x, y, width, height);
    }
    else if (rowNumber == rowUnderMouse && (rowSizes[rowNumber] != AccountChartRowComponent::maxRowSize)) {
        g.setColour(Colours::lightgrey.brighter().brighter());
        g.fillRect(x, y, width, height);
    }
    else if (getNumRows() && (rowSizes[rowNumber] == AccountChartRowComponent::maxRowSize)) {
        g.setColour(Colour(Colour(0xffbebebe)));
        g.fillRect(x, y, width, height);
    }
}

CoeusListRowComponent * AccountChartTableListBoxModel::refreshComponentForRow(int rowNumber, bool isRowSelected, CoeusListRowComponent *existingComponentToUpdate)
{
    // create
    if (existingComponentToUpdate == nullptr) {
        AccountChartRowComponent *newComp = new AccountChartRowComponent(*this, false);
        newComp->addMouseListener(this, true);
        newComp->addChangeListener(this);
        newComp->setRow(rowNumber);
        
        const bool dView = (rowNumber < getNumRows()) ? rowSizes[rowNumber] == AccountChartRowComponent::maxRowSize : false;
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
        AccountChartRowComponent * cmp = dynamic_cast<AccountChartRowComponent *>(existingComponentToUpdate);
        
        if(cmp) {
            const bool dView = (rowNumber < getNumRows()) ? rowSizes[rowNumber] == AccountChartRowComponent::maxRowSize : false;
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
    accountChartTableListBoxModel = new AccountChartTableListBoxModel(this);
    addAndMakeVisible(accountChartTableListBoxModel);
    accountChartTableListBoxModel->addChangeListener(this);
    
    tableHeader1->setText("Code", dontSendNotification);
    tableHeader2->setText("Name", dontSendNotification);
    tableHeader3->setText("Type", dontSendNotification);
    tableHeader4->setText("Total", dontSendNotification);
    
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
	compBounds.setHeight(compBounds.getHeight() - bottomDemo->getHeight());
//	compBounds.setWidth(compBounds.getWidth());
    accountChartTableListBoxModel->setBounds(compBounds);
    
    const int starty = compBounds.getY()-40;
    const int lm = 4;
    const int tm = 2;
    const int pad = 4;
    const int teHS = 40;
    const int teWS = 250;
    
    tableHeader1->setBounds(lm, starty+tm, teWS/2, teHS);
    tableHeader2->setBounds(lm+teWS/2+pad, starty+tm, teWS+teWS/2, teHS);
    tableHeader3->setBounds(lm+2*(teWS+pad)+teWS/2, starty+tm, 150, teHS);
    tableHeader4->setBounds(lm+2*(teWS+pad)+pad+150+teWS/2, starty+tm, teWS/2, teHS);
}

void AccountChartComponent::receivedResults(QueryEntry *qe_)
{
    if (qe_->num_fields > 1) {
        qe = qe_;
        accountChartTableListBoxModel->setQueryEntry(qe);
        accountChartTableListBoxModel->update();
    }
    else {
        // if update
        if (accountChartTableListBoxModel->savedpks.size()) {
            // fix this v
            StringArray pk = accountChartTableListBoxModel->savedpks[0];
            accountChartTableListBoxModel->wasSaved(pk);
        }
        // if delete
        else {
            searchButtonPressed();
        }
    }
    
    addOverlayComp->setVisible(false);
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

void AccountChartComponent::saveButtonPressed()
{

//    if (!editButton->getToggleState()) {
//        //
//        StringArray pkNames;
//        pkNames.add("VAT");
//
//        accountChartTableListBoxModel->updateDatabaseTable("accounts", pkNames, this);
//
//    }
//
//    accountChartTableListBoxModel->update();
}

void AccountChartComponent::removeButtonPressed()
{
    accountChartTableListBoxModel->removeSelectedDatabaseTableEntries(this);
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

CoeusListRowComponent * AccountChartComponent::getAddComponent()
{
    return new AccountChartRowComponent(*accountChartTableListBoxModel, true);
}
