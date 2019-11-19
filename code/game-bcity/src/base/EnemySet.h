////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EnemySet
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___EnemySet_h___
#define ___EnemySet_h___
#include <list>
#include <vector>

class TmxMap;

class Map;
class Scene;
class EnemyTank;

class EnemySet
{
	std::vector<int>		types;
	std::vector<bool>		bonus;
	int						count;
	int						index;
public:
	EnemySet();
	~EnemySet();
public:
	void load(const TmxMap* tmx);
	bool isEmpty() const;
	int  getRemanent() const;
	EnemyTank* getEnemyTank(Map* map, Scene* scene, int x, int y);
};

#endif
