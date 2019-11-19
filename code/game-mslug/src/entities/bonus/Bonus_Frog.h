////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Frog | Bonus rana
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_Frog_h___
#define ___Bonus_Frog_h___
#include <src/entities/bonus/Bonus.h>

class Bonus_Frog : public Bonus
{
	int animationStepIndex;
	int animationStepFrame;

	static const int frames1[];
	static const int frames2[];
	static const int frames3[];
	static const int frames4[];
	static struct AnimationStep
	{
		double			delay;
		int				count;
		const int*		frames;
	}animationSteps[];
	static const int animationStepsLength;
public:
	static const char* NAME;
public:
	Bonus_Frog(Scene* scene, double x, double y);
	~Bonus_Frog();
public:
	Rectanglef bounds(double px, double py) const;
//	void collide(Entity* other);
protected:
	void animate(double dt);
	void activate(Hero* hero);
};

#endif
