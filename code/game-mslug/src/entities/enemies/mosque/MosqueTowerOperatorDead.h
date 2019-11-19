////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MosqueTowerOperatorDead
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___MosqueTowerOperatorDead_h___
#define ___MosqueTowerOperatorDead_h___
#include <src/scene/Entity.h>

#include <gamelib/TimeClock.h>

class Sprite;

class MosqueTowerOperatorDead : public Entity
{
	enum STATE
	{
		STATE_FALLING,
		STATE_ONGROUND,
		STATE_BLINKING,
	};
	STATE			state;
	Vector2f		vel;
	Vector2f		accel;
	TimeClock		clock;
	Sprite*			sprite;
	int				spriteFrame;
	unsigned int	blinkingCount;
public:
	MosqueTowerOperatorDead(Scene* scene, double x, double y);
	~MosqueTowerOperatorDead();
public:
	void update(double dt);
	void render(Graphics* gr);
	Rectanglef bounds() const;
	Rectanglef bounds(double px, double py) const;
};

#endif
