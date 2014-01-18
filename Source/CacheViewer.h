#ifndef CacheViewerGuard
#define CacheViewerGuard

#include "../JuceLibraryCode/JuceHeader.h"
#include "Theme.h"

class CacheViewer : public Component
{
public:
	CacheViewer();
	~CacheViewer();

	void paint(Graphics &g) override;
	void resized() override;

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

	ScopedPointer<TextButton> saveButton;
	ScopedPointer<TextButton> discardButton;
	ScopedPointer<TextButton> balanceButton;
};



#endif