////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ShotGun
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___ShotGun_h___
#define ___ShotGun_h___
#include <src/entities/hero/Weapon.h>

class Sound;
class Sprite;

class ShotGun : public Weapon
{
	bool		ready;
	int			animIndex;
	Sound*		shootSound;
	Sprite*		spriteShotGun0;
	Sprite*		spriteShotGun90;
	Sprite*		spriteShotGunDown;
	Sprite*		spriteShotGunCrouched;
public:
	ShotGun();
	~ShotGun()
	{
	}
public:
	virtual int         type() const;
	virtual const char* name() const;
	virtual int         getAmmo(bool firstTime) const;
	virtual bool        canChangeAngleWhileShooting() const;

	virtual void        reset(SpriteSheet* sheet);
	virtual int         update(Scene* scene, Hero* hero, double dt, double posX, double posY, int lookX, int shotAngle, int ammo);
	virtual int         trigger(Scene* scene, Hero* hero, double posX, double posY, int lookX, int shotAngle, int ammo);
private:
	bool                checkAngle(int shotAngle);
	bool                checkSprite(Hero* hero, int shotAngle);};

#endif

