#include <MGE\Tile\CMap.h>

CMap::CMap() {
    ILOG() << "CMap::ctor()" << std::endl;
}


CMap::~CMap()
{
	ILOG() << "CMap::dtor()" << std::endl;
}


bool CMap::onLoad(const std::string & File, int sizeX, int sizeY){
		mSize.x = sizeX;mSize.y = sizeY; 
    TileList.clear();

    FILE* FileHandle = fopen(File.c_str(), "r");

    if(FileHandle == NULL) {
        return false;
    }

    for(int Y = 0;Y < mSize.y;Y++) {
        for(int X = 0;X < mSize.x;X++) {
            CTile tempTile;

            fscanf(FileHandle, "%d:%d ", &tempTile.TileID, &tempTile.TypeID);

            TileList.push_back(tempTile);
        }
        fscanf(FileHandle, "\n");
    }

    fclose(FileHandle);

    return true;
}

void CMap::onRender(sf::RenderWindow & window, const sf::Vector2f & mapPos) {

		int tilesetWidth  = mapSprite.getTexture()->getSize().x / TILE_SIZE;
    int tilesetHeight = mapSprite.getTexture()->getSize().y / TILE_SIZE;

    int ID = 0;

    for(int Y = 0;Y < mSize.y;Y++) {
        for(int X = 0;X < mSize.x;X++) {
            if(TileList[ID].TypeID == TILE_TYPE_NONE) {
                ID++;
                continue;
            }

            int tX = mapPos.x + (X * TILE_SIZE);
            int tY = mapPos.y + (Y * TILE_SIZE);

            int tilesetX = (TileList[ID].TileID % tilesetWidth) * TILE_SIZE;
            int tilesetY = (TileList[ID].TileID / tilesetWidth) * TILE_SIZE;

            //CSurface::OnDraw(Surf_Display, Surf_Tileset, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);
						mapSprite.setPosition(tX,tY);
						mapSprite.setTextureRect(sf::IntRect(tilesetX,tilesetY,TILE_SIZE,TILE_SIZE));
						window.draw(mapSprite);
            ID++;
        }
    }
}

void CMap::setTexture(MGE::TextureAsset& tileSet){
		this->mapTileset=tileSet;
		this->mapSprite.setTexture(mapTileset.getAsset());
}

CTile* CMap::getTile(int X, int Y) {
    size_t ID = 0;

    ID = X / TILE_SIZE;
    ID = ID + (mSize.x * (Y / TILE_SIZE));

    if(ID < 0 || ID >= TileList.size()) {
        return NULL;
    }

    return &TileList[ID];
}
