////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MasknellBulletCartridge | Cartucho de bala del Masknell
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___MasknellBulletCartridge_h___
#define ___MasknellBulletCartridge_h___
#include <src/scene/Entity.h>

#include <gamelib/TimeClock.h>

class Sprite;

class MasknellBulletCartridge : public Entity
{
	Vector2f		vel;
	Sprite*			sprite;
	int				spriteFrame;
	unsigned int	spriteHints;
	TimeClock		spriteClock;
public:
	MasknellBulletCartridge(Scene* scene, double x, double y, int dir);
	~MasknellBulletCartridge();
public:
	void update(double dt);
	void render(Graphics* gr);
};

#endif
