////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Ranking
//
// Germán Martínez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Ranking_h___
#define ___Ranking_h___
#include <vector>

#include <src/ranking/RankingRecord.h>

class Ranking
{
	std::vector<RankingRecord> records;
public:
	Ranking(const char* fname);
	~Ranking();
public:
	void save();
	Ranking& addRecord(const char* name, unsigned int score);
	const std::vector<RankingRecord> getRecords() const { return records; }
};

#endif
