////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MissionMap
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___MissionMap_h___
#define ___MissionMap_h___
#include <src/scene/Map.h>
#include <src/scene/EntityParameters.h>

#include <mach/Color.h>

#include <vector>

class Music;
class Image;
class Enemy;
class CollisionInfo;
class MissionMapRenderable;

class MissionMap : public Map
{
	class EntitySpawnNode
	{
	public:
		int					x;
		int					y;
		EntitySpawnNode*	prev;
		EntitySpawnNode*	next;
		bool				boss;
		EntityParameters	params;
		const char*			type;
	public:
		EntitySpawnNode(const char* type);
		~EntitySpawnNode();
	};
	struct
	{
		EntitySpawnNode*	head;
		EntitySpawnNode*	tail;
	}entitySpawner;

	int									width;
	int									height;
	int*								slopes;
	Image*								terrain;

	std::vector<MissionMapRenderable*>	backgrounds;
	std::vector<MissionMapRenderable*>	foregrounds;
	Color								backgroundColor;

	Enemy*								finalBoss;

	Music*								missionMusic;
	bool								isPlayingMusic;
	friend class Mission;
public:
	MissionMap()
		: width(0)
		, height(0)
		, slopes(0)
		, terrain(0)
	{
		entitySpawner.head = null;
		entitySpawner.tail = null;
		
		finalBoss = null;
		
		missionMusic = null;
		isPlayingMusic = false;
	}
	~MissionMap();
public:
	virtual int getWidth() const { return width; }
	virtual int getHeight() const { return height; }
	virtual Vector2f getSuggestedSceneScroll(Entity* entity) const;
	virtual void update(Scene* scene, double dt);
	virtual void renderBackground(Graphics* gr, int sx, int sy) const;
	virtual void renderForeground(Graphics* gr, int sx, int sy) const;

	virtual unsigned int checkCollision(
								Entity* entity,
								Vector2f& newPosition,
								Vector2f& newVelocity,
								const Vector2f& oldPosition,
								const Vector2f& oldVelocity,
								unsigned int terrainType) const;
public:
private:
	Entity* newEntity(Scene* scene, EntitySpawnNode* node);
};

#endif
