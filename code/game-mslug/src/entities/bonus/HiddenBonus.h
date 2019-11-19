////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HiddenBonus | Clase para generar bonus ocultos
//
// Germán Martínez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___HiddenBonus_h___
#define ___HiddenBonus_h___
#include <src/scene/Entity.h>
#include <src/___/HurtableRect.h>

#include <string>

class HiddenBonus : public Entity, public HurtableRect
{
	int					health;
	const std::string	droppableBonus;
public:
	HiddenBonus(Scene* scene, double x, double y, int health, const char* bonus);
	~HiddenBonus();
public:
	void update(double dt);
	void render(Graphics* gr);
	Rectanglef bounds() const;
	Rectanglef bounds(double px, double py) const;

	void hurt(int damage);
	bool isHurtable() const;
	Rectanglef hurtableRect() const;
};

#endif
