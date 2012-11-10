#include "SplashState.hpp"
#include <MGE/Core/interfaces/IApp.hpp>

SplashState::SplashState( MGE::IApp& app,float splashDuration ):
	MGE::IState("Splash",app),
	mSplashDuration(splashDuration),
	mSpashScreenAsset("./resources/pacmanlogo.gif")
{
}

SplashState::~SplashState()
{
}

void SplashState::init()
{
	 IState::init();
	 //mSpalshScreenSprite.setTexture(mSpashScreenAsset.getAsset());
	 mIntroFilter.setFilterTexture(mSpashScreenAsset.getAsset());
	 mIntroFilter.setAlphaChanger(500/(1000*mSplashDuration));
	 mIntroFilter.setFilterDelay(1.0/(1000*mSplashDuration));
	 mIntroFilter.changeFade(true);
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

void SplashState::updateVariable(float elapsedTime )
{
	mIntroFilter.run();
	if(false == isPaused() && getElapsedTime() > mSplashDuration)
	{
		mApp.mStateManager.removeActiveState();
	}
}

void SplashState::draw()
{
	mApp.mWindow.draw(mIntroFilter.getFilterSprite());
}

void SplashState::handleCleanup()
{
	
}


