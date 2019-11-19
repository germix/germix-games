#include "TiledMap.h"

TiledMap::TiledMap(const char* fileName)
: tiles(0)
, width(0)
, height(0)
{
}
TiledMap::~TiledMap()
{
	if(tiles)
		delete [] tiles;
}
void TiledMap::draw(Graphics* gr, int x, int y, int w, int h)
{
}
