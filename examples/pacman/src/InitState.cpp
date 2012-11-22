#include "InitState.hpp"
#include <MGE/Core/interfaces/IApp.hpp>

InitState::InitState( MGE::IApp& app):
	MGE::IState("Init",app)
{
}

InitState::~InitState()
{
}

void InitState::init()
{
	 IState::init();
}

void InitState::reset()
{
	//Nothing
}

void InitState::handleEvents( sf::Event tEvent )
{

}

void InitState::updateFixed()
{
	//Perform a single update, then crash the state

	//Perform initialization to state 
	mApp.mWindow.setSize(sf::Vector2u(800,600));
	
	// Make sure our update loop is only called 30 times per second
	mApp.setUpdateRate(1);
	mApp.setMaxUpdates(1);
	mApp.mStatManager.setShow(true);
	mApp.mWindow.setFramerateLimit(60);

	//Remove init state
	mApp.mStateManager.removeActiveState();

}

void InitState::updateVariable(float elapsedTime )
{
}

void InitState::draw()
{
}

void InitState::handleCleanup()
{
}


