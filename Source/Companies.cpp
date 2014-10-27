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

        // add fields
        addAndMakeVisible(companyNameTE = new TextEditor());
        addAndMakeVisible(legalIncTE = new TextEditor());
        addAndMakeVisible(telephoneTE = new TextEditor());
        addAndMakeVisible(activityTE = new TextEditor());

        // control
        addAndMakeVisible(edit = new TextButton(L"edit"));
        addAndMakeVisible(save = new TextButton(L"save"));
        addAndMakeVisible(remove = new TextButton(L"remove"));

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
        setDetailedView(detailedView, true);
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

            const int btnW=66;
            edit->setBounds(lm+3*(teWS+pad)+pad+150+10, tm, btnW, teHS);
            save->setBounds(lm+3*(teWS+pad)+pad+150+10+btnW, tm, btnW, teHS);
            remove->setBounds(lm+3*(teWS+pad)+pad+150+10+2*btnW, tm, btnW, teHS);
        }
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

void CompaniesTableListBoxModel::paint(Graphics &g)
{
    for(int i=0; i<getNumRows(); i++) {
        paintRowBackground(g, i, 0, getYStartForRow(i), getWidth(), getRowSize(i), selectedRow == i);
    }
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

        const bool dView = false;//(rowSizes[rowNumber] == CompaniesRowComponent::maxRowSize);
        newComp->updateFromQueryForRow(qe, rowNumber,  dView);

		return newComp;
	}
	// update
	else {
        CompaniesRowComponent * cmp = dynamic_cast<CompaniesRowComponent *>(existingComponentToUpdate);

        if(cmp) {
            cmp->updateFromQueryForRow(qe, rowNumber, rowSizes[rowNumber] == CompaniesRowComponent::maxRowSize);
        }

		return existingComponentToUpdate;
	}
}

void CompaniesTableListBoxModel::setQueryEntry(QueryEntry *qe_)
{
    if(qe_) {
        qe = qe_;
        rowSizes.realloc(qe->num_rows+1); //hack +1
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

    if (rcomp) {
        selectRow(rcomp->row);
        const int prevR = rowUnderMouse;
        rowUnderMouse = rcomp->row;
        repaintRow(rowUnderMouse);
        repaintRow(prevR);
    }
}

void CompaniesTableListBoxModel::mouseMove(const MouseEvent &event)
{
    CoeusListRowComponent *rcomp = dynamic_cast<CoeusListRowComponent *>(event.eventComponent);
    Component *parent = event.eventComponent->getParentComponent();;
    
    while (!rcomp && parent) {
        rcomp = dynamic_cast<CoeusListRowComponent *>(parent);
        parent = parent->getParentComponent();
    }
    
    if (rcomp) {
        const int r = rcomp->row;
        if (r != rowUnderMouse) {
            const int prevR = rowUnderMouse;
            rowUnderMouse = r;
            repaintRow(rowUnderMouse);
            repaintRow(prevR);
        }
    }
}

void CompaniesTableListBoxModel::mouseExit(const MouseEvent &event)
{
	const int prevR = rowUnderMouse;
	rowUnderMouse = -1;
	repaintRow(rowUnderMouse);
	repaintRow(prevR);
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



	CacheSystem *cs = CacheSystem::getInstance();
    cs->getResultsFor(queryStr, QueryEntry::Companies, this);
    
	std::cout << queryStr << std::endl;
}
