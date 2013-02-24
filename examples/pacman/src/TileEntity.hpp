#ifndef TILEENTITY_HPP
	#define TILEENTITY_HPP

#include <MGE/Tile/CEntity.h>
#include <MGE/Tile/CAnimation.h>
#include <MGE/Tile/CCamera.h>
#include <MGE/Tile/Define.h>

enum Direction {
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_UP,
	MOVE_DOWN,
	MOVE_NONE
};

enum {
	ENTITY_TYPE_FOOD_CANDY,
	ENTITY_TYPE_FOOD_FRUIT,
};

class TileEntity : public CEntity
{
public:
	/**
	 * Basic constructor
	 */
	TileEntity();

	/**
	 * Basic destructor
	 */
	virtual ~TileEntity();
	
public:

	virtual void reset();

	virtual void onLoop(float dt);

	virtual void onAnimate();

	virtual void onCleanup();

	virtual void setDirection(Direction direction);

	virtual bool onCollision(CEntity* entity);

	void setTilePos(const sf::Vector2i& newPos);

	void setTileSpeed(float speed);

protected:

	void updateBound();

	void moveTile();
	
	bool directionIsValid( Direction direction );

protected:

	// Direction of the tiled object
	Direction				mDirection;

protected:
	// Tile speed, number of tiles per second
	float						mTileSpeed;

	// Logical tile position of the object
	sf::Vector2i		mTilePos;
	// Clock that keeps time of when to move again
	sf::Clock				mMoveClock; 
	
};

/// Helper functions

sf::Vector2i getIncrement(Direction direction);

#endif /* TILEENTITY_HPP */