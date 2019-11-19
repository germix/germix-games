////////////////////////////////////////////////////////////////////////////////////////////////////
//
// RocketLauncher
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___RocketLauncher_h___
#define ___RocketLauncher_h___
#include <src/entities/hero/Weapon.h>

class Sound;
class Sprite;

class RocketLauncher : public Weapon
{
	bool		ready;
	int			animIndex;
	Sound*		shootSound;
	Sprite*		spriteRocketLauncher0;
	Sprite*		spriteRocketLauncher90;
	Sprite*		spriteRocketLauncherDown;
	Sprite*		spriteRocketLauncherCrouched;
public:
	RocketLauncher();
	~RocketLauncher()
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
	bool                checkSprite(Hero* hero, int shotAngle);
};

#endif

