////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TiledMap
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/tiled/TiledMap.h>
#include <src/Config.h>
#include <src/resources/ResourceManager.h>

#include <mach/Texture.h>
#include <mach/Graphics.h>

#include <tmx/TmxMap.h>
#include <tmx/layers/TmxPatternLayer.h>
#include <tmx/layers/TmxTilesetLayer.h>

TiledMap::TiledMap(const char* tmxName)
{
	TmxMap* tmx = new TmxMap(tmxName);
	const TmxPatternLayer* patternLayer = tmx->getPatternLayer("tiles");
	const TmxTilesetLayer* tilesetLayer = tmx->getTilesetLayer("pacman-tileset");
	const std::vector<int>& gids = patternLayer->getIds();
	int firstGidTileset = tilesetLayer->getFirstGid();
	
	mapWidth = tmx->getMapWidth();
	mapHeight = tmx->getMapHeight();
	tileWidth = tmx->getTileWidth();
	tileHeight = tmx->getTileHeight();
	tiles = new int[mapWidth*mapHeight];
	
	for(int tx = 0; tx < mapWidth; tx++)
	{
		for(int ty = 0; ty < mapHeight; ty++)
		{
			int i = (ty*mapWidth)+tx;
			int gid = gids[i];
			
			tiles[i] = (gid-firstGidTileset);
		}
	}
	delete tmx;
}
/*
TiledMap::TiledMap(int mapWidth, int mapHeight, int tileWidth, int tileHeight, const std::vector<int>& gids, int firstGidTileset)
{
	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	this->tiles = new int[mapWidth*mapHeight];
	
	for(int tx = 0; tx < mapWidth; tx++)
	{
		for(int ty = 0; ty < mapHeight; ty++)
		{
			int i = (ty*mapWidth)+tx;
			int gid = gids[i];
			
			tiles[i] = (gid-firstGidTileset);
		}
	}
}
*/
TiledMap::~TiledMap()
{
	delete [] tiles;
}
void TiledMap::render(Graphics* gr, int dx, int dy)
{
	for(int tx = 0; tx < mapWidth; tx++)
	{
		for(int ty = 0; ty < mapHeight; ty++)
		{
			renderTile(gr, dx, dy, tx, ty, tiles[(ty*mapWidth)+tx]);
		}
	}
}
void TiledMap::renderTile(Graphics* gr, int dx, int dy, int tileX, int tileY, int tileIndex)
{
	if(tileIndex >= 0)
	{
		int dx1 = dx + tileX*tileWidth;
		int dy1 = dy + tileY*tileWidth;
		int dx2 = dx1+tileWidth;
		int dy2 = dy1+tileHeight;
		int sx1 = (tileIndex%(Config::currentTileset->getWidth()/tileWidth))*tileWidth;
		int sy1 = (tileIndex/(Config::currentTileset->getWidth()/tileWidth))*tileWidth;
		int sx2 = sx1+tileWidth;
		int sy2 = sy1+tileHeight;
		gr->drawTexture(Config::currentTileset, sx1, sy1, sx2, sy2, dx1, dy1, dx2, dy2);
	}
}
