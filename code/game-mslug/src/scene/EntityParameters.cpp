////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EntityParameters
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/scene/EntityParameters.h>

const char* EntityParameters::get(const char* key, const char* defaultValue) const
{
	std::map<std::string,std::string>::const_iterator it = map.find(key);
	if(it != map.end())
	{
		return (*it).second.c_str();
	}
	return defaultValue;
}
