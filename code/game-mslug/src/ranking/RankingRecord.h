////////////////////////////////////////////////////////////////////////////////////////////////////
//
// RankingRecord
//
// Germán Martínez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___RankingRecord_h___
#define ___RankingRecord_h___
#include <string.h>

class RankingRecord
{
public:
	char				name[12+1];
	char				date[10+1];
	unsigned int		score;
public:
	RankingRecord()
	{
	}
	RankingRecord(const RankingRecord& r)
	{
		strcpy(name, r.name);
		strcpy(date, r.date);
		score = r.score;
	}
	RankingRecord(const char* n, const char* d, unsigned int s)
	{
		strncpy(name, n, 12+1);
		strncpy(date, d, 10+1);
		score = s;
	}
	~RankingRecord()
	{
	}
};

#endif
