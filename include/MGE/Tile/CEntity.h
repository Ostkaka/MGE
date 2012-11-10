#ifndef _CENTITY_H_
    #define _CENTITY_H_

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include "CArea.h"
#include "CAnimation.h"
#include "CCamera.h"
#include "CFPS.h"
#include "Define.h"
#include <SFML/Graphics.hpp>

#define ENTITY_JUMP_FRAME 7

#define X_COL_OFFSET -20
#define Y_COL_OFFSET -1

//Usefull macros
#define Maximum(a, b) ((a > b) ? a : b)
#define Minimum(a, b) ((a < b) ? a : b)

enum {
    ENTITY_TYPE_GENERIC = 0,
    ENTITY_TYPE_PLAYER
};

enum {
    ENTITY_FLAG_NONE     = 0,
    ENTITY_FLAG_GRAVITY  = 0x00000001,
    ENTITY_FLAG_GHOST    = 0x00000002,
    ENTITY_FLAG_MAPONLY  = 0x00000004
};

class CEntity{
    public:
        static std::vector<CEntity*>    EntityList;

    protected:
		CAnimation anim_Control;

		//Graphics
		sf::Sprite sprite;
	    sf::Texture * texture;

    public:
		sf::Vector2f pos;
		sf::Vector2f size;

        bool        moveLeft;
        bool        moveRight;

    //Status flags
    public:
        int        type;
        bool       dead;
        int        flags;

		//Speed variables
		sf::Vector2f speed;
		sf::Vector2f accel;
		sf::Vector2f maxSpeed;

    //Frame animation variables
    protected:
        int             CurrentFrameCol;
        int             CurrentFrameRow;

    /*
    *   Test version of bouding box instead of collision box
    */
    protected:
		//Bound
		sf::IntRect bound;

    public:
        CEntity();

        virtual ~CEntity();

    public:
        virtual bool onLoad(const std::string & file, int width, int height, int maxFrames);

        virtual void onLoop();

		virtual void onRender(sf::RenderWindow & window);

        virtual void onCleanup();

        virtual void onAnimate();

        virtual bool onCollision(CEntity* entity);

		void    onMove(sf::Vector2f move);

        void    stopMove();

        bool    collides(sf::IntRect rect);

        //Check if new position is valid
        bool     posValid(sf::Vector2f newPos);
        bool     posValidTile(CTile* Tile);
        bool     posValidEntity(CEntity* Entity,const sf::IntRect & newBound);

		//Returns the bound of the sprite for collision
		sf::IntRect getBound();
		void setCentralBound(int width, int height);

		void CEntity::printStats();

	protected:
        bool    canJump;

    public:
        bool     jump();
};

class CEntityCol {
    public:
        static std::vector<CEntityCol>  EntityColList;

    public:
        CEntity* entityA;
        CEntity* entityB;

    public:
        CEntityCol();
};

#endif
