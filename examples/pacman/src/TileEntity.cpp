#include "TileEntity.hpp"

TileEntity::TileEntity():
CEntity(),
mTilePos(0,0),
mDirection(MOVE_NONE),
mMoveClock(),
mTileSpeed(0)
{
	dead = false;
	flags = ENTITY_FLAG_NONE;
	mMoveClock.restart();
}

TileEntity::~TileEntity()
{

}

void TileEntity::onLoop(float dt)
{	
	
	//Interpolate position from current tile to next tile
	//onAnimate();

	//We're not Moving
	if(mDirection != MOVE_NONE){	
		// Check if it is time to move
		if(mMoveClock.getElapsedTime().asMilliseconds() > 1000.0f/float(mTileSpeed)){
			moveTile();
			mMoveClock.restart();
		}
	}

	// Set the sprite pos - needs interpolating from speed clock
	mEntitySprite.setPosition(pos);

	// Check for collision with other entities
	posValid(pos);

}

void TileEntity::moveTile(){
	if(directionIsValid(mDirection))
		setTilePos(mTilePos +getIncrement(mDirection));
	else 
		mDirection = MOVE_NONE;

#ifdef MOVE_ONE
	mDirection = MOVE_NONE;
#endif

}

void TileEntity::onAnimate()
{

}

bool TileEntity::onCollision(CEntity* entity)
{
	return true;
}

void TileEntity::onCleanup()
{

}

void TileEntity::setDirection(Direction direction)
{
		if(directionIsValid(direction))
			mDirection = direction;
}

bool TileEntity::directionIsValid(Direction direction)
{
	// The next position of the pacman
	sf::Vector2i nextPos = mTilePos;

	//get increment
	nextPos += getIncrement(direction);

	// get map size
	sf::Vector2i mapSize = CArea::areaControl->mMapSize;

	// Se if next tile is allowed
	if(!posValidTile(CArea::areaControl->getTile(nextPos.x * TILE_SIZE, nextPos.y * TILE_SIZE)))
		return false;
	else
		return true;
}

void TileEntity::reset()
{

}

void TileEntity::setTilePos(const sf::Vector2i& newPos)
{
	mTilePos = newPos;

	pos = sf::Vector2f(float(mTilePos.x * TILE_SIZE),float(mTilePos.y * TILE_SIZE));

	updateBound();
}

void TileEntity::updateBound()
{
	// Update Bound
	bound.top = pos.y + (this->size.y * mEntitySprite.getScale().y)/2 - bound.height/2;
	bound.left = pos.x + (this->size.x * mEntitySprite.getScale().x)/2 - bound.width/2;
}

void TileEntity::setTileSpeed( float speed )
{
	mTileSpeed = speed;
}

sf::Vector2i getIncrement(Direction direction){
	sf::Vector2i increment; 
	// if direction is valid, move
	switch(direction)
	{
	case MOVE_RIGHT:
		increment.x = 1;
		break;
	case MOVE_LEFT:
		increment.x = -1;
		break;
	case MOVE_UP:
		increment.y = -1;
		break;
	case MOVE_DOWN:
		increment.y = 1;
		break;
	case MOVE_NONE:
		break;
	default:
		break;
	}
	return increment;
}