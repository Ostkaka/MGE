#include "App.hpp"

using namespace MGE;
/*
* Test implemenation of the application class
*/

TestApp::TestApp( const std::string title /*= "TestApp"*/ ): IApp(title)
{

}

TestApp::~TestApp()
{

}

void TestApp::initCustomAssetHandlers()
{
	//Test custom asset stuff
}

void TestApp::initCustomGameStates()
{
	mStateManager.addActiveState(new(std::nothrow) GameState(*this));
	mStateManager.addActiveState(new(std::nothrow) SplashState(*this,5));
}

void TestApp::handleCustomCleanup()
{

}


