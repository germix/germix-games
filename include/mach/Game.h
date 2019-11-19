////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Game
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Game_h___
#define ___Game_h___

class Machine;
class Graphics;

class Game
{
public:
	Game() {}
	virtual ~Game() {}
public:
	virtual void init(Machine* mach) = 0;
	virtual void close(Machine* mach) = 0;
	virtual void update(Machine* mach, double dt) = 0;
	virtual void render(Machine* mach, Graphics* gr) = 0;
};

#endif
