////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Spider
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Spider_h___
#define ___Spider_h___
#include <src/entities/Enemy.h>

class Texture;

class Spider : public Enemy
{
	enum MODE
	{
		MODE_FIXED,
		MODE_MOVABLE,
	};
	int				dir;
	double			min;
	double			max;
	MODE			mode;
	bool			alive;
	Texture*		texture;
	Vector2f		velocity;
public:
	Spider(Scene* s, double x, double y, int min = 0, int max = 0);
	~Spider();
public:
	void update(double dt);
	void render(Graphics* gr);
	void collides(Entity* e);
	Rectanglef getCollisionRectangle() const;
};

#endif
