////////////////////////////////////////////////////////////////////////////////////////////////////
//
// JumpSpring
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___JumpSpring_h___
#define ___JumpSpring_h___
#include <src/entities/platforms/Platform.h>

class Sprite;

class JumpSpring : public Platform
{
public:
	enum STATE
	{
		STATE_DOWN,
		STATE_UP,
	};
private:
	bool		jump;
	int			state;
	Sprite*		sprite;
public:
	JumpSpring(Scene* s, double x, double y, int initialState = STATE_DOWN);
	~JumpSpring();
public:
	void update(double dt);
	void render(Graphics* gr);
	Rectanglef bounds() const;
	Rectanglef bounds(double px, double py) const;
	Rectanglef getCollisionRectangle() const;
public:
	void setHero(Hero* h);
};

#endif
