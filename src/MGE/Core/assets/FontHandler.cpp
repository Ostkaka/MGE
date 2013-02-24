#include <MGE/Core/assets/FontHandler.hpp>

namespace MGE
{
	FontHandler::FontHandler():
		TAssetHandler<sf::Font>()
	{
		ILOG() << "FontHandler::ctor()" << std::endl;
	}

	FontHandler::~FontHandler()
	{
		ILOG() << "FontHandler::dtor()" << std::endl;
	}

	bool FontHandler::loadFromFile( const typeAssetID assetID, sf::Font& asset )
	{
		// Start with a return result of false
		bool succ = false;

		// Retrieve the filename for this asset
		std::string anFilename = assetID;

		// Was a valid filename found? then attempt to load the asset from anFilename
		if(anFilename.length() > 0)
		{
			// Load the asset from a file
			succ = asset.loadFromFile(anFilename);
		}
		else
		{
			ELOG() << "FontHandler::LoadFromFile(" << assetID
				<< ") No filename provided!" << std::endl;
		}

		// Return anResult of true if successful, false otherwise
		return succ;
	}
}


