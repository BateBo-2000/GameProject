#pragma once
#ifndef DAMAGEABILITY_H
#define DAMAGEABILITY_H

#include "IAbility.h"

class DamageAbility : public IAbility {
public:
    DamageAbility(const std::string& name, unsigned manaCost, unsigned damage);

    IAbility* clone() const override;
    const std::string& getName() const override;
    unsigned getManaCost() const override;
    void apply(IUnit* user, const std::vector<IUnit*>& targets, BattleContext& ctx) override;

private:
    std::string name;
    unsigned manaCost;
    unsigned damage;
};

#endif // DAMAGE_ABILITY_H
