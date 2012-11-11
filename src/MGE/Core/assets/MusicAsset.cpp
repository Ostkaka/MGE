#include <assert.h>
#include <stddef.h>
#include <MGE/Core/assets/MusicAsset.hpp>

namespace MGE
{
	MusicAsset::MusicAsset():
	TAsset<sf::Music>()
	{
	}

	MusicAsset::MusicAsset( const typeAssetID assetID ):
	TAsset<sf::Music>(assetID)
	{
	}

	MusicAsset::~MusicAsset()
	{
	}
}