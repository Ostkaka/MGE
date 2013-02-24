#include "HudBoard.hpp"
#include <MGE/Core/interfaces/IApp.hpp>

HudBoard::HudBoard():
mFontAsset(RESOURCE_DIR"/arial.tff")
{
	mTextSize = 10;
}

HudBoard::~HudBoard()
{

}

void HudBoard::draw(sf::Window& window,  int lives, int score )
{ 
	// Get text for lives
	std::ostringstream	sLives;
	sLives << "Lives: " << lives;
	sf::Text livesText(sLives.str(),mFontAsset.getAsset(),mTextSize);

	// Get text for lives
	std::ostringstream	sScore;
	sLives << "Score: " << score;
	sf::Text scoreText(sScore.str(),mFontAsset.getAsset(),mTextSize);

	// Draw it on screen
	sf::Vector2u size = window.getSize();

	scoreText.setPosition(size.x*(3/4),size.y*(3/4));
	livesText.setPosition(size.x*(3/4),size.y*(2.5/4));
}

