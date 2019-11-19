////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_JewelRed | Bonus joya roja
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_JewelRed_h___
#define ___Bonus_JewelRed_h___
#include <src/entities/bonus/Bonus_Jewel.h>

class Bonus_JewelRed : public Bonus_Jewel
{
public:
	static const char* NAME;
public:
	Bonus_JewelRed(Scene* scene, double x, double y);
	~Bonus_JewelRed();
public:
};

#endif

