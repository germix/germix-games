////////////////////////////////////////////////////////////////////////////////////////////////////
//
// IronNokanaCannonShot | Efecto de disparo del ca��n de IronNokana
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/nokana/IronNokanaCannonShot.h>
#include <src/ResourceManager.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

IronNokanaCannonShot::IronNokanaCannonShot(Scene* scene, double x, double y) : Entity(scene, x, y)
, frame(0)
, clock(0.02)
, sprite(null)
{
	sprite = res.findSpriteSheet("IronNokanaCannonShot")->getSprite();
}
IronNokanaCannonShot::~IronNokanaCannonShot()
{
}
void IronNokanaCannonShot::update(double dt)
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
void IronNokanaCannonShot::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, frame, 0);
}
