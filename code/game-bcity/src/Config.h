////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Config
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Config_h___
#define ___Config_h___

#include <mach/Color.h>

class Sprite;
class Sound;
class Texture;

#define MAP_X				(16+16)
#define MAP_Y				16
#define MAP_WIDTH			208
#define MAP_HEIGHT			208
#define SCREEN_WIDTH		(256+16)
#define SCREEN_HEIGHT		(224+16)

class Debug
{
public:
	static const bool oneEnemy;
	static const bool enemiesDisabled;
	static const bool spawnersDisabled;
	static const bool spawnBonusByMouse;
	
	static const bool showTankRectangle;
	static const bool showBulletRectangle;
	
	static const bool infiniteEnemies;
	
	static const bool enemiesCanShoot;
	
	static const bool gameOverByBaseDestroyedDisabled;
};

class Config
{
public:
	static Texture* tileset;
	static int currentBonus;
	static const Color mapBackgroundColor;

	static Sound*		auTick;
	static Sound*		auHitArmoredTank;
	static Sound*		auHitMetal;
	static Sound*		auHitBrick;
	static Sound*		auShot;
	static Sound*		auEnemeyDead;
	static Sound*		auHeroDead;
	static Sound*		auEnemeyDeadWithBonus;
	static Sound*		auPause;
	static Sound*		auBonusActivated;
	static Sound*		auNewLife;
	static Sound*		auBackground;

	static Sprite*		bird;
	static Sprite*		bonus;
	static Sprite*		bullet;
	static Sprite*		helmet;
	static Sprite*		blink;
	static Sprite*		arrows;
	static Sprite*		scores;
	static Sprite*		tankSprites[];
	static Sprite*		bigExplosion;
	static Sprite*		smallExplosion;
	static Sprite*		tanksIndicator;
	
public:
	static void load();
	static void save();
};

#endif
