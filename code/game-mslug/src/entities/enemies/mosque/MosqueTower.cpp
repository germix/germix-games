////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MosqueTower | Torre de mezquita
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/mosque/MosqueTower.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/NormalExplosionB.h>
#include <src/entities/enemies/mosque/Mosque.h>
#include <src/entities/enemies/mosque/MosqueRocket.h>
#include <src/entities/enemies/mosque/MosqueRocketSmoke.h>
#include <src/entities/enemies/mosque/MosqueTowerOperatorDead.h>

#include <mach/Random.h>
#include <mach/Color.h>
#include <mach/Texture.h>

#include <gamelib-sprites/Sprite.h>

#define TIME_TURN			0.04
#define TIME_FIRING			0.04
#define TIME_FREEZED1		0.8

#define MAX_HEALTH			70
#define MAX_DAMAGED_TIME	0.02

#define DAMAGED_COLOR		Color(255, 150, 0)

#define DOOR_OFFSET_X		2
#define DOOR_OFFSET_Y		16

#define OPERATOR_OFFSET_X	26
#define OPERATOR_OFFSET_Y	29

static const int turnIndexes[] =
{
	10,9,8,7,6
};
static const int firingIndexes[] =
{
	6,7,8,9,10,11,10,11,
};

#define turnIndexes_length (sizeof(turnIndexes)/sizeof(turnIndexes[0]))
#define firingIndexes_length (sizeof(firingIndexes)/sizeof(firingIndexes[0]))

MosqueTower::MosqueTower(int x, int y, Mosque* m, Sprite* s)
: state(STATE_NOTHING)
, pos(x, y)
, sprite(s)
, health(MAX_HEALTH)
, damaged(false)
, damagedTime(0)
, towerFrame(0)
, operatorFrame(-1)
, clock()
, index(0)
, mosque(m)
, doorOffset(2, 16)
{
}
MosqueTower::~MosqueTower()
{
}
void MosqueTower::init()
{
	index = 0;
	state = STATE_FREEZED2;
	clock.reset(Random().nextDouble(0.5, 1.5));
	towerFrame = Mosque::BASE_INDEX_TOWER_ATTACKING_FRAMES;
}
void MosqueTower::open()
{
	operatorFrame++;
}
void MosqueTower::update(double dt)
{
	switch(state)
	{
		case STATE_NOTHING:
			break;
		case STATE_FIRING:
			if(clock.update(dt))
			{
				index++;
				if(index >= firingIndexes_length)
				{
					index = 0;
					state = STATE_FREEZED1;
					clock.reset(TIME_FREEZED1);
					{
						Rectanglef r = getDomeRectangle();
						int x = (int)r.getX()+27;
						int y = (int)r.getY()+29;
						
						mosque->scene->addEntity(new MosqueRocket(mosque->scene, x, y, mosque));
						
						mosque->scene->addEntity(new MosqueRocketSmoke(mosque->scene, x, y));
					}
				}
				else
				{
					operatorFrame = firingIndexes[index];
				}
			}
			break;
		case STATE_FREEZED1:
			if(clock.update(dt))
			{
				state = STATE_TURN;
				index = 0;
				clock.reset(TIME_TURN);
			}
			break;
		case STATE_TURN:
			if(clock.update(dt))
			{
				index++;
				if(index >= turnIndexes_length)
				{
					index = 0;
					state = STATE_FREEZED2;
					clock.reset(Random().nextDouble(1, 2));
				}
				else
				{
					operatorFrame = turnIndexes[index];
				}
			}
			break;
		case STATE_FREEZED2:
			if(clock.update(dt))
			{
				state = STATE_FIRING;
				index = 0;
				clock.reset(TIME_FIRING);
			}
			break;
		case STATE_DESTROYED:
			break;
	}
	if(damaged)
	{
		damagedTime += dt;
		if(damagedTime > MAX_DAMAGED_TIME)
		{
			damaged = false;
			damagedTime = 0;
		}
	}
}
void MosqueTower::render(Graphics* gr, unsigned int doorFrame)
{
	//
	// Dibujar torre
	//
	sprite->render(gr, pos.x, pos.y, towerFrame, 0);
	
	//
	// Dibujar puerta de torre
	//
	if(doorFrame != -1)
	{
		mosque->doorSprite->render(gr, pos.x + DOOR_OFFSET_X, pos.y + DOOR_OFFSET_Y, doorFrame, 0);
	}
	
	//
	// Dibujar operador de torre
	//
	if(operatorFrame != -1)
	{
		if(!damaged)
			mosque->operatorSprite->render(gr, pos.x + OPERATOR_OFFSET_X, pos.y + OPERATOR_OFFSET_Y, operatorFrame, 0);
		else
			mosque->operatorSprite->render(gr, pos.x + OPERATOR_OFFSET_X, pos.y + OPERATOR_OFFSET_Y, operatorFrame, 0, DAMAGED_COLOR);
	}
}
bool MosqueTower::isDestroyed() const
{
	return (state == STATE_DESTROYED);
}
Rectanglef MosqueTower::getDomeRectangle() const
{
	int opWidth = 40;
	int opHeight = 40;
	return Rectanglef(pos.x + OPERATOR_OFFSET_X, pos.y + OPERATOR_OFFSET_Y, opWidth, opHeight);
}
void MosqueTower::hurt(int damage)
{
	health -= damage;
	if(health < 0)
	{
		mosque->scene->getHero()->addScore(300);
		// ...
		state = STATE_DESTROYED;
		health = 0;
		towerFrame = Mosque::BASE_INDEX_TOWER_DESTROYED_FRAMES;
		operatorFrame = -1;
		
		Rectanglef r = getDomeRectangle();
		mosque->scene->addEntity(new NormalExplosionB(mosque->scene, r.getCenterX(), r.getCenterY()));
		mosque->scene->addEntity(new MosqueTowerOperatorDead(mosque->scene, r.getCenterX(), r.getCenterY()));
	}
	damaged = true;
	damagedTime = 0;
}
bool MosqueTower::isHurtable() const
{
	return (!damaged && state != STATE_DESTROYED && state != STATE_NOTHING);
}
Rectanglef MosqueTower::hurtableRect() const
{
	return getDomeRectangle();
}

