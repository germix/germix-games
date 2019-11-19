////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MasknellSubordinate | Helicóptero Masknell subordinado en la flota
//
// Germán Martínez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/masknell/MasknellSubordinate.h>
#include <src/ResourceManager.h>
#include <src/routes/Route.h>
#include <src/routes/RouteCoordinate.h>

#include <mach/Math.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

MasknellSubordinate::MasknellSubordinate(Scene* scene, double x, double y, Route* r) : Masknell(scene, x, y, r)
{
	sprite = res.findSpriteSheet("Masknell")->getSprite("Subordinate");
}
MasknellSubordinate::~MasknellSubordinate()
{
}
void MasknellSubordinate::update(double dt)
{
	RouteCoordinate rc;
	Masknell::update(dt, &rc);
	// ...
	double degrees = rc.angle * (180.0/Math::PI);
	if(degrees < 0.0)
		degrees = 360.0 + degrees;
	if((int)degrees == 180)
	{
		spriteHints = 0;
		spriteFrame = 3+0;
	}
	else if(degrees > 180 && degrees < 225)
	{
		spriteHints = 0;
		spriteFrame = 3+1;
	}
	else if((int)degrees == 225)
	{
		spriteHints = 0;
		spriteFrame = 3+2;
	}
	else if(degrees > 225 && degrees < 270)
	{
		spriteHints = 0;
		spriteFrame = 3+3;
	}
	else if((int)degrees == 270)
	{
		spriteHints = 0;
		spriteFrame = 3+4;
	}
	else if(degrees > 270 && degrees < 315)
	{
		spriteHints = Sprite::FLIP_X;
		spriteFrame = 3+3;
	}
	else if((int)degrees == 315)
	{
		spriteHints = Sprite::FLIP_X;
		spriteFrame = 3+2;
	}
	else if(degrees > 315 && degrees < 360)
	{
		spriteHints = Sprite::FLIP_X;
		spriteFrame = 3+1;
	}
	else if((int)degrees == 0)
	{
		spriteHints = Sprite::FLIP_X;
		spriteFrame = 3;
	}
	else if(degrees > 0 && degrees < 45)
	{
		spriteHints = Sprite::FLIP_X;
		spriteFrame = 3+1;
	}
	else if((int)degrees == 45)
	{
		spriteHints = Sprite::FLIP_X;
		spriteFrame = 3+2;
	}
	else if(degrees > 45 && degrees < 90)
	{
		spriteHints = Sprite::FLIP_X;
		spriteFrame = 3+3;
	}
	else if((int)degrees == 90)
	{
		spriteHints = Sprite::FLIP_X;
		spriteFrame = 3+4;
	}
	else if(degrees > 90 && degrees < 135)
	{
		spriteHints = 0;
		spriteFrame = 3+3;
	}
	else if((int)degrees == 135)
	{
		spriteHints = 0;
		spriteFrame = 3+2;
	}
	else if(degrees > 135 && degrees < 180)
	{
		spriteHints = 0;
		spriteFrame = 3+1;
	}
}

