#include "CacheViewer.h"

CacheViewer::CacheViewer()
{
	transactionTypeLabel = new Label(String::empty, L"ÔÕÐÏÓ ÊÉÍÇÓÇÓ");
	dateLabel = new Label(String::empty, L"ÇÌÅÑÏÌÇÍÉÁ");
	articleNumberLabel = new Label(String::empty, L"ÁÑÉÈÌÏÓ ÁÑÈÑÏÕ");
	taxLabel = new Label(String::empty, L"ÕÐÏ×ÑÅÙÓÇ Ö.Ð.Á.");
	accountLabel = new Label(String::empty, L"ËÏÃÁÑÉÁÓÌÏÓ");
	accountNameLabel = new Label(String::empty, L"¼íïìá Êéíïýìåíïõ Ëïãáñéáóìïý");
	creditLabel = new Label(String::empty, L"×ÑÅÙÓÇ");
	debtLabel = new Label(String::empty, L"ÐÉÓÔÙÓÇ");
	invoiceLabel = new Label(String::empty, L"ÐÁÑÁÓÔÁÔÉÊÏ");

	transactionTypeLabel->setEditable(false);
	dateLabel->setEditable(false);
	articleNumberLabel->setEditable(false);
	taxLabel->setEditable(false);
	accountLabel->setEditable(false);
	accountNameLabel->setEditable(false);
	creditLabel->setEditable(false);
	debtLabel->setEditable(false);
	invoiceLabel->setEditable(false);

	saveButton = new TextButton(L"ÁðïèÞêåõóç");
	discardButton = new TextButton(L"ÅðáíáöïñÜ");
	balanceButton = new TextButton(L"Éóïóêåëéóìüò");

	addAndMakeVisible(transactionTypeLabel);
	addAndMakeVisible(dateLabel);
	addAndMakeVisible(articleNumberLabel);
	addAndMakeVisible(taxLabel);
	addAndMakeVisible(accountLabel);
	addAndMakeVisible(accountNameLabel);
	addAndMakeVisible(creditLabel);
	addAndMakeVisible(debtLabel);
	addAndMakeVisible(invoiceLabel);

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
	const float gridSize = 1.0f / 24.0f;
	const float hr = gridSize / 2.0f;
	const float vr = gridSize * 2.25f;

	// labels
	transactionTypeLabel->setBoundsRelative(padH, padV, gridSize * 2, gridSize * 2);
	dateLabel->setBoundsRelative(padH + gridSize * 12.0f, padV, gridSize * 2, gridSize * 2);
	articleNumberLabel->setBoundsRelative(padH, padV + gridSize * 2 + hr, gridSize * 2, gridSize * 2);
	taxLabel->setBoundsRelative(padH + gridSize * 12.0f, padV + gridSize * 2 + hr, gridSize * 2, gridSize * 2);
	accountLabel->setBoundsRelative(padH + gridSize, padV + gridSize * 7, gridSize * 2, gridSize * 2);
	accountNameLabel->setBoundsRelative(padH, 1.0f - padV - gridSize * 4, gridSize * 2, gridSize * 2);
	creditLabel->setBoundsRelative(padH + gridSize * 11.0f, padV + gridSize * 7, gridSize * 2, gridSize * 2);
	debtLabel->setBoundsRelative(padH + gridSize * 17.0f, padV + gridSize * 7, gridSize * 2, gridSize * 2);
	invoiceLabel->setBoundsRelative(padH, padV + gridSize * 4 + hr*2, gridSize * 2, gridSize * 2);

	// text edits

	// buttons
	saveButton->setBoundsRelative(1.0f - padH - gridSize * 2.0f, 1.0f - padV - gridSize*2, gridSize*2, gridSize*2);
	discardButton->setBoundsRelative(1.0f - padH - gridSize * 2.0f - vr, 1.0f - padV - gridSize * 2, gridSize * 2, gridSize * 2);
	balanceButton->setBoundsRelative(1.0f - padH - gridSize * 4.0f - vr *2.0f, 1.0f - padV - gridSize * 2, gridSize * 2, gridSize * 2);
}