////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MosqueRocketSmoke | Humo del lanzamiento del cohete de la mezquita
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/mosque/MosqueRocketSmoke.h>
#include <src/ResourceManager.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

MosqueRocketSmoke::MosqueRocketSmoke(Scene* scene, double x, double y) : Entity(scene, x, y)
, frame(0)
, clock(0.02)
, sprite(null)
{
	sprite = res.findSpriteSheet("MosqueRocketSmoke")->getSprite();
}
MosqueRocketSmoke::~MosqueRocketSmoke()
{
}
void MosqueRocketSmoke::update(double dt)
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
void MosqueRocketSmoke::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, frame, 0);
}

