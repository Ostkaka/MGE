/*
* Class that handles statistical information about the applicaiton such
* as framerates and updates per second.
*/

#include <assert.h>
#include <sstream>
#include <MGE/Core/classes/StatManager.hpp>
#include <MGE/Core/loggers/Log.hpp>
#include <MGE/Core/interfaces/IApp.hpp>

namespace MGE
{
	StatManager::StatManager():
		mApp(NULL),
		mShow(false),
		mFrames(0),
		mFrameClock(),
		mDefaultFont(),
		mFPS(NULL),
		mUpdates(0),
		mUpdateClock(),
		mUPS(NULL)
	{
		ILOG() << "StatManager::ctor()" << std::endl;
		mDefaultFont.loadFromFile(RESOURCE_DIR"/arial.ttf");
	}

	StatManager::~StatManager()
	{
		ILOG() << "StatManager::dtor()" << std::endl;

		// Clear pointers we don't need anymore
		mApp = NULL;
	}

	void StatManager::init()
	{
		ILOGM("StatManager::init()");

		// Reset counters
		mFrames = 0;
		mUpdates = 0;

		mFrameClock.restart();
		mUpdateClock.restart();

		// Position and color for the FPS/UPS string
		mFPS = new(std::nothrow) sf::Text("", mDefaultFont, 30);
		mFPS->setColor(sf::Color(0,255,0,128));
		mFPS->setPosition(0,0);

		mUPS = new(std::nothrow) sf::Text("", mDefaultFont, 30);
		mUPS->setColor(sf::Color(0,255,0,128));
		mUPS->setPosition(0,30);

	}

	void StatManager::deInit()
	{
		ILOGM("StatManager::deInit()");

		// Delete FPS string
		delete mFPS;
		mFPS = NULL;

		// Delete UPS string
		delete mUPS;
		mUPS = NULL;
	}

	bool StatManager::isShowing()
	{
		return mShow;
	}

	void StatManager::setShow( bool show )
	{
		mShow = show;
	}

	int StatManager::getUpdates()
	{
		return mUpdates;
	}

	int StatManager::getFrames()
	{
		return mFrames;
	}

	void StatManager::registerApp( IApp * app )
	{
		// Check that our pointer is good
		assert(NULL != app && "StatManager::RegisterApp() theApp pointer provided is bad");

		// Make a note of the pointer
		assert(NULL == mApp && "StatManager::RegisterApp() theApp pointer was already registered");
		mApp = app;
	}

	void StatManager::updateFixed()
	{
		// Check App pointer
		assert(NULL != mApp && "StatManager::Update() bad app pointer");

		// Increment updates
		mUpdates++;
		if(mUpdateClock.getElapsedTime().asSeconds() > 1.0f)
		{
			std::ostringstream updates;
			updates.precision(2);
			updates.width(7);
			updates << "UPS: " << std::fixed << mUpdates;
			mUPS->setString(updates.str());
			
			//Reset updates
			mUpdates = 0;
			mUpdateClock.restart();
		}
	}

	void StatManager::draw()
	{
		// Check our mApp pointer
		assert(NULL != mApp && "StatManager::Draw() invalid app pointer provided");

		// Increment frame counter
		mFrames++;
		if(mFrameClock.getElapsedTime().asSeconds() > 1.0f)
		{			
			std::ostringstream frames;
			
			frames.precision(2);
			frames.width(7);
			frames << "FPS: " << std::fixed << mFrames;
			mFPS->setString(frames.str());

			// Reset updates
			mFrames = 0;
			mFrameClock.restart();
		}

		if(mShow)
		{
			#ifndef PRINT_COUT_ONLY
			// Draw FPS
			mApp->mWindow.draw(*mUPS);
			// Draw UPS
			mApp->mWindow.draw(*mFPS);
			#else
			std::cout << mFPS->getString().toAnsiString() 
				<< mUPS->getString().toAnsiString() 
				<< std::endl;
			#endif
		}
	}
}