////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Config
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Config_h___
#define ___Config_h___

#define SCREEN_WIDTH		256
#define SCREEN_HEIGHT		224

class Debug
{
public:
	static const bool showPixelMap;
	static const bool showCollisionRect;
	static const bool showHeroVelocityMarks;
	static const bool showHeroCollisionEdges;
	static const bool disableHealthDecrement;
	static const bool disableEnemiesCollision;
};

class Config
{
};

#endif
