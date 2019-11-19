////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Ranking
//
// Germán Martínez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/ranking/Ranking.h>

#include <time.h>
#include <stdlib.h>

#include <tinyxml2/tinyxml2.h>

using namespace tinyxml2;

Ranking::Ranking(const char* fname)
{
	const char* s;
	XMLError err;
	XMLDocument doc;
	XMLElement* root;
	XMLElement* elem;
	
	err = doc.LoadFile(fname);
	if(err != XML_SUCCESS)
		return;
	
	root = doc.FirstChildElement("MetalSlugRanking");
	for(elem = root->FirstChildElement("Record"); elem != null; elem = elem->NextSiblingElement())
	{
		std::string name;
		std::string date;
		
		elem->QueryStringAttribute("name", &s);
		name = s;
		elem->QueryStringAttribute("date", &s);
		date = s;
		elem->QueryStringAttribute("score", &s);
		
		records.push_back(RankingRecord(name.c_str(), date.c_str(), atoi(s)));
	}
}
Ranking::~Ranking()
{
}
void Ranking::save()
{
	XMLDocument doc;
	XMLNode* root;
	
	root = doc.NewElement("MetalSlugRanking");
	doc.InsertFirstChild(root);
	
	for(unsigned int i = 0; i < records.size(); i++)
	{
		XMLElement* elem = doc.NewElement("Record");
		
		elem->SetAttribute("name", records[i].name);
		elem->SetAttribute("date", records[i].date);
		elem->SetAttribute("score", records[i].score);
		root->InsertEndChild(elem);
	}
	doc.SaveFile("mslug-ranking.xml");
}
Ranking& Ranking::addRecord(const char* name, unsigned int score)
{
	time_t t = time(NULL);
#ifdef _USE_32BIT_TIME_T
	struct tm* tm = _localtime32((const __time32_t*)&t);
#else
	struct tm* tm = _localtime64((const __time64_t*)&t);
#endif
	char date[32];
	strftime(date, 32, "%d/%m/%Y", tm);
	
	unsigned int i;
	//
	// Eliminar el record que contiene el nombre
	//
	for(i = 0; i < records.size(); i++)
	{
		if(0 == strcmp(records[i].name, name))
		{
			if(records[i].score >= score)
				return *this;
			records.erase(records.begin()+i);
			break;
		}
	}
	//
	// Agregar el nuevo record en la posición adecuada
	//
	for(i = 0; i < records.size(); i++)
	{
		if(records[i].score < score)
			break;
	}
	records.insert(records.begin()+i, RankingRecord(name, date, score));
	
	return *this;
}

