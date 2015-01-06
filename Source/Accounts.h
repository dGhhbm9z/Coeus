#ifndef AccountsGuard
#define AccountsGuard

#include "../JuceLibraryCode/JuceHeader.h"
#include "CacheSystem.h"
#include "CustomComponents.h"
#include "CoeusList.h"

//=======================================================================================================
class AccountsTableListBoxModel : public CoeusList
{
public:
    AccountsTableListBoxModel(CacheSystemClient *ccc_);
    
    int getNumRows() override;
    int getRowSize(int rowNumber) override;
    int getMinRowSize() override;
    int getMaxRowSize() override;
    Array<int> getKeyField() override;
    
    void paintRowBackground(Graphics &g, int rowNumber, int x, int y, int width, int height, bool rowIsSelected) override;
    CoeusListRowComponent * refreshComponentForRow(int rowNumber, bool isRowSelected, CoeusListRowComponent *existingComponentToUpdate) override;
};

//=======================================================================================================
class AccountsComponent :	public CustomTabContent,
public CacheSystemClient
{
public:
    AccountsComponent();
    ~AccountsComponent();
    
    void resized() override;
    void mouseExit(const MouseEvent &event) override;
    
    void receivedResults(QueryEntry *qe_) override;
    
    void searchButtonPressed() override;
    void addButtonPressed() override;
    void saveButtonPressed() override;
    void changeListenerCallback(ChangeBroadcaster *source) override;
    
    CoeusListRowComponent *getAddComponent() override;
    
private:
    ScopedPointer<AccountsTableListBoxModel> AccountsTableListBoxModel;
    ScopedPointer<QueryEntry> qe;
};

#endif
