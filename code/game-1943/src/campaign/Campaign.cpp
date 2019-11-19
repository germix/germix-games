////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Campaign
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/campaign/Campaign.h>
#include <src/campaign/CampaignRound.h>

#include <tinyxml2/tinyxml2.h>

Campaign::Campaign()
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement* root;
	tinyxml2::XMLElement* elem;
	
	if(tinyxml2::XML_SUCCESS != doc.LoadFile("1943/campaign/Campaign.xml"))
		return;
	
	if(null != (root = doc.FirstChildElement("Campaign")))
	{
		if(null != (elem = root->FirstChildElement("RoundList")))
		{
			for(elem = elem->FirstChildElement("Round"); elem != null; elem = elem->NextSiblingElement())
			{
				const char* s;
				
				elem->QueryStringAttribute("file", &s);
				rounds.push(s);
			}
		}
	}
}
Campaign::~Campaign()
{
}
CampaignRound* Campaign::nextRound()
{
	if(!rounds.empty())
	{
		CampaignRound* r = new CampaignRound(rounds.front());
		rounds.pop();
		return r;
	}
	return null;
}

