////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Ghost
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/Ghost.h>
#include <src/Config.h>
#include <src/resources/ResourceManager.h>
#include <src/Scene.h>
#include <src/entities/Pacman.h>

#include <mach/Random.h>
#include <mach/Color.h>
#include <mach/Graphics.h>

Random Ghost::random;
Texture* Ghost::scaredImage = null;
Texture* Ghost::damagedImage = null;
Texture* Ghost::normalImages[4] = {null,null,null,null};
const double Ghost::MOVE_CLOCK_NORMAL = 0.014;
const double Ghost::MOVE_CLOCK_SCARED = 0.03;
const double Ghost::MOVE_CLOCK_DAMAGED = 0.01;

Ghost::Ghost(Scene* scene, Pacman* ___pacman, int x, int y, COLOR ___color, double ___timeToActivation) : Entity(scene, x, y)
, state(STATE_NORMAL)
, color(___color)
, pacman(___pacman)

, astar()
, path()
, pathIndex(0)
, pathfindingPolicy(PATHFINDING_POLICY_FIND_BY_TIME)

, direction(DIRECTION_UP)

, moveClock(MOVE_CLOCK_NORMAL)
, moveCounts(0)

, animIndex(0)
, baseIndex(0)
, imageIndex(0)
, currentImage(null)
, activationClock(___timeToActivation)

, atHome(true)
, initialPositionX(x)
, initialPositionY(y)

, hidden(false)
, scaredBlick(false)
, scaredBlickClock(0.4)

, scatterTimeByPath(0)
{
	if(scaredImage == null)
	{
		scaredImage = res.findTexture("Ghost.0");
		damagedImage = res.findTexture("Ghost.1");
		normalImages[0] = res.findTexture("Ghost.Blinky");
		normalImages[1] = res.findTexture("Ghost.Inky");
		normalImages[2] = res.findTexture("Ghost.Pinky");
		normalImages[3] = res.findTexture("Ghost.Clyde");
	}
	currentImage = normalImages[color];
}
Ghost::~Ghost()
{
}
void Ghost::update(double dt)
{
	if(hidden)
		return;
	if(atHome)
	{
		if(moveClock.update(dt))
		{
			if(!move(direction, 0x3, rect16()))
			{
				if(direction == DIRECTION_UP) direction = DIRECTION_DOWN;
				else if(direction == DIRECTION_DOWN) direction = DIRECTION_UP;
			}
		}
		if(activationClock.update(dt))
		{
			atHome = false;
			findPath(DIRECTION_UNDEFINED);
		}
	}
	else
	{
		int targetMode = 0;		// 0=Pacman, 1=Random, 2=TryRandom
		bool findNewPath = false;
		
		if(state == STATE_SCARED)
		{
			targetMode = 1;
		}
		else if(state == STATE_NORMAL && pathfindingPolicy == PATHFINDING_POLICY_FIND_BY_TIME)
		{
			scatterTimeByPath += dt;
			if(scatterTimeByPath > 3)
			{
				targetMode = 2;
				findNewPath = true;
			}
		}
		if(checkEndOfNodePath(findNewPath))
		{
			bool valid = false;
			Point target;
			
			if(targetMode == 1)
			{
				valid = true;
				target = randomPoint();
			}
			else if(targetMode == 2)
			{
				valid = tryRandomPoint(&target);
			}
			if(valid)
			{
				findPath(direction, target);
			}
			else if(!findPath(direction, pacman->pos()))
			{
				findPath(direction, randomPoint());
			}
			
			if(state == STATE_DAMAGED)
			{
				gotoStateNormal();
			}
		}
		if(moveClock.update(dt))
		{
			checkDirection();
			if(move(direction, 0x1))
			{
				moveCounts++;
			}
			if(moveCounts >= 3)
			{
				moveCounts = 0;
				animIndex = (++animIndex)&1;
			}
		}
	}
	//
	// Calcular indice de imagen
	//
	if(state == STATE_SCARED)
	{
		if(!scaredBlick)
		{
			baseIndex = 0;
		}
		else
		{
			if(scaredBlickClock.update(dt))
			{
				if(baseIndex == 0)
					baseIndex = 2;
				else
					baseIndex = 0;
			}
		}
	}
	else
	{
		switch(direction)
		{
			case DIRECTION_UP:			baseIndex = 6;	break;
			case DIRECTION_DOWN:		baseIndex = 2;	break;
			case DIRECTION_LEFT:		baseIndex = 4;	break;
			case DIRECTION_RIGHT:		baseIndex = 0;	break;
			case DIRECTION_UNDEFINED:	baseIndex = 0;	break;
		}
	}
	imageIndex = baseIndex+animIndex;
}
void Ghost::render(Graphics* gr)
{
	if(hidden)
	{
		return;
	}
	int w = 16;
	int h = 16;
	int dx1 = x-4;
	int dy1 = y-4;
	int dx2 = dx1+w;
	int dy2 = dy1+h;
	int sx1 = imageIndex*w;
	int sy1 = 0;
	int sx2 = sx1+w;
	int sy2 = sy1+h;
	
	gr->drawTexture(currentImage, sx1, sy1, sx2, sy2, dx1, dy1, dx2, dy2);
	if(Debug::ghostDir)
	{
		Rectangle r = rect8();
		switch(direction)
		{
			case DIRECTION_UP:
				gr->drawRect((int)r.getX(), (int)r.getY(), (int)r.getWidth(), (int)r.getHeight(), Color(255,0,0));
				break;
			case DIRECTION_DOWN:
				gr->drawRect((int)r.getX(), (int)r.getY(), (int)r.getWidth(), (int)r.getHeight(), Color(0,0,255));
				break;
			case DIRECTION_LEFT:
				gr->drawRect((int)r.getX(), (int)r.getY(), (int)r.getWidth(), (int)r.getHeight(), Color(0,255,255));
				break;
			case DIRECTION_RIGHT:
				gr->drawRect((int)r.getX(), (int)r.getY(), (int)r.getWidth(), (int)r.getHeight(), Color(0,255,0));
				break;
			default:
				break;
		}
	}
	if(Debug::ghostPath)
	{
		if(!path.empty())
		{
			for(unsigned int i = 0; i < path.size(); i++)
			{
				gr->fillRect(path[i].x+3, path[i].y+3, 3, 3, Color(255,150,0));
			}
			gr->fillRect(path.back().x+3, path.back().y+3, 3, 3, Color(255,0,0));
			gr->fillRect(path.front().x+3, path.front().y+3, 3, 3, Color(0,255,0));
		}
	}
}
void Ghost::reset()
{
	path.clear();
	pathIndex = 0;
	hidden = false;
	x = initialPositionX;
	y = initialPositionY;
	state = STATE_NORMAL;
	atHome = true;
	direction = DIRECTION_UP;
	moveClock.reset(MOVE_CLOCK_NORMAL);
	currentImage = normalImages[color];
	activationClock.reset();
}
Point Ghost::randomPoint() const
{
	const std::vector<int>& validIndexes = scene->getValidIndexesToRandomPositions();
	int idx = validIndexes[Random().nextInt(validIndexes.size())];
	
	return Point(scene->getTileX(idx), scene->getTileY(idx));
}
void Ghost::findPath(DIRECTION dir)
{
	Point p;
	if(!tryRandomPoint(&p))
	{
		p = pacman->pos();
	}
	if(!findPath(dir, p))
		findPath(dir, randomPoint());
}
bool Ghost::findPath(DIRECTION dir, const Point& target)
{
	path.clear();
	pathIndex = 0;
	scatterTimeByPath = 0;
	if(x == target.x && y == target.y)
		return false;
	if(x < 0 || y < 0 || x >= MAP_WIDTH || y >= MAP_HEIGHT)
		return false;
	if(target.x < 0 || target.y < 0 || target.x >= MAP_WIDTH || target.y >= MAP_HEIGHT)
		return false;
	path = astar.find(scene, x, y, target.x, target.y, dir);

	return !path.empty();
}
void Ghost::checkDirection()
{
	if(!path.empty())
	{
		int fromX = x;
		int fromY = y;
		int toX = path[pathIndex].x;
		int toY = path[pathIndex].y;
		
		if(fromX == toX)
		{
			if(toY < fromY)		direction = DIRECTION_UP;
			else				direction = DIRECTION_DOWN;
		}
		else if(fromY == toY)
		{
			if(toX < fromX)		direction = DIRECTION_LEFT;
			else				direction = DIRECTION_RIGHT;
		}
		else
		{
			if(toY < fromY && scene->tryMove(rect8(), 0, -1, 0x1))		direction = DIRECTION_UP;
			else if(toY > fromY && scene->tryMove(rect8(), 0, +1, 0x1))	direction = DIRECTION_DOWN;
			else if(toX < fromX && scene->tryMove(rect8(), -1, 0, 0x1))	direction = DIRECTION_LEFT;
			else if(toX > fromX && scene->tryMove(rect8(), +1, 0, 0x1))	direction = DIRECTION_RIGHT;
		}
	}
}
bool Ghost::checkEndOfNodePath(bool findNewPath)
{
	if(!path.empty())
	{
		const AStar::PathNode& node = path[pathIndex];
		//direction = node.dir;
		if(x == node.x && y == node.y)
		{
			pathIndex++;
			if(findNewPath || pathIndex == path.size())
			{
				path.clear();
			}
		}
	}
	return path.empty();
}
bool Ghost::tryRandomPoint(Point* p) const
{
	if((Random().nextInt(100+1)%6) == 0)
	{
		*p = randomPoint();
		return true;
	}
	return false;
}
void Ghost::gotoStateScare()
{
	state = STATE_SCARED;
	baseIndex = 0;
	currentImage = scaredImage;
	moveClock.reset(MOVE_CLOCK_SCARED);
	scaredBlick = false;
	if(!atHome)
	{
		findPath(DIRECTION_UNDEFINED, randomPoint());
	}
}
void Ghost::gotoStateNormal()
{
	state = STATE_NORMAL;
	moveClock.reset(MOVE_CLOCK_NORMAL);
	currentImage = normalImages[color];
	scaredBlick = false;
}
void Ghost::gotoStateDamaged()
{
	hidden = true;
	state = STATE_DAMAGED;
	currentImage = damagedImage;
	path = astar.find(scene, x, y, scene->getHomeX(), scene->getHomeY(), DIRECTION_UNDEFINED);
	pathIndex = 0;
	moveClock.reset(MOVE_CLOCK_DAMAGED);
	scaredBlick = false;
}

