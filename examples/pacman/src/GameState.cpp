#include "GameState.hpp"
#include <MGE/Core/interfaces/IApp.hpp>
#include <MGE/Core/utils/FilePathContainer.h>

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
	if(!pacman.onLoad(RESOURCE_DIR"/tilesets/1.png",16,16,1)){
		ELOG() << "Could not to load pacman: " << RESOURCE_DIR"/tilesets/1.png" << std::endl;
	}

	// Inits players in the world
	if(!ghost1.onLoad(RESOURCE_DIR"/tilesets/1.png",16,16,1)){
		ELOG() << "Could not to load pacman: " << RESOURCE_DIR"/tilesets/1.png" << std::endl;
	}

	//Pacman 
	pacman.mTilePos.x = 10;
	pacman.mTilePos.y = 10;
	//Ghost
	ghost1.mTilePos.x = 11;
	ghost1.mTilePos.y = 12;
	ghost1.setDirection(Direction::MOVE_UP);

	// Inits players in the world
	CEntity::EntityList.push_back(&pacman);
	CEntity::EntityList.push_back(&ghost1);

	sf::Vector2f offset(200,100);

	// Set pos of camera
	CCamera::CameraControl.setPos(sf::Vector2f(mApp.mWindow.getSize().x/2.0,mApp.mWindow.getSize().y/2.0) - offset);

	//CCamera::CameraControl.targetMode = TARGET_MODE_CENTER;
	//CCamera::CameraControl.SetTarget(&Player.X, &Player.Y);

	//Set position
  reset();
}

void GameState::reset()
{
	//Reset the state

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

	//reset view 
	mApp.mWindow.setView(mApp.mWindow.getDefaultView());

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
