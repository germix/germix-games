////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CampaignRound
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___CampaignRound_h___
#define ___CampaignRound_h___
#include <vector>
#include <string>

class Scene;
class CampaignMap;

class CampaignRound
{
	std::string					boss;
	std::vector<std::string>	stages;
public:
	CampaignRound(const std::string& fname);
	~CampaignRound();
public:
	CampaignMap* getMap(Scene* scene, char stage) const;
	std::string  getBossName() const;
};

#endif
