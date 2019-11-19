////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Screen
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Screen_h___
#define ___Screen_h___

class Machine;
class Graphics;

class Screen
{
public:
	Screen() {}
	virtual ~Screen() {}
public:
	virtual Screen* getNext() = 0;
	virtual bool    isRemovable() = 0;
	virtual void    show(Machine* mach) = 0;
	virtual void    hide(Machine* mach) = 0;
	virtual void    update(Machine* mach, double dt) = 0;
	virtual void    render(Machine* mach, Graphics* gr) = 0;
};

#endif
