////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_h___
#define ___Bonus_h___

class Hero;
class Scene;
class Sprite;

class Bonus
{
	const char* _name;
	Sprite*     _sprite;
public:
	Bonus(const char* name, const char* spriteName);
	virtual ~Bonus();
public:
	const char* name() const { return _name; }
	Sprite* sprite() const { return _sprite; }
	virtual void action(Scene* scene, Hero* hero) = 0;
};

#endif
