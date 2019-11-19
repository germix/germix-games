////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CampaignMap
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___CampaignMap_h___
#define ___CampaignMap_h___
#include <string>
#include <vector>

class Scene;
class Entity;
class BossStatistics;

class Texture;
class Graphics;

class TmxImageLayer;
class TmxObjectLayer;

class CampaignMap
{
	enum STATE
	{
		STATE_INIT,
		STATE_COMBAT,
		STATE_ENDED,
	};
	STATE								state;
	int									width;
	int									height;
	
	double								offset;

	Scene*								scene;
	std::vector<std::vector<Entity*>>	entities;

	Texture*							oceanTexture;
	Texture*							cloudsTexture;

	BossStatistics*						bossStatistics;
public:
	CampaignMap(Scene* scene, const std::string& fname);
	~CampaignMap();
public:
	void init();
	void update(double dt);
	void render(Graphics* gr);
	bool isEnded() const;
	const BossStatistics* getBossStatistics() const;
private:
	void initImageLayers(const std::vector<TmxImageLayer*>& layers);
	void readObjectLayer(const TmxObjectLayer* layer);
	void initObjectLayers(const std::vector<TmxObjectLayer*>& layers);
	void insertEntitiesInScene(double dt, double oldOffset, double newOffset);

	void addObjectToDataList(int startY, Entity* e);
};

#endif
