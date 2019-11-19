////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Random
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <mach/Random.h>
#include <time.h>
#include <stdlib.h>

Random::Random()
{
	holdrand = (unsigned long)time(0);
}
Random::Random(unsigned long seed)
{
	holdrand = seed;
}
Random::Random(const Random& other)
{
	this->holdrand = other.holdrand;
}
Random::~Random()
{
}
int Random::nextInt() const
{
	return (((holdrand = holdrand * 214013L + 2531011L) >> 16) & 0x7fff);
}
int Random::nextInt(int n) const
{
	return nextInt() % n;
}
int Random::nextInt(int min, int max) const
{
	return min + nextInt(max-min);
}
double Random::nextDouble() const
{
	return double(nextInt())/double(RAND_MAX);
}
double Random::nextDouble(double n) const
{
	return ((double)(nextInt())/double(RAND_MAX))*n;
}
double Random::nextDouble(double min, double max) const
{
	return min + nextDouble(max-min);
}
Random& Random::operator = (const Random& other)
{
	this->holdrand = other.holdrand;
	return *this;
}

