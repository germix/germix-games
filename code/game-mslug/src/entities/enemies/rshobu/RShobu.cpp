////////////////////////////////////////////////////////////////////////////////////////////////////
//
// RShobu | Helicóptero R-Shobu
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/rshobu/RShobu.h>
#include <src/Debug.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/NormalExplosionB.h>
#include <src/entities/enemies/rshobu/RShobuBomb.h>
#include <src/entities/enemies/rshobu/RShobuBombSmoke.h>
#include <src/___/HurtableRect.h>
#include <src/entities/bonus/Bonus_Letter.h>

#include <mach/Math.h>
#include <mach/Mixer.h>
#include <mach/Color.h>
#include <mach/Graphics.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

#define DIR_LEFT					(-1)
#define DIR_RIGHT					(+1)

#define MAX_VELOCITY				60.2
#define MAX_ACCELERATION			70.0
#define INCR_ACCELERATION			8

#define MAX_VELOCITY_Y				30.2
#define MAX_ACCELERATION_Y			40.0

#define DISTANCE_TO_CAMERA_BOTTOM	210		// Distancia vertical desde la parte inferior de la cámara

class RShobuHurtableRect : public HurtableRect
{
	RShobu* rshobu;
	const char* name;
public:
	RShobuHurtableRect(RShobu* r, const char* n) : rshobu(r), name(n)
	{
	}
	~RShobuHurtableRect()
	{
	}
public:
	void hurt(int damage)
	{
		rshobu->hurt(damage);
	}
	bool isHurtable() const
	{
		return true;
	}
	Rectanglef hurtableRect() const
	{
		return rshobu->body->rectangle(
			name,
			rshobu->pos.x,
			rshobu->pos.y + rshobu->offsetY,
			rshobu->frameIndex,
			(rshobu->lookX == 1) ? Sprite::FLIP_X : 0);
	}
};

RShobu::RShobu(Scene* scene, double x, double y) : Enemy(scene, x, y)
, velocity()
, acceleration()
, lookX(DIR_LEFT)

, clock(8)
, clockEnabled(false)
, frameIndex(CENTRAL_FRAME)

, valueY(0)
, offsetY(0)

, body(null)

, bladesFrame(0)
, bladesClock(0.05)

, timeBetweenBursts(2.5)
, timeBetweenShots(0.2)
, attacks(0)
, attackClock(0)
, attackStage(-1)

, health(60)

, firstUpdate(true)
{
	char s[8] = "Blades0";
	SpriteSheet* sheet = res.findSpriteSheet("RShobu");
	
	body = sheet->getSprite("Body");
	for(int i = 0; i < MAX_FRAMES; i++)
	{
		s[6] = '1' + i;
		s[7] = '\0';
		blades[i] = sheet->getSprite(s);
	}
	hits.push_back(new RShobuHurtableRect(this, "hit1"));
	hits.push_back(new RShobuHurtableRect(this, "hit2"));
}
RShobu::~RShobu()
{
	for(unsigned int i = 0; i < hits.size(); i++)
		delete hits[i];
	hits.clear();
}
void RShobu::update(double dt)
{
	Hero* hero;
	
	if(firstUpdate)
	{
		scene->setRightLimit((int)(pos.x + 70));
		firstUpdate = false;
	}
	double oldPositionX = pos.x;
	if(null != (hero = scene->getHero()) && hero->isAlive())
	{
		double heroX = hero->getPosition().x;
		double cameraBottom = scene->getCameraRect().getMaxY();
		
		if((heroX+8) < pos.x)
		{
			clockEnabled = true;
			acceleration.x -= INCR_ACCELERATION;
		}
		else if((heroX-8) > pos.x)
		{
			clockEnabled = true;
			acceleration.x += INCR_ACCELERATION;
		}
		else
		{
			velocity.x = 0;
			acceleration.x = 0;
		}
#if 1
		if((cameraBottom-pos.y) > DISTANCE_TO_CAMERA_BOTTOM)
		{
			acceleration.y += INCR_ACCELERATION;
		}
		else if((cameraBottom-pos.y) < DISTANCE_TO_CAMERA_BOTTOM)
		{
			acceleration.y -= INCR_ACCELERATION;
		}
		else
		{
			velocity.y = 0;
			acceleration.y = 0;
		}
#endif
		//
		// Controlar límites de velocidad y aceleración
		//
		if(velocity.x > +MAX_VELOCITY)					velocity.x = (+MAX_VELOCITY);
		else if(velocity.x < -MAX_VELOCITY)				velocity.x = (-MAX_VELOCITY);
		if(acceleration.x > +MAX_ACCELERATION)			acceleration.x = (+MAX_ACCELERATION);
		else if(acceleration.x < -MAX_ACCELERATION)		acceleration.x = (-MAX_ACCELERATION);
#if 1
		if(velocity.y > +MAX_VELOCITY_Y)				velocity.y = (+MAX_VELOCITY_Y);
		else if(velocity.y < -MAX_VELOCITY_Y)			velocity.y = (-MAX_VELOCITY_Y);
		if(acceleration.y > +MAX_ACCELERATION_Y)		acceleration.y = (+MAX_ACCELERATION_Y);
		else if(acceleration.y < -MAX_ACCELERATION_Y)	acceleration.y = (-MAX_ACCELERATION_Y);
#endif
		//
		// Mover
		//
		CollisionInfo ci = scene->moveEntity(this, dt, pos, velocity, acceleration, false, 0);
#if 1
		if((cameraBottom-pos.y) < DISTANCE_TO_CAMERA_BOTTOM && velocity.y > 0)
		{
			pos.y = cameraBottom - DISTANCE_TO_CAMERA_BOTTOM;
			velocity.y = 0;
			acceleration.y = 0;
		}
		else if((cameraBottom-pos.y) > DISTANCE_TO_CAMERA_BOTTOM && velocity.y < 0)
		{
			pos.y = cameraBottom - DISTANCE_TO_CAMERA_BOTTOM;
			velocity.y = 0;
			acceleration.y = 0;
		}
#endif
		if(!(velocity.y > 0 || velocity.y < 0))
		{
			updateOffsetY(dt);
		}
	}
	else
	{
		velocity.x = 0;
		acceleration.x = 0;
#if 1
		velocity.y = 0;
		acceleration.y = 0;
#endif
		updateOffsetY(dt);
	}
	double newPositionX = pos.x;
	
	//
	// Controlar la animación del helicóptero
	//
	if(clockEnabled && clock.update(dt))
	{
		if(newPositionX > oldPositionX)
		{
			frameIndex--;
			if(frameIndex < 0)
				frameIndex = 0;
		}
		else if(newPositionX < oldPositionX)
		{
			frameIndex++;
			if(frameIndex >= body->count())
				frameIndex = body->count()-1;
		}
		else
		{
			if(frameIndex > CENTRAL_FRAME)
				frameIndex--;
			else if(frameIndex < CENTRAL_FRAME)
				frameIndex++;
				
			if(frameIndex == CENTRAL_FRAME)
			{
				clockEnabled = false;
			}
		}
	}
	if(bladesClock.update(dt))
	{
		bladesFrame++;
		if(bladesFrame >= blades[frameIndex]->count())
			bladesFrame = 0;
	}
	if(!Debug::enemyPassive && (null != (hero = scene->getHero()) && hero->isAlive()))
	{
		//
		// Controlar ráfagas y disparos
		//
		switch(attackStage)
		{
			case -1:
				if(frameIndex == CENTRAL_FRAME)
				{
					attackClock.reset(timeBetweenBursts);
					attackStage = 0;
				}
				break;
			case 0:	// Esperando
				if(attackClock.update(dt))
				{
					attacks = 0;
					attackStage = 1;
					attackClock.reset(timeBetweenShots);
				}
				break;
			case 1:	// Disparando
				if(attackClock.update(dt))
				{
					double attackX = pos.x;
					double attackY = pos.y+(offsetY/48)+48+8+8;

					scene->addEntityBackOfOther(this, new RShobuBombSmoke(scene, attackX, attackY));
					scene->addEntityBackOfOther(this, new RShobuBomb(scene, attackX, attackY));

					attacks++;
					if(attacks >= MAX_ATTACKS)
					{
						attackStage = 0;
						attackClock.reset(timeBetweenBursts);
					}
				}
				break;
		}
	}
}
void RShobu::render(Graphics* gr)
{
	int posX = (int)pos.x;
	int posY = (int)(pos.y + offsetY);
	int size = 4;
	int hints = 0;
	
	if(lookX == 1)
		hints |= Sprite::FLIP_X;
	
	body->render(gr, posX, posY, frameIndex, hints);
	blades[frameIndex]->render(gr, posX, posY, bladesFrame, hints);
	
	if(Debug::showEnemyRects)
	{
		gr->fillRect(posX-size/2, posY-size/2, size, size, Debug::colorEnemyRects);
		
		gr->drawRect(bounds(), Debug::colorEnemyRects);
		for(unsigned int i = 0; i < hits.size(); i++)
		{
			gr->drawRect(hits[i]->hurtableRect(), Debug::colorEnemyRects);
		}
	}
}
Rectanglef RShobu::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef RShobu::bounds(double px, double py) const
{
	return body->rectangle(pos.x, pos.y + offsetY, frameIndex, (lookX == 1) ? Sprite::FLIP_X : 0);
}
void RShobu::hurt(int damage)
{
	health -= damage;
	if(health <= 0)
	{
		scene->getHero()->addScore(250);
		// ...
		destroyed = true;
		removable = true;
		Rectanglef b = bounds();
		scene->setRightLimit(-1);
		scene->addEntity(new Bonus_Letter(scene, b.getCenterX(), b.getCenterY()));
		scene->addEntity(new NormalExplosionB(scene, b.getCenterX(), b.getCenterY()));
		Mixer::playChannel(res.findSound("RShobu.Explode"));
	}
}
void RShobu::getHurtableRects(const Rectanglef& area, std::vector<HurtableRect*>& rects) const
{
	for(unsigned int i = 0; i < hits.size(); i++)
	{
		if(hits[i]->isHurtable() && hits[i]->hurtableRect().intersects(area))
		{
			rects.push_back(hits[i]);
			return;
		}
	}
}
void RShobu::updateOffsetY(double dt)
{
	//
	// Acualizar desplazamiento vertical
	//
	valueY += 190.0 * dt;
	if(valueY > 360)
	{
//		valueY = 0;
		valueY = 360 - valueY;
	}
	offsetY = 10.0 * Math::sin(Math::toRadians(valueY));
}
