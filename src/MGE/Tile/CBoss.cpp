#include <MGE/Tile/CBoss.h>

CBoss::CBoss() {
}

bool CBoss::onLoad(const std::string & file, int width, int height, int maxFrames) {
	if(CEntity::onLoad(file, width, height, maxFrames) == false) {
		return false;
	}
	mEntitySprite.setScale(3,3);
	setCentralBound(width*3,height*3);
	return true;
}

void CBoss::onLoop(float dt) {
	CEntity::onLoop(dt);
	//If yoshi is still in the air and falling/Jumping. Do Jump animation
	if(fabs(speed.y) > 0.05){
		//anim_Control.maxFrames = 8;
		//anim_Control.setCurrentFrame(7);
	}
}

void CBoss::onRender(sf::RenderWindow & window) {
	CEntity::onRender(window);
}

void CBoss::onCleanup() {
	CEntity::onCleanup();
}

void CBoss::onAnimate(){
	if(speed.x != 0) {
		anim_Control.maxFrames = 8;
	}else{
		anim_Control.maxFrames = 0;
	}
	CEntity::onAnimate();
}

bool CBoss::onCollision(CEntity* Entity) {
	jump();
	return true;
}
