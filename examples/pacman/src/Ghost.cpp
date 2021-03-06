#include "Ghost.hpp"
#include <vector>

Direction reverseDirection(Direction direction){
	switch(direction)
	{
	case MOVE_RIGHT:
		return MOVE_LEFT;
		break;
	case MOVE_LEFT:
		return MOVE_RIGHT;
		break;
	case MOVE_UP:
		return MOVE_DOWN;
		break;
	case MOVE_DOWN:
		return MOVE_UP;
		break;
	case MOVE_NONE:
		break;
	default:
		break;
	}
	//If all else fails
	return direction;
}

Ghost::Ghost():
TileEntity()
{
	type = ENTITY_TYPE_ENEMY;
	mTileSpeed = 2;
}

Ghost::~Ghost()
{
}

void Ghost::onLoop(float dt)
{	

	//Interpolate position from current tile to next tile
	onAnimate();

	//We're not Moving
	if(mDirection != MOVE_NONE){	
		// Check if it is time to move
		if(mMoveClock.getElapsedTime().asMilliseconds() > 1000.0f/float(mTileSpeed)){
			mDirection = getNewDirection();
			moveTile();
			mMoveClock.restart();
		}
	}

	// Set sprite pos
	mEntitySprite.setPosition(pos);

	// Check for collision with other entities
	posValid(pos);
	//checkCollsions();
}

void Ghost::onAnimate()
{
	//Animate ghost
}

bool Ghost::onCollision(CEntity* entity)
{
	return true;
}

void getAllowedDirections( CArea * area, 
	const sf::Vector2i& pos, 
	std::vector<Direction>& directions){
	for (int i=0 ; i < 4; i++)
	{
		sf::Vector2i inc = getIncrement(Direction(i));
		CTile* tile = area->getTile((pos.x + inc.x)* TILE_SIZE,(pos.y + inc.y)* TILE_SIZE);
		if(tile->TypeID != TILE_TYPE_BLOCK)
			directions.push_back(Direction(i));
	}
}

Direction Ghost::getNewDirection()
{
	// Get possible neighbour tiles
	std::vector<Direction> directions;
	getAllowedDirections(CArea::areaControl,mTilePos,directions);
	
	// Return if only one path is allowed
	if(directions.size() == 1) 
		return directions[0];

	// Filter those that goes backwards
	std::vector<Direction> filtered;
	for (int i=0 ; i < directions.size() ; i++)
	{
		if(directions[i] != reverseDirection(mDirection))
			filtered.push_back(directions[i]);
	}

	// Get random direction
	return filtered[rand() % filtered.size()];
}
