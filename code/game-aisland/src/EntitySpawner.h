////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EntitySpawner
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___EntitySpawner_h___
#define ___EntitySpawner_h___
#include <list>

class Scene;
class HeroInfo;
class Entity;
class EntityCreationNode;

namespace tinyxml2
{
	class XMLElement;
};

class EntitySpawner
{
	std::list<EntityCreationNode*> creationList;
public:
	EntitySpawner();
	~EntitySpawner();
public:
	void read(tinyxml2::XMLElement* elem);
	void clear();
	void reset(int x);
	void spawnEntities(Scene* scene, HeroInfo& info);
private:
	Entity* createEntity(Scene* scene, EntityCreationNode* node, HeroInfo& info);
};

#endif
