////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ExplosiveBurst
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___ExplosiveBurst_h___
#define ___ExplosiveBurst_h___
#include <src/entities/explosions/Explosion.h>
#include <vector>
#include <queue>

#include <gamelib/TimeClock.h>

class ExplosiveBurst : public Explosion
{
	TimeClock							clock;
	std::queue<double>					timesQueue;
	std::queue<std::vector<Explosion*>>	explosionsQueue;
public:
	ExplosiveBurst(Scene* s);
	~ExplosiveBurst();
public:
	void update(double dt);
	void render(Graphics* gr);
public:
	void addExplosions(double time, const std::vector<Explosion*>& explosions);
};

#endif
