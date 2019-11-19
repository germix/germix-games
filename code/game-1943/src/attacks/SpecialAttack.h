////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SpecialAttack
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___SpecialAttack_h___
#define ___SpecialAttack_h___

class Graphics;

class SpecialAttack
{
public:
	SpecialAttack() {}
	virtual ~SpecialAttack() {}
public:
	virtual void update(double dt) = 0;
	virtual void render(Graphics* gr) const = 0;
	virtual bool isFinished() const = 0;
	virtual int  damageForHero() const = 0;
	virtual int  damageForAircrafts() const = 0;
	virtual int  damageForBattleships() const = 0;
};

#endif
