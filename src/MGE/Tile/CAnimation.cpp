#include "CAnimation.h"

CAnimation::CAnimation() {
    currentFrame    = 0;
    maxFrames       = 0;
    frameInc        = 1;

    frameRate       = 100; //Milliseconds
    oldTime         = 0;

    oscillate       = false;
}

void CAnimation::onAnimate() {
	if(oldTime + frameRate > clock.getElapsedTime().asMilliseconds()) {
        return;
    }

    oldTime = clock.getElapsedTime().asMilliseconds();

    currentFrame += frameInc;

    if(oscillate) {
        if(frameInc > 0) {
            if(currentFrame >= maxFrames -1) {
                frameInc = -frameInc;
            }
        }else{
            if(currentFrame <= 0) {
                frameInc = -frameInc;
            }
        }
    }else{
        if(currentFrame >= maxFrames -1) {
            currentFrame = 0;
        }
    }
}

void CAnimation::setFrameRate(int Rate) {
    frameRate = Rate;
}

void CAnimation::setCurrentFrame(int Frame) {
    if(Frame < 0 || Frame >= maxFrames) return;

    currentFrame = Frame;
}

int CAnimation::getCurrentFrame() {
    return currentFrame;
}
