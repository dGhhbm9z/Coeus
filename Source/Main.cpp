/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifdef _MSC_VER
	#include <windows.h>
	#include <stdio.h>
	#include <fcntl.h>
	#include <io.h>
	#include <iostream>
	#include <fstream>

	// maximum mumber of lines the output console should have
	#define MAX_CONSOLE_LINES 500

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

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"

//==============================================================================
/**
    This is the top-level window that we'll pop up. Inside it, we'll create and
    show a component from the MainComponent.cpp file (you can open this file using
    the Jucer to edit it).
*/
class HelloWorldWindow  : public DocumentWindow
{
public:
    //==============================================================================
    HelloWorldWindow()
        : DocumentWindow ("Coeus Logistics",
                          Colours::lightgrey,
                          DocumentWindow::allButtons,
                          true)
    {
		setWantsKeyboardFocus(false);
		// Centre the window on the screen
		juce::Rectangle<int> r = Desktop::getInstance().getDisplays().getMainDisplay().userArea;
		centreWithSize(r.getWidth(), r.getHeight());

        // Create an instance of our main content component, and add it to our window..
        setContentOwned (new MainComponent(), true);

        // And show it!
        setVisible (true);
		setResizable(true, false);

		#ifdef _MSC_VER
		RedirectIOToConsole();
		#endif

		CacheSystem::getInstance()->connectToServer();
    }

    ~HelloWorldWindow()
    {
        // (the content component will be deleted automatically, so no need to do it here)
    }

    //==============================================================================
    void closeButtonPressed()
    {
        // When the user presses the close button, we'll tell the app to quit. This
        // HelloWorldWindow object will be deleted by the JUCEHelloWorldApplication class.
        JUCEApplication::quit();
    }
};

//==============================================================================
class coeusApplication  : public JUCEApplication
{
public:
    //==============================================================================
    coeusApplication() {
		helloWorldWindow = new HelloWorldWindow();
	}

    const String getApplicationName()       { return ProjectInfo::projectName; }
    const String getApplicationVersion()    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed()       { return true; }

    //==============================================================================
    void initialise (const String& commandLine)
    {
        // Add your application's initialisation code here..
    }

    void shutdown()
    {
        // Add your application's shutdown code here..
    }

    //==============================================================================
    void systemRequestedQuit()
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const String& commandLine)
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

private:
	 ScopedPointer<HelloWorldWindow> helloWorldWindow;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (coeusApplication)
