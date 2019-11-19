////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bird
//
// Germ�n Mart�nez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/Bird.h>
#include <src/Config.h>
#include <src/base/Sprite.h>
#include <src/Scene.h>
#include <src/entities/explosions/BigExplosion.h>

Bird::Bird(Map* m, Scene* s, int x, int y) : Entity(m, s, x, y), alive(true)
{
	sprite = Config::bird;
}
Bird::~Bird()
{
}
void Bird::update(double dt)
{
}
void Bird::render(Graphics* gr)
{
	sprite->render(gr, x, y, alive ? 0 : 1);
}
void Bird::kill()
{
	if(alive)
	{
		alive = false;
		if(!Debug::gameOverByBaseDestroyedDisabled)
		{
			scene->setGameOver();
		}
		
		//
		// Generar una explosi�n
		//
		scene->addEntity(new BigExplosion(map, scene, x + width/2, y + height/2));
	}
}
bool Bird::isAlive() const
{
	return alive;
}
