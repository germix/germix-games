////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SpecialAttack_Tsunami
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___SpecialAttack_Tsunami_h___
#define ___SpecialAttack_Tsunami_h___
#include <src/attacks/SpecialAttack.h>
#include <gamelib/TimeClock.h>

class Scene;
class Texture;

class SpecialAttack_Tsunami : public SpecialAttack
{
	bool			finished;

	int				fadingDir;
	int				fadingAlpha;
	TimeClock		fadingClock;

	double			tsunamiOffset;
	Texture*		tsunamiTexture;
public:
	SpecialAttack_Tsunami(Scene* s);
	virtual ~SpecialAttack_Tsunami();
public:
	virtual void update(double dt);
	virtual void render(Graphics* gr) const;
	virtual bool isFinished() const;
	virtual int  damageForHero() const;
	virtual int  damageForAircrafts() const;
	virtual int  damageForBattleships() const;
};

#endif
