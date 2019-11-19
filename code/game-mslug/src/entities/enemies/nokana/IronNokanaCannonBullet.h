////////////////////////////////////////////////////////////////////////////////////////////////////
//
// IronNokanaCannonBullet | Bala lanzada por el cañón de IronNokana
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___IronNokanaCannonBullet_h___
#define ___IronNokanaCannonBullet_h___
#include <src/entities/projectiles/EnemyProjectile.h>

#include <gamelib/TimeClock.h>

class Sprite;

class IronNokanaCannonBullet : public EnemyProjectile
{
	enum
	{
		MAX_COLORS = 3,
		MAX_OLD_POSITIONS = 3,
	};
	Vector2f			vel;
	Vector2f			accel;
	Sprite*				sprite;
	int					colorIndex;
	TimeClock			colorClock;
	TimeClock			positionClock;
	Vector2f			oldPositions[MAX_COLORS];
public:
	IronNokanaCannonBullet(Scene* scene, double x, double y);
	~IronNokanaCannonBullet();
public:
	void update(double dt);
	void render(Graphics* gr);

	void collide(Entity* other);
	Rectanglef collisionRect() const;
};

#endif
