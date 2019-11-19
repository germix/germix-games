////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TexturedTileMap
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/TexturedTileMap.h>
#include <src/Config.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include <mach/Graphics.h>
#include <mach/Texture.h>
#include <mach/TextureLoader.h>

TexturedTileMap::TexturedTileMap(int w, int h, const char* tilesFilename, const char* tilesetFilename)
{
	FILE* fp;
	
	mapWidth = w/TILE_SIZE;
	mapHeight = h/TILE_SIZE;
	tilesCount = (mapWidth*mapHeight);
	tiles = new unsigned short[tilesCount];
	
	//
	// Read tile indexes
	//
	if(null != (fp = fopen(tilesFilename, "rb")))
	{
		// Get file size
		fseek(fp, 0, SEEK_END);
		long size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		
		// Read file
		char* buffer = new char[size];
		fread(buffer, 1, size, fp);
		fclose(fp);
		
		//
		// Parse buffer of indexes
		//
		int i = 0;
		char* p = buffer;
		char* end = buffer+size;
		while(p < end)
		{
			// Store the index
			tiles[i++] = atoi(p);
			
			// Skip digits
			while(p < end && isalnum(*p)) p++;
			
			// Skip other characters
			while(p < end && !isalnum(*p)) p++;
		}
		int xx = tiles[(1*mapWidth)+0];
		delete [] buffer;
	}
	//
	// Load tileset
	//
	tileset = TextureLoader::load(tilesetFilename);
}
TexturedTileMap::~TexturedTileMap()
{
	delete tiles;
	delete tileset;
}
void TexturedTileMap::render(Graphics* gr, int cameraX, int cameraY)
{
	int col_from = cameraX/TILE_SIZE;
	int col_to = col_from + (SCREEN_WIDTH/TILE_SIZE);
	int row_from = cameraY/TILE_SIZE;
	int row_to = row_from + (SCREEN_HEIGHT/TILE_SIZE);

	if(0 != (cameraX%TILE_SIZE))
		col_to++;
	if(0 != (cameraY%TILE_SIZE))
		row_to++;
	
	int dx = -cameraX%TILE_SIZE;
	for(int col = col_from; col < col_to; col++)
	{
		int dy = -cameraY%TILE_SIZE;
		for(int row = row_from; row < row_to; row++)
		{
			int x = dx;
			int y = dy;
			int idx = (tiles[(row*mapWidth)+col]);
			int tileX = idx%(tileset->getWidth()/TILE_SIZE);
			int tileY = idx/(tileset->getWidth()/TILE_SIZE);
			dy += TILE_SIZE;
			
			gr->drawTexture
			(
				tileset,
				// Source
				tileX*TILE_SIZE,
				tileY*TILE_SIZE,
				tileX*TILE_SIZE+TILE_SIZE,
				tileY*TILE_SIZE+TILE_SIZE,
				// Destination
				x,
				y,
				x+TILE_SIZE,
				y+TILE_SIZE
			);
		}
		dx += TILE_SIZE;
	}
}
