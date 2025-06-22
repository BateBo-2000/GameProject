#pragma once
#ifndef HEAL_ABILITY_H
#define HEAL_ABILITY_H

#include "IAbility.h"

class HealAbility : public IAbility {
public:
    HealAbility(const std::string& name, unsigned manaCost, unsigned healAmount);

    IAbility* clone() const override;
    const std::string& getName() const override;
    unsigned getManaCost() const override;
    void apply(IUnit* user, const std::vector<IUnit*>& targets, BattleContext& ctx) override;

private:
    std::string name;
    unsigned manaCost;
    unsigned healAmount;
};

#endif // HEAL_ABILITY_H
