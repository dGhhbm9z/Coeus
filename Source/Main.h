#ifndef MainGuard
#define MainGaurd

#ifdef _MSC_VER
	#include <windows.h>
	#include <stdio.h>
	#include <fcntl.h>
	#include <io.h>
	#include <iostream>
	#include <fstream>

	// maximum mumber of lines the output console should have
	#define MAX_CONSOLE_LINES 500
#endif

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"
#include "Splash.h"

//==============================================================================
/**
    This is the top-level window that we'll pop up. Inside it, we'll create and
    show a component from the MainComponent.cpp file (you can open this file using
    the Jucer to edit it).
*/
class HelloWorldWindow  :   public DocumentWindow,
                            public ComponentBoundsConstrainer
{
public:
    //==============================================================================
    HelloWorldWindow();
    ~HelloWorldWindow();

    //==============================================================================
    void closeButtonPressed();
    void resizeStart();
    void resizeEnd();
    void login();
    void logout();

private:
    ScopedPointer<CoeusSplashScreen> splash;
    ScopedPointer<MainComponent> cmp;
};

//==============================================================================
class coeusApplication  : public JUCEApplication
{
public:
    //==============================================================================
    coeusApplication();

    const String getApplicationName();
    const String getApplicationVersion();
    bool moreThanOneInstanceAllowed();

    //==============================================================================
    void initialise (const String& commandLine);

    void shutdown();

    //==============================================================================
    void systemRequestedQuit();

    void anotherInstanceStarted (const String& commandLine);

private:
	 ScopedPointer<HelloWorldWindow> helloWorldWindow;
};

#endif
