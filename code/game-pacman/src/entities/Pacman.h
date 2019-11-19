////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Pacman
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Pacman_h___
#define ___Pacman_h___
#include <src/entities/Entity.h>

#include <gamelib/TimeClock.h>

class Texture;

class Pacman : public Entity
{
	enum STATE
	{
		STATE_INACTIVE,
		STATE_ACTIVE,
		STATE_DYING,
		STATE_DEAD,
		STATE_GAME_OVER,
		STATE_WINNER,
	};
	STATE		state;
	Texture*	texture;
	int			imageIndex;
	
	TimeClock	clock;

	DIRECTION	dir;
	int			moveCounts;
	
	int			eatImageIndex;
	
	int			score;
	int			lives;
	bool		hidden;

	int			startPositionX;
	int			startPositionY;
public:
	Pacman(Scene* scene, int x, int y);
	~Pacman();
public:
	void update(double dt);
	void render(Graphics* gr);
	void hurt();
	void start();
	bool canMove(int dx, int dy) const;

	void hide()
	{
		hidden = true;
	}
	void show()
	{
		hidden = false;
	}
	void reset()
	{
	}
	bool isDead() const
	{
		return (state == STATE_DEAD);
	}
	bool isActive() const
	{
		return (state == STATE_ACTIVE);
	}
	int getScore() const
	{
		return score;
	}
	void addScore(int s)
	{
		score += s;
	}
	void setStartPosition(int x, int y)
	{
		startPositionX = x;
		startPositionY = y;
	}
	void win()
	{
		state = STATE_WINNER;
		imageIndex = 0;
	}
	int getLives() const
	{
		return lives;
	}
	bool isWinner() const
	{
		return (state == STATE_WINNER);
	}
	bool isGameOver() const
	{
		return (state == STATE_GAME_OVER);
	}
};

#endif
