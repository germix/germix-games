////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Config
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Config_h___
#define ___Config_h___
#include <string>

class Texture;

#define MAP_Y				(16+8)
#define MAP_WIDTH			(28*8)
#define MAP_HEIGHT			(31*8)

#define SCREEN_WIDTH		MAP_WIDTH
#define SCREEN_HEIGHT		(MAP_Y+MAP_HEIGHT)

enum
{
	MIXCHANNEL_LOOP,
	MIXCHANNEL_NORMAL,
	MAX_MIXCHANNELS,
};

class Debug
{
public:
	static const bool collisionMap;
	static const bool ghostDir;
	static const bool ghostPath;
	static const bool pacmanLives;
	static const bool pacmanDamaged;
	static const bool noCollisionWithGhosts;
};

class Config
{
public:
	static int			maxScore;
	static Texture*		currentTileset;
	static std::string	currentTilesetName;
public:
	static void load();
	static void save();
};

#endif
