////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MonsterBullet
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___MonsterBullet_h___
#define ___MonsterBullet_h___
#include <src/entities/Enemy.h>

class Sprite;

class MonsterBullet : public Enemy
{
	Sprite*		sprite;
	Vector2f	velocity;
public:
	MonsterBullet(Scene* s, double x, double y, Sprite* spr);
	~MonsterBullet();
public:
	void update(double dt);
	void render(Graphics* gr);
	void collides(Entity* e);
	Rectanglef bounds() const;
	Rectanglef bounds(double px, double py) const;
};

#endif
