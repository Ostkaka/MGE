#include "CEntity.h"
#include "CApp.h"

std::vector<CEntity*> CEntity::EntityList;

CEntity::CEntity() {
    texture=NULL;

	pos.x=0;pos.y=0;
	speed.x=0;speed.y=0;
	accel.x=0;accel.y=0;

    moveLeft  = false;
    moveRight = false;
    canJump = false;

    type = ENTITY_TYPE_GENERIC;

    dead = false;
    flags = ENTITY_FLAG_GRAVITY;
    
	maxSpeed.x = 5;
    maxSpeed.y = 5;

    CurrentFrameCol = 0;
    CurrentFrameRow = 0;

}

CEntity::~CEntity() {
}

bool CEntity::onLoad(const std::string & file, int width, int height, int maxFrames) {
	texture = new sf::Texture();
	if((texture = ant::AssetManager::mAssetManager.getOrLoadTexture(file)) == NULL) {
		delete texture;
        fprintf(stderr,"could not load file %s\n",file.c_str());
        return false;
    }

    this->size.x = width;
    this->size.y = height;

	anim_Control.maxFrames = maxFrames;

	sprite.setTexture(*texture);
	sprite.setTextureRect(sf::IntRect(0,0,size.x,size.y));
	
	//Init bound
	bound.left=pos.x;
	bound.top=pos.y;
	bound.width=size.x;
	bound.height=size.y;

    return true;
}

void CEntity::onLoop() {
    //We're not Moving
    if(moveLeft == false && moveRight == false) {
        stopMove();
    }

    if(moveLeft) {
        accel.x = -0.5;
    }else if(moveRight) {
        accel.x = 0.5;
    }

    if(flags & ENTITY_FLAG_GRAVITY) {
        accel.y = 0.75f;
    }

    speed.x += accel.x * CFPS::FPSControl.getSpeedFactor();
    speed.y += accel.y * CFPS::FPSControl.getSpeedFactor();

    if(speed.x > maxSpeed.x)  speed.x =  maxSpeed.x;
    if(speed.x < -maxSpeed.x) speed.x = -maxSpeed.x;
    if(speed.y > maxSpeed.y)  speed.y =  maxSpeed.y;
    if(speed.y < -maxSpeed.y) speed.y = -maxSpeed.y;

    onAnimate();
    onMove(speed);
	sprite.setPosition(pos);

	//Update Bound
	bound.top = pos.y + size.y/2 - bound.height/2;
	bound.left = pos.x + size.x/2 - bound.width/2;
}

void CEntity::onAnimate() {
    if(moveLeft){
        CurrentFrameCol = 0;
    }else

    if(moveRight) {
        CurrentFrameCol = 1;
    }
    anim_Control.onAnimate();
	sprite.setTextureRect(sf::IntRect((CurrentFrameCol * size.x),((CurrentFrameRow + anim_Control.getCurrentFrame()) * size.y), size.x, size.y));
}

void CEntity::onRender(sf::RenderWindow & window) {
    if(texture == NULL) return;
	window.draw(sprite);
	if(DEBUG){
		sf::RectangleShape rect(sf::RectangleShape(sf::Vector2f(bound.width,bound.height)));
		rect.setPosition(sf::Vector2f(bound.left,bound.top));
		rect.setOutlineThickness(1);
		rect.setFillColor(sf::Color::Transparent);
		window.draw(rect);
	}
}

void CEntity::onCleanup() {
    if(texture) {
        delete texture;
    }
}

bool CEntity::onCollision(CEntity* entity) {
    return true;
}

void CEntity::onMove(sf::Vector2f move) {
    canJump = false;

    if(move.x == 0 && move.y == 0) return;

    float newX = 0;
    float newY = 0;

    move.x *= CFPS::FPSControl.getSpeedFactor();
    move.y *= CFPS::FPSControl.getSpeedFactor();

    if(move.x != 0) {
        if(move.x >= 0)   newX =  CFPS::FPSControl.getSpeedFactor();
        else             newX = -CFPS::FPSControl.getSpeedFactor();
    }

    if(move.y != 0) {
        if(move.y >= 0)   newY =  CFPS::FPSControl.getSpeedFactor();
        else             newY = -CFPS::FPSControl.getSpeedFactor();
    }

    while(true){
        if(flags & ENTITY_FLAG_GHOST) {
            posValid(sf::Vector2f((pos.x + newX), (pos.y + newY))); //We don't care about collisions, but we need to send events to other entities

            pos.x += newX;
            pos.y += newY;
        }else{
			if(posValid(sf::Vector2f((pos.x + newX),(pos.y)))) {
                pos.x += newX;
            }else{
                speed.x = 0;
            }

            if(posValid(sf::Vector2f((pos.x),(pos.y + newY)))) {
                pos.y += newY;
            }else{
                if(move.y > 0) {
                    canJump = true;
                }
                speed.y = 0;
            }
        }

        move.x += -newX;
        move.y += -newY;

        if(newX > 0 && move.x <= 0) newX = 0;
        if(newX < 0 && move.x >= 0) newX = 0;

        if(newY > 0 && move.y <= 0) newY = 0;
        if(newY < 0 && move.y >= 0) newY = 0;

        if(move.x == 0) newX = 0;
        if(move.y == 0) newY = 0;

        if(move.x == 0 && move.y     == 0)     break;
        if(newX  == 0 && newY     == 0)     break;
    }
}

void CEntity::stopMove() {
    if(speed.x > 0) {
        accel.x = -1;
    }

    if(speed.x < 0) {
        accel.x =  1;
    }

    if(speed.x < 2.0f && speed.x > -2.0f) {
        accel.x = 0;
        speed.x = 0;
    }
}

bool CEntity::collides(sf::IntRect trialBound) {
	if(bound.intersects(trialBound)) return true;
	else return false;
}

bool CEntity::posValid(sf::Vector2f newPos) {
    bool Return = true;

	//Create new rectangle for bound
	sf::IntRect trialBound = bound;
	trialBound.left = ((int)newPos.x) + size.x/2 - bound.width/2;
	trialBound.top = ((int)newPos.y) + size.y/2 - bound.height/2;

    /*
    * Do collision against the Map
    */
    int startX = (trialBound.left)/TILE_SIZE;
    int startY = (trialBound.top)/TILE_SIZE;

    int EndX = ((trialBound.left + trialBound.width) - 1)/TILE_SIZE;
	int EndY = ((trialBound.top + trialBound.height) - 1)/TILE_SIZE;

    for(int iY = startY;iY <= EndY;iY++) {
        for(int iX = startX;iX <= EndX;iX++) {
            CTile* Tile = CArea::areaControl.getTile(iX * TILE_SIZE, iY * TILE_SIZE);
            if(posValidTile(Tile) == false) {
                Return = false;
            }
        }
    }

    /*
	* Do collision against other entities if entity
    * can collide with other entities
    */
    if(flags & ENTITY_FLAG_MAPONLY) {
    }else{
        //Check for collisions with entities
        for(size_t i = 0;i < EntityList.size();i++) {
            if(posValidEntity(EntityList[i], trialBound) == false) {
                Return = false;
            }
        }
    }
    return Return;
}

bool CEntity::posValidTile(CTile* Tile) {
    if(Tile == NULL) {
        return true;
    }
    if(Tile->TypeID == TILE_TYPE_BLOCK && !(flags & ENTITY_FLAG_GHOST)) {
        return false;
    }
    return true;
}

bool CEntity::posValidEntity(CEntity * entity,const sf::IntRect & trialBound) {

    if(this != entity && entity != NULL && entity->dead == false &&
        entity->flags ^ ENTITY_FLAG_MAPONLY &&
        entity->collides(trialBound) == true){
			 
        CEntityCol EntityCol;

        EntityCol.entityA = this;
        EntityCol.entityB = entity;

        CEntityCol::EntityColList.push_back(EntityCol);

        return false;
    }
    return true;
}

bool CEntity::jump() {
    if(canJump == false) return false;
    speed.y = -maxSpeed.y;
    return true;
}

sf::IntRect CEntity::getBound(){
	return this->bound;
}

void CEntity::setCentralBound(int width, int height){
	this->bound.width=width;
	this->bound.height=height;
}

void CEntity::printStats(){
	std::cout << "Position: " << pos.x << " " << pos.y << std::endl;
	std::cout << "Speed: " << speed.x << " " << speed.y << std::endl;
	std::cout << "Acceleration: " << accel.x << " " << accel.y << std::endl;
}