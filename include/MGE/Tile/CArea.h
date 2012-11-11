#ifndef _CAREA_H_
    #define _CAREA_H_

#include <SFML/Graphics.hpp>
#include "MGE/Tile/CMap.h"
#include <MGE/Core/Core_types.hpp>
#include <MGE/Core/assets/TextureAsset.hpp>

class CArea {
		public:
        std::vector<CMap> mapList;

    public:
        CArea();
				~CArea();
        bool    onLoad(const std::string & File);
				void    onRender(sf::RenderWindow & window, const sf::Vector2f & cameraPos);
        void    onCleanup();

    public:
			CMap * getMap(int X, int Y);
			CTile *	getTile(int X, int Y);
			static CArea *			areaControl;

		private:
			int									areaSize;
			MGE::TextureAsset		mTilesetTexture;

};

#endif
