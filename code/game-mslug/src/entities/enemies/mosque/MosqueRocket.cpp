////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MosqueRocket | Cohete lanzado por la torre de la mezquita
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/mosque/MosqueRocket.h>
#include <src/Debug.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/enemies/mosque/Mosque.h>
#include <src/entities/effects/NormalExplosionS.h>

#include <mach/Math.h>
#include <mach/Random.h>
#include <mach/Graphics.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

#define MAX_TIME			0.06

#define MAX_SPRITES			3

#define VELOCITY			12
#define MIN_ANGLE			(-25)
#define MAX_ANGLE			(+25)
#define MIN_DISTANCE		10
#define MAX_DISTANCE		20

static int spriteFrameFromAngle360(double radians, int count)
{
	double degrees = radians * (180.0/Math::PI);

	if(degrees < 0.0)
		degrees = 360.0 + degrees;
	
	return (int)(Math::round(degrees/(360.0/(double)(count)))) % count;
}

MosqueRocket::MosqueRocket(Scene* scene, double x, double y, Mosque* m) : EnemyProjectile(scene, x, y)
, mosque(m)
, vel()
, accel(0, GRAVITY_CONSTANT*GRAVITY_DOWN)
, oldPos(pos)

, elapsed(0)
, lastFrame(0)
, currentFrame(0)
, currentSprite(0)

, currentAngle(0)
, currentDistance(1)
, distanceTraveled(0)

{
	SpriteSheet* sheet = res.findSpriteSheet("MosqueRocket");
	sprites[0] = sheet->getSprite("Rocket1");
	sprites[1] = sheet->getSprite("Rocket2");
	sprites[2] = sheet->getSprite("Rocket3");
	currentAngle = (double)Random().nextInt(60, 120);
}
MosqueRocket::~MosqueRocket()
{
}
void MosqueRocket::update(double dt)
{
	if(mosque->isDestroyed())
	{
		//
		// Auto-destruirse si la mezquita fue está destruida
		//
		removable = true;
		scene->addEntity(new NormalExplosionS(scene, pos.x, pos.y));
	}
	else
	{
		//
		// Intercambiar sprites
		//
		elapsed += dt;
		if(elapsed > MAX_TIME)
		{
			elapsed = 0;
			
			currentSprite++;
			if(currentSprite >= MAX_SPRITES)
				currentSprite = 0;
		}
		//
		// Guardar vieja posición
		//
		oldPos = pos;
		
		//
		// Calcular nuevo ángulo y nueva distancia
		//
		if(distanceTraveled >= currentDistance)
		{
			currentAngle += Random().nextDouble(MIN_ANGLE, MAX_ANGLE);
			currentDistance = Random().nextDouble(MIN_DISTANCE, MAX_DISTANCE);
			distanceTraveled = 0;
		}
		//
		// Moverse
		//
		double dv = VELOCITY*dt;
		double rad = Math::toRadians(currentAngle);
		
		distanceTraveled += dv;
		
		vel.x = Math::cos(rad)*VELOCITY;
		vel.y = Math::sin(rad)*VELOCITY;
		CollisionInfo ci = scene->moveEntity(this, dt, pos, vel, accel, false, MAP_TERRAIN_SOLID);
		
		if(ci.flags & COLLISION_FLAG_BOTTOM)
		{
			//
			// Si hay colisión en el mapa, explotar
			//
			removable = true;
			scene->addEntity(new NormalExplosionS(scene, pos.x, pos.y));
		}
		else if(scene->getCameraRect().excluded(sprites[currentSprite]->rectangle(pos.x, pos.y, currentFrame, 0)))
		{
			//
			// Si está fuera de cámara, remover sin explotar
			//
			removable = true;
		}
	}
}
void MosqueRocket::render(Graphics* gr)
{
	double angle = Math::atan2(pos.x-oldPos.x, oldPos.y-pos.y);
	
	currentFrame = spriteFrameFromAngle360(angle, 16);
	if(currentFrame == 0)
	{
		if(!(angle > 0 || angle < 0))
		{
			currentFrame = lastFrame;
		}
	}
	lastFrame = currentFrame;
	
	sprites[currentSprite]->render(gr, pos.x, pos.y, currentFrame, 0);

	if(Debug::showBulletRects)
	{
		gr->drawRect(bounds(), Debug::colorBulletRects);
	}
}
Rectanglef MosqueRocket::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef MosqueRocket::bounds(double px, double py) const
{
	return Rectanglef(px-6, py-6, 12, 12);
}
void MosqueRocket::collide(Entity* other)
{
	if(dynamic_cast<Hero*>(other))
	{
		removable = true;
		((Hero*)other)->hurt();
		scene->addEntity(new NormalExplosionS(scene, pos.x, pos.y));
	}
}
Rectanglef MosqueRocket::collisionRect() const
{
	return bounds();
}
void MosqueRocket::hurt(int damage)
{
	removable = true;
	scene->getHero()->addScore(10);
	scene->addEntity(new NormalExplosionS(scene, pos.x, pos.y));
}
bool MosqueRocket::isHurtable() const
{
	return true;
}
Rectanglef MosqueRocket::hurtableRect() const
{
	return bounds();
}
