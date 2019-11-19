#ifndef ___UTILS_H___
#define ___UTILS_H___
#include <map>
#include <string>
#include <tinyxml2/tinyxml2.h>

void readProperties(std::map<std::string,std::string>& properties, tinyxml2::XMLElement* elem);

#endif
