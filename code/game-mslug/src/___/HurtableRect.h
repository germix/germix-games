////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HurtableRect
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___HurtableRect_h___
#define ___HurtableRect_h___
#include <mach/Rectanglef.h>

class HurtableRect
{
public:
	//!
	//! Generar daño a la entidad
	//!
	//! \param damage Poder de daño
	//!
	virtual void hurt(int damage) = 0;
	
	//!
	//! Comprobrar si puede resibir el daño
	//!
	//! \return true ó false
	//!
	virtual bool isHurtable() const = 0;
	
	//!
	//! Rectángulo
	//!
	//! \return Rectángulo de colisión que recibe el daño
	//!
	virtual Rectanglef hurtableRect() const = 0;
};

#endif
