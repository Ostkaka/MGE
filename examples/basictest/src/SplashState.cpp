#include "SplashState.hpp"
#include <MGE/Core/interfaces/IApp.hpp>

SplashState::SplashState( MGE::IApp& app,float splashDuration ):
	MGE::IState("Splash",app),
	mSplashDuration(splashDuration),
	mSpashScreenAsset("./resources/index.jpg")
{
}

SplashState::~SplashState()
{

}

void SplashState::init()
{
	 IState::init();
	 mSpalshScreenSprite.setTexture(mSpashScreenAsset.getAsset());
}

void SplashState::reset()
{
	//Nothing
}

void SplashState::handleEvents( sf::Event tEvent )
{

}

void SplashState::updateFixed()
{

}

void SplashState::updateVariable( float elapsedTime )
{
	// Drop our state after 10 seconds have elapsed
	if(false == isPaused() && getElapsedTime() > mSplashDuration)
	{
		mApp.mStateManager.removeActiveState();
		std::cout << "Splash ended..." << std::endl;
	}
}

void SplashState::draw()
{
	mApp.mWindow.draw(mSpalshScreenSprite);
}

void SplashState::handleCleanup()
{
	std::cout << "Cleaning SplashState!" << std::endl;
}


