////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Mission
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Mission_h___
#define ___Mission_h___

#include <vector>

class Map;
class MissionMap;
class MissionMapRenderable;

namespace tinyxml2
{
class XMLElement;
};

class Mission
{
public:
	Mission();
	~Mission();
public:
	Map* load(const char* fname);
private:
	void readMap(MissionMap* map, const char* fullPath, char* semiPath, tinyxml2::XMLElement* elem);
	void readMusic(MissionMap* map, const char* fullPath, char* semiPath, tinyxml2::XMLElement* elem);
	void readEntities(MissionMap* map, const char* fullPath, char* semiPath, tinyxml2::XMLElement* elem);
	void readRenderables(MissionMap* map, const char* fullPath, char* semiPath, tinyxml2::XMLElement* elem, const char* elemName, std::vector<MissionMapRenderable*>& renderables);
};

#endif
