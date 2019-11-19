////////////////////////////////////////////////////////////////////////////////////////////////////
//
// WeaponHandler | Controlador de arma
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___WeaponHandler_h___
#define ___WeaponHandler_h___
#include <vector>

class Hero;
class Scene;
class Weapon;
class Graphics;
class SpriteSheet;

class WeaponHandler
{
	static const double NO_ANGLE;
	static const double MIN_ANGLE;
	static const double MAX_ANGLE;
private:
	Hero*					hero;
	Weapon*					weapon;
	std::vector<Weapon*>	weaponList;
	int						weaponIndex;
	int						ammo;
	
	double					step;				// �ngulo de incremento o decremento
	double					shotAngle;			// �ngulo de disparo
	double					prevShotAngle;		// �ngulo de disparo anterior
public:
	WeaponHandler(Hero* h);
	~WeaponHandler();
public:
	int			getAmmo() const { return ammo; }
	Weapon*		getWeapon() const { return weapon; }
	bool		isShooting() const;
	double		getShotAngle() const { return shotAngle; }
	double		getPreviousShotAngle() const { return prevShotAngle; }
	
	int			setWeapon(SpriteSheet* sheet, int widx);
	void		setShotAngle(int angle);

	void		stop();
	void		reset(SpriteSheet* sheet);
	void		render(Graphics* gr, int posX, int posY, int hints);
	bool		update(Scene* scene, double dt, double posX, double posY, int lookX, int lookY);
	bool		trigger(Scene* scene, double posX, double posY, int lookX);
private:
	void		updateAngle(double dt, int lookY);
};

#endif
