////////////////////////////////////////////////////////////////////////////////////////////////////
//
// RShobuBombSmoke | Humo generado en cuando el helic�ptero R-Shobu lanza una bomba
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/rshobu/RShobuBombSmoke.h>
#include <src/ResourceManager.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

RShobuBombSmoke::RShobuBombSmoke(Scene* scene, double x, double y) : Entity(scene, x, y)
, frame(0)
, clock(0.02)
, sprite(null)
{
	sprite = res.findSpriteSheet("RShobuBombSmoke")->getSprite();
}
RShobuBombSmoke::~RShobuBombSmoke()
{
}
void RShobuBombSmoke::update(double dt)
{
	if(clock.update(dt))
	{
		if(++frame >= sprite->count())
		{
			frame = 0;
			removable = true;
		}
	}
}
void RShobuBombSmoke::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, frame, 0);
}

