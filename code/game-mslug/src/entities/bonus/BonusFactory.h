////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BonusFactory | Factor�a de bonus
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___BonusFactory_h___
#define ___BonusFactory_h___

class Bonus;
class Scene;

class BonusFactory
{
public:
	static const char* bonus[];
	static const int   bonusLength;
public:
	static Bonus* create(Scene* scene, double px, double py, const char* name);
};

#endif
