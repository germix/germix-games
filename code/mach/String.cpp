////////////////////////////////////////////////////////////////////////////////////////////////////
//
// String
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <mach/String.h>

int String::toInt() const
{
	return atoi(c_str());
}
bool String::toBool() const
{
	if(*this == "true")
		return true;
	return false;
}
std::vector<String> String::split(const char* delimiter) const
{
	return split(std::string(delimiter));
}
std::vector<String> String::split(const std::string& delimiter) const
{
	size_t pos = 0;
	std::string s = *this;
	std::string token;
	std::vector<String> v;
	while((pos = s.find(delimiter)) != std::string::npos)
	{
		token = s.substr(0, pos);
		s.erase(0, pos + delimiter.length());
		v.push_back(token);
	}
	if(!s.empty())
	{
		v.push_back(s);
	}
	return v;
}
String String::fromInt(int n)
{
	char sz[32];
	itoa(n, sz, 10);
	return String(sz);
}
