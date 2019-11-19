////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BossBattleship
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___BossBattleship_h___
#define ___BossBattleship_h___
#include <src/entities/enemies/battleships/Battleship.h>
#include <src/BossStatistics.h>

class BossBattleship : public Battleship, public BossStatistics
{
	class ZigZag
	{
		double		value;
		double		length;
	public:
		ZigZag() : value(0), length(0)
		{
		}
		void init(int len)
		{
			length = len;
		}
		double update(double dt, double velocity);
	};
	ZigZag	zigZag;
	double	referenceX;
	int		initialHealth;
public:
	BossBattleship(Scene* s, double x, double y, const std::string& fname);
	~BossBattleship();
public:
	void update(double dt);
	int getDestroyedPercent() const;
};

#endif
