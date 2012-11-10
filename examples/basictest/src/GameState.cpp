#include "GameState.hpp"
#include <MGE/Core/interfaces/IApp.hpp>

GameState::GameState(MGE::IApp& theApp) :
  MGE::IState("Game",theApp),
	mBackgroundTexture("./resources/index.jpg"),
	mBackgroundMusic("./resources/TurfIntro.ogg"){
}

GameState::~GameState()
{
}

void GameState::init()
{
  // First call our base class implementation
  IState::init();

	mBackgroundSprite.setTexture(mBackgroundTexture.getAsset());
	mBackgroundTexture.getAsset().setSmooth(true);
	mBackgroundSprite.setScale(1,1);
	mBackgroundSprite.setPosition(50,50);
	//mBackgroundMusic.getAsset().setLoop(true);
	//mBackgroundMusic.getAsset().setVolume(20);
	//mBackgroundMusic.getAsset().play();
	std::cout << "Init!" << std::endl;

  reset();
	
  // Make sure our update loop is only called 30 times per second
  mApp.setUpdateRate(1);
}

void GameState::reset()
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
	mApp.mWindow.clear();
	mApp.mWindow.draw(mBackgroundSprite);
}

void GameState::handleEvents( sf::Event tEvent)
{
	if((tEvent.type == sf::Event::KeyReleased) && (tEvent.key.code == sf::Keyboard::Escape))
		mApp.quit(MGE::StatusAppOK);

	if(tEvent.type == sf::Event::MouseButtonReleased){
		std::cout << "This is klick!" << std::endl;
	}
}

