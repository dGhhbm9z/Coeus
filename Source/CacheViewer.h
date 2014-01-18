#ifndef CacheViewerGuard
#define CacheViewerGuard

#include "../JuceLibraryCode/JuceHeader.h"
#include "Theme.h"

class CacheViewer : public Component,
					public ListBoxModel
{
public:
	CacheViewer();
	~CacheViewer();

	void paint(Graphics &g) override;
	void resized() override;

	int getNumRows() override;
	void paintListBoxItem(int rowNumber, Graphics &g, int width, int height, bool rowIsSelected) override;
	Component* refreshComponentForRow(int rowNumber, bool isRowSelected, Component *existingComponentToUpdate) override;

private:
	ScopedPointer<Label> transactionTypeLabel;
	ScopedPointer<Label> dateLabel;
	ScopedPointer<Label> articleNumberLabel;
	ScopedPointer<Label> taxLabel;
	ScopedPointer<Label> accountLabel;
	ScopedPointer<Label> accountNameLabel;
	ScopedPointer<Label> creditLabel;
	ScopedPointer<Label> debtLabel;
	ScopedPointer<Label> invoiceLabel;

	ScopedPointer<TextEditor> dateText;
	ScopedPointer<TextEditor> articleNumberText;
	ScopedPointer<TextEditor> invoiceText;
	ScopedPointer<TextEditor> generalCommentsText;
	ScopedPointer<TextEditor> taxText;
	ScopedPointer<TextEditor> descriptionText;

	ScopedPointer<ComboBox> transactionTypeComboBox;

	ScopedPointer<ListBox> accountTransactions;

	ScopedPointer<TextButton> saveButton;
	ScopedPointer<TextButton> discardButton;
	ScopedPointer<TextButton> balanceButton;
};



#endif