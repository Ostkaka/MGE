/*
* This is the abstract IState class in MGE used as an interface
*/

#include <assert.h>
#include <MGE/Core/interfaces/IState.hpp>
#include <MGE/Core/loggers/Log.hpp>
#include <MGE/Core/interfaces/IApp.hpp>

namespace MGE
{
	IState::IState(const typeStateID stateID, IApp& theApp) :
		mApp(theApp),
		mStateID(stateID),
		mInit(false),
		mPaused(false),
		mCleanup(false),
		mElapsedTime(0.0f),
		mPausedTime(0.0f)
	{
		ILOG() << "IState::ctor(" << mStateID << ")" << std::endl;
	}

	IState::~IState()
	{
		ILOG() << "IState::dtor(" << mStateID << ")" << std::endl;
	}

	const typeStateID IState::getID(void) const
	{
		return mStateID;
	}

	void IState::init(void)
	{
		ILOG() << "IState::DoInit(" << mStateID << ")" << std::endl;

		// If Cleanup hasn't been called yet, call it now!
		if(true == mCleanup)
		{
			handleCleanup();
		}

		// Initialize if necessary
		if(false == mInit)
		{
			mInit = true;
			mPaused = false;
			mElapsedTime = 0.0f;
			mElapsedClock.restart();
			mPausedTime = 0.0f;
			mPausedClock.restart();
		}
	}

	void IState::deInit()
	{
		ILOG() << "IState::DeInit(" << mStateID << ")" << std::endl;

		if(true == mInit)
		{
			mCleanup = true;
			mInit = false;
			mElapsedTime += mElapsedClock.getElapsedTime().asSeconds();
			if(true == mPaused)
			{
				mPausedTime += mPausedClock.getElapsedTime().asSeconds();
			}
		}
	}

	bool IState::isInitComplete()
	{
		return mInit;
	}

	bool IState::isPaused()
	{
		return mPaused;
	}

	void IState::pause()
	{
		ILOG() << "IState::Pause(" << mStateID << ")" << std::endl;

		if(false == mPaused)
		{
			mPaused = true;
			mPausedClock.restart();
		}
	}

	void IState::resume()
	{
		ILOG() << "IState::Resume(" << mStateID << ")" << std::endl;

		if(true == mPaused)
		{
			mPaused = false;
			mPausedTime += mPausedClock.getElapsedTime().asSeconds();
		}
	}

	void IState::handleEvents(sf::Event theEvent)
	{
		// Exit program if Escape key is pressed
		if((theEvent.type == sf::Event::KeyReleased) && (theEvent.key.code == sf::Keyboard::Escape))
		{
			// Signal the application to exit
			mApp.quit(StatusAppOK);
		}
	}

	float IState::getElapsedTime() const
	{
			float result = mElapsedClock.getElapsedTime().asSeconds();

			if(false == mInit)
			{
				result = mElapsedTime;
			}

			return result;
	}
	
	void IState::cleanup()
	{
		// This will be true if this IState is about to be deleted soon
		if(true == mCleanup)
		{
			// Call our handle cleanup virtual method
			handleCleanup();

			// Clear our cleanup flag
			mCleanup = false;
		}
	}
} 
