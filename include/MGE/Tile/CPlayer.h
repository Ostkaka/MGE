#ifndef _CPLAYER_H_
    #define _CPLAYER_H_

#include "CEntity.h"
#include <string>

class CPlayer : public CEntity {
    public:
        CPlayer();

        bool onLoad(const std::string & file, int width, int height, int maxFrames);

        void onLoop();

        void onRender(sf::RenderWindow & window);

        void onCleanup();

        void onAnimate();

        bool onCollision(CEntity* Entity);
};

#endif
