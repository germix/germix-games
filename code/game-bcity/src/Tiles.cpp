////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Tiles
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/Tiles.h>

//
// 0x01 = 00000001 = Se puede atravesar con los tanques
// 0x02 = 00000010 = Se puede atravesar con los disparos
// 0x04 = 00000100 = Dibujar por arriba
// 0x08 = 00001000 = Se puede romper con los disparos
// 0x10 = 00010000 = Se puede romper con los disparos (si el disparo es fuerte)
//
const unsigned char Tiles::tileFlags[] =
{
	0x01 | 0x02 | 0x00 | 0x00 | 0x00,		// TILE_EMPTY
	0x00 | 0x00 | 0x00 | 0x08 | 0x00,		// TILE_WALL
	0x00 | 0x00 | 0x00 | 0x00 | 0x10,		// TILE_METAL
	0x01 | 0x02 | 0x04 | 0x00 | 0x00,		// TILE_GRASS
	0x01 | 0x02 | 0x00 | 0x00 | 0x00,		// TILE_SAND
	0x00 | 0x02 | 0x00 | 0x00 | 0x00,		// TILE_WATER
};
