////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TmxImageLayer
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TmxImageLayer_h___
#define ___TmxImageLayer_h___
#include <map>
#include <string>

namespace tinyxml2
{
	class XMLElement;
};

class TmxImageLayer
{
	std::string							name;
	std::string							image;
	int									width;
	int									height;

	std::map<std::string, std::string>	properties;
	friend class TmxMap;
private:
	TmxImageLayer(tinyxml2::XMLElement* elem);
	~TmxImageLayer();
public:
	inline std::string    getName() const { return name; }
	inline std::string    getImage() const { return image; }
	inline int            getWidth() const { return width; }
	inline int            getHeight() const { return height; }
	inline std::string    getProperty(const char* name, const char* defValue = "") const
	{
		std::map<std::string,std::string>::const_iterator it = properties.find(name);
		if(it != properties.end())
			return it->second;
		return defValue;
	}
};

#endif
