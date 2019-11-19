////////////////////////////////////////////////////////////////////////////////////////////////////
//
// String
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___String_h___
#define ___String_h___
#include <string>
#include <string.h>
#include <vector>

class String : public std::string
{
public:
	String() : std::string()
	{
	}
	String(const char* s) : std::string(s)
	{
	}
	String(const std::string& s) : std::string(s)
	{
	}
public:
	int toInt() const;
	bool toBool() const;

	String toLower() const
	{
		String s(c_str());
		strlwr((char*)s.c_str());
		return s;
	}
	String toUpper() const
	{
		String s(c_str());
		strupr((char*)s.c_str());
		return s;
	}
	std::vector<String> split(const char* delimiter) const;
	std::vector<String> split(const std::string& delimiter) const;
public:
	static String fromInt(int n);
};

typedef std::vector<String> StringList;

#endif
