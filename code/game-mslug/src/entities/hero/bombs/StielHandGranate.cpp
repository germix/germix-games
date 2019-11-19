////////////////////////////////////////////////////////////////////////////////////////////////////
//
// StielHandGranate
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/bombs/StielHandGranate.h>
#include <src/Config.h>
#include <src/scene/Scene.h>
#include <src/ResourceManager.h>
#include <src/entities/effects/GrenadeExplosion.h>
#include <src/___/HurtableRect.h>

#include <mach/Math.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

//
//http://laplace.ucv.cl/Cursos/Old/fisica/dinamica/con_mlineal/restitucion/restitucion.htm
//
#define STIELHANDGRANATE_DAMAGE		10

StielHandGranate::StielHandGranate(Scene* scene, double px, double py, double vx, double vy) : HeroBomb(scene, px, py)
, vel(vx, vy)
, accel(0, GRAVITY_DOWN*GRAVITY_CONSTANT)
, sprite(null)
, spriteIndex(0)
, spriteClock(0.02)
, rebounds(0)
, onGround(false)
{
	sprite = res.findSpriteSheet("StielHandGranate")->getSprite();
}
StielHandGranate::~StielHandGranate()
{
}
void StielHandGranate::update(double dt)
{
	bool exploit = false;
	double oldY = pos.y;
	CollisionInfo ci = scene->moveEntity(this, dt, pos, vel, accel, onGround, MAP_TERRAIN_SOLID);
	
	if(ci.flags != 0)
	{
		if(ci.flags & COLLISION_FLAG_BOTTOM)
		{
			if(!onGround)
			{
				rebounds++;
				if(rebounds == 2)
				{
					exploit = true;
				}
				else
				{
#if 1
					//
					// Rebote constante
					//
					if(vel.x < 0)
						vel.x = -90.0;
					else if(vel.x > 0)
						vel.x = +90.0;
					vel.y = -140.0;
#else
					//
					// Rebote dependiente de la velocidad
					//
					double e = 0.65;		// Coeficiente de restitución
					
					vel.y = -e*vel.y;
					if(Math::abs(vel.y) < 0.01)
						vel.y = 0;
					
					vel.x = (FRICTION*vel.x);
					if(Math::abs(vel.x) < 0.01)
						vel.x = 0;
#endif
				}
			}
			onGround = true;
		}
		else
		{
			exploit = true;
		}
	}
	else if((int)oldY != (int)pos.y)
	{
		onGround = false;
	}
	//
	// ...
	//
	if(exploit)
	{
		explode();
	}
	else
	{
		if(spriteClock.update(dt))
		{
			spriteIndex++;
			if(spriteIndex >= sprite->count())
				spriteIndex = 0;
		}
	}
}
void StielHandGranate::render(Graphics* gr)
{
	sprite->render(gr, pos.x, pos.y, spriteIndex, 0);
}
Rectanglef StielHandGranate::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef StielHandGranate::bounds(double px, double py) const
{
	const int size = 8;
	return Rectanglef(px-size/2, py-size, size, size);
}
void StielHandGranate::explode()
{
	removable = true;
	scene->addEntity(new GrenadeExplosion(scene, pos.x, pos.y));
	
	std::vector<HurtableRect*> rects = scene->getHurtableRectanglesInArea(Rectanglef(pos.x-25, pos.y-25, 50, 50));
	for(unsigned int i = 0; i < rects.size(); i++)
	{
		rects[i]->hurt(STIELHANDGRANATE_DAMAGE);
	}
}

