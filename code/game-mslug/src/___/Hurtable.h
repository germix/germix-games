////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Hurtable | Interface que para entidades que tienes rect�ngulos que pueden recibir da�o
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Hurtable_h___
#define ___Hurtable_h___
#include <vector>

class HurtableRect;

class Hurtable
{
public:
	//!
	//! Obtiene los rect�ngulos que pueden recibir el da�o
	//!
	//! \param area		�rea de rect�ngulos
	//! \param rects	Vector de rect�ngulos
	//!
	virtual void getHurtableRects(const Rectanglef& area, std::vector<HurtableRect*>& rects) const = 0;
};

#endif
