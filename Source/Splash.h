#ifndef SplashGuard
#define SplashGuard

#include "../JuceLibraryCode/JuceHeader.h"
#include "CacheSystem.h"
#include "CustomComponents.h"

class CoeusSplashScreen :	public Component,
							public ChangeBroadcaster,
							public TextEditor::Listener
{
public:
	CoeusSplashScreen(DocumentWindow *owner_, Component *other_);
	~CoeusSplashScreen();
    
	void paint(Graphics &g) override;
	void resized() override;

	void textEditorReturnKeyPressed(TextEditor &) override;

private:
	Image bg;
	DocumentWindow *owner;
	Component *other;

	ScopedPointer<Label> usernameLabel;
	ScopedPointer<Label> passwordLabel;

	ScopedPointer<TextEditor> userText;
	ScopedPointer<TextEditor> passwordText;
};


#endif
