////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TmxObject
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TmxObject_h___
#define ___TmxObject_h___
#include <map>
#include <string>

class TmxProperties;

namespace tinyxml2
{
	class XMLElement;
};

class TmxObject
{
	std::string							type;
	int									x;
	int									y;
	int									width;
	int									height;
	std::string							polyline;
	bool								visible;
	std::map<std::string,std::string>	properties;
public:
	TmxObject(tinyxml2::XMLElement* elem);
	~TmxObject();
public:
	inline std::string getType() const { return type; }
	inline int         getX() const { return x; }
	inline int         getY() const { return y; }
	inline int         getWidth() const { return width; }
	inline int         getHeight() const { return height; }
	inline std::string getPolyline() const { return polyline; }
	inline bool        isVisible() const { return visible; }
	inline std::string getProperty(const char* name, const char* defValue = "") const
	{
		std::map<std::string,std::string>::const_iterator it = properties.find(name);
		if(it != properties.end())
			return it->second;
		return defValue;
	}
};

#endif
