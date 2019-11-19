////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AircraftTroop
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___AircraftTroop_h___
#define ___AircraftTroop_h___
#include <list>
#include <string>

class Scene;
class Aircraft;

class AircraftTroop
{
	int							refs;
	std::list<Aircraft*>		units;
	bool						canCreateBonus;
	std::string					bonusDescriptor;
public:
	AircraftTroop(const std::string& bonusDescriptor);
private:
	~AircraftTroop();
public:
	void ref()
	{
		refs++;
	}
	void unref()
	{
		if(--refs == 0)
			delete this;
	}
	void add(Aircraft* unit);
	void remove(Aircraft* unit, Scene* scene, bool destroyed);
};

#endif
