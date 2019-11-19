////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bonus_Chicken | Bonus pollo al horno
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Bonus_Chicken_h___
#define ___Bonus_Chicken_h___
#include <src/entities/bonus/Bonus.h>

class Bonus_Chicken : public Bonus
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
	Bonus_Chicken(Scene* scene, double x, double y);
	~Bonus_Chicken();
protected:
	void animate(double dt);
	void activate(Hero* hero);
};

#endif


