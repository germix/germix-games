////////////////////////////////////////////////////////////////////////////////////////////////////
//
// WeaponHandler
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___WeaponHandler_h___
#define ___WeaponHandler_h___

class Sound;
class Scene;
class Weapon;

class WeaponHandler
{
	Weapon*			weapon;
	bool			strong;
	double			initialTime;
	double			triggerTime;
	double			delayTime;
	double			continuityTime;
	Sound*			sound;
public:
	WeaponHandler();
	~WeaponHandler();
public:
	bool trigger(Scene* scene, double x, double y, bool initialTrigger, double pressedTime, bool isReinforced);
	void setWeapon(Weapon* w);
	Weapon* getWeapon() const
	{
		return weapon;
	}
};

#endif
