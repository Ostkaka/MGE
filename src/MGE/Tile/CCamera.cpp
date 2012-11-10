#include "CCamera.h"

CCamera CCamera::CameraControl;

CCamera::CCamera() {
	pos.x = pos.y = 0;
	targetCenter = NULL;

    targetMode = TARGET_MODE_NORMAL;
}

void CCamera::onMove(const sf::Vector2f & move) {
	pos += move;
}

sf::Vector2f CCamera::getPos(){
	if(targetMode == TARGET_MODE_CENTER){
		if(targetCenter != NULL) return sf::Vector2f(*targetCenter);
		else return pos;
	}
	return pos;
}

void CCamera::setPos(const sf::Vector2f & pos) {
	this->pos = pos;
}

void CCamera::setTarget(sf::Vector2f * Center) {
    this->targetCenter = Center;
}


