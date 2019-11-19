////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Mosque | Mezquita con torres lanza cohetes
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/mosque/Mosque.h>
#include <src/Debug.h>
#include <src/Config.h>
#include <src/ResourceManager.h>
#include <src/scene/Scene.h>
#include <src/entities/hero/Hero.h>
#include <src/entities/effects/NormalExplosionB.h>
#include <src/entities/effects/NormalExplosionM.h>
#include <src/entities/effects/NormalExplosionS.h>
#include <src/entities/enemies/mosque/MosqueTower.h>

#include <mach/Texture.h>
#include <mach/Graphics.h>

#include <gamelib-sprites/Sprite.h>
#include <gamelib-sprites/SpriteSheet.h>

static struct ExplosionDescriptor
{
	char	type;
	int		dx;
	int		dy;
}explosionDescriptors[]=
{
	{ 'M', 143, 71 },
	{ 'M', 43,56 },
	{ 'M', 120, 119 },
	{ 'M', 100,140 },
	{ 'M', 96,54 },
	{ 'M', 129,88 },
	{ 'B', 118,171 },
	{ 'M', 186,121 },
	{ 'B', 57,41 },
	{ 'M', 133,182 },
	{ 'M', 36,157 },
	{ 'M', 224,168 },
	{ 'M', 183,66 },
	{ 'M', 81,22 },
	{ 'B', 228,100 },
	{ 'S', 127,157 },
	{ 'M', 180,170 },
	{ 'M', 155,153 },
	{ 'M', 64,140 },
	{ 'M', 128,126 },
	{ 'S', 228,46 },
	{ 'M', 86,77 },
	{ 'M', 132,171 },
	{ 'M', 268,95 },
	{ 'B', 98,110 },
	{ 'M', 250,50 },
	{ 'M', 240,120 },
	{ 'B', 253,32 },
	{ 'B', 153,42 },
	{ 'B', 290,100 },
	
	{ 'B', 118,171 },
	{ 'M', 186,121 },
	{ 'B', 57,41 },
	{ 'M', 133,182 },
	{ 'M', 36,157 },
	{ 'B', 153,42 },
	{ 'B', 290,100 },
	{ 'M', 128,126 },
	{ 'S', 228,46 },
	{ 'M', 86,77 },
	{ 'M', 132,171 },
	{ 'M', 268,95 },
	{ 'B', 186,121 },
	{ 'B', 57,41 },
	{ 'B', 133,182 },
	{ 'B', 132,171 },
	{ 'B', 268,95 },
	{ 'B', 118,171 },
	{ 'M', 186,121 },
	{ 'B', 57,41 },
	{ 'M', 133,182 },
	{ 'M', 36,157 },
	{ 'B', 153,42 },
	{ 'B', 290,100 },
	{ 'M', 128,126 },
	{ 'S', 228,46 },
	{ 'M', 86,77 },
	{ 'M', 132,171 },
	{ 'M', 268,95 },
	{ 'B', 186,121 },
	{ 'B', 57,41 },
	{ 'B', 133,182 },
	{ 'B', 132,171 },
	{ 'B', 268,95 },
};
#define explosionDescriptors_length			(sizeof(explosionDescriptors)/sizeof(explosionDescriptors[0]))

//
// Desplazamientos de las torres durante su elevación
// 0x1 = Significa desplazamiento horizontal
// 0x2 = Significa desplazamiento hacia arriba
// 0x4 = Significa desplazamiento hacia arriba (otra vez)
// 0x8 = Significa desplazamiento extra del escenario (es hacia abajo)
//
static const unsigned int liftingOffsets[] =
{
	(1|2|0|0),		// 1º
	(0|2|0|0),		// 2º
	(1|2|0|8),		// 3º
	(0|0|0|8),		// 4º
	(0|2|0|8),		// 5º
	(1|2|0|0),		// 6º
	(0|2|0|8),		// 7º
	(0|0|0|8),		// 8º
	(1|2|0|8),		// 9º
	(0|2|0|0),		// 10º
	(0|0|0|8),		// 11º
	(1|2|0|8),		// 12º
	(0|0|0|8),		// 13º
	(1|2|4|0),		// 14º
	(0|0|0|8),		// 15º
	(0|2|0|8),		// 16º
	(1|0|0|8),		// 17º
	(0|2|4|0),		// 18º
	(0|0|0|8),		// 19º
	(1|2|0|8),		// 20º
	(0|0|0|8),		// 21º
	(0|2|0|0),		// 22º
	(1|2|0|8),		// 23º
};
#define liftingOffsets_length (sizeof(liftingOffsets)/sizeof(liftingOffsets[0]))

static const unsigned int openingDoorsFrames[] =
{
	0,1,2,3,4,5,6,7,8,9,10,9,10,11,12,13,12,13,14,15,14,15,
};
#define openingDoorsFrames_length (sizeof(openingDoorsFrames)/sizeof(openingDoorsFrames[0]))

#define TIME_LIFTING						0.07
#define TIME_OPENING1						0.04
#define TIME_OPENING2						0.04
#define TIME_EXPLOITING_1					0.14
#define TIME_EXPLOITING_SHAKE				0.03

Mosque::Mosque(Scene* scene, double x, double y) : Enemy(scene, x, y)
, state(STATE_NOTHING)
, mosqueWidth(0)
, mosqueHeight(0)

, activationX((int)(pos.x + SCREEN_WIDTH/2 - 80))

, textureBaseNormal(null)
, textureBaseDestroyed(null)

, clock()
, animationIndex(0)

, doorFrame(-1)
, doorSprite(null)

, operatorSprite(null)

, lastExplosionIndex(0)

, shakeValue(10)
, shakeDirection(1)

{
	SpriteSheet* sheet = res.findSpriteSheet("Mosque");

	textureBaseNormal = res.findTexture("Mosque.Normal");
	textureBaseDestroyed = res.findTexture("Mosque.Destroyed");
	mosqueWidth = textureBaseNormal->getWidth();
	mosqueHeight = textureBaseNormal->getHeight();

	doorSprite = sheet->getSprite("TowerDoors");
	operatorSprite = sheet->getSprite("TowerOperator");

	//
	// Crear las torres
	//
	{
		int mx = (int)pos.x;
		int my = ((int)pos.y-mosqueHeight);
		towers[0] = new MosqueTower(mx+82, my-71, this, sheet->getSprite("LeftTower"));
		towers[1] = new MosqueTower(mx+174, my-71, this, sheet->getSprite("CenterTower"));
		towers[2] = new MosqueTower(mx+265, my-71, this, sheet->getSprite("RightTower"));
	}
}
Mosque::~Mosque()
{
	for(unsigned int i = 0; i < MAX_TOWERS; i++)
		delete towers[i];
}
void Mosque::update(double dt)
{
	switch(state)
	{
		case STATE_NOTHING:
			if(scene->getLeftLimit() > activationX)
			{
				scene->setLeftLimit(activationX);
				scene->setRightLimit((int)pos.x + mosqueWidth);
				
				state = STATE_LIFTING;
				
				//
				// Setear animación de la elevación de torres
				//
				clock.reset(TIME_LIFTING);
				animationIndex = 0;
			}
			break;
		case STATE_LIFTING:
			if(clock.update(dt))
			{
				//
				// Ajustar desplazamientos
				//
				unsigned int offsetMask = liftingOffsets[animationIndex];
				
				if((offsetMask&0x1) != 0)
				{
					towers[0]->pos.x--;
					towers[2]->pos.x++;
				}
				if((offsetMask&0x2) != 0)
				{
					towers[0]->pos.y--;
					towers[1]->pos.y--;
					towers[2]->pos.y--;
				}
				if((offsetMask&0x4) != 0)
				{
					towers[0]->pos.y--;
					towers[1]->pos.y--;
					towers[2]->pos.y--;
				}
				if((offsetMask&0x8) != 0)
				{
					towers[0]->pos.y--;
					towers[1]->pos.y--;
					towers[2]->pos.y--;
					scene->addRelativeScroll(0, -1);
				}
				//
				// Avanzar animación
				//
				animationIndex++;
				if(animationIndex >= liftingOffsets_length)
				{
					//
					// Abrir torres
					//
					state = STATE_OPENING1;
					clock.reset(TIME_OPENING1);
					doorFrame = 0;
					animationIndex = 0;
					
					for(int i = 0; i < MAX_TOWERS; i++)
					{
						towers[i]->towerFrame = 1;
					}
				}
			}
			break;
		case STATE_OPENING1:
			if(clock.update(dt))
			{
				doorFrame = openingDoorsFrames[animationIndex];
				// ...
				animationIndex++;
				if(animationIndex >= openingDoorsFrames_length)
				{
					state = STATE_OPENING2;
					clock.reset(TIME_OPENING2);
					animationIndex = 0;
				}
			}
			break;
		case STATE_OPENING2:
			if(clock.update(dt))
			{
				for(int i = 0; i < MAX_TOWERS; i++)
				{
					towers[i]->towerFrame = BASE_INDEX_TOWER_OPENING_FRAMES + animationIndex;
				}
				animationIndex++;
				if(animationIndex > MAX_OPENING_FRAMES)
				{
					//
					// Comenzar ataque
					//
					state = STATE_ATTACKING;
					for(int i = 0; i < MAX_TOWERS; i++)
					{
						towers[i]->init();
					}
				}
				else if(animationIndex == 7)
				{
					doorFrame = -1;
				}
				else if(animationIndex >= 13)
				{
					for(int i = 0; i < MAX_TOWERS; i++)
					{
						towers[i]->open();
					}
				}
			}
			break;
		case STATE_ATTACKING:
			{
				bool allDestroyed = true;
				
				for(int i = 0; i < MAX_TOWERS; i++)
				{
					towers[i]->update(dt);
					if(!towers[i]->isDestroyed())
						allDestroyed = false;
				}
				if(allDestroyed)
				{
					state = STATE_EXPLOITING_1;
					clock.reset(TIME_EXPLOITING_1);
					destroyed = true;
					scene->getHero()->disableControls();
				}
			}
			break;
		case STATE_EXPLOITING_1:
			if(clock.update(dt))
			{
				explode();
				if(lastExplosionIndex == explosionDescriptors_length/4)
				{
					state = STATE_EXPLOITING_SHAKE;
					clock.reset(TIME_EXPLOITING_SHAKE);
				}
			}
			break;
		case STATE_EXPLOITING_SHAKE:
			if(clock.update(dt))
			{
				double ey = scene->getRelativeScrollY();
				
				ey += shakeValue*shakeDirection;
				shakeDirection *= -1;
				if(shakeDirection == +1)
				{
					shakeValue--;
				}
				scene->setRelativeScrollY(ey);
				if(shakeValue == 0)
				{
					state = STATE_RESTORING;
					scene->setRightLimit(-1);
				}
				explode();
			}
			break;
		case STATE_RESTORING:
			if(!scene->isRestoringScroll())
			{
				state = STATE_DESTROYED;
				scene->getHero()->enableControls();
			}
			break;
		case STATE_DESTROYED:
			if(activationX+mosqueWidth < scene->getCameraRect().getMinX())
			{
				removable = true;
			}
			break;
	}
}
void Mosque::render(Graphics* gr)
{
	//
	// Dibujar torres
	//
	if(state != STATE_DESTROYED && state != STATE_RESTORING && state != STATE_EXPLOITING_SHAKE)
	{
		for(int i = 0; i < MAX_TOWERS; i++)
		{
			towers[i]->render(gr, doorFrame);
		}
	}
	//
	// Dibujar base
	//
	{
		Texture* texture = null;
		
		switch(state)
		{
			case STATE_NOTHING:
			case STATE_LIFTING:
			case STATE_OPENING1:
			case STATE_OPENING2:
			case STATE_ATTACKING:
				texture = textureBaseNormal;
				break;
			case STATE_EXPLOITING_1:
			case STATE_EXPLOITING_SHAKE:
			case STATE_RESTORING:
			case STATE_DESTROYED:
				texture = textureBaseDestroyed;
				break;
		}
		if(texture != null)
		{
			gr->drawTexture(texture, (int)pos.x+(mosqueWidth-texture->getWidth()), (int)pos.y-texture->getHeight());
		}
	}
	if(Debug::showEnemyRects)
	{
		gr->drawRect(bounds(), Debug::colorEnemyRects);
		for(unsigned int i = 0; i < MAX_TOWERS; i++)
		{
			gr->drawRect(towers[i]->hurtableRect(), Debug::colorEnemyRects);
		}
	}
}
void Mosque::getHurtableRects(const Rectanglef& area, std::vector<HurtableRect*>& rects) const
{
	for(unsigned int i = 0; i < MAX_TOWERS; i++)
	{
		bool h = towers[i]->isHurtable();
		bool ri = towers[i]->hurtableRect().intersects(area);
		if(h && ri)
		{
			rects.push_back(towers[i]);
		}
	}
}
void Mosque::explode()
{
	if(lastExplosionIndex < explosionDescriptors_length)
	{
		explode(&explosionDescriptors[lastExplosionIndex]);
		explode(&explosionDescriptors[explosionDescriptors_length-1-lastExplosionIndex]);
		lastExplosionIndex++;
	}
}
void Mosque::explode(ExplosionDescriptor* ed)
{
	switch(ed->type)
	{
		case 'S':
			scene->addEntity(new NormalExplosionS(scene, activationX+ed->dx, ed->dy));
			break;
		case 'M':
			scene->addEntity(new NormalExplosionM(scene, activationX+ed->dx, ed->dy));
			break;
		case 'B':
			scene->addEntity(new NormalExplosionB(scene, activationX+ed->dx, ed->dy));
			break;
	}
}
