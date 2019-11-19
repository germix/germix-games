////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Scene
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/Scene.h>
#include <src/Config.h>
#include <src/resources/ResourceManager.h>
#include <src/Portal.h>
#include <src/entities/Ghost.h>
#include <src/entities/Pacman.h>
#include <src/CollisionMap.h>

#include <mach/Mixer.h>
#include <mach/Texture.h>
#include <mach/Graphics.h>

#include <tmx/TmxMap.h>
#include <tmx/TmxObject.h>
#include <tmx/layers/TmxObjectLayer.h>
#include <tmx/layers/TmxTilesetLayer.h>
#include <tmx/layers/TmxPatternLayer.h>

static struct Tile
{
	int x;
	int y;
}tiles[56];

Scene::Scene(const char* mapName)
: scared(false)
, scaredTime(0)

, actionPause(ACTION_PAUSE_PACMAN_READY)
, actionPauseClock(1)

, pacman(null)
, ghosts()
, portals()
, scorePoints()
, scoresCollected(0)
, validIndexesToRandomPositions()

, ghostDamaged(null)
, ghostDamageScoresIndex(-1)
, ghostDamageScoresPosition()

, mapWidth(0)
, mapHeight(0)
, tileSize(8)
, tilesId(null)
, tilesCount(0)

, homeX(0)
, homeY(0)
, collisionMap(null)

, eatSound(null)
, dieSound(null)
, loop1Sound(null)
, loop2Sound(null)
, bonusSound(null)
, openingSound(null)
{
	ghostDamageScores[0].score = 200;
	ghostDamageScores[0].texture = res.findTexture("score.200");
	ghostDamageScores[1].score = 400;
	ghostDamageScores[1].texture = res.findTexture("score.400");
	ghostDamageScores[2].score = 800;
	ghostDamageScores[2].texture = res.findTexture("score.800");
	ghostDamageScores[3].score = 1600;
	ghostDamageScores[3].texture = res.findTexture("score.1600");

	//
	// Leer mapa
	//
	TmxMap* tmx = new TmxMap(mapName);
	mapWidth = tmx->getMapWidth();
	mapHeight = tmx->getMapHeight();
	tileSize = tmx->getTileWidth();
	tilesId = new int[tilesCount = mapWidth*mapHeight];
	for(int i = 0; i < tilesCount; i++)
	{
		tilesId[i] = 0;
	}
	
	loadTiles(tmx);
	loadObjects(tmx);

	delete tmx;

	// ...
	eatSound = res.findSound("Eat");
	dieSound = res.findSound("Die");
	loop1Sound = res.findSound("Loop1");
	loop2Sound = res.findSound("Loop2");
	bonusSound = res.findSound("Bonus");
	openingSound = res.findSound("Opening");
	
	if(openingSound)
	{
		Mixer::playChannel(openingSound, MIXCHANNEL_NORMAL);
		actionPauseClock.reset(9);
	}
}
Scene::~Scene()
{
	delete pacman;
	for(unsigned int i = 0; i < ghosts.size(); i++)
		delete ghosts[i];
	ghosts.clear();
	portals.clear();
	scorePoints.clear();
	validIndexesToRandomPositions.clear();

	delete [] tilesId;
	
	delete collisionMap;
}
void Scene::update(double dt)
{
	if(openingSound)
	{
		if(actionPauseClock.update(dt))
		{
			openingSound = null;
			actionPauseClock.reset(1);
		}
	}
	if(actionPause == ACTION_PAUSE_NONE)
	{
		pacman->update(dt);
		for(unsigned int i = 0; i < ghosts.size(); i++)
			ghosts[i]->update(dt);
		
		if(scared)
		{
			scaredTime += dt;
			if(scaredTime > 8)
			{
				for(unsigned int i = 0; i < ghosts.size(); i++)
				{
					ghosts[i]->setScaredBlick();
				}
			}
			if(scaredTime > 12)
			{
				for(unsigned int i = 0; i < ghosts.size(); i++)
				{
					ghosts[i]->normalize();
				}
				scared = false;
				scaredTime = 0;
				restoreGhostDamageScores();

				Mixer::playChannel(loop1Sound, MIXCHANNEL_LOOP, -1);
			}
		}
		if(pacman->isDead())
		{
			actionPause = ACTION_PAUSE_PACMAN_READY;
			pacman->reset();
			for(unsigned int i = 0; i < ghosts.size(); i++)
			{
				ghosts[i]->reset();
			}
		}
		else if(pacman->isActive())
		{
			checkCollisionWithPortals();
			checkPacmanCollisionWithGhosts();
			checkPacmanCollisionWithScorePoints();
		}
	}
	else
	{
		if(actionPauseClock.update(dt))
		{
			switch(actionPause)
			{
				case ACTION_PAUSE_NONE:
					break;
				case ACTION_PAUSE_GHOST_DAMAGED:
					pacman->show();
					ghostDamaged->show();
					if(++ghostDamageScoresIndex == MAX_GHOST_DAMAGE_SCORES)
					{
						restoreGhostDamageScores();
					}
					if(scared)
						Mixer::playChannel(loop2Sound, MIXCHANNEL_LOOP, -1);
					else
						Mixer::playChannel(loop1Sound, MIXCHANNEL_LOOP, -1);
					break;
				case ACTION_PAUSE_PACMAN_READY:
					pacman->start();
					for(unsigned int i = 0; i < ghosts.size(); i++)
					{
						ghosts[i]->start();
					}
					Mixer::playChannel(loop1Sound, MIXCHANNEL_LOOP, -1);
					break;
				case ACTION_PAUSE_PACMAN_DAMAGED:
					pacman->hurt();
					for(unsigned int i = 0; i < ghosts.size(); i++)
					{
						ghosts[i]->hide();
					}
					Mixer::playChannel(dieSound, MIXCHANNEL_NORMAL);
					break;
				case ACTION_PAUSE_PACMAN_WINNER:
					for(unsigned int i = 0; i < ghosts.size(); i++)
					{
						ghosts[i]->hide();
					}
					break;
			}
			actionPause = ACTION_PAUSE_NONE;
		}
	}
}
void Scene::render(Graphics* gr)
{
	renderMap(gr);
	
	pacman->render(gr);
	for(unsigned int i = 0; i < ghosts.size(); i++)
		ghosts[i]->render(gr);
	
	if(actionPause == ACTION_PAUSE_GHOST_DAMAGED)
	{
		gr->drawTexture(
				ghostDamageScores[ghostDamageScoresIndex].texture,
				ghostDamageScoresPosition.x,
				ghostDamageScoresPosition.y);
	}
}
bool Scene::tryMove(const Rectangle& entityRect, int dx, int dy, unsigned short mask) const
{
	return collisionMap->tryMove(entityRect, dx, dy, mask);
}
void Scene::loadTiles(TmxMap* tmx)
{
	int firstGidTileset = 0;
	
	for(std::vector<TmxTilesetLayer*>::const_iterator it = tmx->getTilesetLayers().begin(); it != tmx->getTilesetLayers().end(); it++)
	{
		const TmxTilesetLayer* layer = *it;
		if(0 == strcmp(layer->getName().c_str(), "pacman-tileset"))
		{
			firstGidTileset = layer->getFirstGid();
			int w = Config::currentTileset->getWidth()/tileSize;
			int h = Config::currentTileset->getHeight()/tileSize;
			for(int x = 0; x < w; x++)
			{
				for(int y = 0; y < h; y++)
				{
					int i = (y*w+x);
					tiles[i].x = x*tileSize;
					tiles[i].y = y*tileSize;
				}
			}
		}
	}
	for(std::vector<TmxPatternLayer*>::const_iterator it = tmx->getPatternLayers().begin(); it != tmx->getPatternLayers().end(); it++)
	{
		const TmxPatternLayer* layer = *it;
		const std::vector<int>& gids = layer->getIds();

		if(0 == strcmp(layer->getName().c_str(), "walls"))
		{
			for(int x = 0; x < mapWidth; x++)
			{
				for(int y = 0; y < mapHeight; y++)
				{
					int i = (y*mapWidth)+x;
					int gid = gids[i];
					if(gid > 0)
						tilesId[i] = (gid-firstGidTileset);
				}
			}
			collisionMap = new CollisionMap(mapWidth, mapHeight, gids, firstGidTileset);
		}
		else if(0 == strcmp(layer->getName().c_str(), "items"))
		{
			for(int x = 0; x < mapWidth; x++)
			{
				for(int y = 0; y < mapHeight; y++)
				{
					int i = (y*mapWidth)+x;
					int gid = gids[i];
					if(gid > 0)
					{
						gid -= firstGidTileset;
					
						int px = (x*8)+4;
						int py = (y*8)+4;
						if(gid == TILE_ID_SCORE_10)
						{
							validIndexesToRandomPositions.push_back(i);
							scorePoints.push_back(ScorePoint(px, py, 10));
						}
						else if(gid == TILE_ID_SCORE_50)
						{
							validIndexesToRandomPositions.push_back(i);
							scorePoints.push_back(ScorePoint(px, py, 50));
						}
					}
				}
			}
		}
	}
}
void Scene::loadObjects(TmxMap* tmx)
{
	pacman = new Pacman(this, 104+4, 180+4);
	for(std::vector<TmxObjectLayer*>::const_iterator it = tmx->getObjectLayers().begin(); it != tmx->getObjectLayers().end(); it++)
	{
		TmxObjectLayer* layer = *it;
		if(layer->getName() == "objects")
		{
			for(std::vector<TmxObject*>::const_iterator it = layer->getObjects().begin(); it != layer->getObjects().end(); it++)
			{
				TmxObject* obj = *it;
				
				if(obj->getType() == "home")
				{
					homeX = obj->getX() + (obj->getWidth()/2 - 8/2);
					homeY = obj->getY() + (obj->getHeight()/2 - 8/2);
				}
				else if(obj->getType() == "pacman")
				{
					Point p(obj->getX()+4, obj->getY()+4);
					
					pacman->setPosition(p);
					pacman->setStartPosition(p.x, p.y);
				}
				else if(obj->getType() == "portal")
				{
					portals.push_back(Portal(
								obj->getX(),
								obj->getY(),
								obj->getWidth(),
								obj->getHeight(),
								atoi(obj->getProperty("dstX").c_str()),
								atoi(obj->getProperty("dstY").c_str())));
				}
				else if(obj->getType() == "ghost-red")
				{
					createGhost(obj, Ghost::COLOR_RED);
				}
				else if(obj->getType() == "ghost-pink")
				{
					createGhost(obj, Ghost::COLOR_PINK);
				}
				else if(obj->getType() == "ghost-cyan")
				{
					createGhost(obj, Ghost::COLOR_CYAN);
				}
				else if(obj->getType() == "ghost-orange")
				{
					createGhost(obj, Ghost::COLOR_ORANGE);
				}
			}
		}
	}
}
void Scene::createGhost(TmxObject* obj, Ghost::COLOR color)
{
	double defaultTimeAtHome[] =
	{
		0, 7.8, 3, 12.4,
	};
	std::string timeAtHome = obj->getProperty("timeAtHome");
	double timeAtHomeValue;
	if(timeAtHome.empty())
		timeAtHomeValue = defaultTimeAtHome[color];
	else
		timeAtHomeValue = atoi(timeAtHome.c_str());
	
	ghosts.push_back(
		new Ghost(
			this,
			pacman,
			obj->getX()+4,
			obj->getY()+4,
			color,
			timeAtHomeValue));
}
void Scene::renderMap(Graphics* gr)
{
	for(int x = 0; x < mapWidth; x++)
	{
		for(int y = 0; y < mapHeight; y++)
		{
			renderTile(gr, tilesId[(y*mapWidth)+x], x, y);
		}
	}
	//
	// Renderizar puntos
	//
	for(unsigned int i = 0; i < scorePoints.size(); i++)
	{
		const ScorePoint& s = scorePoints[i];

		if(s.score == 10)
			renderTile(gr, TILE_ID_SCORE_10, s.x/8, s.y/8);
		else if(s.score == 50)
			renderTile(gr, TILE_ID_SCORE_50, s.x/8, s.y/8);
	}
	//
	// Renderizar solidos
	//
	if(Debug::collisionMap)
	{
		collisionMap->render(gr);
	}
}
void Scene::renderTile(Graphics* gr, unsigned int tileIndex, int x, int y)
{
	int dx1 = x*tileSize;
	int dy1 = y*tileSize;
	int dx2 = dx1+tileSize;
	int dy2 = dy1+tileSize;
	int sx1 = tiles[tileIndex].x;
	int sy1 = tiles[tileIndex].y;
	int sx2 = sx1+tileSize;
	int sy2 = sy1+tileSize;
	gr->drawTexture(Config::currentTileset, sx1, sy1, sx2, sy2, dx1, dy1, dx2, dy2);
}
void Scene::checkCollisionWithPortals()
{
	checkCollisionWithPortals(pacman);
	for(unsigned int i = 0; i < ghosts.size(); i++)
	{
		checkCollisionWithPortals(ghosts[i]);
	}
}
void Scene::checkCollisionWithPortals(Entity* e)
{
	for(unsigned int i = 0; i < portals.size(); i++)
	{
		const Portal& p = portals[i];
		if(p.getRectangle().intersects(e->rect16()))
		{
			e->setPosition(p.getDestination());
			break;
		}
	}
}
void Scene::checkPacmanCollisionWithGhosts()
{
	if(Debug::noCollisionWithGhosts)
		return;
	for(unsigned int i = 0; i < ghosts.size(); i++)
	{
		Ghost* g = ghosts[i];
		
		if(g->rect8().intersects(pacman->rect8()))
		{
			if(g->getState() == Ghost::STATE_SCARED)
			{
				Mixer::haltChannel(MIXCHANNEL_LOOP);
				Mixer::playChannel(bonusSound, MIXCHANNEL_NORMAL);
				pacman->hide();
				ghostDamaged = g;
				ghostDamaged->hurt();
				actionPause = ACTION_PAUSE_GHOST_DAMAGED;
				ghostDamageScoresPosition = pacman->pos();
				pacman->addScore(ghostDamageScores[ghostDamageScoresIndex].score);
				break;
			}
			else if(g->getState() == Ghost::STATE_NORMAL)
			{
				if(Debug::pacmanDamaged)
				{
					Mixer::haltChannel(MIXCHANNEL_LOOP);
					actionPause = ACTION_PAUSE_PACMAN_DAMAGED;
				}
				break;
			}
		}
	}
}
void Scene::checkPacmanCollisionWithScorePoints()
{
	for(unsigned int i = 0; i < scorePoints.size(); i++)
	{
		ScorePoint& s = scorePoints[i];
		if(s.score > 0 && pacman->rect8().intersects(Rectangle(s.x-4,s.y-4,8,8)))
		{
			if(s.score == 50)
			{
				for(unsigned int i = 0; i < ghosts.size(); i++)
				{
					ghosts[i]->scare();
				}
				scared = true;
				scaredTime = 0;
				restoreGhostDamageScores();
				
				Mixer::playChannel(loop2Sound, MIXCHANNEL_LOOP, -1);
			}
			pacman->addScore(s.score);
			s.score = 0;
			scoresCollected++;
			if(scoresCollected == scorePoints.size())
			{
				pacman->win();
				actionPause = ACTION_PAUSE_PACMAN_WINNER;
				Mixer::haltChannel(MIXCHANNEL_LOOP);
			}
			else
			{
				Mixer::playChannel(eatSound, MIXCHANNEL_NORMAL);
			}
		}
	}
}

