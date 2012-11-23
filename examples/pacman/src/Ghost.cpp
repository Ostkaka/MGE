#include "Ghost.hpp"

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
}

Ghost::~Ghost()
{

}

void Ghost::onLoop( float dt )
{
	//Call parent onLoop
	TileEntity::onLoop(dt);

	//Check if are to collide with wall, reverse direction if true
	if(!directionIsValid(mDirection))
		mDirection = reverseDirection(mDirection);

}

void Ghost::onAnimate()
{
	//Animate ghost
}

bool Ghost::onCollision(CEntity* entity)
{
	return true;
}
