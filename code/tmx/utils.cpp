#include "utils.h"

void readProperties(std::map<std::string,std::string>& properties, tinyxml2::XMLElement* elem)
{
	const char* s;
	if(null != (elem = elem->FirstChildElement("properties")))
	{
		for(elem = elem->FirstChildElement("property"); elem != null; elem = elem->NextSiblingElement())
		{
			elem->QueryStringAttribute("name", &s);
			std::string name = s;
			elem->QueryStringAttribute("value", &s);
			std::string value = s;
			
			properties[name] = value;
		}
	}
}
