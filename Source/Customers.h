#ifndef CustomersGuard
#define CustomersGuard

#include "../JuceLibraryCode/JuceHeader.h"
#include "CacheSystem.h"
#include "CustomComponents.h"

//=======================================================================================================
class CustomersTableListBoxModel :	public TableListBoxModel,
									public TableListBox,
									public ChangeListener
{
public:
	CustomersTableListBoxModel();

	int getNumRows() override;
	void paintRowBackground(Graphics &g, int rowNumber, int width, int height, bool rowIsSelected) override;
	void paintCell(Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
	Component * refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate) override;
	void setQueryEntry(QueryEntry *qe_);

	void changeListenerCallback(ChangeBroadcaster *source) override;
	void mouseMove(const MouseEvent &event) override;
	void mouseExit(const MouseEvent &event) override;

private:
	QueryEntry *qe;
	int rowUnderMouse;
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

private:
	ScopedPointer<CustomersTableListBoxModel> customersTableListBoxModel;
	QueryEntry *qe;
};

#endif