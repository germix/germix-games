////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Knifeable | Interface que sirve para las entidades que se pueden atacar con cuchillo
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Knifeable_h___
#define ___Knifeable_h___

class Knifeable
{
public:
	//!
	//! Generar daño a la entidad con cuchillo (Apuñalar)
	//!
	//! \param damage Poder de daño
	//!
	virtual void knifeHurt(int damage) = 0;
	
	//!
	//! Comprobrar si puede resibir el daño
	//!
	//! \return true ó false
	//!
	virtual bool isKnifeHurtable() const = 0;
};

#endif
