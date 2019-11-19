////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MosqueRocket | Cohete lanzado por la torre de la mezquita
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___MosqueRocket_h___
#define ___MosqueRocket_h___
#include <src/entities/projectiles/EnemyProjectile.h>
#include <src/___/HurtableRect.h>

class Sprite;
class Mosque;

class MosqueRocket : public EnemyProjectile, public HurtableRect
{
	Mosque*				mosque;
	Vector2f			vel;
	Vector2f			accel;
	Vector2f			oldPos;

	Sprite*				sprites[3];
	double				elapsed;
	int					lastFrame;				// Sirve para evitar un mal calculo de frame,
												// cuando el ángulo entre la vieja posición y la actual es 0
	int					currentFrame;
	int					currentSprite;
	
	double				currentAngle;
	double				currentDistance;
	double				distanceTraveled;
public:
	MosqueRocket(Scene* scene, double x, double y, Mosque* m);
	~MosqueRocket();
public:
	void update(double dt);
	void render(Graphics* gr);
	Rectanglef bounds() const;
	Rectanglef bounds(double px, double py) const;

	void collide(Entity* other);
	Rectanglef collisionRect() const;

	void hurt(int damage);
	bool isHurtable() const;
	Rectanglef hurtableRect() const;
};

#endif
