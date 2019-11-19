////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Tiles
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Tiles_h___
#define ___Tiles_h___

class Tiles
{
public:
	enum
	{
		TILE_EMPTY		= 0,
		TILE_WALL		= 1,
		TILE_METAL		= 2,
		TILE_GRASS		= 3,
		TILE_SAND		= 4,
		TILE_WATER		= 5,
	};
public:
	static bool isWater(int index)							{ return (index == TILE_WATER); }
	static bool isTopmost(int index)						{ return (tileFlags[index] & 0x04) != 0; }
	static bool isTankWalkable(int index)					{ return (tileFlags[index] & 0x01) != 0; }
	static bool isBulletWalkable(int index)					{ return (tileFlags[index] & 0x02) != 0; }
//	static bool isBulletBreakable(int index)				{ return (tileFlags[index] & 0x08) != 0; }
	static bool isBulletBreakable(int index, bool strong)	{ return (((tileFlags[index] & 0x08) != 0) || (strong && ((tileFlags[index] & 0x10) != 0))); }

	static unsigned short getWalkableMask(int index)		{ return (tileFlags[index] & 0x03); }
private:
	static const unsigned char tileFlags[];
};

#endif
