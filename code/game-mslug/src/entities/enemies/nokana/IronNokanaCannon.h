////////////////////////////////////////////////////////////////////////////////////////////////////
//
// IronNokanaCannon | Ca��n de IronNokana
//
// Germ�n Mart�nez
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
		STATE_PREPARING,			// Preparando la r�faga
		STATE_WAITING,				// Estado de espera entre r�fagas de ca�onazo
		STATE_SHOOTING,				// Tirando ca�onazos
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
