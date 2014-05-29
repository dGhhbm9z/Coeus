#include "AccountChart.h"
#include "PortDefinitions.h"
#include "CacheViewer.h"

int AccountChartsListBoxModel::getNumRows() 
{
	return 8;
}

void AccountChartsListBoxModel::paintListBoxItem(int rowNumber, Graphics &g, int width, int height, bool rowIsSelected) 
{
	/*g.fillAll(Colours::grey);
	g.setColour(Colours::black);
	g.drawRect(Rectangle<float>(0,0,width+1,height+1));
	g.setColour(Colours::azure);
	g.drawText(String(rowNumber), Rectangle<int>(0,0,width,height), Justification::centred, false);*/
}

Component* AccountChartsListBoxModel::refreshComponentForRow(int rowNumber, bool isRowSelected, Component *existingComponentToUpdate) 
{
	// create
	if (existingComponentToUpdate == nullptr) {
		Component *newComponent = (Component *) new CacheViewer();
		return newComponent;
	}
	// update
	else {
		return existingComponentToUpdate;
	}
}

//========================================================================================

AccountChartComponent::AccountChartComponent() 
{
	accountChartListBoxModel = new AccountChartsListBoxModel();
	accountChart = new ListBox(String::empty, accountChartListBoxModel);
	accountChart->setRowHeight(620);

	addAndMakeVisible(accountChart);
}

AccountChartComponent::~AccountChartComponent() 
{
	accountChart = nullptr;
}

void AccountChartComponent::resized() 
{
	accountChart->setBounds(0.01f*getWidth(), 0.01f*getHeight(), getWidth() - 0.01f*getWidth(), getHeight() - 0.01f*getHeight());
}