////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MasknellFleet | Flota de Masknell's
//
// Germán Martínez / Gerardo Ponce
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/masknell/MasknellFleet.h>
#include <src/routes/Route.h>
#include <src/scene/Scene.h>
#include <src/entities/enemies/masknell/MasknellLeader.h>
#include <src/entities/enemies/masknell/MasknellSubordinate.h>

MasknellFleet::MasknellFleet(Scene* scene, double x, double y) : Entity(scene, x, y)
, route(null)
//, clock(0.45)
, leader(null)
, lastMasknellCreated(null)
{
	route = new Route(0, 0, "0,0 -68,0 -168,0 -300,0 -308,-4 -312,-8 -316,-16 -316,-24 -312,-32 -308,-36 -300,-40 -68,-40 -60,-36 -56,-32 -52,-24 -52,-16 -56,-8 -60,-4 -68,0");
}
MasknellFleet::~MasknellFleet()
{
	delete route;
}
void MasknellFleet::update(double dt)
{
	if(leader == null)
	{
		if(scene->getCameraRect().getMaxX()+20>pos.x)
		{
			leader = new MasknellLeader(scene, pos.x+32, pos.y, route);
			scene->addEntity(leader);
			scene->setRightLimit((int)pos.x);
			lastMasknellCreated = leader;
		}
	}
	else
	{
		if(leader->isDestroyed())
		{
			for(unsigned int i = 0; i < subordinates.size();i++)
			{
				subordinates[i]->destroy();
			}
			leader = null;
			subordinates.clear();
			removable = true;
			scene->setRightLimit(-1);
		}
#if 0
		else
		{
			if(subordinates.size()<4 && clock.update(dt))
			{
				MasknellSubordinate* m = new MasknellSubordinate(scene, pos.x+32, pos.y, route);
				scene->addEntity(m);
				subordinates.push_back(m);
			}
		}
#else
		else if(lastMasknellCreated)
		{
			int dx = pos.x - lastMasknellCreated->getPosition().x;
			if(dx > 40)
			{
				MasknellSubordinate* m = new MasknellSubordinate(scene, pos.x+32, pos.y, route);
				scene->addEntity(m);
				subordinates.push_back(m);
				lastMasknellCreated = m;
			}
			if(subordinates.size() == 4)
				lastMasknellCreated = null;
		}
#endif
	}
}
void MasknellFleet::render(Graphics* gr)
{
}
