#ifndef _CMAP_H_
    #define _CMAP_H_

#include <vector>
#include "CTile.h"
#include <SFML/Graphics.hpp>
#include <MGE/Core/Core_types.hpp>
#include <MGE/Core/assets/TextureAsset.hpp>

class CMap {
    public:
        CMap();
				~CMap();
    public:
      bool onLoad(const std::string & File,int sizeX, int sizeY);

			void onRender(sf::RenderWindow  & window, const sf::Vector2f & mapPos);
		
			void setTexture(MGE::TextureAsset& tileSet);

    public:
        CTile* getTile(int X, int Y);

		protected:
			std::vector<CTile> TileList;
			MGE::TextureAsset  mapTileset;
			sf::Sprite				 mapSprite;
			sf::Vector2i			 mSize;
};

#endif
