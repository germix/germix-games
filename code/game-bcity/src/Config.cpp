////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Config
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/Config.h>
#include <src/res/ResourceManager.h>
#include <src/base/Sprite.h>
#include <src/entities/Tank.h>

#include <mach/Texture.h>

const bool Debug::oneEnemy = false;
const bool Debug::enemiesDisabled = false;
const bool Debug::spawnersDisabled = false;
const bool Debug::spawnBonusByMouse = true;
const bool Debug::showTankRectangle = false;
const bool Debug::showBulletRectangle = false;
const bool Debug::infiniteEnemies = true;
const bool Debug::enemiesCanShoot = true;
const bool Debug::gameOverByBaseDestroyedDisabled = false;

Texture* Config::tileset = null;
int Config::currentBonus = 0;
const Color Config::mapBackgroundColor(0,0,0);

Sound*		Config::auTick;
Sound*		Config::auHitArmoredTank;
Sound*		Config::auHitMetal;
Sound*		Config::auHitBrick;
Sound*		Config::auShot;
Sound*		Config::auEnemeyDead;
Sound*		Config::auHeroDead;
Sound*		Config::auEnemeyDeadWithBonus;
Sound*		Config::auPause;
Sound*		Config::auBonusActivated;
Sound*		Config::auNewLife;
Sound*		Config::auBackground;
Sprite*		Config::bird;
Sprite*		Config::bonus;
Sprite*		Config::bullet;
Sprite*		Config::helmet;
Sprite*		Config::blink;
Sprite*		Config::arrows;
Sprite*		Config::scores;
Sprite*		Config::tankSprites[Tank::MAX_TANK_MODELS*Tank::MAX_TANK_COLORS];
Sprite*		Config::bigExplosion;
Sprite*		Config::smallExplosion;
Sprite*		Config::tanksIndicator;

void Config::load()
{
	tileset = res.findTexture("Tiles");

	auTick					= res.findSound("Tick");
	auHitArmoredTank		= res.findSound("HitArmoredTank");
	auHitMetal				= res.findSound("HitMetal");
	auHitBrick				= res.findSound("HitBrick");
	auShot					= res.findSound("Shot");
	auEnemeyDead			= res.findSound("EnemeyDead");
	auHeroDead				= res.findSound("HeroDead");
	auEnemeyDeadWithBonus	= res.findSound("EnemeyDeadWithBonus");
	auPause					= res.findSound("Pause");
	auBonusActivated		= res.findSound("BonusActivated");
	auNewLife				= res.findSound("NewLife");
	auBackground			= res.findSound("Background");
	
	Texture* tanksTexture;
	if(null != (tanksTexture = res.findTexture("Tanks")))
	{
		int c = Tank::MAX_TANK_MODELS*Tank::MAX_TANK_COLORS;
		int h = tanksTexture->getHeight()/c;
		
		for(int i = 0; i < c; i++)
		{
			tankSprites[i] = new Sprite(tanksTexture, 8, i*h, h);
		}
	}
	bird = new Sprite(res.findTexture("Bird"), 2);
	bonus = new Sprite(res.findTexture("Bonus"), 7);
	bullet = new Sprite(res.findTexture("Bullet"), 4);
	helmet = new Sprite(res.findTexture("Helmet"), 2);
	blink = new Sprite(res.findTexture("Blink"), 4);
	arrows = new Sprite(res.findTexture("Arrows"), 2);
	scores = new Sprite(res.findTexture("Scores"), 5);
	bigExplosion = new Sprite(res.findTexture("BigExplosion"), 2);
	smallExplosion = new Sprite(res.findTexture("SmallExplosion"), 3);
	tanksIndicator = new Sprite(res.findTexture("TanksIndicator"), 2);
}
void Config::save()
{
	delete bird;
	delete bonus;
	delete bullet;
	delete helmet;
	delete blink;
	delete arrows;
	delete scores;
	delete bigExplosion;
	delete smallExplosion;
	delete tanksIndicator;
	
	for(int i = 0; i < (Tank::MAX_TANK_MODELS*Tank::MAX_TANK_COLORS); i++)
	{
		delete tankSprites[i];
	}
}
