////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TestCampaignResult
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TestCampaignResult_h___
#define ___TestCampaignResult_h___
#include <mach/Game.h>

class CampaignResult;

class TestCampaignResult : public Game
{
	CampaignResult* result;
public:
	TestCampaignResult();
	~TestCampaignResult();
public:
	virtual void init(Machine* mach);
	virtual void close(Machine* mach);
	virtual void update(Machine* mach, double dt);
	virtual void render(Machine* mach, Graphics* gr);
};

#endif
