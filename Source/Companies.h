#ifndef CompaniesGuard
#define CompaniesGuard

#include "../JuceLibraryCode/JuceHeader.h"
#include "CacheSystem.h"
#include "CustomComponents.h"
#include "CoeusList.h"

//=======================================================================================================
class CompaniesTableListBoxModel : public CoeusList
{
public:
	CompaniesTableListBoxModel();

	int getNumRows() override;
    int getRowSize(int rowNumber) override;
    int getMinRowSize() override;
    int getMaxRowSize() override;
    
    void paintRowBackground(Graphics &g, int rowNumber, int x, int y, int width, int height, bool rowIsSelected) override;
    CoeusListRowComponent * refreshComponentForRow(int rowNumber, bool isRowSelected, CoeusListRowComponent *existingComponentToUpdate) override;
};

//=======================================================================================================
class CompaniesComponent :	public CustomTabContent,
							public CacheSystemClient
{
public:
	CompaniesComponent();
	~CompaniesComponent();

	void resized() override;
    
	void mouseExit(const MouseEvent &event) override;

	void receivedResults(QueryEntry *qe_) override;

	void searchButtonPressed() override;
	void addButtonPressed() override;
    void editButtonPressed() override;
    void changeListenerCallback(ChangeBroadcaster *source) override;

private:
	ScopedPointer<CompaniesTableListBoxModel> companiesTableListBoxModel;    
	QueryEntry *qe;
};

#endif
