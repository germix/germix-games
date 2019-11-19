////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SarubiaBombSmoke | Efecto de disparo del Sarubia
//
// Germán Martínez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/sarubia/SarubiaBombSmoke.h>
#include <src/ResourceManager.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

SarubiaBombSmoke::SarubiaBombSmoke(Scene* scene, double x, double y) : Entity(scene, x, y)
, frame(0)
, clock(0.02)
, sprite(null)
{
	sprite = res.findSpriteSheet("SarubiaBombSmoke")->getSprite();
}
SarubiaBombSmoke::~SarubiaBombSmoke()
{
}
void SarubiaBombSmoke::update(double dt)
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
void SarubiaBombSmoke::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, frame, 0);
}

