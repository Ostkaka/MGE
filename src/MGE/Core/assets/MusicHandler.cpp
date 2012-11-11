/*
* Derived class from IAssetHandler for managing sf:Textures
*/

#include <MGE/Core/assets/MusicHandler.hpp>
#include <MGE/Core/loggers/Log.hpp>
#include <iostream>

namespace MGE
{
	MusicHandler::MusicHandler():
TAssetHandler<sf::Music>()
{
	ILOG() << "MusicHandler::ctor()" << std::endl;
}

MusicHandler::~MusicHandler()
{
	ILOG() << "MusicHandler::dtor()" << std::endl;
}

bool MusicHandler::loadFromFile(const typeAssetID assetID, sf::Music& asset)
{
	// Start with a return result of false
	bool succLoad = false;

	// Retrieve the filename for this asset
	std::string filename = assetID;

	// Was a valid filename found? then attempt to load the asset from anFilename
	if(filename.length() > 0)
	{
		// Load the asset from a file
		succLoad = asset.openFromFile(filename);
	}
	else
	{
		ELOG() << "MusicHandler::LoadFromFile(" << assetID
			<< ") No filename provided!" << std::endl;
	}

	// Return anResult of true if successful, false otherwise
	return succLoad;
}
}