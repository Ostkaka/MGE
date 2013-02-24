#include <MGE/Core/assets/FontAsset.hpp>

namespace MGE
{
	FontAsset::FontAsset():
	TAsset<sf::Font>()
	{
	}

	FontAsset::FontAsset(const typeAssetID assetID):
	TAsset<sf::Font>(assetID)
	{
	}

	FontAsset::~FontAsset()
	{
	}
};


