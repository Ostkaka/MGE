#include <MGE\Tile\CArea.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

CArea* CArea::areaControl = NULL;

CArea::CArea() {
    areaSize = 0;
}

bool CArea::onLoad(const std::string & file) {
    mapList.clear();

    FILE* fileHandle = fopen(file.c_str(), "r");

    if(fileHandle == NULL) {
        return false;
    }

    char tilesetFile[255] = "";

    fscanf(fileHandle, "%s\n", tilesetFile);

		//Load texture for the area
		mTilesetTexture.setID(RESOURCE_DIR + std::string("/") + tilesetFile);

    fscanf(fileHandle, "%d\n", &areaSize);

    for(int X = 0;X < areaSize;X++) {
        for(int Y = 0;Y < areaSize;Y++) {
            std::string mapPath = "";
						mapPath.append(RESOURCE_DIR"/");
						char mapfile[255];
            fscanf(fileHandle, "%s ", mapfile);
						mapPath.append(mapfile);
            CMap tempMap;
            if(tempMap.onLoad(mapPath) == false) {
                fclose(fileHandle);
								ELOG() << "Could not load map (" << mapPath << ")"  << std::endl;
                return false;
            }

						tempMap.setTexture(mTilesetTexture);

            mapList.push_back(tempMap);
        }
        fscanf(fileHandle, "\n");
    }

    fclose(fileHandle);

    return true;
}

void CArea::onRender(sf::RenderWindow & window, const sf::Vector2f & cameraPos) {
    int MapWidth  = MAP_WIDTH * TILE_SIZE;
    int MapHeight = MAP_HEIGHT * TILE_SIZE;

		//Calc number of maps that needs to be shown
		int numMapsShow = 2*MAX(((MAP_WIDTH * TILE_SIZE)/window.getView().getSize().x + 2),
			((MAP_HEIGHT * TILE_SIZE)/window.getView().getSize().y + 2));
		int factor = numMapsShow/2;

    size_t FirstID = int(cameraPos.x) / MapWidth;
    FirstID = FirstID + ((int(cameraPos.y)) / MapHeight) * areaSize;

    for(size_t i = 0;i < numMapsShow;i++) {
        size_t ID = FirstID + ((i / factor) * areaSize) + (i % factor);

        if(ID < 0 || ID >= mapList.size()) continue;

        int X = ((ID % areaSize) * MapWidth);
        int Y = ((ID / areaSize) * MapHeight);

				mapList[ID].onRender(window,sf::Vector2f(X,Y));
    }
}

CMap* CArea::getMap(int X, int Y) {
    int MapWidth  = MAP_WIDTH * TILE_SIZE;
    int MapHeight = MAP_HEIGHT * TILE_SIZE;

    int ID = X / MapWidth;
        ID = ID + ((Y / MapHeight) * areaSize);

    if(ID < 0 || ID >= mapList.size()) {
        return NULL;
    }

    return &mapList[ID];
}

CTile* CArea::getTile(int X, int Y) {
    int MapWidth  = MAP_WIDTH * TILE_SIZE;
    int MapHeight = MAP_HEIGHT * TILE_SIZE;

    CMap* Map = getMap(X, Y);

    if(Map == NULL) return NULL;

    X = X % MapWidth;
    Y = Y % MapHeight;

    return Map->getTile(X, Y);
}

void CArea::onCleanup() {
   mapList.clear();
}

CArea::~CArea()
{
	onCleanup();
}
