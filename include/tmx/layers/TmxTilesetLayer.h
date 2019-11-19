////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TmxTilesetLayer
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TmxTilesetLayer_h___
#define ___TmxTilesetLayer_h___
#include <map>
#include <string>

namespace tinyxml2
{
	class XMLElement;
};

class TmxTilesetLayer
{
	int									firstgid;
	std::string							name;
	int									tileWidth;
	int									tileHeight;
	std::string							imageName;
	int									imageWidth;
	int									imageHeight;
	
	std::map<std::string, std::string>	properties;

	friend class TmxMap;
private:
	TmxTilesetLayer(tinyxml2::XMLElement* elem);
	~TmxTilesetLayer();
public:
	inline int         getFirstGid() const { return firstgid; }
	inline std::string getName() const { return name; }
	inline std::string getImageName() const { return imageName; }
	inline std::string getProperty(const char* name, const char* defValue = "") const
	{
		std::map<std::string,std::string>::const_iterator it = properties.find(name);
		if(it != properties.end())
			return it->second;
		return defValue;
	}
};

#endif
