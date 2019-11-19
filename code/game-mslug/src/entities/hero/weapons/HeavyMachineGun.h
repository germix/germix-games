////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeavyMachineGun
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___HeavyMachineGun_h___
#define ___HeavyMachineGun_h___
#include <src/entities/hero/Weapon.h>

class Sound;
class Sprite;

class HeavyMachineGun : public Weapon
{
	Sound*				shootSound;
	int					shootSoundChannel;
	Sprite*				spriteHeavyMachineGun0;
	Sprite*				spriteHeavyMachineGun30;
	Sprite*				spriteHeavyMachineGun60;
	Sprite*				spriteHeavyMachineGun90;
	Sprite*				spriteHeavyMachineGunDown;
	Sprite*				spriteHeavyMachineGunCrouched;
	
	int					animIndex;
	int					prevAngle;
	int					currentAngle;
public:
	HeavyMachineGun();
	~HeavyMachineGun()
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
	bool                checkSprite(Hero* hero, int shotAngle);
	void                shoot(Scene* scene, double posX, double posY, int lookX, int shotAngle);
};

#endif

