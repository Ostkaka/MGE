/*
* 
*/
#include <assert.h>
#include <MGE/Core/interfaces/IApp.hpp>
#include <MGE/Core/interfaces/IState.hpp>
#include <iostream>

namespace MGE 
{

	/// Default application wide settings file string
	const char* IApp::APP_SETTINGS = "resources/settings.cfg";

	/// Single instance of the most recently created App class
	IApp* IApp::gApp = NULL;

	// Implementations
	IApp::IApp( const std::string theTitle /*= "MGE Application"*/ ):
		mTitle(theTitle),
		mVideoMode(DEFAULT_VIDEO_WIDTH, DEFAULT_VIDEO_HEIGHT, DEFAULT_VIDEO_BPP),
		mWindow(),
		mContextSettings(),
		mWindowStyle(sf::Style::Close | sf::Style::Resize),
		mGraphicRange(LowRange),
		//mAssetManager(),
		//mStatManager(),
		//mStateManager(),
		mExitCode(0),
		mRunning(false),
		mUpdateRate((int)(1000.0f / 20.0f)), // 20 updates per second
		mMaxUpdates(5)
	{
		// Save our global App pointer
		gApp = this;
	}

	IApp::~IApp()
	{
		//Set running flag to false
		mRunning = false;

		// Are we going out of scope? then remove our static pointer
		if(gApp == this)
		{
			gApp = NULL;
		}
	}

	IApp* IApp::getApp(void)
	{
		return gApp;
	}

	void IApp::processArguments( int argc, char* argv[] )
	{
		//This is to be implemented

		//Add logger stuff
	}

	int IApp::run()
	{
		std::cout << "Applications is running" << std::endl;
		//Logger stuff

		//Register 

		//Register custom asset classes
		initCustomAssetHandlers();

		//Load the application setting file settings.cfg
		initConfig();

		//Opens and inits the render vindow
		initRenderer();

		// Do gameLoop of the running flag is active
		gameLoop();

		// Perform cleanup for custom configurations
		customCleanup();

		// Handle internal IApp cleaning
		cleanup();

		// Set running to be false
		mRunning = false;

		//Set exist code message
		if(mExitCode < 0)
			std::cout << "exitCode: " << mExitCode << std::endl;
		else
			std::cout << "exitCode: " << mExitCode << std::endl;

		// Return the exit code generated by quit
		return mExitCode;

	}

	bool IApp::isRunning() const
	{
		return mRunning;
	}

	void IApp::setGraphicRange(const GraphicRange theGraphicRange)
	{
		// Sanity check theGraphicRange provided
		if(theGraphicRange >= LowRange && theGraphicRange <= HighRange)
		{
			mGraphicRange = theGraphicRange;
		}
	}

	float IApp::getUpdateRate(void) const
	{
		// Return the current set UpdateFixed game loop rate
		return (1000.0f / (float)(mUpdateRate));
	}

	void IApp::setMaxUpdates(int newMaxUpdates)
	{
		// Validate Max Updates range first
		if(200 >= newMaxUpdates && 1 <= newMaxUpdates)
		{
			// Set max updates value to theMaxUpdates value provided
			mMaxUpdates = newMaxUpdates;
		}
	}

	void IApp::quit(int theExitCode)
	{
		mExitCode = theExitCode;
		mRunning = false;
	}

	const GraphicRange IApp::calculateRange(int theHeight) const
	{
		// Default to LowRange
		GraphicRange anResult = LowRange;

		// Do we fall under the Medium Range category?
		if(((theHeight - 240) / 10.0) > 52.0 && ((theHeight - 240) / 10.0) <= 72.0)
		{
			// Return MidRange
			anResult = MidRange;
		}
		else if(((theHeight - 240) / 10.0) > 72.0)
		{
			// Return HighRange
			anResult = HighRange;
		}

		// Return anResult determined above or the default of LowRange
		return anResult;
	}

	void IApp::initConfig()
	{
		//SLOG(App_InitSettingsConfig, SeverityInfo) << std::endl;
		//ConfigAsset anSettingsConfig(IApp::APP_SETTINGS);
	}

	void IApp::initRenderer()
	{
		
		//SLOG(App_InitRenderer, SeverityInfo) << std::endl;
		//ConfigAsset anSettingsConfig(IApp::APP_SETTINGS);

		// Are we in Fullscreen mode?
		//if(anSettingsConfig.GetAsset().GetBool("window","fullscreen",false))
		//{
		//	mWindowStyle = sf::Style::Fullscreen;
		//}

		// What size window does the user want?
		/*mVideoMode.width =
			anSettingsConfig.GetAsset().GetUint32("window","width",DEFAULT_VIDEO_WIDTH);
		mVideoMode.height =
			anSettingsConfig.GetAsset().GetUint32("window","height",DEFAULT_VIDEO_HEIGHT);
		mVideoMode.bitsPerPixel =
			anSettingsConfig.GetAsset().GetUint32("window","depth",DEFAULT_VIDEO_BPP);*/

		// For Fullscreen, verify valid VideoMode, otherwise revert to defaults for Fullscreen
		if(sf::Style::Fullscreen == mWindowStyle && false == mVideoMode.isValid())
		/*{
			mVideoMode.width = DEFAULT_VIDEO_WIDTH;
			mVideoMode.height = DEFAULT_VIDEO_HEIGHT;
			mVideoMode.bitsPerPixel = DEFAULT_VIDEO_BPP;
		}*/

		mVideoMode.width = DEFAULT_VIDEO_WIDTH;
		mVideoMode.height = DEFAULT_VIDEO_HEIGHT;
		mVideoMode.bitsPerPixel = DEFAULT_VIDEO_BPP;

		// Calculate and set GraphicRange value
		setGraphicRange(calculateRange(mVideoMode.height));

		// Create a RenderWindow object using VideoMode object above
		mWindow.create(mVideoMode, mTitle, mWindowStyle, mContextSettings);

		// Use Vertical Sync
		mWindow.setVerticalSyncEnabled(true);
	}

	void IApp::gameLoop(void)
	{
		//SLOG(App_GameLoop, SeverityInfo) << std::endl;

		// Clock used in restricting Update loop to a fixed rate
		sf::Clock anUpdateClock;

		// Clock used in calculating the time elapsed since the last frame
		sf::Clock anFrameClock;

		// Restart/Reset our Update clock
		anUpdateClock.restart();

		// When do we need to update next (in milliseconds)?
		sf::Int32 anUpdateNext = anUpdateClock.getElapsedTime().asMilliseconds();

		// Make sure we have at least one state active
		//if(mStateManager.IsEmpty())
		//{
			// Exit with an error since there isn't an active state
			//Quit(StatusAppInitFailed);
		//}

		// Loop while IsRunning returns true

		while(isRunning() && mWindow.isOpen() /*&& !mStateManager.IsEmpty()*/)
		{
			// Get the currently active state
			//IState& anState = mStateManager.GetActiveState();

			// Count the number of sequential UpdateFixed loop calls
			int anUpdates = 0;

			// Process any available input
			//processInput(anState);

			sf::Int32 anUpdateTime = anUpdateClock.getElapsedTime().asMilliseconds();

			// Process our UpdateFixed portion of the game loop
			while((anUpdateTime - anUpdateNext) >= mUpdateRate && anUpdates++ < mMaxUpdates)
			{
				// Let the current active state perform fixed updates next
				//anState.updateFixed();

				// Let the StatManager perfom its updates
				//mStatManager.UpdateFixed();

				// Compute the next appropriate UpdateFixed time
				anUpdateNext += mUpdateRate;
			} // while((anUpdateTime - anUpdateNext) >= mUpdateRate && anUpdates <= mMaxUpdates)

			// Let the current active state perform its variable update

			// Convert to floating point value of seconds for SFML 2.0
			//anState.UpdateVariable(anFrameClock.restart().asSeconds());

			// Let the current active state draw stuff
			//anState.draw();

			// Let the StatManager perform its drawing
			//mStatManager.Draw();

			// Display Render window to the screen
			mWindow.display();

			// Give the state manager a chance to delete any pending states
			//mStateManager.cleanup(); 
		} 
	}

	void IApp::processInput(IState& theState)
	{
		// Variable for storing the current input event to be processed
		sf::Event tEvent;

		while(mWindow.pollEvent(tEvent))
		{
			// Handle some input events and let the current state handle the rest
			// Switch on Event Type
			switch(tEvent.type)
			{
			case sf::Event::Closed:       // Window closed
				quit(StatusAppOK);
				break;
			case sf::Event::GainedFocus:  // Window gained focus
				//theState.Resume();
				break;
			case sf::Event::LostFocus:    // Window lost focus
				//theState.Pause();
				break;
			case sf::Event::Resized:      // Window resized
				break;
			default:                      // Current active state will handle
				std::cout << "Default " << std::endl;
				//theState.HandleEvents(anEvent);
			} 
		} 
	}

	void IApp::cleanup(void)
	{
		//SLOG(App_Cleanup, SeverityInfo) << std::endl;

		// Give the StatManager a chance to de-initialize
		//mStatManager.DeInit();

		// Close the Render window if it is still open
		if(mWindow.isOpen())
		{
			// Show the Mouse cursor
			mWindow.setMouseCursorVisible(true);

			// Close the Render window
			mWindow.close();
		}
	}

}