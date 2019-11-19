////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroBullet
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/bullets/HeroBullet.h>
#include <src/entities/tanks/HeroTank.h>

HeroBullet::HeroBullet(Map* m, Scene* s, int x, int y, Direction dir, HeroTank* shooter, bool speedy, bool strong) : Bullet(m, s, x, y, dir, shooter, (speedy ? 0.005 : 0.01), strong)
{
}
HeroBullet::~HeroBullet()
{
}
