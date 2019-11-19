////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CampaignStagesProvider
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/stages/CampaignStagesProvider.h>

#include <tmx/TmxMap.h>

CampaignStagesProvider::CampaignStagesProvider() : max(35), index(1)
{
}
CampaignStagesProvider::~CampaignStagesProvider()
{
}
bool CampaignStagesProvider::hasStage() const
{
	return (index <= max);
}
TmxMap* CampaignStagesProvider::getStage() const
{
	char sz[128];
	sprintf(sz, "bcity/maps/bcity-%02d.tmx", index);
	index++;
	return new TmxMap(sz);
}

