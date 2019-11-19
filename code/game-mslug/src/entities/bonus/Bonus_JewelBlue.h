////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_JewelBlue | Bonus joya azul
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_JewelBlue_h___
#define ___Bonus_JewelBlue_h___
#include <src/entities/bonus/Bonus_Jewel.h>

class Bonus_JewelBlue : public Bonus_Jewel
{
public:
	static const char* NAME;
public:
	Bonus_JewelBlue(Scene* scene, double x, double y);
	~Bonus_JewelBlue();
public:
};

#endif
