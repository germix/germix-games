////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CampaignRound
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/campaign/CampaignRound.h>
#include <src/campaign/CampaignMap.h>

#include <tinyxml2/tinyxml2.h>

CampaignRound::CampaignRound(const std::string& fname)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement* root;
	tinyxml2::XMLElement* elem;
	const char* s;
	
	if(tinyxml2::XML_SUCCESS != doc.LoadFile(("1943/campaign/" + fname).c_str()))
		return;
	
	if(null != (root = doc.FirstChildElement("CampaignRound")))
	{
		root->QueryStringAttribute("target", &s);
		boss = s;

		for(elem = root->FirstChildElement("Stage"); elem != null; elem = elem->NextSiblingElement())
		{
			elem->QueryStringAttribute("map", &s);
			stages.push_back(s);
		}
	}
}
CampaignRound::~CampaignRound()
{
}
CampaignMap* CampaignRound::getMap(Scene* scene, char stage) const
{
	return new CampaignMap(scene, stages[stage - 'A']);
}
std::string  CampaignRound::getBossName() const
{
	return boss;
}
