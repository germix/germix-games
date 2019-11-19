////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bradley | M-15A Bradley
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bradley_h___
#define ___Bradley_h___
#include <src/entities/enemies/Enemy.h>
#include <src/___/Hurtable.h>

#include <gamelib/TimeClock.h>

class Sprite;
class BradleyHurtableRect;

class Bradley : public Enemy, public Hurtable
{
	enum STATE
	{
		STATE_IDLE,
		STATE_WALKING_FORWARD,			// Caminar hacia adelante
		STATE_WALKING_BACKWARD,			// Caminar hacia atrás
		STATE_STOPPING,					// Detener caminata
		STATE_PREPARING,				// Preparando los lanzamientos
		STATE_LAUNCHING,				// Generando los lanzamientos
		STATE_WRECKED,
	};
	STATE			state;
	Vector2f		vel;
	Vector2f		accel;
	bool			onGround;
	
	Sprite*			sprite;
	int				spriteFrame;
	TimeClock		spriteClock;
	TimeClock		walkingClock;
	TimeClock		launcherClock;			// Clock entre cada lanzamiento
	
	int				animIndex;
	
	int				launchs;				// Contador de lanzamientos
	bool			waitLaunch;				// Esperar un nuevo lanzamiento
	

	int				health;

	std::vector<HurtableRect*> hits;
	
	Sprite*			SPRITE_IDLE;
	Sprite*			SPRITE_WALKING;
	Sprite*			SPRITE_STOPPING;
	Sprite*			SPRITE_SHOOTING;
	Sprite*			SPRITE_WRECKED;
	Sprite*			SPRITE_SHOOTING_FIRE_1;		// Fuego de la parte inferior
//	Sprite*			SPRITE_SHOOTING_FIRE_2;		// Fuego que sale de cada tubo de lanzamiento (No implementado)
	
	friend class BradleyHurtableRect;
public:
	Bradley(Scene* scene, double x, double y);
	~Bradley();
public:
	void update(double dt);
	void render(Graphics* gr);
	Rectanglef bounds() const;
	Rectanglef bounds(double px, double py) const;
	
	void getHurtableRects(const Rectanglef& area, std::vector<HurtableRect*>& rects) const;
private:

	//
	// Va al estado IDLE
	//
	void idle();
	//
	// Detiene la caminata
	//
	void stop();
	//
	// Comenzar a caminar
	//
	void walk(double vx);
	//
	// Preparar lanzamientos
	//
	void preparing();
	//
	// Disparar
	//
	void launch();
	//
	// Dañar
	//
	void hurt(int damage);
};

#endif
