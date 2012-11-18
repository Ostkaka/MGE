/**
 * Provides the Sound Asset type used by the AssetManager 
 */

#include <assert.h>
#include <stddef.h>
#include <MGE/Core/assets/SoundAsset.hpp>
#include <MGE/Core/loggers/Log.hpp>

namespace MGE
{

	SoundAsset::SoundAsset()
	{

	}

	SoundAsset::SoundAsset( const typeAssetID assetID ):
	TAsset<sf::SoundBuffer>(assetID)
	{
	}

	SoundAsset::~SoundAsset()
	{
	}
}