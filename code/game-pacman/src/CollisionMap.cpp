////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CollisionMap
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/CollisionMap.h>

#include <mach/Color.h>
#include <mach/Graphics.h>
#include <mach/Rectangle.h>

CollisionMap::CollisionMap(int w, int h, const std::vector<int>& gids, int firstGidSolids)
{
	width = w*2;
	height = h*2;
	tileSize = 4;
	solidMask = new unsigned short[solidMaskSize = width*height];
	for(int i = 0; i < solidMaskSize; i++)
		solidMask[i] = 0;

	for(int x = 0; x < w; x++)
	{
		for(int y = 0; y < h; y++)
		{
			switch(gmask(x, y, w, h, gids, firstGidSolids))
			{
				case 1:
					fill4(x, y, 1, 1, 1, 1);
					break;
				case 2:
					//
					// ┌─────┬─────┐
					// │mask1│mask3│
					// ├─────┼─────┤
					// │mask2│mask4│
					// └─────┴─────┘
					//
					int mask1 = 2;
					int mask2 = 2;
					int mask3 = 2;
					int mask4 = 2;
					if(gmask(x-1, y, w, h, gids, firstGidSolids) == 1)
					{
						mask1 = 1;
						mask2 = 1;
					}
					else if(gmask(x+1, y, w, h, gids, firstGidSolids) == 1)
					{
						mask3 = 1;
						mask4 = 1;
					}
					fill4(x, y, mask1, mask2, mask3, mask4);
					break;
			}
		}
	}
}
CollisionMap::~CollisionMap()
{
	delete solidMask;
}
void CollisionMap::render(Graphics* gr)
{
	Color colorMask1(0,255,255);
	Color colorMask2(255,0,0);
	for(int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			int i = ((y*width)+x);
			unsigned short mask = solidMask[i];
			
			if(mask != 0)
			{
				if(mask == 1)		gr->fillRect(x*4,y*4,4,4,colorMask1);
				else if(mask == 2)	gr->fillRect(x*4,y*4,4,4,colorMask2);
			}
		}
	}
}
bool CollisionMap::tryMove(const Rectangle& entityRect, int dx, int dy, unsigned short mask) const
{
	int entityX = entityRect.getX()+dx;
	int entityY = entityRect.getY()+dy;
	int entityW = entityRect.getWidth();
	int entityH = entityRect.getHeight();
	int tileX1 = entityX>>2;		// dividir por 4
	int tileY1 = entityY>>2;
	int tileX2 = (entityX+entityW)>>2;
	int tileY2 = (entityY+entityH)>>2;
	Rectangle er(entityX, entityY, entityW, entityH);
	
	for(int x = tileX1; x <= tileX2; x++)
	{
		for(int y = tileY1; y <= tileY2; y++)
		{
			if(x >= 0 && y >= 0 && x < width && y < height)
			{
				int i = ((y*width)+x);
				if((solidMask[i] & mask) != 0)
				{
					if(er.intersects(Rectangle(x*4,y*4,4,4)))
					{
						return false;
					}
				}
			}
		}
	}
	return true;
}
bool CollisionMap::isWalkable(int tileIndex, unsigned short mask) const
{
	if(tileIndex >= 0 && tileIndex < solidMaskSize)
	{
		return ((solidMask[tileIndex] & mask) == 0);
	}
	return false;
}
int CollisionMap::getWalkable(int tileX, int tileY, unsigned short mask) const
{
	return getWalkable(tileX, tileY, mask, 2);
}
int CollisionMap::getWalkable(int tileX, int tileY, unsigned short mask, int size) const
{
	for(int x = 0; x < size; x++)
	{
		for(int y = 0; y < size; y++)
		{
			if(tileX+x < 0) continue;
			if(tileX+x >= width) continue;
			if(tileY+y < 0) continue;
			if(tileY+y >= height) continue;
			if(!isWalkable(getTileIndex(tileX+x, tileY+y), mask))
				return -1;
		}
	}
	return getTileIndex(tileX, tileY);
}
int CollisionMap::gid(int x, int y, int w, int h, const std::vector<int>& gids, int firstGidSolids) const
{
	if(x >= 0 && x < w && y >= 0 && y < h)
	{
		int i = (y*w)+x;
		int gid = gids[i];
		return (gid-firstGidSolids);
	}
	return -1;
}
unsigned short CollisionMap::gmask(int x, int y, int w, int h, const std::vector<int>& gids, int firstGidSolids) const
{
	int mask = 0;
	
	switch(gid(x, y, w, h, gids, firstGidSolids))
	{
		case -1:
		case 12:
			// espacio
			break;
		case 26:
		case 27:
		case 40:
		case 41:
			return 2;
		default:
			return 1;
	}
	return 0;
}
void CollisionMap::fill4(int x, int y, unsigned short mask1, unsigned short mask2, unsigned short mask3, unsigned short mask4)
{
	x *= 2;
	y *= 2;
	solidMask[((y+0)*width)+(x+0)] = mask1;
	solidMask[((y+1)*width)+(x+0)] = mask2;
	solidMask[((y+0)*width)+(x+1)] = mask3;
	solidMask[((y+1)*width)+(x+1)] = mask4;
}
