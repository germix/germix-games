////////////////////////////////////////////////////////////////////////////////////////////////////
//
// IronNokanaTurret | Torreta lanza-llamas del IronNokana
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___IronNokanaTurret_h___
#define ___IronNokanaTurret_h___
#include <gamelib/TimeClock.h>

class IronNokanaTurret
{
	enum STATE
	{
		STATE_IDLE,
		STATE_DAMAGED,
		STATE_DESTROYED,
	};
	STATE			state;
	TimeClock		clock;
	int				fireNode;
	int				fireFrame;
	int				fireLoops;
	
	int				turretFrame;
public:
	IronNokanaTurret();
	~IronNokanaTurret();
public:
	bool update(double dt);
	int renderableTurretFrame() const;
	int renderableTurretFlameShotFrame() const;
	void destroy();
	bool isDestroyed() const;
};

#endif
