#include <MGE/Tile/CPlayer.h>

CPlayer::CPlayer() {
}

bool CPlayer::onLoad(const std::string & file, int width, int height, int maxFrames) {
    if(CEntity::onLoad(file, width, height, maxFrames) == false) {
        return false;
    }
    return true;
}

void CPlayer::onLoop(float dt) {
    CEntity::onLoop(dt);
    //If yoshi is still in the air and falling/Jumping. Do Jump animation
    if(fabs(speed.y) > 0.05){
        //anim_Control.maxFrames = 8;
        //anim_Control.setCurrentFrame(7);
    }
}

void CPlayer::onRender(sf::RenderWindow & window) {
    CEntity::onRender(window);
}

void CPlayer::onCleanup() {
    CEntity::onCleanup();
}

void CPlayer::onAnimate(){
    if(speed.x != 0) {
        anim_Control.maxFrames = 8;
    }else{
        anim_Control.maxFrames = 0;
    }
    CEntity::onAnimate();
}

bool CPlayer::onCollision(CEntity* Entity) {
    jump();
    return true;
}
