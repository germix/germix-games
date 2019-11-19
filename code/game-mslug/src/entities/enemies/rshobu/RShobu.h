////////////////////////////////////////////////////////////////////////////////////////////////////
//
// RShobu | Helicóptero R-Shobu
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___RShobu_h___
#define ___RShobu_h___
#include <src/entities/enemies/Enemy.h>
#include <src/___/Hurtable.h>

#include <gamelib/TimeClock.h>

class Sprite;
class RShobuHurtableRect;

class RShobu : public Enemy, public Hurtable
{
	enum
	{
		MAX_FRAMES = 7,
		CENTRAL_FRAME = (4-1),
		
		MAX_ATTACKS = 2,
		
		INITIAL_HEALTH = 60,
	};
	Vector2f			velocity;
	Vector2f			acceleration;
	
	int					lookX;		// Dirección de observación X
	
	//
	// ...
	//
	TimeClock			clock;
	bool				clockEnabled;
	int					frameIndex;

	double				valueY;
	double				offsetY;
	
	//
	// Cuerpo del helicóptero
	//
	Sprite*				body;
	
	//
	// Aspas del helicóptero
	//
	Sprite*				blades[MAX_FRAMES];
	int					bladesFrame;
	TimeClock			bladesClock;
	
	//
	// Ataque
	//
	double				timeBetweenBursts;			// Tiempo entre ráfagas
	double				timeBetweenShots;			// Tiempo entre disparos
	int					attacks;
	TimeClock			attackClock;
	int					attackStage;
	
	//
	// Salud/Daño
	//
	int					health;
	
	bool				firstUpdate;
	
	std::vector<HurtableRect*> hits;
	friend class RShobuHurtableRect;
public:
	RShobu(Scene* scene, double x, double y);
	~RShobu();
public:
	void update(double dt);
	void render(Graphics* gr);
	Rectanglef bounds() const;
	Rectanglef bounds(double px, double py) const;
	
	void getHurtableRects(const Rectanglef& area, std::vector<HurtableRect*>& rects) const;
private:
	void hurt(int damage);
	void updateOffsetY(double dt);
};

#endif
