////////////////////////////////////////////////////////////////////////////////////////////////////
//
// StielHandGranate
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___StielHandGranate_h___
#define ___StielHandGranate_h___
#include <src/entities/projectiles/HeroBomb.h>
#include <gamelib/TimeClock.h>

class Sprite;

class StielHandGranate : public HeroBomb
{
	Vector2f		vel;
	Vector2f		accel;
	Sprite*			sprite;
	int				spriteIndex;
	TimeClock		spriteClock;
	
	int				rebounds;
	
	bool			onGround;
public:
	StielHandGranate(Scene* scene, double px, double py, double vx, double vy);
	~StielHandGranate();
public:
	void update(double dt);
	void render(Graphics* gr);
	Rectanglef bounds() const;
	Rectanglef bounds(double px, double py) const;
	void explode();
private:
};

#endif
