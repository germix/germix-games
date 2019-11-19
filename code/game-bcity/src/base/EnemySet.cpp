////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EnemySet
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/base/EnemySet.h>
#include <src/Config.h>
#include <src/entities/tanks/EnemyTank.h>

#include <mach/String.h>
#include <mach/Random.h>

#include <tmx/TmxMap.h>

EnemySet::EnemySet()
: types()
, bonus()
, count(0)
, index(0)
{
}
EnemySet::~EnemySet()
{
}
void EnemySet::load(const TmxMap* tmx)
{
	String sEnemies(tmx->getProperty("enemies"));
	
	index = 0;
	count = 0;
	types.clear();
	bonus.clear();
	if(Debug::oneEnemy)
	{
		count = 1;
		types.push_back(Tank::TANK_MODEL_ENEMY_1);
		bonus.push_back(false);
	}
	else
	{
		if(sEnemies.empty())
		{
			printf("WARNING: No se especificó la lista de enemigos");
			//
			// Generar enemigos aleatorios
			//
			Random rand;
			count = 20;
			for(int i = 0; i < count; i++)
			{
				types.push_back(Tank::TANK_MODEL_ENEMY_1 + rand.nextInt(4));
				bonus.push_back(i == (4-1) || i == (11-1) || i == (18-1));
			}
		}
		else
		{
			std::vector<String> s = sEnemies.split(",");
			
			if(s.size() != 20)
			{
				printf("WARNING: La cantidad de enemidos especificados es diferente de 20");
			}
			count = s.size();
			for(int i = 0; i < count; i++)
			{
				types.push_back(Tank::TANK_MODEL_ENEMY_1 + (s[i].toInt()-1));
				bonus.push_back(i == (4-1) || i == (11-1) || i == (18-1));
			}
		}
	}
}
bool EnemySet::isEmpty() const
{
	return count == 0;
}
int EnemySet::getRemanent() const
{
	return count;
}
EnemyTank* EnemySet::getEnemyTank(Map* map, Scene* scene, int x, int y)
{
	count--;
	EnemyTank* tank = new EnemyTank(map, scene, x, y, types[index], bonus[index]);
	index++;
	return tank;
}

