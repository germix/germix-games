////////////////////////////////////////////////////////////////////////////////////////////////////
//
// IronNokanaCannon | Cañón de IronNokana
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___IronNokanaCannon_h___
#define ___IronNokanaCannon_h___
#include <gamelib/TimeClock.h>

class IronNokanaCannon
{
	enum STATE
	{
		STATE_STOPPED,				// Nada
		STATE_PREPARING,			// Preparando la ráfaga
		STATE_WAITING,				// Estado de espera entre ráfagas de cañonazo
		STATE_SHOOTING,				// Tirando cañonazos
	};
	STATE			state;
	TimeClock		clock;
	int				frame;
	int				shots;			// Contador de disparos
public:
	IronNokanaCannon();
	~IronNokanaCannon();
public:
	void init();
	void stop();
	bool update(double dt);
	int renderableFrame() const;
private:
	void gotoWaitingState();
	void gotoShootingState();
};

#endif
