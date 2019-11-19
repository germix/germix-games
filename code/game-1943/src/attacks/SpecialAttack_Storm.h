////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SpecialAttack_Storm
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___SpecialAttack_Storm_h___
#define ___SpecialAttack_Storm_h___
#include <src/attacks/SpecialAttack.h>
#include <gamelib/TimeClock.h>

class Scene;
class Texture;

class SpecialAttack_Storm : public SpecialAttack
{
	bool		finished;
	
	int			fadingDir;
	int			fadingAlpha;
	TimeClock	fadingClock;
	
	Texture*	textures[3];
	int			texturesIndex;
	TimeClock	texturesClock;
	
	double		offsetFactor;
public:
	SpecialAttack_Storm(Scene* s);
	virtual ~SpecialAttack_Storm();
public:
	virtual void update(double dt);
	virtual void render(Graphics* gr) const;
	virtual bool isFinished() const;
	virtual int  damageForHero() const;
	virtual int  damageForAircrafts() const;
	virtual int  damageForBattleships() const;
};

#endif
