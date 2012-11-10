#ifndef _CAREA_H_
    #define _CAREA_H_

#include <SFML/Graphics.hpp>
#include "CMap.h"
#include "AssetManager.h"

class CArea {
    public:
        static CArea areaControl;
        std::vector<CMap> mapList;

    private:
        int areaSize;
		sf::Texture * areaTileset;

    public:
        CArea();

        bool    onLoad(const std::string & File);
		void    onRender(sf::RenderWindow & window, const sf::Vector2f & cameraPos);
        void    onCleanup();

    public:
        CMap*    getMap(int X, int Y);
        CTile*   getTile(int X, int Y);

};

#endif
