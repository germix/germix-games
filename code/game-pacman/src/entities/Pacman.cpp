////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Pacman
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/Pacman.h>
#include <src/resources/ResourceManager.h>
#include <src/Scene.h>
#include <src/Config.h>

#include <mach/Graphics.h>
#include <mach/Keyboard.h>

#define MOVE_CLOCK		0.014
#define DYING_CLOCK		0.2

Pacman::Pacman(Scene* scene, int x, int y) : Entity(scene, x, y)
, state(STATE_INACTIVE)
, texture(null)
, imageIndex(0)
, clock()
, moveCounts(0)
, eatImageIndex(0)
, score(0)
, lives(3)
, hidden(false)
, startPositionX(x)
, startPositionY(y)
{
	texture = res.findTexture("Pacman");
}
Pacman::~Pacman()
{
}
void Pacman::update(double dt)
{
	if(state == STATE_WINNER)
	{
		imageIndex = 0;
	}
	else if(state == STATE_INACTIVE)
	{
	}
	else if(state == STATE_ACTIVE)
	{
		if(clock.update(dt))
		{
			if(move(dir, 0x1|0x2))
			{
				moveCounts++;
			}
			if(moveCounts >= 3)
			{
				moveCounts = 0;
				eatImageIndex = (++eatImageIndex)&1;
			}
			if(x >= 0 && x < scene->getWidth()*scene->getTileSize())
			{
				if(Keyboard::isDown(Key::UP))	if(canMove(0, -1)) dir = DIRECTION_UP;
				if(Keyboard::isDown(Key::DOWN))	if(canMove(0, +1)) dir = DIRECTION_DOWN;
			}
			if(Keyboard::isDown(Key::LEFT))		if(canMove(-1, 0)) dir = DIRECTION_LEFT;
			if(Keyboard::isDown(Key::RIGHT))	if(canMove(+1, 0)) dir = DIRECTION_RIGHT;

			switch(dir)
			{
				case DIRECTION_UP:
					imageIndex = 1+eatImageIndex;
					break;
				case DIRECTION_DOWN:
					imageIndex = 3+eatImageIndex;
					break;
				case DIRECTION_LEFT:
					imageIndex = 5+eatImageIndex;
					break;
				case DIRECTION_RIGHT:
					imageIndex = 7+eatImageIndex;
					break;
				case DIRECTION_UNDEFINED:
					break;
			}
		}
	}
	else if(state == STATE_DYING)
	{
		if(clock.update(dt))
		{
			imageIndex++;
			if(imageIndex == 20)
			{
				state = STATE_DEAD;
				if(lives == 0)
				{
					state = STATE_GAME_OVER;
				}
			}
		}
	}
}
void Pacman::render(Graphics* gr)
{
	if(hidden)
		return;
	if(state != STATE_DEAD)
	{
		int w = 16;
		int h = 16;
		int dx1 = x - 4;
		int dy1 = y - 4;
		int dx2 = dx1+w;
		int dy2 = dy1+h;
		int sx1 = imageIndex*w;
		int sy1 = 0;
		int sx2 = sx1+w;
		int sy2 = sy1+h;
		gr->drawTexture(texture, sx1, sy1, sx2, sy2, dx1, dy1, dx2, dy2);
	}
}
void Pacman::hurt()
{
	state = STATE_DYING;
	clock.reset(DYING_CLOCK);
	imageIndex = 9;
}
void Pacman::start()
{
	dir = DIRECTION_LEFT;
	state = STATE_ACTIVE;
	clock.reset(MOVE_CLOCK);
	imageIndex = 0;
	x = startPositionX;
	y = startPositionY;
	hidden = false;
	if(Debug::pacmanLives)
	{
		lives--;
	}
}
bool Pacman::canMove(int dx, int dy) const
{
	return scene->tryMove(rect8(), dx, dy, 0x3);
}
