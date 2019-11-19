////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ScoreEffect | Mostrar puntaje parpadeante
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___ScoreEffect_h___
#define ___ScoreEffect_h___
#include <src/scene/Entity.h>

#include <gamelib/TimeClock.h>

class Font;

class ScoreEffect : public Entity
{
	class Digit;

	Font*			fonts[2];
	int				stage;
	double			stopY;
	Digit*			digits;
	int				digitsLength;
	TimeClock		fontClock;
	int				currentFont;
	int				lastActivated;
	TimeClock		activationClock;
public:
	ScoreEffect(Scene* scene, double x, double y, unsigned int score);
	~ScoreEffect();
public:
	void update(double dt);
	void render(Graphics* gr);
};

#endif
