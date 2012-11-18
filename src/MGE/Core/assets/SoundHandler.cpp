/*
* Derived class from IAssetHandler for managing sf:Music
*/

#include <MGE/Core/assets/SoundHandler.hpp>
#include <MGE/Core/loggers/Log.hpp>
 
namespace MGE
{
  SoundHandler::SoundHandler():
    TAssetHandler<sf::SoundBuffer>()
  {
    ILOG() << "SoundHandler::ctor()" << std::endl;
  }
 
  SoundHandler::~SoundHandler()
  {
    ILOG() << "SoundHandler::dtor()" << std::endl;
  }

  bool SoundHandler::loadFromFile(const typeAssetID assetID, sf::SoundBuffer& asset)
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
      ELOG() << "SoundHandler::loadFromFile(" << assetID
        << ") No filename provided!" << std::endl;
    }

    // Return anResult of true if successful, false otherwise
    return succ;
  }
} 