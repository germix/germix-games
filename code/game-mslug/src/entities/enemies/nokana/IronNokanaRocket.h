////////////////////////////////////////////////////////////////////////////////////////////////////
//
// IronNokanaRocket | Cohete del IronNokana
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___IronNokanaRocket_h___
#define ___IronNokanaRocket_h___
#include <src/entities/projectiles/EnemyProjectile.h>
#include <src/___/HurtableRect.h>
#include <src/___/Collisionable.h>

#include <gamelib/TimeClock.h>

class Route;
class Sprite;

class IronNokanaRocket : public EnemyProjectile, public HurtableRect
{
	enum STATE
	{
		STATE_STARTING,
		STATE_FLYING,
	};
	STATE				state;
	Sprite*				sprite;
	int					spriteFrame;
	TimeClock			spriteClock;
	
	Route*				route;
	Vector2f			oldPos;
	Vector2f			basePos;
	double				travaled;
	
	int					subSpriteFrame;
public:
	IronNokanaRocket(Scene* scene, double x, double y, Route* r);
	~IronNokanaRocket();
public:
	void update(double dt);
	void render(Graphics* gr);
	Rectanglef bounds() const;
	Rectanglef bounds(double px, double py) const;

	void hurt(int damage);
	bool isHurtable() const;
	Rectanglef hurtableRect() const;
	
	void collide(Entity* other);
	Rectanglef collisionRect() const;
};

#endif
