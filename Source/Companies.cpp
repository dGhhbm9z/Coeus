#include "Companies.h"
#include "CustomComponents.h"
#include "Accounts.h"

class CompaniesRowComponent :   public CoeusListRowComponent,
                                public ButtonListener
{
public:
    CompaniesRowComponent() {
        detailedView = true;
        editView = false;
        showControls = false;

        // add fields
        addAndMakeVisible(companyNameTE = new TextEditor());
        addAndMakeVisible(legalIncTE = new TextEditor());
        addAndMakeVisible(telephoneTE = new TextEditor());
        addAndMakeVisible(activityTE = new TextEditor());

        // control
        addAndMakeVisible(edit = new TextButton(L"edit"));
        addAndMakeVisible(save = new TextButton(L"save"));
        addAndMakeVisible(remove = new TextButton(L"remove"));

        edit->addListener(this);
        save->addListener(this);
        remove->addListener(this);
        
        setDetailedView(false);
    }

    ~CompaniesRowComponent() {
    }

    void paint(Graphics &g) {
//        g.fillAll(Colours::darkgreen);
    }

    void buttonClicked (Button *btn) override {
        if (btn == edit) {

        }
        else if (btn == save) {

        }
        else {
            setDetailedView(!detailedView);
            sendChangeMessage();
        }
    }

    static const int minRowSize = 40;
    static const int maxRowSize = 200;

    int getCoeusListHeight() override {
        if (detailedView) {
            return maxRowSize;
        }

        return minRowSize;
    }

    void resized() {
        setDetailedView(detailedView, true);
    }

    void updateFromQueryForRow(QueryEntry *qe, int row, bool dView) override {
        setDetailedView(dView, true);
        this->row = row;
        if(qe) {
            // summary
            companyNameTE->setText(qe->getFieldFromRow(row, 0));
            legalIncTE->setText(qe->getFieldFromRow(row, 1));
            telephoneTE->setText(qe->getFieldFromRow(row, 2));
            activityTE->setText(qe->getFieldFromRow(row, 3));
            // detailed

        }
    }

    void setDetailedView(bool s, bool force=false) {
        if (detailedView != s || force) {
            detailedView = s;
            const int lm = 4;
            const int tm = 2;
            const int bm = 2;
            const int pad = 4;
            const int teHS = minRowSize - tm - bm;
            const int teWS = 250;

            if(s) {
                // detailed
                companyNameTE->setBounds(lm, tm, teWS, teHS);
                legalIncTE->setBounds(lm+teWS+pad, tm+teHS, teWS, teHS);
                telephoneTE->setBounds(lm+2*(teWS+pad), tm+2*teHS, 150, teHS);
                activityTE->setBounds(lm+2*(teWS+pad)+pad+150, tm+3*teHS, teWS, teHS);
            }
            else {
                // summary
                companyNameTE->setBounds(lm, tm, teWS, teHS);
                legalIncTE->setBounds(lm+teWS+pad, tm, teWS, teHS);
                telephoneTE->setBounds(lm+2*(teWS+pad), tm, 150, teHS);
                activityTE->setBounds(lm+2*(teWS+pad)+pad+150, tm, teWS, teHS);
            }

            if (showControls) {
                const int btnW=66;
                edit->setBounds(lm+3*(teWS+pad)+pad+150+10, tm, btnW, teHS);
                save->setBounds(lm+3*(teWS+pad)+pad+150+10+btnW, tm, btnW, teHS);
                remove->setBounds(lm+3*(teWS+pad)+pad+150+10+2*btnW, tm, btnW, teHS);
            }
        }
    }

    void shouldShowControls(bool show) {
        showControls = show;
        edit->setVisible(show);
        save->setVisible(show);
        remove->setVisible(show);
        setDetailedView(detailedView, true);
    }
    
private:
    // summary
    ScopedPointer<TextEditor> companyNameTE, legalIncTE, telephoneTE, activityTE;

    // detailed
    ScopedPointer<TextEditor> VAT, IRS, Address, AddressNumber, PersonInCharge, StartDate, Comments;

    // control buttons
    ScopedPointer<TextButton> edit, save, remove;
};

//================================================================================

CompaniesTableListBoxModel::CompaniesTableListBoxModel() : qe(nullptr), rowUnderMouse(-1)
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

int CompaniesTableListBoxModel::getMinRowSize()
{
    return CompaniesRowComponent::minRowSize;
}

int CompaniesTableListBoxModel::getMaxRowSize()
{
    return CompaniesRowComponent::maxRowSize;
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
        newComp->row = rowNumber;

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

void CompaniesTableListBoxModel::setQueryEntry(QueryEntry *qe_)
{
    if(qe_) {
        qe = qe_;
        rowSizes.realloc(qe->num_rows);
        // fill in row sizes
        for(int i=0; i<qe->num_rows; i++) {
            rowSizes[i] = getMinRowSize();
        }
        update();
    }
}

void CompaniesTableListBoxModel::changeListenerCallback(ChangeBroadcaster *source)
{
    // row changed size
    CoeusListRowComponent *rcomp = dynamic_cast<CoeusListRowComponent*>(source);
    if(rcomp) {
        const int row = rcomp->row;
        if (row >= 0 && row < getNumRows()) {
            rowSizes[row] = rcomp->getCoeusListHeight();
            rowChangedSize(row, getRowSize(row));
        }
    }
}

void CompaniesTableListBoxModel::mouseDown (const MouseEvent &event)
{
    // selected row
    CoeusListRowComponent *rcomp = dynamic_cast<CoeusListRowComponent *>(event.eventComponent);
    Component *parent = event.eventComponent->getParentComponent();
    
    while (!rcomp && parent) {
        rcomp = dynamic_cast<CoeusListRowComponent *>(parent);
        parent = parent->getParentComponent();
    }

    if (rcomp && (selectedRow[0] != rcomp->row)) {
        CoeusListRowComponent *prevComp = dynamic_cast<CoeusListRowComponent*>(getComponentForRow(selectedRow[0]));
        
        // select new row
        const int prevR = selectedRow[0];
        selectRow(rcomp->row);
        
        // show/hide controls
        rcomp->shouldShowControls(true);
        if (prevComp) {
            prevComp->shouldShowControls(false);
        }
        
        // repaint
//        repaintRow(selectedRow[0]);
        repaintRow(prevR);
    }
}

void CompaniesTableListBoxModel::mouseMove(const MouseEvent &event)
{
    CoeusListRowComponent *rcomp = dynamic_cast<CoeusListRowComponent *>(event.eventComponent);
    Component *parent = event.eventComponent->getParentComponent();
    
    while (!rcomp && parent) {
        rcomp = dynamic_cast<CoeusListRowComponent *>(parent);
        parent = parent->getParentComponent();
    }
    
    if (rcomp && (rowUnderMouse != rcomp->row)) {
        CoeusListRowComponent *prevComp = dynamic_cast<CoeusListRowComponent*>(getComponentForRow(rowUnderMouse));
        
        // select new row
        const int prevR = rowUnderMouse;
        rowUnderMouse = rcomp->row;
        
        // show/hide controls
        rcomp->shouldShowControls(true);
        
        if (prevComp && (prevComp->row != selectedRow[0])) {
            prevComp->shouldShowControls(false);
        }
        
        // repaint
        // TODO: remove after repaitRow todo
//        repaintRow(rowUnderMouse);
        repaintRow(prevR);
    }
}

void CompaniesTableListBoxModel::mouseExit(const MouseEvent &event)
{
//    if (event.eventComponent == this) {
//        const int prevR = rowUnderMouse;
//        CoeusListRowComponent *prevComp = dynamic_cast<CoeusListRowComponent*>(getComponentForRow(rowUnderMouse));
//        if(prevComp && (prevComp->row != selectedRow)) {
//            prevComp->shouldShowControls(false);
//        }
//        rowUnderMouse = -1;
//        repaintRow(prevR);
//    }
}

void CompaniesTableListBoxModel::mouseWheelMove (const MouseEvent &event, const MouseWheelDetails &wheel)
{
    const double cStart = sb.getCurrentRangeStart();
    const double nCStart = cStart + wheel.deltaY;
    sb.setCurrentRangeStart(nCStart);
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
