////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Weapon | Arma
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/Weapon.h>

#include <gamelib-sprites/Sprite.h>

void                Weapon::render(Graphics* gr, double posX, double posY, int hints)
{
	if(sprite != null)
	{
		sprite->render(gr, posX, posY, spriteFrame, hints);
	}
}
