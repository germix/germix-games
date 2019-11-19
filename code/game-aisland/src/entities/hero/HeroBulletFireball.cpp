////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroBulletFireball
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/hero/HeroBulletFireball.h>
#include <src/ResourceManager.h>

#include <gamelib-sprites/SpriteSheet.h>

HeroBulletFireball::HeroBulletFireball(Scene* s, double x, double y, double vx, double vy) : HeroBullet(s, x, y, vx, vy, res.findSpriteSheet("HeroBulletFireball")->getSprite("Idle"))
{
}
HeroBulletFireball::~HeroBulletFireball()
{
}

