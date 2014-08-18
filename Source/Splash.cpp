#include "Splash.h"
#include "PortDefinitions.h"


CoeusSplashScreen::CoeusSplashScreen(DocumentWindow *owner_, Component *other_) : owner(owner_), other(other_)
{
	bg = ImageCache::getFromFile(RESOURCE_FILE("./Resources/splash/3rd.png"));
	usernameLabel = new Label("", "Username: ");
	passwordLabel = new Label("", "Password: ");

	userText = new TextEditor();
	userText->setFont(Font(22));
	userText->setTextToShowWhenEmpty(L"-username-", Colours::black.withAlpha(0.5f));
	userText->addListener(this);

	passwordText = new TextEditor("", '*');
	passwordText->setFont(Font(22));
	passwordText->setTextToShowWhenEmpty(L"-password-", Colours::black.withAlpha(0.5f));
	passwordText->addListener(this);

	addAndMakeVisible(userText);
	addAndMakeVisible(passwordText);
}

CoeusSplashScreen::~CoeusSplashScreen()
{
}

void CoeusSplashScreen::paint(Graphics &g)
{
	const float bgw = bg.getWidth();
	const float bgh = bg.getHeight();

	g.drawImage(bg, 0, 0, getWidth(), getHeight(), 0, 0, bg.getWidth(), bg.getHeight());

	g.setColour(Colours::black);
	g.fillRoundedRectangle(22 / bgw, 486 / bgh, 440 / bgw, 260 / bgh, 10);

	g.setColour(Colours::whitesmoke);
	g.drawRoundedRectangle(22 / bgw, 486 / bgh, 440 / bgw, 260 / bgh, 10, 1.0f);
}

void CoeusSplashScreen::resized()
{
	const float bgw = bg.getWidth();
	const float bgh = bg.getHeight();
	userText->setBoundsRelative( (22 + 10 )/ bgw, (486 + 10 ) / bgh, 440 / bgw, 60 / bgh);
	passwordText->setBoundsRelative((22 + 10) / bgw, (486 + 10 + 60 + 10) / bgh, 440 / bgw, 60 / bgh);
}

void CoeusSplashScreen::textEditorReturnKeyPressed(TextEditor &ed)
{
    String un = userText->getText();
    String pa = passwordText->getText();
	CacheSystem::getInstance()->setUserName(un);
	CacheSystem::getInstance()->setPassword(pa);

	if (CacheSystem::getInstance()->testServer() && owner) {
		owner->setContentOwned(other, true);
	}
}