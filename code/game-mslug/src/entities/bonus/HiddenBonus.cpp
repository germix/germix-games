////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HiddenBonus | Clase para generar bonus ocultos
//
// Germán Martínez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/HiddenBonus.h>
#include <src/Debug.h>
#include <src/scene/Scene.h>
#include <src/entities/bonus/Bonus.h>
#include <src/entities/bonus/BonusFactory.h>

#include <mach/Graphics.h>

HiddenBonus::HiddenBonus(Scene* scene, double x, double y, int _health, const char* _bonus) : Entity(scene, x, y)
, health(_health)
, droppableBonus(_bonus)
{
}
HiddenBonus::~HiddenBonus()
{
}
void HiddenBonus::update(double dt)
{
	if(pos.x+8 < scene->getSceneRect().getMinX())
	{
		removable = true;
	}
}
void HiddenBonus::render(Graphics* gr)
{
	if(Debug::showBonusRects)
	{
		gr->drawRect(bounds(), Debug::colorBonusRects);
	}
}
Rectanglef HiddenBonus::bounds() const
{
	return bounds(pos.x, pos.y);
}
Rectanglef HiddenBonus::bounds(double px, double py) const
{
	return Rectanglef(px-8, py, 16, 16);
}
void HiddenBonus::hurt(int damage)
{
	health -= damage;
	if(health <= 0)
	{
		scene->addEntity(BonusFactory::create(scene, pos.x, pos.y-8, droppableBonus.c_str()));
		removable = true;
	}
}
bool HiddenBonus::isHurtable() const
{
	return true;
}
Rectanglef HiddenBonus::hurtableRect() const
{
	return bounds();
}

