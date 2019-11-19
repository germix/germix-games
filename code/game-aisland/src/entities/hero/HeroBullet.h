////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroBullet
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___HeroBullet_h___
#define ___HeroBullet_h___
#include <src/Entity.h>

#include <gamelib/TimeClock.h>

class Sprite;

class HeroBullet : public Entity
{
protected:
	bool		stopped;
	Vector2f	velocity;

	Sprite*		sprite;
	int			spriteIndex;
	TimeClock	spriteClock;
public:
	HeroBullet(Scene* s, double x, double y, double vx, double py, Sprite* spr);
	~HeroBullet();
public:
	virtual void update(double dt);
	virtual void render(Graphics* gr);
	virtual Rectanglef bounds() const;
	virtual Rectanglef bounds(double px, double py) const;
	
	void remove()
	{
		removable = true;
	}
	Vector2f getVelocity() const
	{
		return velocity;
	}
};

#endif
