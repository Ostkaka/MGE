#ifndef CBOSS_H_
	#define CBOSS_H_

#include "CEntity.h"
#include <string>
#include <MGE/Core/assets/SoundAsset.hpp>

class CBoss : public CEntity {
public:
	CBoss();

	bool onLoad(const std::string & file, int width, int height, int maxFrames);

	void onLoop(float dt);

	void onRender(sf::RenderWindow & window);

	void onCleanup();

	void onAnimate();

	bool onCollision(CEntity* Entity);

protected:
			MGE::SoundAsset			mBossHurtBuffer;
			sf::Sound						mBossHurtSound;
};

#endif /*CBOSS_H_*/