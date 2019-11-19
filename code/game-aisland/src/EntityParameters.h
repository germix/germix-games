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
#include <mach/String.h>

class EntityParameters
{
public:
	std::map<String,String> map;
public:
	EntityParameters()
	{
	}
	~EntityParameters()
	{
	}
public:
	String get(const char* key, const char* defaultValue) const;
	void insert(const char* key, const char* value)
	{
		map[key] = value;
	}
};

#endif
