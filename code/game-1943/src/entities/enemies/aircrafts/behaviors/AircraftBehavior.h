////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AircraftBehavior
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___AircraftBehavior_h___
#define ___AircraftBehavior_h___

class Sprite;
class Vector2f;

class AircraftBehavior
{
public:
	AircraftBehavior() {}
	virtual ~AircraftBehavior() {}
public:
	// Actualizar
	virtual void update(Vector2f& pos, double dt, Sprite* sprite, int& spriteIndex) = 0;
	
	// Nivel en el aire
	virtual int  getLevel() const = 0;
	
	// Comprobar si se puede remover
	virtual bool isRemovable() const = 0;
};

#endif
