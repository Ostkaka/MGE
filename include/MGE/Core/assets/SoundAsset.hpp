/**
 * Provides the Sound Asset type used by the AssetManager 
 */

#ifndef   SOUNDASSET_HPP
	#define   SOUNDASSET_HPP

#include <SFML/Audio.hpp>
#include <MGE/Core/interfaces/TAsset.hpp>
#include <MGE/Core/Core_types.hpp>

namespace MGE
{
  /// Provides the Sound asset class
  class SoundAsset : public TAsset<sf::SoundBuffer>
  {
    public:
      /**
			 * Default constructor. Se parent class
       */
      SoundAsset();
			
      /**
       * SoundAsset constructor
       */
      SoundAsset(const typeAssetID assetID);

      /**
       * SoundAsset deconstructor
       */
      virtual ~SoundAsset();

  };
} 

#endif /*SOUNDASSET_HPP*/