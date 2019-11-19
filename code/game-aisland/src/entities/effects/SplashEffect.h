////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SplashEffect
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___SplashEffect_h___
#define ___SplashEffect_h___
#include <src/Entity.h>

#include <gamelib/TimeClock.h>

class Sprite;
class SpriteSheet;

class SplashEffect : public Entity
{
	SpriteSheet*		sheet;
	Sprite*				sprite;
	int					spriteIndex;
	TimeClock			spriteClock;
public:
	SplashEffect(Scene* s, double x, double y);
	~SplashEffect();
public:
	void update(double dt);
	void render(Graphics* gr);
	Rectanglef bounds() const { return Rectanglef(); };
	Rectanglef bounds(double px, double py) const { return Rectanglef(); };
};

#endif
