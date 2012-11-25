#include "Pacman.hpp"


Pacman::Pacman():
TileEntity()
{
	type = ENTITY_TYPE_PLAYER;
	//Set animation collumn
	anim_Control.setFrameRate(100);
	anim_Control.oscillate=true;
}

Pacman::~Pacman()
{

}

void Pacman::onLoop( float dt )
{
	onAnimate();
	TileEntity::onLoop(dt);
}

void Pacman::onAnimate()
{
	int mod = 1;
	switch(mDirection){
	case MOVE_DOWN:
		CurrentFrameCol = 4;
		mod = 1;
		break;

	case MOVE_RIGHT:
		CurrentFrameCol = 1;
		break;

	case MOVE_UP:
		CurrentFrameCol = 11;
		mod = -1;
		break;

	case MOVE_LEFT:
		CurrentFrameCol = 8;
		mod = -1;
		break;
	}
	int column=0,row=0;
	if(mDirection == MOVE_NONE){
		column = CurrentFrameCol;
		row = CurrentFrameRow;
	}
	else
	{
		anim_Control.onAnimate();
		column = CurrentFrameCol + mod * anim_Control.getCurrentFrame();
		row = CurrentFrameRow;
	}


	mEntitySprite.setTextureRect(sf::IntRect(column * size.x,
		row * size.y, size.x, size.y));
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
	CurrentFrameCol = 0;
	CurrentFrameRow = 5;
	mEntitySprite.setTextureRect(sf::IntRect((CurrentFrameCol * size.x),((CurrentFrameRow + anim_Control.getCurrentFrame()) * size.y), size.x, size.y));
	return succ;
}

