#ifndef _CAREA_H_
    #define _CAREA_H_

#include <SFML/Graphics.hpp>
#include "MGE/Tile/CMap.h"

class CArea {
    public:
        static CArea areaControl;
        std::vector<CMap> mapList;

    public:
        CArea();
        bool    onLoad(const std::string & File);
				void    onRender(sf::RenderWindow & window, const sf::Vector2f & cameraPos);
        void    onCleanup();

    public:
        CMap*    getMap(int X, int Y);
        CTile*   getTile(int X, int Y);

		private:
			int						areaSize;
			sf::Texture * areaTileset;
};

#endif
