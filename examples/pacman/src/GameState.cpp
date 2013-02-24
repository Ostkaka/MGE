#include "GameState.hpp"
#include <MGE/Core/interfaces/IApp.hpp>
#include <MGE/Core/utils/FilePathContainer.h>

#define PACMAN_SPRITES RESOURCE_DIR"/pacman_tiles.png"
#define SHEET_OFFSET sf::Vector2f();

GameState::GameState(MGE::IApp& theApp) :
  MGE::IState("Game",theApp)
{
}

GameState::~GameState()
{
}

void GameState::init()
{
  // First call our base class implementation
  IState::init();

	CArea::areaControl = new CArea();

	//Init the icon
	//std::string assetID = RESOURCE_DIR"/pacman.png";
	//mIcon.setID(assetID);
	//sf::Image icon = mIcon.getAsset().copyToImage();
	//MGE::IApp::getApp()->mWindow.setIcon(32,32,icon.getPixelsPtr());

	//Load the area
	MGEUtil::FilePathContainer fp;
	fp.add(RESOURCE_DIR);
	std::string areafile = fp.find("/maps/pacman.area");
	if(areafile.size()==0) 
		ELOG() << "The area file: " << "./maps/pacman.area" << " could not be found!" << std::endl;
	else if(CArea::areaControl->onLoad(areafile,PACMAN_MAP_WIDTH,PACMAN_MAP_HEIGHT));
		ELOG() << "Failed to load areafile: " << ".areafile" << std::endl;

	// Inits players in the world
	if(!pacman.onLoad(PACMAN_SPRITES,16,16,2)){
		ELOG() << "Could not to load pacman: " << RESOURCE_DIR"/pacmantileset.png" << std::endl;
	}

	// Inits players in the world
	if(!ghost1.onLoad(PACMAN_SPRITES,16,16,1)){
		ELOG() << "Could not to load pacman: " << RESOURCE_DIR"/pacmantileset.png" << std::endl;
	}

	reset();
}

void GameState::reset()
{
	// Clear Candy
	clearCandy();

	// Clear the game state
	CEntity::EntityList.clear();

	// Place candy on map
	candyFactory(CArea::areaControl);

	// Pacman 
	pacman.setTilePos(sf::Vector2i(10,9));
	pacman.dead = false;
	pacman.setDirection(MOVE_NONE);

	// Ghost
	ghost1.setTilePos(sf::Vector2i(12,13));
	ghost1.setDirection(Direction::MOVE_LEFT);

	// Inits players in the world
	CEntity::EntityList.push_back(&pacman);
	CEntity::EntityList.push_back(&ghost1);

	// Inits the player into the world
	sf::Vector2f offset(200,100);

	// Set game data
	mScore = 1000;
	mLives = 3;

	// Set pos of camera
	CCamera::CameraControl.setPos(sf::Vector2f(mApp.mWindow.getSize().x/2.0,mApp.mWindow.getSize().y/2.0) - offset);
}

void GameState::updateFixed()
{
	
}

void GameState::updateVariable(float elapsedTime)
{
	//std::cout << "Elapsed time: " << elapsedTime << std::endl;
	for(int i = 0;i < CEntity::EntityList.size();i++) {
		if(!CEntity::EntityList[i]) continue;

		CEntity::EntityList[i]->onLoop(elapsedTime);
	}

	//Collision Events
	for(int i = 0;i < CEntityCol::EntityColList.size();i++) {
		CEntity* EntityA = CEntityCol::EntityColList[i].entityA;
		CEntity* EntityB = CEntityCol::EntityColList[i].entityB;

		if(EntityA == NULL || EntityB == NULL) continue;

		if(EntityA->onCollision(EntityB)) {
			EntityB->onCollision(EntityA);
		}
	}

	CEntityCol::EntityColList.clear();
}

void GameState::handleCleanup()
{
	delete CArea::areaControl;

	for(int i = 0;i < CEntity::EntityList.size();i++) {
		if(!CEntity::EntityList[i]) continue;

		CEntity::EntityList[i]->onCleanup();
	}
	CEntity::EntityList.clear();

	// Clear candy
	clearCandy();
}

void GameState::draw()
{

	mApp.mWindow.clear();

	//Get camera pos
	sf::Vector2f cameraPos = (CCamera::CameraControl.getPos());

	//Set view according to camera
	mApp.mWindow.setView(sf::View(cameraPos,sf::Vector2f(mApp.mWindow.getSize())));

	//mApp.mWindow.draw(mBackgroundSprite);
	CArea::areaControl->onRender(mApp.mWindow,cameraPos);

	//Render entitys
	for(int i = 0;i < CEntity::EntityList.size();i++) {
		if(!CEntity::EntityList[i]) continue;
		CEntity::EntityList[i]->onRender(mApp.mWindow);
	}

	// Reset view 
	mApp.mWindow.setView(mApp.mWindow.getDefaultView());

	// Draw the hud
	mHudBoard.draw(mApp.mWindow,mLives,mScore);

}

void GameState::handleEvents(sf::Event tEvent)
{
	if((tEvent.type == sf::Event::KeyReleased) && (tEvent.key.code == sf::Keyboard::Escape))
		mApp.quit(MGE::StatusAppOK);

	if(tEvent.type == sf::Event::MouseButtonReleased){
		std::cout << "This is klick!" << std::endl;
	}


	if((tEvent.type == sf::Event::KeyReleased) && (tEvent.key.code == sf::Keyboard::E))
		pause();

	if(tEvent.type == sf::Event::KeyPressed && (tEvent.key.code == sf::Keyboard::Space)){
		pacman.setDirection(MOVE_NONE);
		//CCamera::CameraControl.onMove(sf::Vector2f(0,-40));
	}
	if(tEvent.type == sf::Event::KeyPressed && (tEvent.key.code == sf::Keyboard::Up)){
 		pacman.setDirection(MOVE_UP);			
	}
	if(tEvent.type == sf::Event::KeyPressed && (tEvent.key.code == sf::Keyboard::Down)){
		pacman.setDirection(MOVE_DOWN);
	}
	if(tEvent.type == sf::Event::KeyPressed && (tEvent.key.code == sf::Keyboard::Left)){
		pacman.setDirection(MOVE_LEFT);
	}
	if(tEvent.type == sf::Event::KeyPressed && (tEvent.key.code == sf::Keyboard::Right)){
		pacman.setDirection(MOVE_RIGHT);
		//player.moveRight = true;	
		//player.moveLeft = false;	
	}
	if(tEvent.type == sf::Event::KeyReleased && (tEvent.key.code == sf::Keyboard::Left)){
		//player.moveLeft = false;
	}
	if(tEvent.type == sf::Event::KeyReleased && (tEvent.key.code == sf::Keyboard::Right)){
		//player.moveRight = false;
	}

	if(tEvent.type == sf::Event::KeyPressed && (tEvent.key.code == sf::Keyboard::R)){
		reset();
	}
	/*std::cout << "Camera pos: " << (CCamera::CameraControl.getPos()).x << 
		" " << (CCamera::CameraControl.getPos()).y << std::endl;*/
}

void GameState::constructCandy(int x,int y){

	Candy * candy = new Candy();

	candy->onLoad(PACMAN_SPRITES,16,16);

	candy->setTilePos(sf::Vector2i(x,y));

	CEntity::EntityList.push_back(candy);
	mCandyList.push_back(candy);
}

void GameState::candyFactory(CArea * area)
{
	// Loop all tiles on the map and place candy
	sf::Vector2i map = area->mMapSize;
	for(int i = 0 ; i < map.x ; i++)
	{
		for(int j = 0 ; j < map.y ; j++)
		{
			// Place candy on tile if it is normal
			int x = i * TILE_SIZE, y = j * TILE_SIZE;
			if(area->getTile(x,y)->TypeID == TILE_TYPE_NORMAL)
				constructCandy(i,j);
		}
	}
}

void GameState::clearCandy()
{
	std::list<Candy*>::iterator iter = mCandyList.begin();
	while(iter != mCandyList.end())
		delete *(iter++);
	mCandyList.clear();
}

void GameState::printCandyStatus()
{
	int alive=0,dead=0;
	std::list<Candy*>::iterator iter = mCandyList.begin();
	while(iter != mCandyList.end())
	{
		if((*iter)->dead)
			dead++;
		else 
			alive++;
		iter++;
	}
	std::cout << std::endl << "Alive candy: " << alive <<  " ||dead candy: " << dead << std::endl;
}
