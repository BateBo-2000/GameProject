#pragma once
#ifndef BATTLE_CONTEXT_H
#define BATTLE_CONTEXT_H

#include <vector>
#include <string>

class IUnit;
class IUnitRegistry;

/// context passed into abilities to allow spawning a collection of new units 
class BattleContext {
public:
    BattleContext(IUnitRegistry& registry);
    BattleContext(const BattleContext& other) = delete; //will cause dublication of pointers
    BattleContext& operator=(const BattleContext& other) = delete;
    ~BattleContext();

    IUnit* summonUnit(const std::string& type);

    std::vector<IUnit*> flushNewUnits();

private:
    IUnitRegistry& registry;
    std::vector<IUnit*> spawnedUnits;
};

#endif // BATTLE_CONTEXT_H