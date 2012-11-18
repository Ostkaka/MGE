#ifndef CBOSS_H_
	#define CBOSS_H_

#include "CEntity.h"
#include <string>

class CBoss : public CEntity {
public:
	CBoss();

	bool onLoad(const std::string & file, int width, int height, int maxFrames);

	void onLoop(float dt);

	void onRender(sf::RenderWindow & window);

	void onCleanup();

	void onAnimate();

	bool onCollision(CEntity* Entity);
};

#endif /*CBOSS_H_*/