#ifndef CustomersGuard
#define CustomersGuard

#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomComponents.h"

//=======================================================================================================
class CustomersTableListBoxModel : public TableListBoxModel
{
	int getNumRows() override;
	void paintRowBackground(Graphics &g, int rowNumber, int width, int height, bool rowIsSelected) override;
	void paintCell(Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
	Component * refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate) override;
};

//=======================================================================================================
class CustomersComponent : public CustomTabContent
{
public:
	CustomersComponent();
	~CustomersComponent();
	void resized() override;

private:
	ScopedPointer<TableListBox> customers;
	ScopedPointer<CustomersTableListBoxModel> customersTableListBoxModel;
};

#endif