////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Energy_Yashichi
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_Energy_Yashichi_h___
#define ___Bonus_Energy_Yashichi_h___
#include <src/Bonus.h>

class Bonus_Energy_Yashichi : public Bonus
{
public:
	Bonus_Energy_Yashichi();
	virtual ~Bonus_Energy_Yashichi();
public:
	virtual void action(Scene* scene, Hero* hero);
};

#endif
