////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ScoreEffect
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___ScoreEffect_h___
#define ___ScoreEffect_h___
#include <src/entities/Entity.h>

#include <gamelib/TimeClock.h>

class ScoreEffect : public Entity
{
	TimeClock	clock;
	int			spriteIndex;
public:
	ScoreEffect(Map* m, Scene* s, int x, int y, int score);
	~ScoreEffect();
public:
	void update(double dt);
	void render(Graphics* gr);
};

#endif
