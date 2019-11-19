////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MasknellSubordinate | Helic�ptero Masknell subordinado en la flota
//
// Germ�n Mart�nez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___MasknellSubordinate_h___
#define ___MasknellSubordinate_h___
#include <src/entities/enemies/masknell/Masknell.h>

class MasknellSubordinate : public Masknell
{
public:
	MasknellSubordinate(Scene* scene, double x, double y, Route* r);
	~MasknellSubordinate();
public:
	void update(double dt);
};

#endif
