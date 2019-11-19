////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Weapon
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Weapon_h___
#define ___Weapon_h___

class Scene;

class Weapon
{
public:
	Weapon() {}
	virtual ~Weapon() {}
public:
	virtual const char* name() const = 0;			// Nombre del arma
	virtual double delay() const = 0;				// Tiempo de retraso
	virtual double continuity() const = 0;			// Límite de disparo continuo
	virtual void shoot(Scene* scene, double x, double y, bool isStrong, bool isReinforced) = 0;
};

#endif
