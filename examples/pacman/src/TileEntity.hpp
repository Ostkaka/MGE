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

	virtual void onLoop(float dt);

	virtual void onAnimate();

	virtual void onCleanup();

	virtual void setDirection(Direction direction);

	virtual bool onCollision(CEntity* entity);

protected:

	// Direction of the tiled object
	Direction				mDirection;

	void moveTile();
	bool directionIsValid( Direction direction );

public:
	// Tile speed, number of tiles per second
	float						mTileSpeed;
	// Logical tile position of the object
	sf::Vector2i		mTilePos;
	// Clock that keeps time of when to move again
	sf::Clock				mMoveClock; 
	
};

#endif /* TILEENTITY_HPP */