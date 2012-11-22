#include "GameState.hpp"
#include <MGE/Core/interfaces/IApp.hpp>
#include <MGE/Core/utils/FilePathContainer.h>

GameState::GameState(MGE::IApp& theApp) :
  MGE::IState("Game",theApp),
	mBackgroundTexture(RESOURCE_DIR"/index.jpg"),
	mBackgroundMusic(RESOURCE_DIR"/sounds/11 - Kamek's Theme.flac")
{
}

GameState::~GameState()
{
}

void GameState::init()
{
  // First call our base class implementation
  IState::init();

	mBackgroundSprite.setTexture(mBackgroundTexture.getAsset());
	mBackgroundTexture.getAsset().setSmooth(true);
	mBackgroundSprite.setScale(1,1);
	mBackgroundSprite.setPosition(50,50);
	mBackgroundMusic.getAsset().setLoop(true);
	mBackgroundMusic.getAsset().setVolume(20);
	mBackgroundMusic.getAsset().play();
	std::cout << "Init!" << std::endl;

	CArea::areaControl = new CArea();

	if(player.onLoad(RESOURCE_DIR"/tilesets/yoshi.png", 64, 64, 8) == false) {
		std::cerr << "Failed to load: " << RESOURCE_DIR"/tilesets/yoshi.png" << std::endl;
		return;
	}

	if(mBoss.onLoad(RESOURCE_DIR"/bowser.png", 35, 30, 1) == false) {
		std::cerr << "Failed to load: " << RESOURCE_DIR"/bowser.png" << std::endl;
		return;
	}

	//Init the icon
	std::string assetID = RESOURCE_DIR"/pacman.png";
	mIcon.setID(assetID);
	sf::Image icon = mIcon.getAsset().copyToImage();
	MGE::IApp::getApp()->mWindow.setIcon(32,32,icon.getPixelsPtr());

	//Load the area
	MGEUtil::FilePathContainer fp;
	fp.add(RESOURCE_DIR);
	std::string areafile = fp.find("/maps/myarea.area");
	if(areafile.size()==0) 
		ELOG() << "The area file: " << "./maps/myarea.area" << " could not be found!" << std::endl;
	else if(CArea::areaControl->onLoad(areafile,MAP_WIDTH,MAP_HEIGHT))
		ELOG() << "Failed to load areafile: " << ".areafile" << std::endl;

	// Inits players in the world
	CEntity::EntityList.push_back(&player);
	CEntity::EntityList.push_back(&mBoss);

	CCamera::CameraControl.targetMode = TARGET_MODE_CENTER;
	//CCamera::CameraControl.SetTarget(&Player.X, &Player.Y);
	CCamera::CameraControl.setTarget(&player.pos);

	//Set position
  reset();
	
  // Make sure our update loop is only called 30 times per second
  mApp.setUpdateRate(10);
	mApp.setMaxUpdates(1);

	// Cap frame-rate to a max
	mApp.mWindow.setFramerateLimit(60);

	mApp.mStatManager.setShow(true);

}

void GameState::reset()
{
	player.speed.x=0;	player.speed.y=0;
	player.accel.x=0;	player.accel.y=0;
	player.pos.x = 50; player.pos.y = -40; 
	mBoss.pos.x = 500; mBoss.pos.y = -20;
	mBoss.speed.x=0;	mBoss.speed.y=0;
	mBoss.accel.x=0;	mBoss.accel.y=0;
	player.setCentralBound(30,64);
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

	sf::Vector2f cameraPos = (CCamera::CameraControl.getPos());

	//Set view according to camera
	mApp.mWindow.setView(sf::View(cameraPos,sf::Vector2f(mApp.mWindow.getSize())));

	//mApp.mWindow.draw(mBackgroundSprite);
	CArea::areaControl->onRender(mApp.mWindow,cameraPos);

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
		player.jump();
		//CCamera::CameraControl.onMove(sf::Vector2f(0,-40));
	}
	if(tEvent.type == sf::Event::KeyPressed && (tEvent.key.code == sf::Keyboard::Up)){
		//CCamera::CameraControl.onMove(sf::Vector2f(0,40));
	}
	if(tEvent.type == sf::Event::KeyPressed && (tEvent.key.code == sf::Keyboard::Down)){
		//CCamera::CameraControl.onMove(sf::Vector2f(0,40));
	}
	if(tEvent.type == sf::Event::KeyPressed && (tEvent.key.code == sf::Keyboard::Left)){
		player.moveLeft = true;
		player.moveRight = false;
	}
	if(tEvent.type == sf::Event::KeyPressed && (tEvent.key.code == sf::Keyboard::Right)){
		player.moveRight = true;	
		player.moveLeft = false;	
	}
	if(tEvent.type == sf::Event::KeyReleased && (tEvent.key.code == sf::Keyboard::Left)){
		player.moveLeft = false;
	}
	if(tEvent.type == sf::Event::KeyReleased && (tEvent.key.code == sf::Keyboard::Right)){
		player.moveRight = false;
	}

	if(tEvent.type == sf::Event::KeyPressed && (tEvent.key.code == sf::Keyboard::R)){
		reset();
	}
	/*std::cout << "Camera pos: " << (CCamera::CameraControl.getPos()).x << 
		" " << (CCamera::CameraControl.getPos()).y << std::endl;*/
}
