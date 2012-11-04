/*
* This class wraps the sf::Texture class for use in the game application
*/

#include <assert.h>
#include <stddef.h>
#include <MGE/Core/assets/TextureAsset.hpp>

namespace MGE
{

	MGE::TextureAsset::TextureAsset():
	TAsset<sf::Texture>()
	{
	}

	MGE::TextureAsset::TextureAsset(const typeAssetID assetID ):
		TAsset<sf::Texture>(assetID)
	{
	}

	MGE::TextureAsset::~TextureAsset()
	{
	}

}
