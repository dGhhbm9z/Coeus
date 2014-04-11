#include "CacheViewer.h"

class AccountQuickView : public Component
{
public:
    AccountQuickView() {
		accountText = new TextEditor();
		debtText = new TextEditor();
		creditText = new TextEditor();

		addAndMakeVisible(accountText);
		addAndMakeVisible(debtText);
		addAndMakeVisible(creditText);
	}

	~AccountQuickView() {

	}

	void resized() override {
		const float padH = 0.01f;
		const float padV = 0.2f;

		accountText->setBoundsRelative(0 + padH, padV, 0.20f, 1 - 2 * padV);
		debtText->setBoundsRelative(0.4f, padV, 0.25f, 1 - 2 * padV);
		creditText->setBoundsRelative(0.7f, padV, 0.25f, 1 - 2 * padV);
	}

private:
	ScopedPointer<TextEditor> accountText;
	ScopedPointer<TextEditor> debtText;
	ScopedPointer<TextEditor> creditText;
};

CacheViewer::CacheViewer()
{
	transactionTypeLabel = new Label(String::empty, L"ΤΥΠΟΣ ΚΙΝΗΣΗΣ");
	dateLabel = new Label(String::empty, L"ΗΜΕΡΟΜΗΝΙΑ");
	articleNumberLabel = new Label(String::empty, L"ΑΡΙΘΜΟΣ ΑΡΘΡΟΥ");
	taxLabel = new Label(String::empty, L"ΥΠΟΧΡΕΩΣΗ Φ.Π.Α.");
	accountLabel = new Label(String::empty, L"ΛΟΓΑΡΙΑΣΜΟΣ");
	accountNameLabel = new Label(String::empty, L"Όνομα Κινούμενου Λογαριασμού");
	creditLabel = new Label(String::empty, L"ΧΡΕΩΣΗ");
	debtLabel = new Label(String::empty, L"ΠΙΣΤΩΣΗ");
	invoiceLabel = new Label(String::empty, L"ΠΑΡΑΣΤΑΤΙΚΟ");

	transactionTypeComboBox = new ComboBox();
	transactionTypeComboBox->setTextWhenNoChoicesAvailable(L"Καμία επιλογή");
	transactionTypeComboBox->setTextWhenNothingSelected(L"Επιλέξτε τύπο κίνησης");
	transactionTypeComboBox->setEditableText(false);
	transactionTypeComboBox->addItem(L"Συμψηφιστική", 1);
	transactionTypeComboBox->addItem(L"Ισολογισμού", 2);
	transactionTypeComboBox->addItem(L"Μεταφορά", 3);
	transactionTypeComboBox->addItem(L"Πληρωμή", 4);
	transactionTypeComboBox->addItem(L"Είσπραξη", 5);
	transactionTypeComboBox->addItem(L"Απογραφή", 6);

	transactionTypeLabel->setEditable(false);
	dateLabel->setEditable(false);
	articleNumberLabel->setEditable(false);
	taxLabel->setEditable(false);
	accountLabel->setEditable(false);
	accountNameLabel->setEditable(false);
	creditLabel->setEditable(false);
	debtLabel->setEditable(false);
	invoiceLabel->setEditable(false);

	accountTransactions = new ListBox(String::empty, this);

	dateText = new TextEditor();
	articleNumberText = new TextEditor();
	invoiceText = new TextEditor();
	generalCommentsText = new TextEditor();
	generalCommentsText->setTextToShowWhenEmpty(L"ΓΕΝΙΚΑ ΣΧΟΛΙΑ", Colours::grey);
	taxText = new TextEditor();
	descriptionText = new TextEditor();
	descriptionText->setTextToShowWhenEmpty(L"Αιτιολογία", Colours::grey);

	saveButton = new TextButton(L"Αποθήκευση");
	discardButton = new TextButton(L"Επαναφορά");
	balanceButton = new TextButton(L"Ισοσκελισμός");

	addAndMakeVisible(transactionTypeLabel);
	addAndMakeVisible(dateLabel);
	addAndMakeVisible(articleNumberLabel);
	addAndMakeVisible(taxLabel);
	addAndMakeVisible(accountLabel);
	addAndMakeVisible(accountNameLabel);
	addAndMakeVisible(creditLabel);
	addAndMakeVisible(debtLabel);
	addAndMakeVisible(invoiceLabel);

	addAndMakeVisible(transactionTypeComboBox);

	addAndMakeVisible(accountTransactions);

	addAndMakeVisible(dateText);
	addAndMakeVisible(articleNumberText);
	addAndMakeVisible(invoiceText);
	addAndMakeVisible(generalCommentsText);
	addAndMakeVisible(taxText);
	addAndMakeVisible(descriptionText);

	addAndMakeVisible(saveButton);
	addAndMakeVisible(discardButton);
	addAndMakeVisible(balanceButton);

	cache.connectToServer();
}

CacheViewer::~CacheViewer()
{

}

void CacheViewer::paint(Graphics &g)
{
	Path p = Theme::createRectPath(0, 0, getWidth(), getHeight(), 15, 15, 5);
	g.setColour(Colours::black);
	g.strokePath(p, PathStrokeType(1.0f));
}

void CacheViewer::resized()
{
	const float padV = 1.0f / 20.0f;
	const float padH = 1.0f / 40.0f;
	const float gridSizeH = 1.0f / 24.0f;
	const float gridSizeV = 1.0f / 40.0f;
	const float hr = gridSizeH / 2.0f;
	const float vr = gridSizeV;

	// labels
	transactionTypeLabel->setBoundsRelative(padH, padV, gridSizeH * 2, gridSizeV * 2);
	dateLabel->setBoundsRelative(padH + gridSizeH * 12.0f, padV, gridSizeH * 2, gridSizeV * 2);
	articleNumberLabel->setBoundsRelative(padH, padV + gridSizeV * 2 + hr, gridSizeH * 2, gridSizeV * 2);
	taxLabel->setBoundsRelative(padH + gridSizeH * 12.0f, padV + gridSizeV * 2 + hr, gridSizeH * 2, gridSizeV * 2);
	accountLabel->setBoundsRelative(padH + gridSizeH, padV + gridSizeV * 9, gridSizeH * 2, gridSizeV * 2);
	accountNameLabel->setBoundsRelative(padH, 1.0f - padV - gridSizeV * 4, gridSizeH * 4, gridSizeV * 2);
	creditLabel->setBoundsRelative(padH + gridSizeH * 11.0f, padV + gridSizeV * 9, gridSizeH * 2, gridSizeV * 2);
	debtLabel->setBoundsRelative(padH + gridSizeH * 17.0f, padV + gridSizeV * 9, gridSizeH * 2, gridSizeV * 2);
	invoiceLabel->setBoundsRelative(padH, padV + gridSizeV * 4 + hr * 2, gridSizeH * 2, gridSizeV * 2);

	// combobox
	transactionTypeComboBox->setBoundsRelative(padH + gridSizeH * 2.0f + vr, padV, gridSizeH * 6, gridSizeV * 2);

	// text edits
	dateText->setBoundsRelative(padH + gridSizeH * 14.0f + vr, padV, gridSizeH * 6, gridSizeV * 2);
	articleNumberText->setBoundsRelative(padH + gridSizeH * 2.0f + vr, padV + gridSizeV * 2 + hr, gridSizeH * 6, gridSizeV * 2);
	taxText->setBoundsRelative(padH + gridSizeH * 14.0f + vr, padV + gridSizeV * 2 + hr, gridSizeH * 6, gridSizeV * 2);
	invoiceText->setBoundsRelative(padH + gridSizeH * 2.0f + vr, padV + gridSizeV * 4 + hr * 2, gridSizeH * 6, gridSizeV * 2);
	generalCommentsText->setBoundsRelative(padH + gridSizeH * 12.0f, padV + gridSizeV * 4 + 2 * hr, gridSizeH * 8 + vr, gridSizeV * 2);
	descriptionText->setBoundsRelative(padH, 1.0f - padV - gridSizeV * 6 - hr * 2, 1 - padH * 2, gridSizeV * 2);

	// transactions
	accountTransactions->setRowHeight(getHeight() / 12.0f);
	accountTransactions->setBoundsRelative(padH, padV + gridSizeV * 11 + hr, 1 - padH * 2, (1.0f - padV - gridSizeV * 6 - hr * 2) - (padV + gridSizeV * 11 + 2*hr));

	// buttons
	saveButton->setBoundsRelative(1.0f - padH - gridSizeH * 2.0f, 1.0f - padV - gridSizeV*2, gridSizeH*2, gridSizeV * 2);
	discardButton->setBoundsRelative(1.0f - padH - gridSizeH * 4.0f - vr/4, 1.0f - padV - gridSizeV * 2, gridSizeH * 2, gridSizeV * 2);
	balanceButton->setBoundsRelative(1.0f - padH - gridSizeH * 6.0f - vr, 1.0f - padV - gridSizeV * 2, gridSizeH * 2, gridSizeV *2);
}

int CacheViewer::getNumRows()
{
	return 8;
}

void CacheViewer::paintListBoxItem(int rowNumber, Graphics &g, int width, int height, bool rowIsSelected)
{

}

Component* CacheViewer::refreshComponentForRow(int rowNumber, bool isRowSelected, Component *existingComponentToUpdate)
{
	// create
	if (existingComponentToUpdate == nullptr) {
		Component *newComponent = (Component *) new AccountQuickView();
		return newComponent;
	}
	// update
	else {
		return existingComponentToUpdate;
	}
}