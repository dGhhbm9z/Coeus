#ifndef AccountChartGuard
#define AccountChartGuard

#include "../JuceLibraryCode/JuceHeader.h"
#include "CacheSystem.h"
#include "CustomComponents.h"
#include "CoeusList.h"

//=======================================================================================================
class AccountChartTableListBoxModel : public CoeusList
{
public:
    AccountChartTableListBoxModel(CacheSystemClient *ccc_);
    
    int getNumRows() override;
    int getRowSize(int rowNumber) override;
    int getMinRowSize() override;
    int getMaxRowSize() override;
    Array<int> getKeyField() override;
    
    void paintRowBackground(Graphics &g, int rowNumber, int x, int y, int width, int height, bool rowIsSelected) override;
    CoeusListRowComponent * refreshComponentForRow(int rowNumber, bool isRowSelected, CoeusListRowComponent *existingComponentToUpdate) override;
};

//=======================================================================================================
class AccountChartComponent :	public CustomTabContent,
                                public CacheSystemClient
{
public:
    AccountChartComponent();
    ~AccountChartComponent();
    
    void resized() override;
    void mouseExit(const MouseEvent &event) override;
    
    void receivedResults(QueryEntry *qe_) override;
    
    void searchButtonPressed() override;
	void addButtonPressed() override;
    void saveButtonPressed() override;
    void changeListenerCallback(ChangeBroadcaster *source) override;
    
private:
    ScopedPointer<AccountChartTableListBoxModel> accountChartTableListBoxModel;
    QueryEntry *qe;
};

#endif
