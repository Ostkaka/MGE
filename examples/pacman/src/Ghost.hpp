#ifndef GHOST_HPP
	#define GHOST_HPP

#include "TileEntity.hpp"

class Ghost : public TileEntity
{
public:
	/**
	 * Basic constructor
	 */
	Ghost();

	/**
	 * Basic destructor
	 */
	virtual ~Ghost();
	
public:

	void onLoop(float dt);

	void onAnimate();

	void onCollision();

protected:
	//AI algorithm for moving

public:

	
};

#endif /*GHOST_HPP*/