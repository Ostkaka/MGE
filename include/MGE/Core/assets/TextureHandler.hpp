/*
* Derived class from IAssetHandler for managing sf:Textures
*/

#ifndef   TEXTUREHANDLER_HPP
	#define   TEXTUREHANDLER_HPP

#include <SFML/Graphics.hpp>
#include <MGE/Core/Core_types.hpp>
#include <MGE/Core/interfaces/TAssetHandler.hpp>

namespace MGE
{
	/// TextureHandler manages the textures used in the game
	class TextureHandler : public TAssetHandler<sf::Texture>
	{
	public:
		/*
		* Basic constructor
		*/
		TextureHandler();

		/*
		* Basic deconstructor
		*/
		virtual ~TextureHandler();

		/*
		* See syntax from derived class
		*/
		virtual bool loadFromFile(const typeAssetID assetID, sf::Texture& asset);

	private:

	};
}

#endif /*TEXTUREHANDLER_HPP*/