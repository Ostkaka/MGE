#ifndef _CCAMERA_H_
    #define _CCAMERA_H_

#include <SFML\Graphics.hpp>
#include "Define.h"

enum {
    TARGET_MODE_NORMAL = 0,
    TARGET_MODE_CENTER
};

class CCamera {
    public:
        static CCamera CameraControl;

    private:
			sf::Vector2f pos;
			sf::Vector2f * targetCenter;

    public:
			int targetMode;
			int width;
			int height;

    public:
        CCamera();

    public:
        void onMove(const sf::Vector2f & move);
				sf::Vector2f getPos();
        void setPos(const sf::Vector2f & pos);
				void setTarget(sf::Vector2f * Center);
};

#endif
