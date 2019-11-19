////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ScoreEffect | Mostrar puntaje parpadeante
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/effects/ScoreEffect.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>

#include <gamelib/Font.h>
#include <gamelib/FontLoader.h>

#include <stdio.h>
#include <string.h>

#define DIGIT_VELOCITY		220.0
#define DIGIT_ACCELERATION	380.0

class ScoreEffect::Digit
{
public:
	int			x;
	double		y;
	char		dig;
	double		vel;
	double		accel;
	bool		active;
	bool		stopped;
public:
	Digit()
		: x(0)
		, y(0)
		, dig(0)
		, vel(-DIGIT_VELOCITY)
		, accel(+DIGIT_ACCELERATION)
		, active(false)
		, stopped(false)
	{
	}
	~Digit()
	{
	}
};

ScoreEffect::ScoreEffect(Scene* scene, double x, double y, unsigned int score) : Entity(scene, x, y)
, stage(0)
, stopY(0)
, digits(null)
, digitsLength(0)
, fontClock(0.06)
, currentFont(0)
, lastActivated(0)
, activationClock(0.1)
{
	fonts[0] = res.findFont("Score1");
	fonts[1] = res.findFont("Score2");
	//
	// Crear dígitos
	//
	char text[16];
	sprintf(text, "%d", score);
	
	int    fontWidth = fonts[0]->fontHeight();
	int    textWidth = fonts[0]->textWidth(text);
	int    charX = (int)x - textWidth/2;
	int    charY = (int)y;

	digitsLength = strlen(text);
	digits = new Digit[digitsLength];
	for(int i = 0; i < digitsLength; i++, charX += fontWidth)
	{
		digits[i].x = charX;
		digits[i].y = charY;
		digits[i].dig = text[i];
	}
	//
	// Posición donde se detienen todas los dígitos
	//
	stopY = (double)y-50;
}
ScoreEffect::~ScoreEffect()
{
	delete [] digits;
}
void ScoreEffect::update(double dt)
{
	//
	// Alternar 'currentFont' entre 0 y 1
	//
	if(fontClock.update(dt))
	{
		currentFont = ((++currentFont)&1);
	}
	//
	// Activar dígitos
	//
	if(lastActivated < digitsLength)
	{
		if(activationClock.update(dt))
		{
			digits[lastActivated++].active = true;
		}
	}
	if(stage == 0)
	{
		//
		// Reposicionar dígitos
		//
		int stoppedCount = 0;
		for(int i = 0; i < digitsLength; i++)
		{
			Digit* dig = &digits[i];
			
			if(!dig->active)
				break;
			if(!dig->stopped)
			{
				dig->y += dig->vel*dt + (dig->accel*dt*dt)*0.5;
				dig->vel += dig->accel*dt;
				
//				if(dig->y > stopY && dig->vel > 0)
				if(dig->y < stopY && dig->vel < 0)
					dig->stopped = true;
			}
			else
			{
				stoppedCount++;
			}
		}
		if(stoppedCount == digitsLength)
		{
			stage = 1;
			for(int i = 0; i < digitsLength; i++)
			{
				digits[i].vel = 0;
				digits[i].accel *= -1.;
			}
			activationClock.reset(0.8);
		}
	}
	else if(stage == 1)
	{
		if(activationClock.update(dt))
		{
			stage = 2;
		}
	}
	else
	{
		//
		// Salir fuera de la pantalla
		//
		for(int i = 0; i < digitsLength; i++)
		{
			Digit* dig = &digits[i];
			dig->y += dig->vel*dt + (dig->accel*dt*dt)*0.5;
			dig->vel += dig->accel*dt;
		}
		if(scene->getCameraRect().getMinY() > (digits[0].y+fonts[0]->fontHeight()))
		{
			removable = true;
		}
	}
}
void ScoreEffect::render(Graphics* gr)
{
	for(int i = 0; i < digitsLength; i++)
	{
		if(!digits[i].active)
			break;
		fonts[currentFont]->render(gr, digits[i].x, (int)digits[i].y, digits[i].dig);
	}
}
