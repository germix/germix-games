////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HurtableRect
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___HurtableRect_h___
#define ___HurtableRect_h___
#include <mach/Rectanglef.h>

class HurtableRect
{
public:
	//!
	//! Generar da�o a la entidad
	//!
	//! \param damage Poder de da�o
	//!
	virtual void hurt(int damage) = 0;
	
	//!
	//! Comprobrar si puede resibir el da�o
	//!
	//! \return true � false
	//!
	virtual bool isHurtable() const = 0;
	
	//!
	//! Rect�ngulo
	//!
	//! \return Rect�ngulo de colisi�n que recibe el da�o
	//!
	virtual Rectanglef hurtableRect() const = 0;
};

#endif
