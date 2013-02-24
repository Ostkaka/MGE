#ifndef FOOD_HPP
	#define FOOD_HPP

#include "TileEntity.hpp"

class Candy : public TileEntity
{
public:
	/**
	 * Basic constructor
	 */
	Candy();

	/**
	 * Basic destructor
	 */
	virtual ~Candy();
	
public:

	bool onLoad(const std::string & file, int width, int height, int maxFrames = 1);

	void onRender(sf::RenderWindow & window);

	bool onCollision(CEntity* entity);

protected:

public:
};

class Fruit : public TileEntity
{
public:
	/**
	 * Basic constructor
	 */
	Fruit();

	/**
	 * Basic destructor
	 */
	virtual ~Fruit();
	
public:

	bool onCollision(CEntity* entity);

protected:

public:
};

#endif /*FOOD_HPP*/