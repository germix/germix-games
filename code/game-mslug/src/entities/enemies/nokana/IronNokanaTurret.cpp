////////////////////////////////////////////////////////////////////////////////////////////////////
//
// IronNokanaTurret | Torreta lanza-llamas del IronNokana
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/nokana/IronNokanaTurret.h>

static const int indexesFlameShot1[] =
{
	0,1,2,3,4,5,6,7,8,9,10,11,12,13,
};
static const int indexesFlameShot2[] =
{
	14,15,16,17,18,19,20,21,
};
static const int indexesFlameShot3[] =
{
	22,23,24,25,26,27,28,29,30,
};
static const int indexesFlameShot4[] =
{
	31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47
};
static struct StateNode
{
	const int loops;
	const int* frameIndexes;
	const int frameIndexesLength;
}stateNodes[] = 
{
	{	18,	indexesFlameShot1,	(sizeof(indexesFlameShot1)/sizeof(indexesFlameShot1[0]))	},
	{	1,	indexesFlameShot2,	(sizeof(indexesFlameShot2)/sizeof(indexesFlameShot2[0]))	},
	{	1,	indexesFlameShot3,	(sizeof(indexesFlameShot3)/sizeof(indexesFlameShot3[0]))	},
	{	1,	indexesFlameShot2,	(sizeof(indexesFlameShot2)/sizeof(indexesFlameShot2[0]))	},
	{	8,	indexesFlameShot4,	(sizeof(indexesFlameShot4)/sizeof(indexesFlameShot4[0]))	},
	{	1,	indexesFlameShot3,	(sizeof(indexesFlameShot3)/sizeof(indexesFlameShot3[0]))	},
};
static const int indexesTurretFireAttack[] =	//  En esta versión sólo hay un tipo de ataque
{
	0,9,10,11,
};

#define stateNodesLength				(sizeof(stateNodes)/sizeof(stateNodes[0]))
#define indexesTurretFireAttackLength	(sizeof(indexesTurretFireAttack)/sizeof(indexesTurretFireAttack[0]))

#define BASE_INDEX_TURRET_IDLE			0
#define BASE_INDEX_TURRET_DAMAGED		12
#define BASE_INDEX_TURRET_DESTROYED		13

IronNokanaTurret::IronNokanaTurret()
: state(STATE_IDLE)
, clock(0.02)
, fireNode(0)
, fireFrame(0)
, fireLoops(0)
, turretFrame(0)
{
}
IronNokanaTurret::~IronNokanaTurret()
{
}
bool IronNokanaTurret::update(double dt)
{
	switch(state)
	{
		case STATE_IDLE:
			//
			// 1º: Avanzar frame
			// 2º: Si se llegó al último frame, incrementar contador de loops
			// 3º: Si se alcanzó a la cantidad máxima de loops, ir al siguiente nodeIndex
			// 4º: Si se llegó al último nodeIndex, comenzar de nuevo
			//
			if(clock.update(dt))
			{
				StateNode* node = &stateNodes[fireNode];
				
				fireFrame++;
				if(fireFrame >= node->frameIndexesLength)
				{
					fireFrame = 0;
					fireLoops++;
					if(fireLoops >= node->loops)
					{
						fireLoops = 0;
						fireNode++;
						if(fireNode >= stateNodesLength)
						{
							fireNode = 0;
						}
					}
				}
				//
				// Además avanza frame de la torreta
				//
				if(fireNode == 0 || (fireNode == stateNodesLength-1))
				{
					turretFrame = 0;
				}
				else
				{
					turretFrame++;
					if(turretFrame >= indexesTurretFireAttackLength)
					{
						turretFrame = 0;
					}
				}
			}
			break;
		case STATE_DAMAGED:
			if(clock.update(dt))
			{
				state = STATE_DESTROYED;
				return true;
			}
			break;
		case STATE_DESTROYED:
			break;
	}
	return false;
}
int IronNokanaTurret::renderableTurretFrame() const
{
	int frameIndex = -1;
	switch(state)
	{
		case STATE_IDLE:
			frameIndex = BASE_INDEX_TURRET_IDLE + indexesTurretFireAttack[turretFrame];
			break;
		case STATE_DAMAGED:
			frameIndex = BASE_INDEX_TURRET_DAMAGED;
			break;
		case STATE_DESTROYED:
			frameIndex = BASE_INDEX_TURRET_DESTROYED;
			break;
	}
	return frameIndex;
}
int IronNokanaTurret::renderableTurretFlameShotFrame() const
{
	if(state == STATE_IDLE)
	{
		return stateNodes[fireNode].frameIndexes[fireFrame];
	}
	return -1;
}
void IronNokanaTurret::destroy()
{
	if(state != STATE_DESTROYED)
	{
		state = STATE_DAMAGED;
		clock.reset(0.1);
	}
}
bool IronNokanaTurret::isDestroyed() const
{
	return (state == STATE_DESTROYED);
}
