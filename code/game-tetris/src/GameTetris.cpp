////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GameTetris
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/GameTetris.h>
#include <src/Resources.h>
#include <src/screens/InitScreen.h>

#include <mach/Machine.h>

GameTetris::GameTetris()
{
}
GameTetris::~GameTetris()
{
}
void GameTetris::init(Machine* mach)
{
	smgr.init(mach, new InitScreen());
}
void GameTetris::close(Machine* mach)
{
}
void GameTetris::update(Machine* mach, double dt)
{
	if(!smgr.update(mach, dt))
	{
		mach->shutdown();
	}
}
void GameTetris::render(Machine* mach, Graphics* gr)
{
	smgr.render(mach, gr);
}
