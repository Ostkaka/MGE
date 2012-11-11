#include "App.hpp"

using namespace MGE;
/*
* Test implemenation of the application class
*/

TestApp::TestApp( const std::string title /*= "TestApp"*/ ): 
	IApp(title)
{
	std::string assetID = RESOURCE_DIR"/pacman.gif";
	mIcon.setID(assetID);
	mLooger = new FileLogger("./logger.log",true);
	mWindow.setIcon(32,32,mIcon.getAsset().copyToImage().getPixelsPtr());
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
	mStateManager.addActiveState(new(std::nothrow) GameState(*this));
	//mStateManager.addActiveState(new(std::nothrow) SplashState(*this,5));
}

void TestApp::handleCustomCleanup()
{

}


