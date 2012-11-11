#include "GameState.hpp"
#include <MGE/Core/interfaces/IApp.hpp>
#include <MGE/Core/utils/FilePathContainer.h>

GameState::GameState(MGE::IApp& theApp) :
  MGE::IState("Game",theApp),
	mBackgroundTexture("./resources/index.jpg"),
	mBackgroundMusic("./resources/TurfIntro.ogg"){
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
	//mBackgroundMusic.getAsset().setLoop(true);
	//mBackgroundMusic.getAsset().setVolume(20);
	//mBackgroundMusic.getAsset().play();
	std::cout << "Init!" << std::endl;

	CArea::areaControl = new CArea();


	if(player.onLoad(RESOURCE_DIR"/tilesets/yoshi.png", 64, 64, 8) == false) {
		std::cerr << "Failed to load: " << ("/tilesets/yoshi.png") << std::endl;
		return;
	}

	if(player2.onLoad(RESOURCE_DIR"/tilesets/yoshi.png", 64, 64, 8) == false) {
		std::cerr << "Failed to load: " << ("/tilesets/yoshi.png") << std::endl;
		return;
	}

	//Load the area
	MGEUtil::FilePathContainer fp;
	fp.add(RESOURCE_DIR);
	std::string areafile = fp.find("/maps/myarea.area");
	if(areafile.size()==0) 
		ELOG() << "The area file: " << "./maps/myarea.area" << " could not be found!" << std::endl;
	else if(CArea::areaControl->onLoad(areafile))
		ELOG() << "Failed to load areafile: " << ".areafile" << std::endl;
		
  reset();
	
  // Make sure our update loop is only called 30 times per second
  mApp.setUpdateRate(60);
	mApp.setMaxUpdates(1);
	mApp.mStatManager.setShow(true);
}

void GameState::reset()
{
	player.speed.x=0;	player.speed.y=0;
	player.accel.x=0;	player.accel.y=0;
	player.pos.x = 50;
	player2.pos.x = 500;
	player2.speed.x=0;	player2.speed.y=0;
	player2.accel.x=0;	player2.accel.y=0;
	player.setCentralBound(30,64);

	CEntity::EntityList.push_back(&player);
	CEntity::EntityList.push_back(&player2);

	CCamera::CameraControl.targetMode = TARGET_MODE_CENTER;
	//CCamera::CameraControl.SetTarget(&Player.X, &Player.Y);
	CCamera::CameraControl.setTarget(&player.pos);
}

void GameState::updateFixed()
{
}

void GameState::updateVariable(float theElapsedTime)
{
	for(int i = 0;i < CEntity::EntityList.size();i++) {
		if(!CEntity::EntityList[i]) continue;

		CEntity::EntityList[i]->onLoop(theElapsedTime);
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
	//mApp.mWindow.draw(mBackgroundSprite);
	CArea::areaControl->onRender(mApp.mWindow,(CCamera::CameraControl.getPos() + sf::Vector2f(-CCamera::CameraControl.width/2,-CCamera::CameraControl.height/2)));

	for(int i = 0;i < CEntity::EntityList.size();i++) {
		if(!CEntity::EntityList[i]) continue;
		CEntity::EntityList[i]->onRender(mApp.mWindow);
	}
}

void GameState::handleEvents(sf::Event tEvent)
{
	if((tEvent.type == sf::Event::KeyReleased) && (tEvent.key.code == sf::Keyboard::Escape))
		mApp.quit(MGE::StatusAppOK);

	if(tEvent.type == sf::Event::MouseButtonReleased){
		std::cout << "This is klick!" << std::endl;
	}

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
	std::cout << "Camera pos: " << (CCamera::CameraControl.getPos()).x << 
		" " << (CCamera::CameraControl.getPos()).y << std::endl;
}
