////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BattleshipTower
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/battleships/BattleshipTower.h>
#include <src/Utils.h>
#include <src/Scene.h>
#include <src/entities/explosions/ExplosiveBurst.h>
#include <src/entities/explosions/ScrapExplosion.h>
#include <src/entities/explosions/NormalExplosion.h>
#include <src/entities/enemies/battleships/Battleship.h>

#include <mach/Math.h>
#include <mach/String.h>
#include <mach/Texture.h>
#include <mach/Graphics.h>

BattleshipTower::BattleshipTower(Scene* scene, double x, double y, Texture* ___texture, Battleship* ___battleship) : Enemy(scene, x, y)
, texture(___texture)
, destroyed(false)
, battleship(___battleship)
{
}
BattleshipTower::~BattleshipTower()
{
}
Vector2f BattleshipTower::position() const
{
	Rectanglef rc = battleship->rect();
	return Vector2f(rc.getX() + pos.x, rc.getY() + pos.y);
}
Rectanglef BattleshipTower::rect() const
{
	double mw = texture->getWidth()/2;
	double mh = texture->getHeight()/2;
	return Rectanglef(pos.x-mw, pos.y-mh, mw*2, mh*2);
}
void BattleshipTower::update(double dt)
{
}
void BattleshipTower::render(Graphics* gr)
{
	if(destroyed)
		return;
	Vector2f p = position();
	int iw = texture->getWidth();
	int ih = texture->getHeight();
	int dx1 = (int)(p.x - iw/2);
	int dy1 = (int)(p.y - ih/2);
	int dx2 = dx1 + iw;
	int dy2 = dy1 + ih;
	int sx1 = 0;
	int sy1 = 0;
	int sx2 = iw;
	int sy2 = ih;
	
	gr->drawTexture(texture, sx1, sy1, sx2, sy2, dx1, dy1, dx2, dy2);
}
bool BattleshipTower::hurt(int damage)
{
	return false;
}
bool BattleshipTower::isAlive() const
{
	return !destroyed;
}
bool BattleshipTower::isDestroyed() const
{
	return destroyed;
}
int BattleshipTower::getHealth() const
{
	return 0;
}
int BattleshipTower::getDestructionScore() const
{
	return 0;
}
void BattleshipTower::checkHit(HeroBullet* bullet)
{
}
void BattleshipTower::destroy()
{
	double x = position().x;
	double y = position().y;
	removable = true;
	destroyed = true;
	scene->addEntity(new ScrapExplosion(scene, x, y, '1', Math::toRadians(0.0)));
	scene->addEntity(new ScrapExplosion(scene, x, y, '2', Math::toRadians(45.0)));
	scene->addEntity(new ScrapExplosion(scene, x, y, '1', Math::toRadians(90.0)));
	scene->addEntity(new ScrapExplosion(scene, x, y, '2', Math::toRadians(135.0)));
	scene->addEntity(new ScrapExplosion(scene, x, y, '1', Math::toRadians(180.0)));
	scene->addEntity(new ScrapExplosion(scene, x, y, '2', Math::toRadians(225.0)));
	scene->addEntity(new ScrapExplosion(scene, x, y, '1', Math::toRadians(270.0)));
	scene->addEntity(new ScrapExplosion(scene, x, y, '2', Math::toRadians(315.0)));
	
	ExplosiveBurst* burst = new ExplosiveBurst(scene);
	{
		int i = 0;
		double degrees = 0;
		std::vector<Explosion*> explosions;
		
		for(degrees = 0, i = 0; degrees < 360.0; degrees += 45.0, i++)
		{
			Vector2f p = Utils::getMoved(pos, Math::toRadians(degrees), 20.0);
			Explosion* expl = new NormalExplosion(
					scene,
					p.x,
					p.y,
					battleship,
					"explosions.small",
					("explosions.16x16.v" + String::fromInt((i%2)+1)).c_str());
			
			explosions.push_back(expl);
		}
		burst->addExplosions(0.2, explosions);
	}
	{
		int i = 0;
		double degrees = 0;
		std::vector<Explosion*> explosions;
	
		for(degrees = 0, i = 0; degrees < 360.0; degrees += 45.0, i++)
		{
			Vector2f p = Utils::getMoved(pos, Math::toRadians(degrees), 50.0);
			Explosion* expl = new NormalExplosion(
					scene,
					p.x,
					p.y,
					battleship,
					"explosions.small",
					("explosions.32x32.v" + String::fromInt((i%2)+1)).c_str());
			
			explosions.push_back(expl);
		}
		burst->addExplosions(0.1, explosions);
	}
	{
		std::vector<Explosion*> explosions;
		
		explosions.push_back(new NormalExplosion(
					scene,
					pos.x,
					pos.y,
					battleship,
					"explosions.boss",
					"explosions.64x64.v1"));
		
		burst->addExplosions(0.2, explosions);
	}
	scene->addEntity(burst);
}