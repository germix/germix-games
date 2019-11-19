////////////////////////////////////////////////////////////////////////////////////////////////////
//
// RShobu | Helic�ptero R-Shobu
//
// Germ�n Mart�nez
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
	
	int					lookX;		// Direcci�n de observaci�n X
	
	//
	// ...
	//
	TimeClock			clock;
	bool				clockEnabled;
	int					frameIndex;

	double				valueY;
	double				offsetY;
	
	//
	// Cuerpo del helic�ptero
	//
	Sprite*				body;
	
	//
	// Aspas del helic�ptero
	//
	Sprite*				blades[MAX_FRAMES];
	int					bladesFrame;
	TimeClock			bladesClock;
	
	//
	// Ataque
	//
	double				timeBetweenBursts;			// Tiempo entre r�fagas
	double				timeBetweenShots;			// Tiempo entre disparos
	int					attacks;
	TimeClock			attackClock;
	int					attackStage;
	
	//
	// Salud/Da�o
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
