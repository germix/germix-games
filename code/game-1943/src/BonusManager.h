////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BonusManager
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___BonusManager_h___
#define ___BonusManager_h___
#include <mach/String.h>

class Bonus;

class BonusManager
{
public:
	static void init();
	static void clear();
	static Bonus* findBonus(const String& name);
};

#endif
