#ifndef CustomersGuard
#define CustomersGuard

#include "../JuceLibraryCode/JuceHeader.h"
#include "CacheSystem.h"
#include "CustomComponents.h"
#include "CoeusList.h"

//=======================================================================================================
class CustomersTableListBoxModel : public CoeusList
{
public:
    CustomersTableListBoxModel();

    int getNumRows() override;
    int getRowSize(int rowNumber) override;
    int getMinRowSize() override;
    int getMaxRowSize() override;

    void paintRowBackground(Graphics &g, int rowNumber, int x, int y, int width, int height, bool rowIsSelected) override;
    CoeusListRowComponent * refreshComponentForRow(int rowNumber, bool isRowSelected, CoeusListRowComponent *existingComponentToUpdate) override;
};

//=======================================================================================================
class CustomersComponent :	public CustomTabContent,
							public CacheSystemClient
{
public:
	CustomersComponent();
	~CustomersComponent();

	void resized() override;
	void mouseExit(const MouseEvent &event) override;

	void receivedResults(QueryEntry *qe_) override;

	void searchButtonPressed() override;
	void addButtonPressed() override;
    void editButtonPressed() override;    
    
private:
	ScopedPointer<CustomersTableListBoxModel> customersTableListBoxModel;
	QueryEntry *qe;
};

#endif
