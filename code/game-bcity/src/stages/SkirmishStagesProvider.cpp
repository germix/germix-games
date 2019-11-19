////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SkirmishStagesProvider
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/stages/SkirmishStagesProvider.h>

#include <tmx/TmxMap.h>

SkirmishStagesProvider::SkirmishStagesProvider(const char* tmxName) : tmx(new TmxMap(tmxName))
{
}
SkirmishStagesProvider::~SkirmishStagesProvider()
{
	if(tmx)
		delete tmx;
}
bool SkirmishStagesProvider::hasStage() const
{
	return (tmx != null);
}
TmxMap* SkirmishStagesProvider::getStage() const
{
	TmxMap* ret = tmx;
	tmx = null;
	return ret;
}

