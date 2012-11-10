#ifndef _CANIMATION_H_
    #define _CANIMATION_H_

#include <SFML\System\Clock.hpp>

class CAnimation {
    private:
		sf::Clock clock;
        int currentFrame;
        int     frameInc;
        int     frameRate; //Milliseconds
        long    oldTime;

    public:
        int maxFrames;
        bool    oscillate;

    public:
        CAnimation();

        void onAnimate();

    public:
        void setFrameRate(int Rate);
        void setCurrentFrame(int Frame);
        int getCurrentFrame();
};

#endif
