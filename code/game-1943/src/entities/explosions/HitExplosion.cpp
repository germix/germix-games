////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HitExplosion
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/explosions/HitExplosion.h>

HitExplosion::HitExplosion(Scene* s, double x, double y, Entity* ref) : NormalExplosion(s, x, y, ref, "explosions.hit", "explosions.hit", 0.08)
{
}
HitExplosion::~HitExplosion()
{
}
