#ifndef CompaniesGuard
#define CompaniesGuard

#include "../JuceLibraryCode/JuceHeader.h"
#include "CacheSystem.h"
#include "CustomComponents.h"
#include "CoeusList.h"

//=======================================================================================================
class CompaniesTableListBoxModel : public CoeusList,
									public ChangeListener
{
public:
	CompaniesTableListBoxModel();
    
    void paint(Graphics &g);

	int getNumRows() override;
    int getMinRowSize() override;
    int getMaxRowSize() override;
    int getRowSize(int rowNumber) override;
    
    void paintRowBackground(Graphics &g, int rowNumber, int x, int y, int width, int height, bool rowIsSelected) override;
    CoeusListRowComponent * refreshComponentForRow(int rowNumber, bool isRowSelected, CoeusListRowComponent *existingComponentToUpdate) override;
	void setQueryEntry(QueryEntry *qe_);

	void changeListenerCallback(ChangeBroadcaster *source) override;
	void mouseMove(const MouseEvent &event) override;
	void mouseExit(const MouseEvent &event) override;
    void mouseDown (const MouseEvent &event) override;
    void mouseWheelMove (const MouseEvent &event, const MouseWheelDetails &wheel) override;

private:
	QueryEntry *qe;
	int rowUnderMouse;
    HeapBlock<int> rowSizes;
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

private:
	ScopedPointer<CompaniesTableListBoxModel> companiesTableListBoxModel;
	QueryEntry *qe;
};

#endif
