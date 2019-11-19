////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CampaignStagesProvider
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___CampaignStagesProvider_h___
#define ___CampaignStagesProvider_h___
#include <src/stages/StagesProvider.h>

class CampaignStagesProvider : public StagesProvider
{
	const int		max;
	mutable int		index;
public:
	CampaignStagesProvider();
	~CampaignStagesProvider();
public:
	virtual bool hasStage() const;
	virtual TmxMap* getStage() const;
};

#endif
