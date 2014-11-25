#ifndef AccountsGuard
#define AccountsGuard

#include "../JuceLibraryCode/JuceHeader.h"
#include "CacheSystem.h"
#include "CustomComponents.h"
#include "CoeusList.h"

//=======================================================================================================
class AccountCellButtons : public Component
{
public:
	AccountCellButtons();

	~AccountCellButtons();

	void resized() override;

	int rowIndex;

private:

	ScopedPointer<TextButton> save;
	ScopedPointer<TextButton> restore;
	ScopedPointer<TextButton> remove;
};

//=======================================================================================================
class AccountsTableListBoxModel :	public TableListBox,
									public TableListBoxModel,
									public ChangeListener
{
public:
	AccountsTableListBoxModel();
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

private:
	ScopedPointer<AccountsTableListBoxModel> accounts;
	QueryEntry *qe;
};

#endif
