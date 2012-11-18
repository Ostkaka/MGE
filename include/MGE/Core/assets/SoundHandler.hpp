/**
 * Provides the SoundHandler class used by the AssetManager to manage all
 * sf::SoundBuffer assets for the application.
 *
 */
#ifndef   SOUNDHANDLER_HPP
	#define   SOUNDHANDLER_HPP
 
#include <SFML/Audio.hpp>
#include <MGE/Core/Core_types.hpp>
#include <MGE/Core/interfaces/TAssetHandler.hpp>

namespace MGE
{
  /// Provides the SoundHandler class for managing sf::Sound assets
  class SoundHandler : public TAssetHandler<sf::SoundBuffer>
  {
  public:
    /**
     * SoundHandler constructor
     */
    SoundHandler();
 
    /**
     * SoundHandler deconstructor
     */
    virtual ~SoundHandler();
 
  protected:
		/*
		* See syntax from derived class
		*/
    virtual bool loadFromFile(const typeAssetID theAssetID, sf::SoundBuffer& theAsset);

  }; 
} 

#endif // CORE_SOUND_MANAGER_HPP_INCLUDED