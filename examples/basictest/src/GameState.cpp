#include "GameState.hpp"
#include <MGE/Core/interfaces/IApp.hpp>

GameState::GameState(MGE::IApp& theApp) :
  MGE::IState("Game",theApp),
	mBackgroundTexture("./resources/grid.bmp"){
}

GameState::~GameState(void)
{

}

void GameState::init(void)
{
  // First call our base class implementation
  IState::init();

	mBackgroundSprite.setTexture(mBackgroundTexture.getAsset());

	std::cout << "Init!" << std::endl;

  reset();
	
  // Make sure our update loop is only called 30 times per second
  mApp.setUpdateRate(1);
}

void GameState::reset(void)
{

}

void GameState::updateFixed()
{
	
	std::cout << "Update!" << std::endl;
	if(isPaused())
		std::cout << "Paused!" << std::endl;
}

void GameState::updateVariable(float theElapsedTime)
{

}

void GameState::handleCleanup()
{

}

void GameState::draw()
{
	mApp.mWindow.draw(mBackgroundSprite);
}

void GameState::handleEvents( sf::Event tEvent)
{

	if((tEvent.type == sf::Event::KeyReleased) && (tEvent.key.code == sf::Keyboard::Escape))
		mApp.quit(MGE::StatusAppOK);

	if(tEvent.type == sf::Event::MouseButtonReleased){
		std::cout << "this is klick!" << std::endl;
	}
}

