////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ShotGunExplosion | Explosión del ShotGun
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___ShotGunExplosion_h___
#define ___ShotGunExplosion_h___
#include <src/scene/Entity.h>
#include <gamelib/TimeClock.h>

class Sprite;

class ShotGunExplosion : public Entity
{
	Sprite*				sprite;
	int					spriteHints;
	int					spriteFrame;
	TimeClock			spriteClock;
	bool				firstTime;
public:
	ShotGunExplosion(Scene* scene, double px, double py, int shotAngle, int lookX);
	~ShotGunExplosion();
public:
	void update(double dt);
	void render(Graphics* gr);
	Rectanglef bounds() const;
	Rectanglef bounds(double px, double py) const;
};

#endif

