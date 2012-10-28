/**
*	StateManager class 
**/

#ifndef   CORE_STATE_MANAGER_HPP
	#define   CORE_STATE_MANAGER_HPP

#include <vector>
#include <string>
#include <MGE/Core/Core_types.hpp>

namespace MGE
{
	/// Provides game state manager class for managing game states
	class StateManager
	{
		public:
      /**
       * StateManager constructorb
       */
      StateManager();

      /**
       * StateManager deconstructor
       */
      virtual ~StateManager();

			/**
       * RegisterApp will register a pointer to the App class so it can be used
       * by the StateManager for error handling and log reporting.
       * @param[in] theApp is a pointer to the App (or App derived) class
       */
      void registerApp(IApp* theApp);

			 /**
       * AddCleanup is responsible for adding a class and member function
       * to call during the HandleCleanup method call of the game loop. When
       * this event is called, a pointer to the current IState class will
       * be provided as the Context variable to be used.
       * @param[in] theEventID to use for this event, must be unique
       */
      /**template<class TCLASS>
      void AddCleanup(const typeEventID theEventID, TCLASS& theEventClass,
        typename TEvent<TCLASS, void>::typeEventFunc theEventFunc)
      {
        mCleanupEvents.Add<TCLASS, void>(theEventID, theEventClass, theEventFunc);
      }
			**/

			/**
      * isEmpty will return true if there are no active states on the stack.
      * @return true if state stack is empty, false otherwise.
      */
      bool isEmpty(void);

			/**
      * addActiveState will add theState provided as the current active
      * state.
      * @param[in] theState to set as the current state
      */
      void addActiveState(IState* theState);


			/**
       * addInactiveState will add theState provided as an inactive state.
       * @param[in] theState to be added as an inactive state
       */
      void addInactiveState(IState* theState);

			/**
      * getActiveState will return the current active state on the stack.
      * @return pointer to the current active state on the stack
      */
      IState& getActiveState(void);

			/**
      * inactivateActiveState will cause the current active state to
      * become an inactive state without uninitializing its assets (doesn't
      * call DeInit) and return to the previous state on the stack. This
      * will cause the state to retain its assets.
      */
      void inactivateActivateState(void);

			/**
       * dropActiveState will cause the current active state to uninitialize
       * (calls DeInit) and become an inactive state and return to the
       * previous state on the stack. When a state is uninitialized its
       * assets are unloaded.
       */
      void dropActiveState(void);

			/**
       * resetActiveState will cause the current active state to be reset
       * by calling the ReInit method for that state. 
       */
      void resetActiveState(void);

			 /**
       * removeActiveState will cause the current active state to be removed
       * and return to the previous state on the stack.  Once a state has
       * been removed, you must re-add the state.  If you just want to
       * inactivate the current active state then use dropActiveState instead.
       */
      void removeActiveState(void);

			/**
       * setActiveState will find the state specified by theStateID and make
       * it the current active state and move the previously current active
       * state as the next state.
       * @param[in] stateID is the ID of the State to make active
       */
      void setActiveState(typeStateID stateID);

			/**
       * Cleanup is responsible for dealing with the cleanup of recently
       * dropped states.
       */
      void cleanup(void);

		private:

      ///////////////////////////////////////////////////////////////////////////
      /// Pointer to the App class for error handling and logging
      IApp*                 mApp;
      /// Stack to store the current and previously active states
      std::vector<IState*>  mStack;
      /// Stack to store the dead states until they properly cleaned up
      std::vector<IState*>  mDead;
      /// The event manager to store cleanup events
      //EventManager          mCleanupEvents;

      /**
       * No copies of the class
       */
      StateManager(const StateManager&); // Intentionally undefined

      /**
       * Our assignment operator is private because we do not allow copies
       * of our class
       */
      StateManager& operator=(const StateManager&); // Intentionally undefined
	};
}


#endif /*CORE_STATE_MANAGER_HPP*/