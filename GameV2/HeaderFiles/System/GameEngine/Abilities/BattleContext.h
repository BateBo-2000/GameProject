#pragma once
#ifndef BATTLE_CONTEXT_H
#define BATTLE_CONTEXT_H

#include <vector>

class IUnit;
#include "../../Services/Registries/Unit/IUnitRegistry.h"

class BattleContext {
public:
    explicit BattleContext(IUnitRegistry& registry)
        : unitRegistry(registry)
    {}

    IUnitRegistry& unitRegistry;
    std::vector<IUnit*> spawnedUnitsToBeAdded;
};

#endif // BATTLE_CONTEXT_H