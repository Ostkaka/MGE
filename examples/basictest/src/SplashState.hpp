#ifndef   SPLASHSTATE_HPP
	#define   SPLASHSTATE_HPP

#include <SFML/Graphics.hpp>
#include <MGE/Core/interfaces/IState.hpp>
#include <MGE/Core/assets/TextureAsset.hpp>
#include <MGE/Core/Core_types.hpp>
#include <MGE/Core/utils/CFilter.hpp>

#include <string>
#include <iostream>

/// Provides the TicTacToe GameState example
class SplashState : public MGE::IState
{
  public:
    /**
     * GameState constructor
     * @param[in] theApp is an address to the App class.
     */
    SplashState(MGE::IApp& app,float splashDuration);

    /**
     * GameState deconstructor
     */
    virtual ~SplashState();

    /**
     * DoInit is responsible for initializing this State
     */
    virtual void init();

    /**
     * ReInit is responsible for Reseting this state when the
     * StateManager::ResetActiveState() method is called.  This way a Game
     * State can be restarted without unloading and reloading the game assets
     */
    virtual void reset();

    /**
     * HandleEvents is responsible for handling input events for this
     * State when it is the active State.
     * @param[in] theEvent to process from the App class Loop method
     */
    virtual void handleEvents(sf::Event tEvent);

    /**
     * UpdateFixed is responsible for handling all State fixed update needs for
     * this State when it is the active State.
     */
    virtual void updateFixed();

    /**
     * UpdateVariable is responsible for handling all State variable update
     * needs for this State when it is the active State.
     * @param[in] theElapsedTime since the last Draw was called
     */
    virtual void updateVariable(float elapsedTime);

    /**
     * Draw is responsible for handling all Drawing needs for this State
     * when it is the Active State.
     */
    virtual void draw();

  protected:
    /**
     * HandleCleanup is responsible for performing any cleanup required before
     * this State is removed.
     */
    virtual void handleCleanup();

  private:

    float mSplashDuration;
		MGE::TextureAsset mSpashScreenAsset;
		sf::Sprite mSpalshScreenSprite;
		MGEUtil::Filter mIntroFilter;

}; // class GameState


#endif /*SPLASHSTATE_HPP*/