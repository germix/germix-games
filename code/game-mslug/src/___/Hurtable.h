////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Hurtable | Interface que para entidades que tienes rectángulos que pueden recibir daño
//
// Germán Martínez
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
	//! Obtiene los rectángulos que pueden recibir el daño
	//!
	//! \param area		Área de rectángulos
	//! \param rects	Vector de rectángulos
	//!
	virtual void getHurtableRects(const Rectanglef& area, std::vector<HurtableRect*>& rects) const = 0;
};

#endif
