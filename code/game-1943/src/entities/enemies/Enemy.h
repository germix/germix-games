////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Enemy
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Enemy_h___
#define ___Enemy_h___
#include <src/Entity.h>
#include <src/Shootable.h>

class Enemy : public Entity, public Shootable
{
public:
	Enemy(Scene* s, double x, double y);
	~Enemy();
public:
	// Dañar y retornar verdadero si causa daño y aún sige vivo
	virtual bool hurt(int damage) = 0;
	
	// Saber si está vivo
	virtual  bool isAlive() const = 0;

	// Indica si el enemigo ha sido destruido
	virtual bool isDestroyed() const = 0;

	// Obtener salud
	virtual int  getHealth() const = 0;
	
	// Obtener puntuación por destrucción del enemigo
	virtual int  getDestructionScore() const = 0;
};

#endif

