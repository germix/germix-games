////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EntityParameters
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___EntityParameters_h___
#define ___EntityParameters_h___
#include <map>
#include <string>

class EntityParameters
{
public:
	std::map<std::string,std::string> map;
public:
	EntityParameters()
	{
	}
	~EntityParameters()
	{
	}
public:
	const char* get(const char* key, const char* defaultValue) const;
};

#endif
