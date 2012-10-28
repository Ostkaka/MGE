/*
* This is the abstract IState class in MGE used as an interface
*/
#ifndef   CORE_ISTATE_HPP
	#define   CORE_ISTATE_HPP

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <MGE/Core/Core_types.hpp>

namespace MGE
{
	class IState  {
    	public:
		   /**
       * IState constructor
       * @param[in] theStateID to use for this State object
       * @param[in] theApp is the address to the IApp derived class
       */
      IState(const typeStateID stateID, IApp& theApp);

      /**
       * IState deconstructor
       */
      virtual ~IState();

      /**
       * GetID will return the ID used to identify this State object
       * @return GQE::typeStateID is the ID for this State object
       */
      const typeStateID getID() const;
			
		  /**
       * DoInit is responsible for initializing this State.  HandleCleanup will
       * be called if mCleanup is true so Derived classes should always call
       * IState::DoInit() first before initializing their assets.
       */
      virtual void doInit();

      /**
       * ReInit is responsible for Reseting this state when the
       * StateManager::ResetActiveState() method is called.  This way a Game
       * State can be restarted without unloading and reloading the game assets
       */
      virtual void reInit() = 0;
				
			/**
			* DeInit is responsible for marking this state to be cleaned up
			*/
      void deInit();

      /**
       * IsInitComplete will return true if the DoInit method has been called
       * for this state.
       * @return true if DoInit has been called, false otherwise or if DeInit
       *         was called
       */
      bool isInitComplete();

      /**
       * IsPaused will return true if this state is not the currently active
       * state.
       * @return true if state is not current active state, false otherwise
       */
      bool isPaused();

			 /**
       * Pause is responsible for pausing this State since the Application
       * may have lost focus or another State has become activate.
       */
      virtual void pause();

      /**
       * Resume is responsible for resuming this State since the Application
       * may have gained focus or the previous State was removed.
       */
      virtual void resume();

      /**
       * HandleEvents is responsible for handling input events for this
       * State when it is the active State.
       * @param[in] theEvent to process from the App class Loop method
       */
      virtual void handleEvents(sf::Event aEvent);

			/**
       * updateFixed is responsible for handling all State fixed update needs for
       * this State when it is the active State.
       */
      virtual void updateFixed() = 0;

			/**
      * updateVariable is responsible for handling all State variable update
      * needs for this State when it is the active State.
      * @param[in] theElapsedTime since the last Draw was called
      */
      virtual void updateVariable(float elapsedTime) = 0;

			/**
       * Draw is responsible for handling all Drawing needs for this State
       * when it is the Active State.
       */
      virtual void draw(void) = 0;

      /**
       * Cleanup is responsible for calling HandleCleanup if this class has
       * been flagged to be cleaned up after it completes the game loop.
       */
      void cleanup(void);

      /**
       * GetElapsedTime will return one of the following:
       * 1) If this state is not paused: total elapsed time since DoInit was called
       * 2) If this state is paused: total elapsed time since Pause was called
       * 3) If this state is not initialized: total elapsed time from DoInit to DeInit
       * @return total elapsed time as described above.
       */
      float getElapsedTime(void) const;

	  protected:
      /// Address to the App class
      IApp&                 mApp;

      /**
       * HandleCleanup is responsible for performing any cleanup required
       * before this State is removed.
       */
      virtual void handleCleanup(void) = 0;

			private:
      /// The State ID
      const typeStateID     mStateID;
      /// Boolean that indicates that DoInit has been called
      bool                  mInit;
      /// State is currently paused (not active)
      bool                  mPaused;
      /// State needs to be cleaned up at the end of the next game loop
      bool                  mCleanup;
      /// Clock will help us keep track of running and paused elapsed time
      sf::Clock             mElapsedClock;
      /// Total elapsed time since DoInit was called
      float                 mElapsedTime;
      /// Clock will help us keep track of time paused
      sf::Clock             mPausedClock;
      /// Total elapsed time paused since DoInit was called
      float                 mPausedTime;

      /**
       * Protected Copy constructor
       */
      IState(const IState&); 

      /**
       * Assignment operator
       */
      IState& operator=(const IState&); 
	};

}

#endif /* CORE_ISTATE_HPP */
