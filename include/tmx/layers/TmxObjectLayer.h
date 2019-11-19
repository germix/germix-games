////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TmxObjectLayer
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TmxObjectLayer_h___
#define ___TmxObjectLayer_h___
#include <map>
#include <vector>
#include <string>

class TmxObject;
class TmxProperties;

namespace tinyxml2
{
	class XMLElement;
};

class TmxObjectLayer
{
	std::string							name;
	int									width;
	int									height;
	std::vector<TmxObject*>				objects;
	

	std::map<std::string, std::string>	properties;
	friend class TmxMap;
private:
	TmxObjectLayer(tinyxml2::XMLElement* elem);
	~TmxObjectLayer();
public:
	inline std::string                    getName() const { return name; }
	inline int                            getWidth() const { return width; }
	inline int                            getHeight() const { return height; }
	inline const std::vector<TmxObject*>& getObjects() const { return objects; }
	inline std::string                    getProperty(const char* name, const char* defValue = "") const
	{
		std::map<std::string,std::string>::const_iterator it = properties.find(name);
		if(it != properties.end())
			return it->second;
		return defValue;
	}
};

#endif
