////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ScoreEffect | Mostrar puntaje
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/effects/ScoreEffect.h>
#include <src/ResourceManager.h>
#include <src/Scene.h>

#include <gamelib/Font.h>

ScoreEffect::ScoreEffect(Scene* s, double x, double y, int score) : Entity(s, x, y)
, font(res.findFont("Font.1"))
, text(String::fromInt(score))
, textX(0)
, textY(0)
{
	textX = x - font->textWidth(text.c_str())/2;
	textY = y;
}
ScoreEffect::~ScoreEffect()
{
}
void ScoreEffect::update(double dt)
{
	//
	// Salir fuera de la pantalla
	//
	textY -= (dt * 100);
	
	if(scene->getCameraRect().getMinY() > (textY+font->fontHeight()))
	{
		removable = true;
	}
}
void ScoreEffect::render(Graphics* gr)
{
	font->render(gr, int(textX), int(textY), text.c_str());
}
