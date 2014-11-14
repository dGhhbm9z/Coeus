#ifndef SuppliersGuard
#define SuppliersGuard

#include "../JuceLibraryCode/JuceHeader.h"
#include "CacheSystem.h"
#include "CustomComponents.h"
#include "CoeusList.h"

//=======================================================================================================
class SuppliersTableListBoxModel : public CoeusList
{
public:
    SuppliersTableListBoxModel();
    
    int getNumRows() override;
    int getRowSize(int rowNumber) override;
    int getMinRowSize() override;
    int getMaxRowSize() override;
    
    void paintRowBackground(Graphics &g, int rowNumber, int x, int y, int width, int height, bool rowIsSelected) override;
    CoeusListRowComponent * refreshComponentForRow(int rowNumber, bool isRowSelected, CoeusListRowComponent *existingComponentToUpdate) override;
};

//=======================================================================================================
class SuppliersComponent :	public CustomTabContent,
public CacheSystemClient
{
public:
    SuppliersComponent();
    ~SuppliersComponent();
    
    void resized() override;
    void mouseExit(const MouseEvent &event) override;
    
    void receivedResults(QueryEntry *qe_) override;
    
    void searchButtonPressed() override;
    
private:
    ScopedPointer<SuppliersTableListBoxModel> suppliersTableListBoxModel;
    QueryEntry *qe;
};

#endif
