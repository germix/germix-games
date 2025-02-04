////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BonusHelmet
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___BonusHelmet_h___
#define ___BonusHelmet_h___
#include <src/entities/Bonus.h>

class BonusHelmet : public Bonus
{
public:
	BonusHelmet(Map* m, Scene* s, int x, int y);
	~BonusHelmet();
protected:
	virtual void activated(HeroTank* hero);
};

#endif
