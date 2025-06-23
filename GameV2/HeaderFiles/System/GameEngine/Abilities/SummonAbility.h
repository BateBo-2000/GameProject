#pragma once
#ifndef SUMMON_ABILITY_H
#define SUMMON_ABILITY_H

#include "IAbility.h"
#include <string>
#include <vector>

class BattleContext;
class IUnit;

class SummonAbility : public IAbility {
public:
    SummonAbility(const std::string& name,
        unsigned manaCost,
        const std::string& unitType,
        unsigned count);

    IAbility* clone() const override;
    const std::string& getName() const override;
    unsigned getManaCost() const override;
    void apply(IUnit* user, const std::vector<IUnit*>& targets, BattleContext& ctx) override;

private:
    std::string name;
    unsigned    manaCost;
    std::string unitType;
    unsigned    count;
};

#endif // SUMMON_ABILITY_H