/**
* StateManager class 
**/

#include <assert.h>
#include <stddef.h>
//#include <GQE/Core/loggers/Log_macros.hpp>
#include <MGE/Core/classes/StateManager.hpp>
#include <MGE/Core/interfaces/IApp.hpp>
#include <MGE/Core/interfaces/IState.hpp>

namespace MGE
{
	StateManager::StateManager() :
	mApp(NULL)
	{
		//ILOGM("StateManager::ctor()");
	}

	StateManager::~StateManager()
	{
		//ILOGM("StateManager::dtor()");
		// Drop all active states
		while(!mStack.empty())
		{
			// Retrieve the currently active state
			IState* anState = mStack.back();

			// Pop the currently active state off the stack
			mStack.pop_back();

			// Pause the currently active state
			anState->pause();

			// De-initialize the state
			anState->deInit();

			// Handle the cleanup before we pop it off the stack
			anState->cleanup();

			// Just delete the state now
			delete anState;

			// Clear pointer
			anState = NULL;
		}

		// Delete all our dropped states
		while(!mDead.empty())
		{
			// Retrieve the currently active state
			IState* anState = mDead.back();

			// Pop the currently active state off the stack
			mDead.pop_back();

			// Pause the currently active state
			anState->pause();

			// De-initialize the state
			anState->deInit();

			// Handle the cleanup before we pop it off the stack
			anState->cleanup();

			// Just delete the state now
			delete anState;

			// Clear pointer
			anState = NULL;
		}

		// Clear pointers 
		mApp = NULL;
	}

	void StateManager::registerApp(IApp* app)
	{
		// Check that our pointer is good
		assert(NULL != app && "StateManager::registerApp() theApp pointer is bad");

		// Make a note of the pointer
		assert(NULL == mApp && "StateManager::registerApp() theApp pointer already registered");
		mApp = app;
	}

	bool StateManager::isEmpty(void)
	{
		return mStack.empty();
	}

	void StateManager::addActiveState(IState* state)
	{
		// Check that they didn't provide a bad pointer
		assert(NULL != state && "StateManager::addActiveState() received a bad pointer");

		// Log the adding of each state
		//ILOG() << "StateManager::AddActiveState(" << theState->GetID() << ")" << std::endl;

		// Is there a state currently running? then Pause it
		if(!mStack.empty())
		{
			// Pause the currently running state since we are changing the
			// currently active state to the one provided
			mStack.back()->pause();
		}

		// Add the active state
		mStack.push_back(state);

		// Initialize the new active state
		mStack.back()->doInit();
	}

	void StateManager::addInactiveState(IState* state)
	{
		// Check that they didn't provide a bad pointer
		assert(NULL != state && "StateManager::addInactiveState() received bad pointer");

		// Log the adding of each state
		//ILOG() << "StateManager::AddInactiveState(" << theState->GetID() << ")" << std::endl;

		// Add the inactive state to the bottom of the stack
		mStack.insert(mStack.begin(), state);
	}

	IState& StateManager::getActiveState()
	{
		return *mStack.back();
	}

	void StateManager::inactivateActivateState()
	{
		// Is there no currently active state to drop?
		if(!mStack.empty())
		{
			// Retrieve the currently active state
			IState* state = mStack.back();

			// Log the inactivating an active state
			//ILOG() << "StateManager::InactivateActiveState(" << state->GetID() << ")" << std::endl;

			// Pause the currently active state
			state->pause();

			// Pop the currently active state off the stack
			mStack.pop_back();

			// Move this now inactive state to the absolute back of our stack
			mStack.insert(mStack.begin(), state);

			// Don't keep pointers around we don't need anymore
			state = NULL;
		}
		else
		{
			// Quit the application with an error status response
			if(NULL != mApp)
			{
				mApp->quit(StatusAppStackEmpty);
			}
			return;
		}

		// Is there another state to activate? then call Resume to activate it
		if(!mStack.empty())
		{
			// Has this state ever been initialized?
			if(mStack.back()->isInitComplete())
			{
				// Resume the new active state
				mStack.back()->resume();
			}
			else
			{
				// Initialize the new active state
				mStack.back()->doInit();
			}
		}
		else
		{
			// There are no states on the stack, exit the program
			if(NULL != mApp)
			{
				mApp->quit(StatusAppOK);
			}
		}
	}

	void StateManager::dropActiveState(void)
	{
		// Is there no currently active state to drop?
		if(!mStack.empty())
		{
			// Retrieve the currently active state
			IState* state = mStack.back();

			// Log the dropping of an active state
			//ILOG() << "StateManager::DropActiveState(" << anState->GetID() << ")" << std::endl;

			// Pause the currently active state
			state->pause();

			// Deinit currently active state before we pop it off the stack
			// (HandleCleanup() will be called by IState::DoInit() method if this
			// state is ever set active again)
			state->deInit();

			// Pop the currently active state off the stack
			mStack.pop_back();

			// Move this now inactive state to the absolute back of our stack
			mStack.insert(mStack.begin(), state);

			// Don't keep pointers around we don't need anymore
			state = NULL;
		}
		else
		{
			// Quit the application with an error status response
			if(NULL != mApp)
			{
				mApp->quit(StatusAppStackEmpty);
			}
			return;
		}

		// Is there another state to activate? then call Resume to activate it
		if(!mStack.empty())
		{
			// Has this state ever been initialized?
			if(mStack.back()->isInitComplete())
			{
				// Resume the new active state
				mStack.back()->resume();
			}
			else
			{
				// Initialize the new active state
				mStack.back()->doInit();
			}
		}
		else
		{
			// There are no states on the stack, exit the program
			if(NULL != mApp)
			{
				mApp->quit(StatusAppOK);
			}
		}
	}
}