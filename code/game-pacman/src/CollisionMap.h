////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CollisionMap
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___CollisionMap_h___
#define ___CollisionMap_h___
#include <vector>

class Graphics;
class Rectangle;

class CollisionMap
{
	int					width;
	int					height;
	int					tileSize;
	unsigned short*		solidMask;
	int					solidMaskSize;
public:
	CollisionMap(int w, int h, const std::vector<int>& gids, int firstGidSolids);
	~CollisionMap();
public:
	void render(Graphics* gr);
	int  getWidth() const { return width; }
	int  getHeight() const { return height; }
	bool tryMove(const Rectangle& entityRect, int dx, int dy, unsigned short mask) const;
	bool isWalkable(int tileIndex, unsigned short mask) const;
	int  getWalkable(int tileX, int tileY, unsigned short mask) const;
	int  getWalkable(int tileX, int tileY, unsigned short mask, int size) const;
	int  getTileSize() const
	{
		return tileSize;
	}
	int  getTileIndex(int tileX, int tileY) const
	{
		if(tileX >= 0 && tileX < width && tileY >= 0 && tileY < height)
		{
			return ((tileY*width)+tileX);
		}
		return -1;
	}
	int  getTileIndex8x8(int tileX, int tileY) const
	{
		tileX /= tileSize;
		tileY /= tileSize;
		if(tileX >= 0 && tileX < width && tileY >= 0 && tileY < height)
		{
			return ((tileY*width)+tileX);
		}
		return -1;
	}
private:
	int gid(int x, int y, int w, int h, const std::vector<int>& gids, int firstGidSolids) const;
	unsigned short gmask(int x, int y, int w, int h, const std::vector<int>& gids, int firstGidSolids) const;
	void fill4(int x, int y, unsigned short mask1, unsigned short mask2, unsigned short mask3, unsigned short mask4);
};

#endif
