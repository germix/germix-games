////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ScoreEffect
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/ScoreEffect.h>
#include <src/Config.h>
#include <src/base/Sprite.h>

ScoreEffect::ScoreEffect(Map* m, Scene* s, int x, int y, int score) : Entity(m, s, x, y)
, clock(0.7)
, spriteIndex(-1)
{
	switch(score)
	{
		case 100: spriteIndex = 0; break;
		case 200: spriteIndex = 1; break;
		case 300: spriteIndex = 2; break;
		case 400: spriteIndex = 3; break;
		case 500: spriteIndex = 4; break;
		default:  spriteIndex = -1; break;
	}
}
ScoreEffect::~ScoreEffect()
{
}
void ScoreEffect::update(double dt)
{
	if(clock.update(dt))
		removable = true;
}
void ScoreEffect::render(Graphics* gr)
{
	if(spriteIndex != -1)
		Config::scores->render(gr, x, y, spriteIndex);
}

