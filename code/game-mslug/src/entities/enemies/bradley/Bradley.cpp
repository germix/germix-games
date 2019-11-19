////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bradley | M-15A Bradley
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/bradley/Bradley.h>
#include <src/Debug.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/___/HurtableRect.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/NormalExplosionB.h>
#include <src/entities/enemies/bradley/BradleyRocket.h>
#include <src/entities/enemies/bradley/BradleyShootingFire.h>

#include <mach/Graphics.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

static const int INDEXES_PREPARING[] = 
{
	0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2
};
static const int INDEXES_LAUNCHING[] = 
{
	3,4,5,6
};

#define INDEXES_PREPARING_LENGTH (sizeof(INDEXES_PREPARING)/sizeof(int))
#define INDEXES_LAUNCHING_LENGTH (sizeof(INDEXES_LAUNCHING)/sizeof(int))

#define MAX_LAUNCHS							4

#define TIME_IDLE							0.10
#define TIME_WALKING						0.08
#define TIME_STOPPING						0.06
#define TIME_SHOOTING_1						0.03
#define TIME_WRECKED						0.05
#define TIME_SHOOTING_2						0.07

#define WALK_VELOCITY						30

#define MAX_DISTANCE_FOR_WALK_FORWARD		155
#define MIN_DISTANCE_FOR_WALK_BACKWARD		100

class BradleyHurtableRect : public HurtableRect
{
	int			px;
	int			py;
	int			width;
	int			height;
	Bradley*	bradley;
public:
	BradleyHurtableRect(Bradley* e, int x, int y, int w, int h) : px(x), py(y), width(w), height(h), bradley(e)
	{
	}
	~BradleyHurtableRect()
	{
	}
public:
	void hurt(int damage)
	{
		bradley->hurt(damage);
	}
	bool isHurtable() const
	{
		return true;
	}
	Rectanglef hurtableRect() const
	{
		return Rectanglef(bradley->pos.x - px, bradley->pos.y - py, width, height);
	}
};

Bradley::Bradley(Scene* scene, double x, double y) : Enemy(scene, x, y)
, state(STATE_IDLE)
, vel()
, accel(0, GRAVITY_CONSTANT*GRAVITY_DOWN)
, onGround(false)
, sprite(null)
, spriteFrame(0)
, spriteClock(TIME_IDLE)
, walkingClock(2.0)
, launcherClock(0.7)
, animIndex(0)
, launchs(0)
, waitLaunch(false)
, health(120)
{
	SpriteSheet* sheet;
	
	hits.push_back(new BradleyHurtableRect(this, 28, 24, 64, 24));
	hits.push_back(new BradleyHurtableRect(this, 0, 24+24, 32, 24));
	hits.push_back(new BradleyHurtableRect(this, 8, 24+24+8, 32, 8));
	hits.push_back(new BradleyHurtableRect(this, 8+8, 24+24+8+8, 32, 8));
	hits.push_back(new BradleyHurtableRect(this, 8+8, 24+24+8+8+8, 24, 8));
	
	sheet = res.findSpriteSheet("Bradley");
	SPRITE_IDLE = sheet->getSprite("Idle");
	SPRITE_WALKING = sheet->getSprite("Walking");
	SPRITE_STOPPING = sheet->getSprite("Stopping");
	SPRITE_SHOOTING = sheet->getSprite("Shooting");
	SPRITE_WRECKED = sheet->getSprite("Wrecked");
	
	SPRITE_SHOOTING_FIRE_1 = res.findSpriteSheet("Bradley.ShootingFire1")->getSprite();
//	SPRITE_SHOOTING_FIRE_2 = res.findSpriteSheet("Bradley.ShootingFire2")->getSprite();

	sprite = SPRITE_IDLE;
}
Bradley::~Bradley()
{
	for(unsigned int i = 0; i < hits.size(); i++)
		delete hits[i];
	hits.clear();
}
void Bradley::update(double dt)
{
	CollisionInfo ci = scene->moveEntity(this, dt, pos, vel, accel, onGround, MAP_TERRAIN_SOLID|MAP_TERRAIN_TOPDOWN);
	
	if(ci.flags & COLLISION_FLAG_BOTTOM)
	{
		vel.y = 0;
		onGround = true;
	}
	switch(state)
	{
		case STATE_IDLE:
			if(spriteClock.update(dt))
			{
				if(++spriteFrame >= sprite->count())
				{
					spriteFrame = 0;
				}
			}
			if(waitLaunch)
			{
				if(launcherClock.update(dt))
				{
					launch();
				}
			}
			else
			{
				if(walkingClock.update(dt))
				{
					Hero* hero = scene->getHero();
					Vector2f heroPos = hero->getPosition();
					int thisX = (int)pos.x;
					int heroX = (int)heroPos.x;
					
					if(heroX < thisX)
					{
						if((thisX-heroX) > MAX_DISTANCE_FOR_WALK_FORWARD)
						{
							//printf("WALKING_FORWARD");
							walk(-WALK_VELOCITY);
						}
						else if((thisX-heroX) < MIN_DISTANCE_FOR_WALK_BACKWARD)
						{
							//printf("WALKING_BACKWARD");
							walk(+WALK_VELOCITY);
						}
						else
						{
							preparing();
						}
					}
				}
			}
			break;
		case STATE_WALKING_FORWARD:
			if(spriteClock.update(dt))
			{
				if(++spriteFrame >= sprite->count())
				{
					spriteFrame = 0;
				}
			}
			if((pos.x - scene->getHero()->getPosition().x) < MAX_DISTANCE_FOR_WALK_FORWARD)
			{
				stop();
			}
			break;
		case STATE_WALKING_BACKWARD:
			if(spriteClock.update(dt))
			{
				if(--spriteFrame < 0)
				{
					spriteFrame = sprite->count()-1;
				}
			}
			if((pos.x-scene->getHero()->getPosition().x) > MIN_DISTANCE_FOR_WALK_BACKWARD)
			{
				//printf("STOPPING");
				stop();
			}
			break;
		case STATE_STOPPING:
			if(spriteClock.update(dt))
			{
				if(++spriteFrame >= sprite->count())
				{
					idle();
				}
			}
			break;
		case STATE_PREPARING:
			if(spriteClock.update(dt))
			{
				if(++animIndex >= INDEXES_PREPARING_LENGTH)
				{
					launch();
				}
				else
				{
					spriteFrame = INDEXES_PREPARING[animIndex];
				}
			}
			break;
		case STATE_LAUNCHING:
			if(spriteClock.update(dt))
			{
				if(++animIndex >= INDEXES_LAUNCHING_LENGTH)
				{
					idle();
				}
				else
				{
					spriteFrame = INDEXES_LAUNCHING[animIndex];
				}
			}
			break;
		case STATE_WRECKED:
			if(spriteClock.update(dt))
			{
				if(++spriteFrame >= sprite->count())
				{
					spriteFrame = sprite->count()-1;
				}
			}
			break;
	}
	if(scene->getCameraRect().getMinX() > bounds().getMaxX())
	{
		removable = true;
	}
}
void Bradley::render(Graphics* gr)
{
	if(state == STATE_PREPARING)
	{
		Point p = SPRITE_SHOOTING->point("Fire", pos.x, pos.y, 0, 0);
		
		SPRITE_SHOOTING_FIRE_1->render(gr, p.x, p.y, spriteFrame, 0);
	}
	sprite->render(gr, pos.x, pos.y, spriteFrame, 0);
	
	if(Debug::showEnemyRects)
	{
		gr->drawRect(bounds(), Debug::colorEnemyRects);
		for(unsigned int i = 0; i < hits.size(); i++)
		{
			gr->drawRect(hits[i]->hurtableRect(), Debug::colorEnemyRects);
		}
	}
}
Rectanglef Bradley::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef Bradley::bounds(double px, double py) const
{
	return Rectanglef(px-32, py-64, 64, 64);
}
void Bradley::getHurtableRects(const Rectanglef& area, std::vector<HurtableRect*>& rects) const
{
	if(state != STATE_WRECKED)
	{
		for(unsigned int i = 0; i < hits.size(); i++)
		{
			if(hits[i]->isHurtable() && hits[i]->hurtableRect().intersects(area))
			{
				rects.push_back(hits[i]);
			}
		}
	}
}

void Bradley::idle()
{
	state = STATE_IDLE;
	sprite = SPRITE_IDLE;
	spriteFrame = 0;
	spriteClock.reset(TIME_IDLE);
}
void Bradley::stop()
{
	state = STATE_STOPPING;
	sprite = SPRITE_STOPPING;
	spriteFrame = 0;
	spriteClock.reset(TIME_STOPPING);
	vel.x = 0;
}
void Bradley::walk(double vx)
{
	if(vx < 0)
	{
		state = STATE_WALKING_FORWARD;
		spriteFrame = 0;
	}
	else
	{
		state = STATE_WALKING_BACKWARD;
		spriteFrame = sprite->count()-1;
	}
	sprite = SPRITE_WALKING;
	spriteClock.reset(TIME_WALKING);
	vel.x = vx;
}
void Bradley::preparing()
{
	//
	// Ir al estado de preparación
	//
	state = STATE_PREPARING;
	sprite = SPRITE_SHOOTING;
	animIndex = 0;
	spriteFrame = INDEXES_PREPARING[animIndex];
	spriteClock.reset(TIME_SHOOTING_1);
}
void Bradley::launch()
{
	//
	// Ir al estado de lanzamiento
	//
	state = STATE_LAUNCHING;
	sprite = SPRITE_SHOOTING;
	animIndex = 0;
	spriteFrame = INDEXES_LAUNCHING[animIndex];
	spriteClock.reset(TIME_SHOOTING_2);
	
	//
	// Generar lanzamiento
	//
	launchs++;
	waitLaunch = true;
	
	//
	// Obtener tubo de lanzamiento
	//
	char pipeName[6] = "Pipe_";
	pipeName[4] = '0' + launchs;
	Point  pipePoint = SPRITE_SHOOTING->point(pipeName, pos.x, pos.y, 0, 0);
	char rocketName[8] = "Rocket_";
	rocketName[6] = '0' + launchs;
	Point  rocketPoint = SPRITE_SHOOTING->point(rocketName, pos.x, pos.y, 0, 0);
	
	//
	// Lanzar
	//
	scene->addEntity(new BradleyRocket(scene, rocketPoint.x, rocketPoint.y));
	scene->addEntity(new BradleyShootingFire(scene, pipePoint.x, pipePoint.y));
	
	//
	// Resetear lanzamientos
	//
	if(launchs >= MAX_LAUNCHS)
	{
		launchs = 0;
		waitLaunch = false;
	}
}
void Bradley::hurt(int damage)
{
	health -= damage;
	if(health <= 0)
	{
		vel.x = 0;
		health = 0;
		state = STATE_WRECKED;
		destroyed = true;
		animIndex = 0;
		sprite = SPRITE_WRECKED;
		spriteFrame = 0;
		spriteClock.reset(TIME_WRECKED);
		scene->addEntity(new NormalExplosionB(scene, pos.x, pos.y-50));
	}
}

