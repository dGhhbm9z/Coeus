#ifndef SuppliersGuard
#define SuppliersGuard

#include "../JuceLibraryCode/JuceHeader.h"
#include "CacheSystem.h"
#include "CustomComponents.h"

//=======================================================================================================
class SuppliersTableListBoxModel : public TableListBoxModel
{
public:
	SuppliersTableListBoxModel();

	int getNumRows() override;
	void paintRowBackground(Graphics &g, int rowNumber, int width, int height, bool rowIsSelected) override;
	void paintCell(Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
	Component * refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate) override;
	void setQueryEntry(QueryEntry *qe_);

private:
	QueryEntry *qe;
};

//=======================================================================================================
class SuppliersComponent :	public CustomTabContent,
							public CacheSystemClient
{
public:
	SuppliersComponent();
	~SuppliersComponent();

	void resized() override;
	void receivedResults(QueryEntry *qe_);

private:
	ScopedPointer<TableListBox> accounts;
	ScopedPointer<SuppliersTableListBoxModel> suppliersTableListBoxModel;
	QueryEntry *qe;
};

#endif