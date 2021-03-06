#include <MGE/Tile/CBoss.h>

CBoss::CBoss():
mBossHurtBuffer(){
}

bool CBoss::onLoad(const std::string & file, int width, int height, int maxFrames) {
	if(CEntity::onLoad(file, width, height, maxFrames) == false) {
		return false;
	}
	mBossHurtBuffer.setID(RESOURCE_DIR"/YI_Sounds/Sounds/babyBowserComplain.wav");
	mBossHurtSound.setBuffer(mBossHurtBuffer.getAsset());
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
	mEntitySprite.setTextureRect(sf::IntRect((CurrentFrameCol * size.x),((CurrentFrameRow + anim_Control.getCurrentFrame()) * size.y), size.x, size.y));
}

bool CBoss::onCollision(CEntity* Entity) {
	jump();
	if(mBossHurtSound.getStatus() != sf::Sound::Playing)
		mBossHurtSound.play();
	return true;
}
