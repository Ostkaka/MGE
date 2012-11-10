#ifndef _CMAP_H_
    #define _CMAP_H_

#include <vector>
#include "CTile.h"
#include <SFML/Graphics.hpp>

class CMap {
    public:
        
    private:
        std::vector<CTile> TileList;
		sf::Texture * mapTileset;
		sf::Sprite mapSprite;

    public:
        CMap();

    public:
        bool onLoad(const std::string & File);

		void onRender(sf::RenderWindow  & window, const sf::Vector2f & mapPos);
		
		void setTexture(sf::Texture * tileSet);

    public:
        CTile* getTile(int X, int Y);
};

#endif
