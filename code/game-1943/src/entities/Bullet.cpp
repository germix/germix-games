////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bullet
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/Bullet.h>
#include <src/Debug.h>
#include <src/sprites/Sprite.h>

#include <mach/Color.h>
#include <mach/Graphics.h>

Bullet::Bullet(Scene* s, double x, double y, Sprite* ___sprite, double ___angle, double ___velocity) : Entity(s, x, y)
, frame(0)
, sprite(___sprite)
, angle(___angle)
, velocity(___velocity)
, destroyed(false)
{
}
Bullet::~Bullet()
{
}
Rectanglef Bullet::rect() const
{
	return sprite->rect(pos);
}
void Bullet::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, frame);
	
	if(Debug::showRectangle)
	{
		gr->drawRect(rect(), Color(255,0,0));
	}
}

