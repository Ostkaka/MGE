/**
 * Provides the FontHandler class used by the AssetManager to manage all
 * sf::Font assets for the application.
 *
 */
#ifndef   FONTHANDLER_HPP
	#define   FONTHANDLER_HPP
 
#include <SFML/Graphics.hpp>
#include <MGE/Core/Core_types.hpp>
#include <MGE/Core/interfaces/TAssetHandler.hpp>

namespace MGE
{
  /// Provides the FontHandler class for managing sf::Font assets
  class FontHandler : public TAssetHandler<sf::Font>
  {
  public:
    /**
     * FontHandler constructor
     */
    FontHandler();
 
    /**
     * FontHandler deconstructor
     */
    virtual ~FontHandler();
 
  protected:
    /**
		 * See parent class
     */
    virtual bool loadFromFile(const typeAssetID assetID, sf::Font& asset);

  private:
  }; 
} 

#endif 
