#include "../../HeaderFiles/System/GameEngine/Abilities/BattleContext.h"

#include "../../HeaderFiles/System/Services/Registries/Unit/IUnitRegistry.h"

BattleContext::BattleContext(IUnitRegistry& reg)
	: registry(reg)
{
}

BattleContext::~BattleContext() {
	for (size_t i = 0; i < this->spawnedUnits.size(); i++)
	{
		delete this->spawnedUnits[i];
	}
	spawnedUnits.clear();
}

IUnit* BattleContext::summonUnit(const std::string& type) {
	IUnit* unit = this->registry.createByName(type);
	if (!unit) return nullptr;

	spawnedUnits.push_back(unit);
	return unit;
}

std::vector<IUnit*> BattleContext::flushNewUnits()
{
	std::vector<IUnit*> result = std::move(spawnedUnits);
	spawnedUnits.clear(); //just in case
	return result;
}
