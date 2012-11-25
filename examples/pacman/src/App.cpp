#include "App.hpp"
#include <ctime>

using namespace MGE;
/*
* Test implemenation of the application class
*/

TestApp::TestApp( const std::string title /*= "TestApp"*/ ): 
	IApp(title)
{

	mLooger = new FileLogger("./logger.log",true);
	srand(std::time(NULL));
}

TestApp::~TestApp()
{
		std::cout << mLooger->getStream() << std::endl;
}

void TestApp::initCustomAssetHandlers()
{
	//Test custom asset stuff
}

void TestApp::initCustomGameStates()
{
	mStateManager.addActiveState(new(std::nothrow) InitState(*this));
	//mStateManager.addInactiveState(new(std::nothrow) SplashState(*this,5));
	mStateManager.addInactiveState(new(std::nothrow) GameState(*this));
}

void TestApp::handleCustomCleanup()
{
}

void TestApp::processInput(IState& theState)
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
			theState.resume();
			break;
		case sf::Event::LostFocus:    // Window lost focus
			theState.pause();
			break;
		case sf::Event::Resized:      // Window resized
			mWindow.setSize(sf::Vector2u(800,600));
			break;
		default:                      // Current active state will handle
			theState.handleEvents(tEvent);
			//std::cout << "Default " << std::endl;
		} 
	} 
}

