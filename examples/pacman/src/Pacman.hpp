#ifndef PACMAN_HPP
	#define PACMAN_HPP

#include "TileEntity.hpp"

class Pacman : public TileEntity
{
public:
	/**
	 * Basic constructor
	 */
	Pacman();

	/**
	 * Basic destructor
	 */
	virtual ~Pacman();
	
public:

	bool onLoad(const std::string & file, int width, int height, int maxFrames);

	void onLoop(float dt);

	void onAnimate();

	bool onCollision(CEntity* entity);

protected:
	//AI algorithm for moving

public:

	
};

#endif /*PACMAN_HPP*/