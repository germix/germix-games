////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_JewelYellow | Bonus joya amarilla
//
// Germ�n Mart�nez
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

