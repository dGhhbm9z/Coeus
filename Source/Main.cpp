#include "Main.h"

#ifdef _MSC_VER
	void RedirectIOToConsole()
	{
		int hConHandle;
		long lStdHandle;
		CONSOLE_SCREEN_BUFFER_INFO coninfo;
		FILE *fp;

		// allocate a console for this app
		AllocConsole();

		// set the screen buffer to be big enough to let us scroll text
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
		coninfo.dwSize.Y = MAX_CONSOLE_LINES;
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

		// redirect unbuffered STDOUT to the console
		lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
		hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
		fp = _fdopen(hConHandle, "w");
		*stdout = *fp;
		setvbuf(stdout, NULL, _IONBF, 0);

		// redirect unbuffered STDIN to the console
		lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
		hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
		fp = _fdopen(hConHandle, "r");
		*stdin = *fp;
		setvbuf(stdin, NULL, _IONBF, 0);

		// redirect unbuffered STDERR to the console
		lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
		hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
		fp = _fdopen(hConHandle, "w");
		*stderr = *fp;
		setvbuf(stderr, NULL, _IONBF, 0);

		// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
		// point to console as well
		std::ios::sync_with_stdio();
	}
#endif


//==============================================================================
HelloWorldWindow::HelloWorldWindow()
    : DocumentWindow ("Coeus Finance",
                      Colours::lightgrey,
                      DocumentWindow::allButtons,
                      true)
{
    setWantsKeyboardFocus(false);
    // Centre the window on the screen

    /*
    juce::Rectangle<int> r = Desktop::getInstance().getDisplays().getMainDisplay().userArea;
    r.setWidth(r.getWidth() - getBorderThickness().getLeft() - getBorderThickness().getRight() );
    r.setHeight(r.getHeight() - getBorderThickness().getTop() - getBorderThickness().getBottom() - getTitleBarHeight());
    setSize(r.getWidth(), r.getHeight());
    setTopLeftPosition(0, 0);
    */

    //centreWithSize(100, 100);

    // Create an instance of our main content component, and add it to our window..
    cmp = new MainComponent();
	juce::Rectangle<int> r = Desktop::getInstance().getDisplays().getMainDisplay().userArea;
    cmp->setBounds(0.1f*r.getX(), 0.1f*r.getY(), 0.8f*r.getWidth(), 0.8f*r.getHeight());

    splash = new CoeusSplashScreen(this, cmp);
    splash->centreWithSize(1024, 589);

    setContentNonOwned (splash, true);
    setTopLeftPosition(cmp->getWidth()*0.1f / 0.8f, cmp->getHeight()*0.1f / 0.8f);

    // size constrains
//    setMinimumWidth(1024);
//    setMinimumHeight(589);
//    setConstrainer(this);

    // And show it!
    setVisible (true);
    setResizable(true, false);

    #ifdef _MSC_VER
        #if _SHOW_CONSOLE_
            RedirectIOToConsole();
        #endif
    #endif
}

HelloWorldWindow::~HelloWorldWindow()
{
    setContentNonOwned(nullptr, false);
    splash = nullptr;
    cmp = nullptr;
}

//==============================================================================
void HelloWorldWindow::closeButtonPressed()
{
    // When the user presses the close button, we'll tell the app to quit. This
    // HelloWorldWindow object will be deleted by the JUCEHelloWorldApplication class.
    JUCEApplication::quit();
}

void HelloWorldWindow::resizeStart()
{
    cmp->resizeStart();
}

void HelloWorldWindow::resizeEnd()
{
    cmp->resizeEnd();
}

void HelloWorldWindow::login() {
    // TODO: load user workspace
    setContentNonOwned(cmp, true);
    
    // size constrains
//    setMinimumWidth(500);
//    setMinimumHeight(920);
//    setConstrainer(this);
    
	juce::Rectangle<int> r = Desktop::getInstance().getDisplays().getMainDisplay().userArea;
    this->setBounds(0.1f*r.getX(), 0.1f*r.getY(), 0.8f*r.getWidth(), 0.8f*r.getHeight());
}

void HelloWorldWindow::logout()
{
    // TODO: clear current workspace
    setContentNonOwned(splash, true);
    
    // size constrains
//    setMinimumWidth(1024);
//    setMinimumHeight(589);
//    setConstrainer(this);
}



//==============================================================================
coeusApplication::coeusApplication() {
    helloWorldWindow = new HelloWorldWindow();
}

const String coeusApplication::getApplicationName()       { return ProjectInfo::projectName; }
const String coeusApplication::getApplicationVersion()    { return ProjectInfo::versionString; }
bool coeusApplication::moreThanOneInstanceAllowed()       { return true; }

//==============================================================================
void coeusApplication::initialise (const String& commandLine)
{
    // Add your application's initialisation code here..
}

void coeusApplication::shutdown()
{
    // Add your application's shutdown code here..
}

//==============================================================================
void coeusApplication::systemRequestedQuit()
{
    // This is called when the app is being asked to quit: you can ignore this
    // request and let the app carry on running, or call quit() to allow the app to close.
    quit();
}

void coeusApplication::anotherInstanceStarted (const String& commandLine)
{
    // When another instance of the app is launched while this one is running,
    // this method is invoked, and the commandLine parameter tells you what
    // the other instance's command-line arguments were.
}


//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (coeusApplication)
