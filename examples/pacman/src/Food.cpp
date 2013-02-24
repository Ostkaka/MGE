#include "Food.hpp"

Candy::Candy()
{

}

Candy::~Candy()
{

}

bool Candy::onLoad( const std::string & file, int width, int height, int maxFrames)
{
	bool succ = CEntity::onLoad(file,width,height,maxFrames);

	CurrentFrameRow = 6;
	CurrentFrameCol = 12;
	mEntitySprite.setTextureRect(sf::IntRect((CurrentFrameCol * size.x),((CurrentFrameRow) * size.y), size.x, size.y));
	type = ENTITY_TYPE_FOOD_CANDY;

	return succ;
}


void Candy::onRender(sf::RenderWindow & window)
{
	if(!dead) CEntity::onRender(window);
}

bool Candy::onCollision( CEntity* entity )
{
	if(dead) return false;

	// If candy collides with non.player, return false
	if(entity->type != ENTITY_TYPE_PLAYER)
		return false;
	else
	{
		// Kill candy
		dead = true;
	}

	return true;
}

