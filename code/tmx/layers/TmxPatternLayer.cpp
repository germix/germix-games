////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TmxPatternLayer
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <tmx/layers/TmxPatternLayer.h>

#include "../utils.h"
#include <tinyxml2/tinyxml2.h>

TmxPatternLayer::TmxPatternLayer(tinyxml2::XMLElement* elem)
{
	const char* s;
	
	readProperties(properties, elem);
	
	elem->QueryStringAttribute("name", &s);
	name = s;
	
	elem->QueryIntAttribute("width", &width);
	elem->QueryIntAttribute("height", &height);
	
	if(null != (elem = elem->FirstChildElement("data")))
	{
		elem->QueryStringAttribute("encoding", &s);
		
		if(0 == strcmp(s, "csv"))
		{
			s = elem->GetText();
			while(!isalnum(*s) && *s != 0)
			{
				s++;
			}
			while(*s != 0)
			{
				ids.push_back(atoi(s));
				while(isalnum(*s)) {s++; } s++; while(!isalnum(*s) && *s != 0) {s++; }
			}
		}
	}
}
TmxPatternLayer::~TmxPatternLayer()
{
}

