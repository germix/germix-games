////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TmxPatternLayer
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TmxPatternLayer_h___
#define ___TmxPatternLayer_h___
#include <map>
#include <string>
#include <vector>

namespace tinyxml2
{
	class XMLElement;
};

class TmxPatternLayer
{
	std::string							name;
	int									width;
	int									height;
	std::vector<int>					ids;
	
	std::map<std::string, std::string>	properties;

	friend class TmxMap;
private:
	TmxPatternLayer(tinyxml2::XMLElement* elem);
	~TmxPatternLayer();
public:
	inline const std::vector<int>& getIds() const { return ids; }
	inline std::string             getName() const { return name; }
	inline std::string             getProperty(const char* name, const char* defValue = "") const
	{
		std::map<std::string,std::string>::const_iterator it = properties.find(name);
		if(it != properties.end())
			return it->second;
		return defValue;
	}
};

#endif
