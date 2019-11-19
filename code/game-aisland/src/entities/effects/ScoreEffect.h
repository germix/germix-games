////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ScoreEffect | Mostrar puntaje
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___ScoreEffect_h___
#define ___ScoreEffect_h___
#include <src/Entity.h>

#include <mach/String.h>

class Font;

class ScoreEffect : public Entity
{
	Font*		font;
	String		text;
	double		textX;
	double		textY;
public:
	ScoreEffect(Scene* s, double x, double y, int score);
	~ScoreEffect();
public:
	void update(double dt);
	void render(Graphics* gr);
};

#endif
