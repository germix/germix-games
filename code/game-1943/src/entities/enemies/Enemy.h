////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Enemy
//
// Germ�n Mart�nez
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
	// Da�ar y retornar verdadero si causa da�o y a�n sige vivo
	virtual bool hurt(int damage) = 0;
	
	// Saber si est� vivo
	virtual  bool isAlive() const = 0;

	// Indica si el enemigo ha sido destruido
	virtual bool isDestroyed() const = 0;

	// Obtener salud
	virtual int  getHealth() const = 0;
	
	// Obtener puntuaci�n por destrucci�n del enemigo
	virtual int  getDestructionScore() const = 0;
};

#endif

