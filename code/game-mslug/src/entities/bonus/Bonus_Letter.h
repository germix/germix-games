////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Letter | Bonus carta de amor
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_Letter_h___
#define ___Bonus_Letter_h___
#include <src/entities/bonus/Bonus.h>

class Bonus_Letter : public Bonus
{
	enum STATE
	{
		STATE_FALLING,
		STATE_STOPPING,
		STATE_NOTHING,
	};
	static const int framesFalling[];
	static const int framesStooping[];

	static const int framesFallingLength;
	static const int framesStoopingLength;

	STATE state;
	int frameIndex;
public:
	static const char* NAME;
public:
	Bonus_Letter(Scene* scene, double x, double y);
	~Bonus_Letter();
protected:
	void animate(double dt);
	void activate(Hero* hero);
};

#endif

