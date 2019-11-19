////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Map
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/Map.h>
#include <src/Tiles.h>
#include <src/Config.h>

#include <mach/Color.h>
#include <mach/Texture.h>
#include <mach/Graphics.h>
#include <mach/Rectangle.h>

#include <tmx/TmxMap.h>
#include <tmx/layers/TmxPatternLayer.h>
#include <tmx/layers/TmxTilesetLayer.h>

Map::Map(const TmxMap* tmx)
: mapWidth()
, mapHeight()
, tileWidth()
, tileHeight()

, tiles(null)
, tilesCount(null)

, walkableMask(null)

, waterIndex(0)
, waterClock(0.8)
{
	load(tmx);
}
Map::Map(const std::string& tmxName)
: mapWidth()
, mapHeight()
, tileWidth()
, tileHeight()

, tiles(null)
, tilesCount(null)

, walkableMask(null)

, waterIndex(0)
, waterClock(0.8)
{
	TmxMap* tmx = new TmxMap(tmxName.c_str());
	load(tmx);
	delete tmx;
}
Map::~Map()
{
	delete [] tiles;
	delete [] walkableMask;
}
void Map::update(double dt)
{
	if(waterClock.update(dt))
	{
		waterIndex++;
		if(waterIndex == 2) waterIndex = 0;
	}
}
void Map::render(Graphics* gr)
{
	gr->fillRect(0, 0, mapWidth*tileHeight, mapHeight*tileHeight, Config::mapBackgroundColor);
	
	for(unsigned int i = 0; i < normalTiles.size(); i++)
	{
		int idx = normalTiles[i];
		int tileX = idx%mapWidth;
		int tileY = idx/mapWidth;
		drawTile(gr, 0, 0, tileX, tileY, tiles[idx]);
	}
}
void Map::renderTopmost(Graphics* gr)
{
	for(unsigned int i = 0; i < topmostTiles.size(); i++)
	{
		int idx = topmostTiles[i];
		int tileX = idx%mapWidth;
		int tileY = idx/mapWidth;
		drawTile(gr, 0, 0, tileX, tileY, tiles[idx]);
	}
}
std::vector<int> Map::getTiles(const Rectangle& entityRect, int dx, int dy) const
{
	std::vector<int> ret;
	
	int entityX = entityRect.getX()+dx;
	int entityY = entityRect.getY()+dy;
	int entityW = entityRect.getWidth();
	int entityH = entityRect.getHeight();
	int tileX1 = entityX>>3;		// dividir por 8
	int tileY1 = entityY>>3;
	int tileX2 = (entityX+entityW)>>3;
	int tileY2 = (entityY+entityH)>>3;
	Rectangle er(entityX, entityY, entityW, entityH);
	
	for(int x = tileX1; x <= tileX2; x++)
	{
		for(int y = tileY1; y <= tileY2; y++)
		{
			if(x >= 0 && y >= 0 && x < mapWidth && y < mapHeight)
			{
				if(er.intersects(Rectangle(x*8, y*8, 8, 8)))
				{
					ret.push_back(tiles[((y*mapWidth)+x)]);
				}
			}
		}
	}
	return ret;
}
bool Map::tryMoveTank(const Rectangle& entityRect, int dx, int dy) const
{
	return tryMove(entityRect, dx, dy, 1);
}
bool Map::tryMoveBullet(const Rectangle& entityRect, int dx, int dy) const
{
	return tryMove(entityRect, dx, dy, 2);
}
bool Map::tryMoveTankHorz(const Rectangle& entityRect, int dx) const
{
	return tryMoveHorz(entityRect, dx, 0, 1);
}
bool Map::tryMoveTankVert(const Rectangle& entityRect, int dy) const
{
	return tryMoveVert(entityRect, 0, dy, 1);
}
void Map::breakTile(const Rectangle& entityRect, int dx, int dy, bool strong)
{
	int entityX = entityRect.getX()+dx;
	int entityY = entityRect.getY()+dy;
	int entityW = entityRect.getWidth();
	int entityH = entityRect.getHeight();
	int tileX1 = entityX>>3;		// dividir por 8
	int tileY1 = entityY>>3;
	int tileX2 = (entityX+entityW)>>3;
	int tileY2 = (entityY+entityH)>>3;
	Rectangle er(entityX, entityY, entityW, entityH);
	
	for(int x = tileX1; x <= tileX2; x++)
	{
		for(int y = tileY1; y <= tileY2; y++)
		{
			if(x >= 0 && y >= 0 && x < mapWidth && y < mapHeight)
			{
				if(er.intersects(Rectangle(x*8, y*8, 8, 8)))
				{
					int idx = ((y*mapWidth)+x);
					if(Tiles::isBulletBreakable(tiles[idx], strong))
					{
						tiles[idx] = Tiles::TILE_EMPTY;
						walkableMask[idx] = Tiles::getWalkableMask(Tiles::TILE_EMPTY);
					}
				}
			}
		}
	}
}
void Map::replaceTile(int x, int y, int newTile)
{
	if(x >= 0 && y >= 0 && x < mapWidth && y < mapHeight)
	{
		int idx = ((y*mapWidth)+x);
		
		tiles[idx] = newTile;
	}
}
void Map::replaceTile(int x, int y, int currentTile, int newTile)
{
	if(x >= 0 && y >= 0 && x < mapWidth && y < mapHeight)
	{
		int idx = ((y*mapWidth)+x);
		
		if(tiles[idx] == currentTile)
		{
			tiles[idx] = newTile;
		}
	}
}
void Map::load(const TmxMap* tmx)
{
	mapWidth = tmx->getMapWidth();
	mapHeight = tmx->getMapHeight();
	tileWidth = tmx->getTileWidth();
	tileHeight = tmx->getTileHeight();
	
	loadTiles(tmx);
	loadObjects(tmx);
}
void Map::loadTiles(const TmxMap* tmx)
{
	const std::vector<int>& gids = tmx->getPatternLayer("map")->getIds();
	int                     firstGidTileset = tmx->getTilesetLayer("bcity")->getFirstGid();
	
	//
	// Cargar tiles visuales
	//
	tiles = new int[tilesCount = gids.size()];
	walkableMask = new unsigned short[tilesCount];
	for(int i = 0; i < tilesCount; i++)
	{
		tiles[i] = gids[i]-firstGidTileset;
		if(tiles[i] == -1)
			tiles[i] = 0;
		
#if 0
		// ¿Es agua?
		if(Tiles::isWater(tiles[i]))
			waterTiles.push_back(i);
#endif

		// ¿Se dibuja por arriba o por abajo?
		if(Tiles::isTopmost(tiles[i]))
			topmostTiles.push_back(i);
		// ¿Es diferente de vacío?
		else if(tiles[i] != Tiles::TILE_EMPTY)
			normalTiles.push_back(i);
		
		// ¿Se puede pasar por a través de el?
		walkableMask[i] = Tiles::getWalkableMask(tiles[i]);
	}
}
void Map::loadObjects(const TmxMap* tmx)
{
}
void Map::drawTile(Graphics* gr, int dx, int dy, int tileX, int tileY, int tileIndex)
{
	int dx1 = dx + tileX*tileWidth;
	int dy1 = dy + tileY*tileHeight;
	if(tileIndex >= 0)
	{
		if(tileIndex == Tiles::TILE_WATER)
		{
			tileIndex += waterIndex;
		}
		int dx2 = dx1+tileWidth;
		int dy2 = dy1+tileHeight;
		int sx1 = (tileIndex%(Config::tileset->getWidth()/tileWidth))*tileWidth;
		int sy1 = (tileIndex/(Config::tileset->getWidth()/tileWidth))*tileWidth;
		int sx2 = sx1+tileWidth;
		int sy2 = sy1+tileHeight;
		
		gr->drawTexture(Config::tileset, sx1, sy1, sx2, sy2, dx1, dy1, dx2, dy2);
	}
	else
	{
		gr->fillRect(dx1, dy1, tileWidth, tileHeight, Color(0,0,0));
	}
}
bool Map::tryMove(const Rectangle& entityRect, int dx, int dy, unsigned short mask) const
{
	int entityX = entityRect.getX()+dx;
	int entityY = entityRect.getY()+dy;
	int entityW = entityRect.getWidth();
	int entityH = entityRect.getHeight();
	int tileX1 = entityX>>3;		// dividir por 8
	int tileY1 = entityY>>3;
	int tileX2 = (entityX+entityW)>>3;
	int tileY2 = (entityY+entityH)>>3;
	Rectangle er(entityX, entityY, entityW, entityH);
	
	if(er.getMinX() < 0) return false;
	if(er.getMinY() < 0) return false;
	if(er.getMaxX() >= mapWidth*tileWidth) return false;
	if(er.getMaxY() >= mapHeight*tileHeight) return false;
	
	for(int x = tileX1; x <= tileX2; x++)
	{
		for(int y = tileY1; y <= tileY2; y++)
		{
			if(x >= 0 && y >= 0 && x < mapWidth && y < mapHeight)
			{
				int i = ((y*mapWidth)+x);
				if((walkableMask[i] & mask) == 0)
				{
					if(er.intersects(Rectangle(x*8, y*8, 8, 8)))
					{
						return false;
					}
				}
			}
		}
	}
	return true;
}
bool Map::tryMoveHorz(const Rectangle& entityRect, int dx, int dy, unsigned short mask) const
{
	int entityX = entityRect.getX()+dx;
	int entityY = entityRect.getY()+dy;
	int entityW = entityRect.getWidth();
	int entityH = entityRect.getHeight();
	int tileX1 = entityX>>3;		// dividir por 8
	int tileY1 = entityY>>3;
	int tileX2 = (entityX+entityW)>>3;
	int tileY2 = (entityY+entityH)>>3;
	Rectangle er(entityX, entityY, entityW, entityH);
	
	if(er.getMinX() < 0) return false;
	if(er.getMinY() < 0) return false;
	if(er.getMaxX() >= mapWidth*tileWidth) return false;
	if(er.getMaxY() >= mapHeight*tileHeight) return false;
	
	for(int x = tileX1; x <= tileX2; x++)
	{
		for(int y = tileY1; y <= tileY2; y++)
		{
			if(x >= 0 && y >= 0 && x < mapWidth && y < mapHeight)
			{
				int i = ((y*mapWidth)+x);
				if((walkableMask[i] & mask) == 0)
				{
					if(er.intersects(Rectangle(x*8, y*8, 8, 8)))
					{
						return false;
					}
				}
			}
		}
	}
	return true;
}
bool Map::tryMoveVert(const Rectangle& entityRect, int dx, int dy, unsigned short mask) const
{
	int entityX = entityRect.getX()+dx;
	int entityY = entityRect.getY()+dy;
	int entityW = entityRect.getWidth();
	int entityH = entityRect.getHeight();
	int tileX1 = entityX>>3;		// dividir por 8
	int tileY1 = entityY>>3;
	int tileX2 = (entityX+entityW)>>3;
	int tileY2 = (entityY+entityH)>>3;
	Rectangle er(entityX, entityY, entityW, entityH);
	
	if(er.getMinX() < 0) return false;
	if(er.getMinY() < 0) return false;
	if(er.getMaxX() >= mapWidth*tileWidth) return false;
	if(er.getMaxY() >= mapHeight*tileHeight) return false;
	
	for(int x = tileX1; x <= tileX2; x++)
	{
		for(int y = tileY1; y <= tileY2; y++)
		{
			if(x >= 0 && y >= 0 && x < mapWidth && y < mapHeight)
			{
				int i = ((y*mapWidth)+x);
				if((walkableMask[i] & mask) == 0)
				{
					if(er.intersects(Rectangle(x*8, y*8, 8, 8)))
					{
						return false;
					}
				}
			}
		}
	}
	return true;
}