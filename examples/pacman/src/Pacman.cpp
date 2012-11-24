#include "Pacman.hpp"


Pacman::Pacman():
TileEntity()
{
	type = ENTITY_TYPE_PLAYER;
	//Set animation collumn
}

Pacman::~Pacman()
{

}

void Pacman::onLoop( float dt )
{
	TileEntity::onLoop(dt);

}

void Pacman::onAnimate()
{

}

bool Pacman::onCollision( CEntity* entity )
{
	if(entity->type == ENTITY_TYPE_ENEMY && !dead){
		std::cout << "PACMAN IS DEAD!!!!! STONE COLD KILLAH! he deeeeeaaaad"<< std::endl;
		dead=true;
	}
	return false;
}

bool Pacman::onLoad(const std::string & file, int width, int height, int maxFrames)
{
	bool succ = CEntity::onLoad(file, width, height,  maxFrames);
	CurrentFrameCol = 1;
	CurrentFrameRow = 5;
	mEntitySprite.setTextureRect(sf::IntRect((CurrentFrameCol * size.x),((CurrentFrameRow + anim_Control.getCurrentFrame()) * size.y), size.x, size.y));
	return succ;
}

