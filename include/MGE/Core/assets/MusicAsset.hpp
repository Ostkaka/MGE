/*
* This class wraps the sf::Music class for use in the game application
*/

#ifndef  MUSICEASSET_HPP
	#define   MUSICASSET_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <MGE/Core/interfaces/TAsset.hpp>
#include <MGE/Core/Core_types.hpp>

namespace MGE
{
	/// Asset class for wrapping sf::Texture
	class MusicAsset : public TAsset<sf::Music>
	{
	public:
		/**
		* See template class description
		*/
		MusicAsset();
		MusicAsset(const typeAssetID assetID);

		/**
		* See template class description
		*/
		virtual ~MusicAsset();
	};
} 
#endif /*TEXTUREASSET_HPP*/