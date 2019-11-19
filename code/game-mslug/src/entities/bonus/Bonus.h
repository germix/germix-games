////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_h___
#define ___Bonus_h___
#include <src/scene/Entity.h>
#include <src/___/Collisionable.h>

#include <gamelib/TimeClock.h>

class Hero;
class Sprite;

class Bonus : public Entity, public Collisionable
{
protected:
	Vector2f		vel;
	Vector2f		accel;
	bool			onGround;
	Sprite*			sprite;
	int				spriteFrame;
	unsigned int	spriteHints;
	TimeClock		spriteClock;
public:
	Bonus(Scene* scene, double x, double y);
	~Bonus();
public:
	void update(double dt);
	void render(Graphics* gr);
	Rectanglef bounds() const;
	Rectanglef bounds(double px, double py) const;

	void collide(Entity* other);
	Rectanglef collisionRect() const;
protected:
	virtual void animate(double dt) {};
	virtual void activate(Hero* hero) {}
};

#endif
