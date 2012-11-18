#ifndef _CPLAYER_H_
    #define _CPLAYER_H_

#include "CEntity.h"
#include <string>
#include <MGE/Core/assets/SoundAsset.hpp>

class CPlayer : public CEntity {
    public:
        CPlayer();

        bool onLoad(const std::string & file, int width, int height, int maxFrames);

        void onLoop(float dt);

        void onRender(sf::RenderWindow & window);

        void onCleanup();

        void onAnimate();

        bool onCollision(CEntity* Entity);

				bool jump();

		protected:
			MGE::SoundAsset			mPlayerJumpBuffer;
			sf::Sound						mPlayerJumpSound;
};

#endif
