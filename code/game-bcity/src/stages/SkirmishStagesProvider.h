////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SkirmishStagesProvider
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___SkirmishStagesProvider_h___
#define ___SkirmishStagesProvider_h___
#include <src/stages/StagesProvider.h>

class SkirmishStagesProvider : public StagesProvider
{
	mutable TmxMap* tmx;
public:
	SkirmishStagesProvider(const char* tmxName);
	~SkirmishStagesProvider();
public:
	virtual bool hasStage() const;
	virtual TmxMap* getStage() const;
};

#endif
