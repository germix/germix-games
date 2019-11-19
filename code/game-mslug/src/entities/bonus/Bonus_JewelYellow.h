////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_JewelYellow | Bonus joya amarilla
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_JewelYellow_h___
#define ___Bonus_JewelYellow_h___
#include <src/entities/bonus/Bonus_Jewel.h>

class Bonus_JewelYellow : public Bonus_Jewel
{
public:
	static const char* NAME;
public:
	Bonus_JewelYellow(Scene* scene, double x, double y);
	~Bonus_JewelYellow();
public:
};

#endif

