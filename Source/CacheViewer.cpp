#include "CacheViewer.h"

CacheViewer::CacheViewer()
{
	transactionTypeLabel = new Label(String::empty, L"����� �������");
	dateLabel = new Label(String::empty, L"����������");
	articleNumberLabel = new Label(String::empty, L"������� ������");
	taxLabel = new Label(String::empty, L"��������� �.�.�.");
	accountLabel = new Label(String::empty, L"�����������");
	accountNameLabel = new Label(String::empty, L"����� ���������� �����������");
	creditLabel = new Label(String::empty, L"������");
	debtLabel = new Label(String::empty, L"�������");
	invoiceLabel = new Label(String::empty, L"�����������");

	transactionTypeComboBox = new ComboBox();
	transactionTypeComboBox->setTextWhenNoChoicesAvailable(L"����� �������");
	transactionTypeComboBox->setTextWhenNothingSelected(L"�������� ���� �������");
	transactionTypeComboBox->setEditableText(false);
	transactionTypeComboBox->addItem(L"������������", 1);
	transactionTypeComboBox->addItem(L"�����������", 2);
	transactionTypeComboBox->addItem(L"��������", 3);
	transactionTypeComboBox->addItem(L"�������", 4);
	transactionTypeComboBox->addItem(L"��������", 5);
	transactionTypeComboBox->addItem(L"��������", 6);

	transactionTypeLabel->setEditable(false);
	dateLabel->setEditable(false);
	articleNumberLabel->setEditable(false);
	taxLabel->setEditable(false);
	accountLabel->setEditable(false);
	accountNameLabel->setEditable(false);
	creditLabel->setEditable(false);
	debtLabel->setEditable(false);
	invoiceLabel->setEditable(false);

	dateText = new TextEditor();
	articleNumberText = new TextEditor();
	invoiceText = new TextEditor();
	generalCommentsText = new TextEditor();
	generalCommentsText->setTextToShowWhenEmpty(L"������ ������", Colours::grey);
	taxText = new TextEditor();
	descriptionText = new TextEditor();
	descriptionText->setTextToShowWhenEmpty(L"����������", Colours::grey);

	saveButton = new TextButton(L"����������");
	discardButton = new TextButton(L"���������");
	balanceButton = new TextButton(L"������������");

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

	addAndMakeVisible(dateText);
	addAndMakeVisible(articleNumberText);
	addAndMakeVisible(invoiceText);
	addAndMakeVisible(generalCommentsText);
	addAndMakeVisible(taxText);
	addAndMakeVisible(descriptionText);

	addAndMakeVisible(saveButton);
	addAndMakeVisible(discardButton);
	addAndMakeVisible(balanceButton);
}

CacheViewer::~CacheViewer()
{

}

void CacheViewer::paint(Graphics &g)
{
	Path p = Theme::createRectPath(0, 0, getWidth(), getHeight(), 15, 15, 5);
	g.setColour(Colours::black);
	g.strokePath(p, PathStrokeType::beveled);
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

	// buttons
	saveButton->setBoundsRelative(1.0f - padH - gridSizeH * 2.0f, 1.0f - padV - gridSizeV*2, gridSizeH*2, gridSizeV * 2);
	discardButton->setBoundsRelative(1.0f - padH - gridSizeH * 4.0f - vr/4, 1.0f - padV - gridSizeV * 2, gridSizeH * 2, gridSizeV * 2);
	balanceButton->setBoundsRelative(1.0f - padH - gridSizeH * 6.0f - vr, 1.0f - padV - gridSizeV * 2, gridSizeH * 2, gridSizeV *2);
}