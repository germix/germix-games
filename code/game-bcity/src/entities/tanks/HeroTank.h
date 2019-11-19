////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HeroTank
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___HeroTank_h___
#define ___HeroTank_h___
#include <src/entities/Tank.h>
#include <src/base/SpawnerBlink.h>

#include <vector>

#include <gamelib/TimeClock.h>

class Player;
class EnemyTank;
class HeroBullet;

class HeroTank : public Tank
{
public:
	enum
	{
		STAR_NONE = 0,
		STAR_SPEED = 1,			// Más velocidad de la bala
		STAR_REPEAT = 2,		// Se puede disparar más balas
		STAR_STRONG = 3,		// La bala puede romper metal
		
		LIMIT_STARS = STAR_STRONG,
	};
	enum
	{
		MAX_VICTIMS_TYPES = 4,
	};
	enum STATE
	{
		STATE_NONE,
		STATE_STARTING,
		STATE_PLAYING,
		STATE_DEAD,
	};
	
	class KeyMovement
	{
	public:
		int			key;
		Direction	dir;
		int			dx;
		int			dy;
		
		bool		down;
		bool		firstDown;
	public:
		KeyMovement()
		{
		}
		KeyMovement(int ___key, Direction ___dir, int ___dx, int ___dy) : key(___key), dir(___dir), dx(___dx), dy(___dy), down(false), firstDown(false)
		{
		}
	public:
		KeyMovement& operator = (const KeyMovement& o)
		{
			dx = o.dx;
			dy = o.dy;
			key = o.key;
			dir = o.dir;
			down = o.down;
			firstDown = o.firstDown;
			return *this;
		}
	};
	
	//
	// Estado
	//
	STATE				state;
	int					lifes;
	int					stars;

	//
	// Escudo
	//
	bool				hasHelmet;
	int					helmetIndex;
	TimeClock			helmetBlinkClock;
	TimeClock			helmetDurationClock;
	
	//
	// Víctimas
	//
	int					victims[MAX_VICTIMS_TYPES];		// Contador de víctimas (según el tipo de tanques)
//	int					totalVictims;					// Contador de víctimas totales
	
	//
	// Disparar
	//
	HeroBullet*			bullet;							// Última bala disparada
	bool				canShoot;
	TimeClock			shootClock;
	
	//
	// Movimiento
	//
	TimeClock			moveClock;
	
	//
	// Respawning
	//
	SpawnerBlink		blink;
	const int			initialX;
	const int			initialY;
	
	//
	// Jugador
	//
	Player*				player;
	
	KeyMovement			keys[4];
public:
	HeroTank(Player* p, Map* m, Scene* s, int x, int y, int color);
	~HeroTank();
public:
	void update(double dt);
	void render(Graphics* gr);
	Rectangle getCollisionRectangle()
	{
		return (state == STATE_PLAYING) ? Rectangle(x,y,width,height) : Rectangle();
	}
public:
	void start();
	void damage();
	void addStar();
	void addLife();
	void addScore(int s);
	void addVictim(EnemyTank* victim);
	void activateHelmet(double seconds);
	bool isAlive() const;
	int getScore() const;
	int getLifes() const;
	Player* getPlayer() const;
	const int* getVictims() const;
	
	void releaseBullet()
	{
		bullet = null;
	}
private:
	void shoot();
	void updateStateNone(double dt);
	void updateStateDead(double dt);
	void updateStatePlaying(double dt);
	void updateStateStarting(double dt);
};

#endif
