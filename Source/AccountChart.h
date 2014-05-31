#ifndef AccountChartGuard
#define AccountChartGuard

#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomComponents.h"

//=======================================================================================================
class AccountChartsListBoxModel : public ListBoxModel
{
public:
	int getNumRows() override;
	void paintListBoxItem(int rowNumber, Graphics &g, int width, int height, bool rowIsSelected) override;
	Component* refreshComponentForRow(int rowNumber, bool isRowSelected, Component *existingComponentToUpdate) override;
};

class AccountChartComponent : public CustomTabContent
{
public:
	AccountChartComponent();
	~AccountChartComponent();

	void resized() override;

	void searchButtonPressed() override;

private:
	ScopedPointer<ListBox> accountChart;
	ScopedPointer<AccountChartsListBoxModel> accountChartListBoxModel;
};

#endif