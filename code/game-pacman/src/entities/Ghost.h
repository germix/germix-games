////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Ghost
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Ghost_h___
#define ___Ghost_h___
#include <src/entities/Entity.h>
#include <src/pathfinding/AStar.h>

#include <vector>

#include <mach/Random.h>

#include <gamelib/TimeClock.h>

class Pacman;
class Texture;

class Ghost : public Entity
{
public:
	enum COLOR
	{
		COLOR_RED,
		COLOR_CYAN,
		COLOR_PINK,
		COLOR_ORANGE,
	};
	enum STATE
	{
		STATE_NORMAL,
		STATE_SCARED,
		STATE_DAMAGED,
	};
private:
	enum PATHFINDING_POLICY
	{
		PATHFINDING_POLICY_FIND_AFTER_COMPLETED,
		PATHFINDING_POLICY_FIND_BY_TIME,
	};
	STATE							state;
	COLOR							color;
	Pacman*							pacman;
	
	AStar							astar;
	std::vector<AStar::PathNode>	path;
	int								pathIndex;
	PATHFINDING_POLICY				pathfindingPolicy;
	
	DIRECTION						direction;

	TimeClock						moveClock;
	int								moveCounts;

	int								animIndex;
	int								baseIndex;
	int								imageIndex;
	Texture*						currentImage;
	TimeClock						activationClock;
	
	bool							atHome;
	const int						initialPositionX;
	const int						initialPositionY;
	
	bool							hidden;
	
	bool							scaredBlick;
	TimeClock						scaredBlickClock;
	
	double							scatterTimeByPath;	// Por cada camino
	
	static const double MOVE_CLOCK_NORMAL;
	static const double MOVE_CLOCK_SCARED;
	static const double MOVE_CLOCK_DAMAGED;
	static Random					random;
	static Texture*					scaredImage;
	static Texture*					damagedImage;
	static Texture*					normalImages[4];
public:
	Ghost(Scene* scene, Pacman* pacman, int x, int y, COLOR color, double timeToActivation);
	~Ghost();
public:
	void update(double dt);
	void render(Graphics* gr);

	void hide()
	{
		hidden = true;
	}
	void show()
	{
		hidden = false;
	}
	void start()
	{
	}
	void reset();
	
	void hurt()
	{
		if(state == STATE_SCARED)
		{
			gotoStateDamaged();
		}
	}
	void scare()
	{
		if(state == STATE_NORMAL || state == STATE_SCARED)
		{
			gotoStateScare();
		}
	}
	void normalize()
	{
		if(state == STATE_SCARED)
		{
			gotoStateNormal();
		}
	}
	STATE getState() const
	{
		return state;
	}
	void setScaredBlick()
	{
		if(!scaredBlick)
		{
			scaredBlick = true;
			scaredBlickClock.reset();
		}
	}
private:
	Point randomPoint() const;
	void findPath(DIRECTION dir);
	bool findPath(DIRECTION dir, const Point& target);
	void checkDirection();
	bool checkEndOfNodePath(bool findNewPath);
	bool randomPoint(Point* p) const;
	bool tryRandomPoint(Point* p) const;
	void gotoStateScare();
	void gotoStateNormal();
	void gotoStateDamaged();
};

#endif
