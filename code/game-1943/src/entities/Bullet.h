////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bullet
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bullet_h___
#define ___Bullet_h___
#include <src/Entity.h>

class Sprite;

class Bullet : public Entity
{
protected:
	int				frame;
	Sprite*			sprite;
	const double	angle;
	const double	velocity;
	bool			destroyed;
public:
	Bullet(Scene* s, double x, double y, Sprite* sprite, double angle, double velocity);
	~Bullet();
public:
	Rectanglef rect() const;
	bool isDestroyed() const
	{
		return destroyed;
	}
	void render(Graphics* gr);
};

#endif
