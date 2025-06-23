#pragma once
#include <string>
#include <vector>
#include "../../HeaderFiles/System/GameEngine/Units/IUnit.h"

struct UnitData {
	std::string type;
	unsigned health;
	unsigned mana;
	unsigned armorDurability;
};

struct GameState {
	unsigned goldLiving;
	unsigned goldUndead;
	unsigned winsLiving;
	unsigned winsUndead;
	std::vector<UnitData> livingUnits;
	std::vector<UnitData> undeadUnits;
	std::string selectedUnitName;
	std::string selectedBossName;
	Faction currentTurn;
};