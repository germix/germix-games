////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Ax
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bonus/Bonus_Ax.h>
#include <src/ResourceManager.h>
#include <src/entities/hero/Hero.h>

Bonus_Ax::Bonus_Ax(Scene* s, double x, double y) : Bonus(s, x, y, 8, 15, res.findTexture("Bonus.Ax"))
{
}
Bonus_Ax::~Bonus_Ax()
{
}
void Bonus_Ax::activated(Hero* h)
{
	if(h->getWeapon() == Hero::WEAPON_NONE)
	{
		h->setWeapon(Hero::WEAPON_AX);
	}
}

