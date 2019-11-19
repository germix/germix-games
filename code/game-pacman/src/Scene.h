////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Scene
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___Scene_h___
#define ___Scene_h___
#include <vector>

#include <src/ScorePoint.h>
#include <src/entities/Ghost.h>

#include <mach/Point.h>

#include <gamelib/TimeClock.h>

class Entity;
class Ghost;
class Pacman;
class Portal;
class CollisionMap;

class Sound;
class Texture;
class Graphics;
class Rectangle;

class TmxMap;
class TmxObject;

class Scene
{
	enum
	{
		TILE_ID_SCORE_10 = 54,
		TILE_ID_SCORE_50 = 55,
	};
	enum
	{
		MAX_GHOST_DAMAGE_SCORES = 4,
	};
	enum ACTION_PAUSE
	{
		ACTION_PAUSE_NONE,
		ACTION_PAUSE_GHOST_DAMAGED,
		ACTION_PAUSE_PACMAN_READY,
		ACTION_PAUSE_PACMAN_DAMAGED,
		ACTION_PAUSE_PACMAN_WINNER,
	};
	struct GhostDamageScore
	{
		int score;
		Texture* texture;
	};
	bool						scared;
	double						scaredTime;
	
	ACTION_PAUSE				actionPause;
	TimeClock					actionPauseClock;

	Pacman*						pacman;
	std::vector<Ghost*>			ghosts;
	std::vector<Portal>			portals;
	std::vector<ScorePoint>		scorePoints;
	int							scoresCollected;
	std::vector<int>			validIndexesToRandomPositions;

	Ghost*						ghostDamaged;
	GhostDamageScore			ghostDamageScores[MAX_GHOST_DAMAGE_SCORES];
	int							ghostDamageScoresIndex;
	Point						ghostDamageScoresPosition;
	
	//
	// Map
	//
	int							mapWidth;
	int							mapHeight;
	int							tileSize;
	int*						tilesId;
	int							tilesCount;
	
	int							homeX;
	int							homeY;
	CollisionMap*				collisionMap;
	
	//
	// Sonidos
	//
	Sound*						eatSound;
	Sound*						dieSound;
	Sound*						loop1Sound;
	Sound*						loop2Sound;
	Sound*						bonusSound;
	Sound*						openingSound;
public:
	Scene(const char* mapName);
	~Scene();
public:
	void update(double dt);
	void render(Graphics* gr);

	int getHomeX() const { return homeX; }
	int getHomeY() const { return homeX; }
	
	int getWidth() const { return mapWidth; }
	int getHeight() const { return mapHeight; }

	Pacman* getPacman() const { return pacman; }
	CollisionMap* getCollisionMap() const { return collisionMap; }
	const std::vector<int>& getValidIndexesToRandomPositions() const { return validIndexesToRandomPositions; }
	
	bool tryMove(const Rectangle& entityRect, int dx, int dy, unsigned short mask) const;
	int  getTileX(int idx) const { return (idx%mapWidth)*8; }
	int  getTileY(int idx) const { return (idx/mapWidth)*8; }
	int  getTileSize() const { return tileSize; }
private:
	void loadTiles(TmxMap* tmx);
	void loadObjects(TmxMap* tmx);
	void createGhost(TmxObject* obj, Ghost::COLOR color);

	void renderMap(Graphics* gr);
	void renderTile(Graphics* gr, unsigned int tileIndex, int x, int y);
	
	void restoreGhostDamageScores()
	{
		ghostDamageScoresIndex = 0;
	}
	void checkCollisionWithPortals();
	void checkCollisionWithPortals(Entity* e);
	void checkPacmanCollisionWithGhosts();
	void checkPacmanCollisionWithScorePoints();
};

#endif
