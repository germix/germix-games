////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Knifeable | Interface que sirve para las entidades que se pueden atacar con cuchillo
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Knifeable_h___
#define ___Knifeable_h___

class Knifeable
{
public:
	//!
	//! Generar da�o a la entidad con cuchillo (Apu�alar)
	//!
	//! \param damage Poder de da�o
	//!
	virtual void knifeHurt(int damage) = 0;
	
	//!
	//! Comprobrar si puede resibir el da�o
	//!
	//! \return true � false
	//!
	virtual bool isKnifeHurtable() const = 0;
};

#endif
