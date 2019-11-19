////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MosqueTower | Torre de mezquita
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___MosqueTower_h___
#define ___MosqueTower_h___
#include <gamelib/TimeClock.h>
#include <src/___/HurtableRect.h>

#include <mach/Point.h>
#include <mach/Rectanglef.h>

class Mosque;
class Sprite;
class Graphics;

class MosqueTower : public HurtableRect
{
	enum STATE
	{
		STATE_NOTHING,
		STATE_FIRING,			// Disparando
		STATE_FREEZED1,			// Momento de espera luego del disparo
		STATE_TURN,				// Girar hacia el otro lado
		STATE_FREEZED2,			// Momento de espera hasta el próximo disparo
		STATE_DESTROYED,		// Destruido
	};
	STATE				state;

	Point				pos;
	Sprite*				sprite;
	
	int					health;
	bool				damaged;
	double				damagedTime;
	
	int					towerFrame;
	int					operatorFrame;
	
	TimeClock			clock;
	int					index;
	
	Mosque*				mosque;

	const Point			doorOffset;
	friend class Mosque;
public:
	MosqueTower(int x, int y, Mosque* m, Sprite* s);
	~MosqueTower();
public:
	void init();
	void open();
	void update(double dt);
	void render(Graphics* gr, unsigned int doorFrame);
	bool isDestroyed() const;
	Rectanglef getDomeRectangle() const;

	void hurt(int damage);
	bool isHurtable() const;
	Rectanglef hurtableRect() const;
};

#endif
