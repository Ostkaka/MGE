#ifndef   HUDBOARD_HPP
	#define   HUDBOARD_HPP

#include <SFML/Graphics.hpp>
#include <MGE/Core/interfaces/IState.hpp>
#include <MGE/Core/assets/TextureAsset.hpp>
#include <MGE/Core/assets/FontAsset.hpp>
#include <MGE/Core/Core_types.hpp>

class HudBoard 
{
	public:
		/**
		 * Basic constructor
		 */
		HudBoard();
		
		/**
		 * Basic deconstructor
		 */
		~HudBoard();

		/**
		 * Draws ints for lives and score on the screen
		 */
		void draw(sf::Window& window, int lives, int score);

	public:

	protected:

		MGE::FontAsset		mFontAsset;
		int								mTextSize;
};


#endif /*HUDBOARD_HPP*/