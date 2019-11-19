////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ScreenManager
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___ScreenManager_h___
#define ___ScreenManager_h___
#include "Screen.h"

class Machine;
class Graphics;

class ScreenManager
{
	struct ScreenNode
	{
		ScreenNode* prev;
		Screen*     screen;
	public:
		ScreenNode(Screen* s, ScreenNode* p) : prev(p), screen(s)
		{
		}
		~ScreenNode()
		{
			delete screen;
		}
	};
	ScreenNode* stack;
public:
	ScreenManager();
	~ScreenManager();
public:
	//
	// Comenzar con una pantalla inicial
	//
	void init(Machine* mach, Screen* s);
	
	//
	// Actualizar la pantalla actual
	// Retorna 'false' si no hay mas pantallas, en caso contrario 'true'
	//
	bool update(Machine* mach, double dt);
	
	//
	// Renderizar la pantalla actual
	//
	void render(Machine* mach, Graphics* gr);
};

#endif
