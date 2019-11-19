////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AircraftTroop
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <src/entities/enemies/aircrafts/AircraftTroop.h>
#include <src/Scene.h>
#include <src/entities/BonusPack.h>
#include <src/entities/enemies/aircrafts/Aircraft.h>

AircraftTroop::AircraftTroop(const std::string& ___bonusDescriptor)
: refs(0)
, units()
, canCreateBonus(true)
, bonusDescriptor(___bonusDescriptor)
{
}
AircraftTroop::~AircraftTroop()
{
}
void AircraftTroop::add(Aircraft* unit)
{
	units.push_back(unit);
}
void AircraftTroop::remove(Aircraft* unit, Scene* scene, bool destroyed)
{
	units.remove(unit);
	if(!destroyed)
	{
		canCreateBonus = false;
	}
	if(canCreateBonus && units.empty())
	{
		scene->addEntity(new BonusPack(scene, unit->position().x, unit->position().y, bonusDescriptor));
	}
}
