#include "SplashState.hpp"
#include <MGE/Core/interfaces/IApp.hpp>

SplashState::SplashState( MGE::IApp& app,float splashDuration ):
	MGE::IState("Splash",app),
	mSplashDuration(splashDuration),
	mSpashScreenAsset(RESOURCE_DIR"/pacmanlogo.gif")
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
	mApp.mWindow.clear();

	sf::Vector2f w = sf::Vector2f(mIntroFilter.getFilterSprite().getLocalBounds().width/2,
		mIntroFilter.getFilterSprite().getLocalBounds().height/2);

	sf::Vector2f size = sf::Vector2f(mApp.mWindow.getSize().x/2,mApp.mWindow.getSize().y/2);
	
	sf::Sprite sprite = mIntroFilter.getFilterSprite();
	sprite.setPosition(size -w);
	mApp.mWindow.draw(sprite);
}

void SplashState::handleCleanup()
{
	
}


