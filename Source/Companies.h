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

	int getNumRows() override;
	void paintRowBackground(Graphics &g, int rowNumber, int width, int height, bool rowIsSelected) override;
	void paintRow(Graphics &g, int rowNumber, int width, int height, bool rowIsSelected) override;
	Component * refreshComponentForRow(int rowNumber, bool isRowSelected, Component *existingComponentToUpdate) override;
	void setQueryEntry(QueryEntry *qe_);

	void changeListenerCallback(ChangeBroadcaster *source) override;
	void mouseMove(const MouseEvent &event) override;
	void mouseExit(const MouseEvent &event) override;

private:
	QueryEntry *qe;
	int rowUnderMouse;
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